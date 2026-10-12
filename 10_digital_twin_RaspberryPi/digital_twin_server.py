"""
Serveur temps reel sur le Raspberry Pi 5.
Recoit (I,V,T) via TCP depuis le PC, calcule SOC_EKF + SOC_XGB, fusionne,
affiche en direct (matplotlib, via Pi Connect).

Prerequis dans ~/digital_twin/ :
  ekf_src_pi/libekf.so
  xgb_model/xgb_last.json
  scaler_25degC.joblib
  xgb_features.py
  fusion_config.json   (genere par calibrate_xgb_rmse.py)

Lancement :
    cd ~/digital_twin
    source venv/bin/activate
    python3 digital_twin_server.py
"""

import ctypes
import socket
import threading
import collections
import json
import csv
import os

import numpy as np
import joblib
import xgboost as xgb
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

from xgb_features import RollingFeatureBuffer, XGB_FEATURE_ORDER, SEQ_LEN

HOST = "0.0.0.0"
PORT = 5005
LOG_PATH = "digital_twin_log.csv"
GT_PATH = "ground_truth_soc.csv"

# --- Charger config de fusion (calibree au prealable) ---
with open("fusion_config.json") as f:
    cfg = json.load(f)
RMSE_XGB_VAR = cfg["RMSE_XGB_VAR"]
print(f"Fusion config chargee : RMSE_XGB_VAR={RMSE_XGB_VAR:.6f}")

# --- EKF via ctypes ---
lib = ctypes.CDLL("./ekf_src_pi/libekf.so")
lib.ekf_step_wrapper.argtypes = [
    ctypes.c_double, ctypes.c_double,
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
    ctypes.POINTER(ctypes.c_double),
]
lib.ekf_init_wrapper()

# --- XGBoost + scaler + buffer glissant ---
scaler = joblib.load("scaler_25degC.joblib")
xgb_model = xgb.Booster()
xgb_model.load_model("xgb_model/xgb_last.json")
feat_buf = RollingFeatureBuffer(scaler)


def fusion(soc_ekf, p_upd, soc_xgb):
    """Fusion inverse-variance. p_upd = variance EKF (dynamique)."""
    w_ekf = (1 / p_upd) / (1 / p_upd + 1 / RMSE_XGB_VAR)
    return w_ekf * soc_ekf + (1 - w_ekf) * soc_xgb


# --- Buffers pour le graphe (historique COMPLET, pas de limite) ---
t_buf = collections.deque()
soc_ekf_buf = collections.deque()
soc_xgb_buf = collections.deque()
soc_final_buf = collections.deque()
lock = threading.Lock()
sample_count = 0
run_finished = False
final_metrics = None

log_file = open(LOG_PATH, "w", newline="")
log_writer = csv.writer(log_file)
log_writer.writerow(["sample", "I", "V", "T", "SOC_EKF", "SOC_XGB", "SOC_final"])


