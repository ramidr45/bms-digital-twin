# [Fichier renommé lors du rangement — ancien nom : client_send.py]
"""
A executer sur le PC (avec Python installe).
Envoie les echantillons I,V,T de test_input.csv au Raspberry Pi via TCP,
au rythme Ts=0.1s (coherent avec le pas fixe du solveur EKF).

Usage :
    python envoyer_donnees_vers_RPi.py
"""

import socket
import csv
import time

RPI_IP = "192.168.0.155"   # <-- verifie avec hostname -I sur le Pi
RPI_PORT = 5005
CSV_PATH = "test_input.csv"   # I,V,T
TS = 0.1   # secondes, doit correspondre au FixedStep du modele EKF

print(f"Connexion a {RPI_IP}:{RPI_PORT} ...")
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.connect((RPI_IP, RPI_PORT))
print("Connecte. Envoi des echantillons...")

count = 0
t0 = time.time()
with open(CSV_PATH) as f:
    for row in csv.reader(f):
        if len(row) < 3:
            continue
        I, V, T = row[0], row[1], row[2]
        sock.sendall(f"{I},{V},{T}\n".encode())
        count += 1
        if count % 500 == 0:
            print(f"Envoye {count} echantillons...")
        time.sleep(TS)

elapsed = time.time() - t0
print(f"Termine. {count} echantillons envoyes en {elapsed:.1f}s.")
sock.close()
