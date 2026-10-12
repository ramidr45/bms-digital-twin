"""
Calcul des features glissantes pour le modele XGBoost (SOC estimation).

Reproduit exactement rolling_stat_features() du notebook Kaggle :
- Fenetre glissante de SEQ_LEN=200 echantillons
- Features calculees sur les valeurs SCALEES (StandardScaler, ordre V,I,T)
- Pour chaque canal : mean, std, min, max, last, first, slope
- Ordre final des 21 colonnes = celui attendu par xgb_last.json (verifie via
  model.feature_names) : V_mean...V_slope, I_mean...I_slope, T_mean...T_slope

Validation faite sur PC : diff max vs pandas.rolling() du notebook = 1e-16.
"""

import numpy as np
from collections import deque

SEQ_LEN = 200
FEATURE_NAMES = ["V", "I", "T"]

# Ordre exact attendu par le modele (confirme via model.feature_names)
XGB_FEATURE_ORDER = [
    "V_mean", "V_std", "V_min", "V_max", "V_last", "V_first", "V_slope",
    "I_mean", "I_std", "I_min", "I_max", "I_last", "I_first", "I_slope",
    "T_mean", "T_std", "T_min", "T_max", "T_last", "T_first", "T_slope",
]


class RollingFeatureBuffer:
    """
    Maintient un buffer glissant de SEQ_LEN echantillons scales (V, I, T)
    et calcule les 21 features statistiques a chaque nouvel echantillon.

    Usage :
        buf = RollingFeatureBuffer(scaler)
        buf.push(V_raw, I_raw, T_raw)
        if buf.ready():
            feat_vector = buf.compute_features()   # np.array shape (21,)
    """

    def __init__(self, scaler):
        self.scaler = scaler
        self.buf_V = deque(maxlen=SEQ_LEN)
        self.buf_I = deque(maxlen=SEQ_LEN)
        self.buf_T = deque(maxlen=SEQ_LEN)

    def push(self, V_raw, I_raw, T_raw):
        """Ajoute un echantillon brut (non scale) au buffer."""
        # scaler attend un array (1,3) dans l'ordre V, I, T
        scaled = self.scaler.transform([[V_raw, I_raw, T_raw]])[0]
        self.buf_V.append(scaled[0])
        self.buf_I.append(scaled[1])
        self.buf_T.append(scaled[2])

    def ready(self):
        """True des que le buffer contient SEQ_LEN echantillons."""
        return len(self.buf_V) == SEQ_LEN

    @staticmethod
    def _window_feats(buf, name):
        arr = np.fromiter(buf, dtype=np.float64, count=len(buf))
        last = arr[-1]
        first = arr[0]
        return {
            f"{name}_mean": arr.mean(),
            f"{name}_std": arr.std(ddof=1),
            f"{name}_min": arr.min(),
            f"{name}_max": arr.max(),
            f"{name}_last": last,
            f"{name}_first": first,
            f"{name}_slope": (last - first) / SEQ_LEN,
        }

    def compute_features(self):
        """
        Retourne un vecteur numpy (1, 21) dans l'ordre exact attendu par
        le modele XGBoost (pret pour xgb.DMatrix ou model.predict()).
        Ne pas appeler avant ready() == True.
        """
        row = {}
        row.update(self._window_feats(self.buf_V, "V"))
        row.update(self._window_feats(self.buf_I, "I"))
        row.update(self._window_feats(self.buf_T, "T"))
        return np.array([[row[k] for k in XGB_FEATURE_ORDER]], dtype=np.float64)


if __name__ == "__main__":
    # Auto-test rapide : verifie que le buffer se remplit et produit un
    # vecteur de la bonne forme, sans crash.
    import joblib
    scaler = joblib.load("scaler_25degC.joblib")
    buf = RollingFeatureBuffer(scaler)
    rng = np.random.default_rng(0)
    for k in range(SEQ_LEN):
        buf.push(3.7 + 0.01 * rng.standard_normal(),
                  -0.7 + 0.1 * rng.standard_normal(),
                  26.0 + 0.01 * rng.standard_normal())
    assert buf.ready()
    feats = buf.compute_features()
    print("Shape:", feats.shape)
    print("Colonnes:", XGB_FEATURE_ORDER)
    print("Valeurs:", feats)
