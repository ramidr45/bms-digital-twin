"""
Serveur Flask-SocketIO temps reel — Digital Twin dashboard.
Reprend la logique de digital_twin_server.py (EKF + XGBoost + fusion),
remplace l'affichage matplotlib par un push WebSocket vers le navigateur.

Lancement :
    cd ~/digital_twin/dashboard
    source ../venv/bin/activate
    python3 app.py
Puis ouvrir http://<IP_du_Pi>:5000 dans le navigateur.
"""

import ctypes
import socket
import threading
import json
import csv
import os
import sys
from pathlib import Path

import numpy as np
import joblib
import xgboost as xgb
from flask import Flask, render_template
from flask_socketio import SocketIO

# --- Chemins : tout ce qui existe deja est dans ~/digital_twin (le dossier parent) ---
BASE_DIR = Path(__file__).resolve().parent.parent  # ~/digital_twin
sys.path.insert(0, str(BASE_DIR))  # pour pouvoir importer xgb_features.py

from xgb_features import RollingFeatureBuffer, XGB_FEATURE_ORDER, SEQ_LEN

TCP_HOST = "0.0.0.0"
TCP_PORT = 5005
LOG_PATH = BASE_DIR / "digital_twin_log.csv"
GT_PATH = BASE_DIR / "ground_truth_soc.csv"

# --- Config fusion (calibree au prealable) ---
with open(BASE_DIR / "fusion_config.json") as f:
    cfg = json.load(f)
RMSE_XGB_VAR = cfg["RMSE_XGB_VAR"]
print(f"Fusion config chargee : RMSE_XGB_VAR={RMSE_XGB_VAR:.6f}")

# --- EKF via ctypes ---
lib = ctypes.CDLL(str(BASE_DIR / "ekf_src_pi" / "libekf.so"))
lib.ekf_step_wrapper.argtypes = [
    ctypes.c_double, ctypes.c_double,
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
]
lib.ekf_init_wrapper()

# --- XGBoost + scaler + buffer glissant ---
scaler = joblib.load(BASE_DIR / "scaler_25degC.joblib")
xgb_model = xgb.Booster()
xgb_model.load_model(str(BASE_DIR / "xgb_model" / "xgb_last.json"))
feat_buf = RollingFeatureBuffer(scaler)


def fusion(soc_ekf, p_upd, soc_xgb):
    """Fusion inverse-variance. p_upd = variance EKF (dynamique)."""
    w_ekf = (1 / p_upd) / (1 / p_upd + 1 / RMSE_XGB_VAR)
    return w_ekf * soc_ekf + (1 - w_ekf) * soc_xgb


# --- Flask + SocketIO ---
app = Flask(__name__)
app.config["SECRET_KEY"] = "digital-twin-dashboard"
socketio = SocketIO(app, async_mode="threading", cors_allowed_origins="*")

sample_count = 0
lock = threading.Lock()

log_file = open(LOG_PATH, "w", newline="")
log_writer = csv.writer(log_file)
log_writer.writerow(["sample", "I", "V", "T", "SOC_EKF", "SOC_XGB", "SOC_final"])

# --- Pour le calcul RMSE final vs verite terrain ---
soc_ekf_hist, soc_xgb_hist, soc_final_hist = [], [], []


def network_thread():
    global sample_count
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((TCP_HOST, TCP_PORT))
    srv.listen(1)
    print(f"En attente de connexion sur {TCP_HOST}:{TCP_PORT} ...")
    conn, addr = srv.accept()
    print(f"PC connecte : {addr}")
    socketio.emit("link_status", {"connected": True, "addr": str(addr)})

    buf_str = ""
    while True:
        data = conn.recv(4096).decode()
        if not data:
            print("PC deconnecte.")
            socketio.emit("link_status", {"connected": False})
            break
        buf_str += data
        while "\n" in buf_str:
            line, buf_str = buf_str.split("\n", 1)
            line = line.strip()
            if not line:
                continue

            I, V, T = map(float, line.split(","))

            # --- EKF ---
            soc_e = ctypes.c_double()
            up_e = ctypes.c_double()
            p_upd = ctypes.c_double()
            lib.ekf_step_wrapper(I, V, ctypes.byref(soc_e),
                                  ctypes.byref(up_e), ctypes.byref(p_upd))

            # --- XGBoost ---
            feat_buf.push(V, I, T)
            if feat_buf.ready():
                feats = feat_buf.compute_features()
                dmat = xgb.DMatrix(feats, feature_names=XGB_FEATURE_ORDER)
                soc_x = float(xgb_model.predict(dmat)[0]) / 100.0
                p_upd_safe = max(p_upd.value, 1e-6)
                soc_f = fusion(soc_e.value, p_upd_safe, soc_x)
            else:
                soc_x = soc_e.value
                soc_f = soc_e.value

            with lock:
                sample_count += 1
                n = sample_count

            soc_ekf_pct = soc_e.value * 100
            soc_xgb_pct = soc_x * 100
            soc_final_pct = soc_f * 100

            soc_ekf_hist.append(soc_ekf_pct)
            soc_xgb_hist.append(soc_xgb_pct)
            soc_final_hist.append(soc_final_pct)

            log_writer.writerow([n, I, V, T, soc_e.value, soc_x, soc_f])
            if n % 500 == 0:
                log_file.flush()

            # --- Push temps reel vers le navigateur ---
            socketio.emit("soc_update", {
                "sample": n,
                "soc_ekf": round(soc_ekf_pct, 3),
                "soc_xgb": round(soc_xgb_pct, 3),
                "soc_final": round(soc_final_pct, 3),
            })

    log_file.close()
    compute_final_metrics()


def compute_final_metrics():
    if not GT_PATH.exists():
        print(f"({GT_PATH} non trouve -- pas de calcul RMSE)")
        return

    soc_true = np.loadtxt(GT_PATH)
    ekf_arr = np.array(soc_ekf_hist)
    xgb_arr = np.array(soc_xgb_hist)
    final_arr = np.array(soc_final_hist)
    n = min(len(soc_true), len(ekf_arr))

    metrics = {
        "rmse_ekf": float(np.sqrt(np.mean((ekf_arr[:n] - soc_true[:n]) ** 2))),
        "rmse_xgb": float(np.sqrt(np.mean((xgb_arr[:n] - soc_true[:n]) ** 2))),
        "rmse_final": float(np.sqrt(np.mean((final_arr[:n] - soc_true[:n]) ** 2))),
        "n": n,
    }
    print(f"\n--- Metriques finales ({n} echantillons) ---")
    print(f"RMSE EKF seul      : {metrics['rmse_ekf']:.3f} %")
    print(f"RMSE XGBoost seul  : {metrics['rmse_xgb']:.3f} %")
    print(f"RMSE Fusion        : {metrics['rmse_final']:.3f} %")
    socketio.emit("run_finished", metrics)


@app.route("/")
def index():
    return render_template("index.html")


if __name__ == "__main__":
    threading.Thread(target=network_thread, daemon=True).start()
    socketio.run(app, host="0.0.0.0", port=5000, debug=False, allow_unsafe_werkzeug=True)