def network_thread():
    global sample_count
    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((HOST, PORT))
    srv.listen(1)
    print(f"En attente de connexion sur {HOST}:{PORT} ...")
    conn, addr = srv.accept()
    print(f"PC connecte : {addr}")

    buf_str = ""
    while True:
        data = conn.recv(4096).decode()
        if not data:
            print("PC deconnecte.")
            break
        buf_str += data
        while "\n" in buf_str:
            line, buf_str = buf_str.split("\n", 1)
            line = line.strip()
            if not line:
                continue

            I, V, T = map(float, line.split(","))

            # --- EKF (tourne des le premier echantillon) ---
            soc_e = ctypes.c_double()
            up_e = ctypes.c_double()
            p_upd = ctypes.c_double()
            lib.ekf_step_wrapper(I, V, ctypes.byref(soc_e),
                                  ctypes.byref(up_e), ctypes.byref(p_upd))

            # --- XGBoost (necessite SEQ_LEN echantillons avant de demarrer) ---
            feat_buf.push(V, I, T)
            if feat_buf.ready():
                feats = feat_buf.compute_features()
                dmat = xgb.DMatrix(feats, feature_names=XGB_FEATURE_ORDER)
                soc_x = float(xgb_model.predict(dmat)[0]) / 100.0  # modele entraine en % -> fraction [0,1]
                # p_upd peut etre tres petit/instable au tout debut -> plancher
                p_upd_safe = max(p_upd.value, 1e-6)
                soc_f = fusion(soc_e.value, p_upd_safe, soc_x)
            else:
                # Pas encore assez d'echantillons pour XGBoost -> EKF seul
                soc_x = soc_e.value
                soc_f = soc_e.value

            with lock:
                sample_count += 1
                t_buf.append(sample_count)
                soc_ekf_buf.append(soc_e.value * 100)
                soc_xgb_buf.append(soc_x * 100)
                soc_final_buf.append(soc_f * 100)

            log_writer.writerow([sample_count, I, V, T,
                                  soc_e.value, soc_x, soc_f])

            if sample_count % 500 == 0:
                print(f"[{sample_count}] EKF={soc_e.value*100:.2f}%  "
                      f"XGB={soc_x*100:.2f}%  Fusion={soc_f*100:.2f}%")
                log_file.flush()

    log_file.close()

    # --- Calcul des metriques finales (RMSE vs verite terrain) ---
    global run_finished, final_metrics
    with lock:
        soc_ekf_arr = np.array(soc_ekf_buf)
        soc_xgb_arr = np.array(soc_xgb_buf)
        soc_final_arr = np.array(soc_final_buf)

    metrics = {}
    if os.path.exists(GT_PATH):
        soc_true = np.loadtxt(GT_PATH)
        n = min(len(soc_true), len(soc_ekf_arr))
        metrics["rmse_ekf"] = float(np.sqrt(np.mean((soc_ekf_arr[:n] - soc_true[:n]) ** 2)))
        metrics["rmse_xgb"] = float(np.sqrt(np.mean((soc_xgb_arr[:n] - soc_true[:n]) ** 2)))
        metrics["rmse_final"] = float(np.sqrt(np.mean((soc_final_arr[:n] - soc_true[:n]) ** 2)))
        metrics["n"] = n
        print(f"\n--- Metriques finales ({n} echantillons) ---")
        print(f"RMSE EKF seul      : {metrics['rmse_ekf']:.3f} %")
        print(f"RMSE XGBoost seul  : {metrics['rmse_xgb']:.3f} %")
        print(f"RMSE Fusion        : {metrics['rmse_final']:.3f} %")
    else:
        print(f"({GT_PATH} non trouve -- pas de calcul RMSE)")

    print(f"\nResultats sauvegardes dans {LOG_PATH}")

    with lock:
        final_metrics = metrics
        run_finished = True


threading.Thread(target=network_thread, daemon=True).start()

# --- Affichage temps reel ---
fig, ax = plt.subplots(figsize=(10, 6))
line_ekf, = ax.plot([], [], label="EKF", linewidth=1, alpha=0.7)
line_xgb, = ax.plot([], [], label="XGBoost", linewidth=1, alpha=0.7)
line_final, = ax.plot([], [], label="Fusion (Digital Twin)", linewidth=2, color="black")
ax.set_ylim(0, 105)
ax.set_xlabel("Echantillon")
ax.set_ylabel("SOC (%)")
ax.set_title("Digital Twin - Estimation SOC en temps reel (RPi5)")
ax.legend(loc="upper right")
ax.grid(True, alpha=0.3)


applied_final = False


def update(frame):
    global applied_final
    with lock:
        if not t_buf:
            return line_ekf, line_xgb, line_final
        line_ekf.set_data(t_buf, soc_ekf_buf)
        line_xgb.set_data(t_buf, soc_xgb_buf)
        line_final.set_data(t_buf, soc_final_buf)
        ax.set_xlim(0, t_buf[-1] + 1)
        finished = run_finished
        metrics = final_metrics

    if finished and not applied_final:
        applied_final = True
        if metrics and "rmse_final" in metrics:
            title = (
                "Digital Twin - Resultat complet\n"
                f"RMSE EKF={metrics['rmse_ekf']:.2f}%  "
                f"XGB={metrics['rmse_xgb']:.2f}%  "
                f"Fusion={metrics['rmse_final']:.2f}%"
            )
        else:
            title = "Digital Twin - Resultat complet (run termine)"
        ax.set_title(title)
        fig.canvas.draw_idle()
        plt.savefig("digital_twin_result.png", dpi=150)
        print("Graphe final sauvegarde dans digital_twin_result.png")

    return line_ekf, line_xgb, line_final


ani = FuncAnimation(fig, update, interval=200, cache_frame_data=False)
plt.tight_layout()
plt.show()
