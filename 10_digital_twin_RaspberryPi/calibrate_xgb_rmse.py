"""
A executer UNE SEULE FOIS sur le Pi, apres avoir transfere :
  - test_input.csv (I,V,T)
  - ground_truth_soc.csv (SOC reel, meme grille que test_input.csv)
  - scaler_25degC.joblib
  - xgb_model/xgb_last.json (deja present)
  - xgb_features.py

Calcule le RMSE de XGBoost sur ce jeu de test et sauvegarde
RMSE_XGB_VAR (variance) dans fusion_config.json, utilise ensuite par le
serveur temps reel pour la fusion inverse-variance.

Usage :
    python3 calibrate_xgb_rmse.py
"""

import json
import numpy as np
import joblib
import xgboost as xgb
from xgb_features import RollingFeatureBuffer, SEQ_LEN, XGB_FEATURE_ORDER

scaler = joblib.load("scaler_25degC.joblib")
model = xgb.Booster()
model.load_model("xgb_model/xgb_last.json")

iv_t = np.loadtxt("test_input.csv", delimiter=",")
soc_true = np.loadtxt("ground_truth_soc.csv") / 100.0  # -> fraction [0,1]

buf = RollingFeatureBuffer(scaler)
preds, targets = [], []

for k in range(len(iv_t)):
    I, V, T = iv_t[k, 0], iv_t[k, 1], iv_t[k, 2]
    buf.push(V, I, T)
    if buf.ready():
        feats = buf.compute_features()
        dmat = xgb.DMatrix(feats, feature_names=XGB_FEATURE_ORDER)
        pred = model.predict(dmat)[0] / 100.0  # modele entraine en % -> conversion en fraction [0,1]
        preds.append(pred)
        targets.append(soc_true[k])

preds = np.array(preds)
targets = np.array(targets)

rmse = np.sqrt(np.mean((preds - targets) ** 2))
mae = np.mean(np.abs(preds - targets))

print(f"N predictions: {len(preds)}")
print(f"RMSE XGBoost : {rmse*100:.3f} %  (soit {rmse:.5f} en fraction)")
print(f"MAE  XGBoost : {mae*100:.3f} %")
print(f"Range predictions: {preds.min():.4f} -> {preds.max():.4f}")
print(f"Range targets    : {targets.min():.4f} -> {targets.max():.4f}")

config = {
    "RMSE_XGB": float(rmse),
    "RMSE_XGB_VAR": float(rmse ** 2),
    "SEQ_LEN": SEQ_LEN,
}
with open("fusion_config.json", "w") as f:
    json.dump(config, f, indent=2)

print("\nSauvegarde dans fusion_config.json :", config)
