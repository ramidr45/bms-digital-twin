==============================================================================
                      STAGE INGÉNIEUR — ACTIA
             BMS Digital Twin : estimation de l'état de charge
==============================================================================

  Ce fichier explique le contenu du dossier, pour quelqu'un qui l'ouvre
  pour la première fois. Lis les parties dans l'ordre.

  SOMMAIRE
    1. Le projet en quelques lignes
    2. Les étapes du travail
    3. Organisation du dossier
    4. Détail de chaque dossier
    5. Points d'attention
    6. Correspondance ancien nom -> nouveau nom
    7. Petit lexique


==============================================================================
 1. LE PROJET EN QUELQUES LIGNES
==============================================================================

  Objectif : estimer l'état de charge (SOC, en %) d'une cellule de
  batterie lithium-ion en temps réel, puis faire tourner cet estimateur
  sur une carte embarquée (Raspberry Pi 5).

  Cellule étudiée : Panasonic NCR18650PF.

  Méthode :
    - Modéliser la cellule par un circuit électrique simple (modèle 1RC).
    - Mesurer les paramètres de ce circuit (R0, R1, C1, OCV).
    - Utiliser ce modèle dans un filtre de Kalman étendu (EKF).
    - Générer le code C de l'EKF et l'exécuter sur le Raspberry Pi.
    - Comparer l'EKF à des modèles d'intelligence artificielle
      (LSTM, BiLSTM, XGBoost) entraînés sur les mêmes données.
    - Fusionner EKF + XGBoost sur le Raspberry Pi, avec un tableau
      de bord temps réel : c'est le "jumeau numérique" final.

  Outils : MATLAB, Simulink, Simscape, Python, Kaggle (TensorFlow,
           XGBoost).


==============================================================================
 2. LES ÉTAPES DU TRAVAIL
==============================================================================

  Chaque étape correspond à un dossier numéroté.

     [01] Prise en main de Simscape (circuit RL)
       |
     [02] Premier modèle de batterie 1RC
       |
     [03] Simulation d'un test HPPC
       |
     [04] Analyse de mesures réelles (HPPC, décharges)
       |
     [05] Identification des paramètres R0, R1, C1, OCV
       |
     [06] Estimation du SOC avec un filtre de Kalman (EKF)
       |
     [07] Génération du code C de l'EKF
       |
     [08] Déploiement sur Raspberry Pi
       |
     [09] Estimation du SOC par IA (LSTM, BiLSTM, XGBoost)
       |
     [10] Jumeau numérique final sur Raspberry Pi
          (fusion EKF + XGBoost + tableau de bord)


==============================================================================
 3. ORGANISATION DU DOSSIER
==============================================================================

  stage_ing_organise/
  |
  |-- README.txt                          <- ce fichier
  |
  |-- 00_documentation/                   datasheets
  |-- 00_dataset_Panasonic_18650PF/       données de mesure (à ajouter)
  |
  |-- 01_projet_RL_simscape_prise_en_main/
  |-- 02_modele_ECM_Samsung25R/
  |-- 03_simulation_HPPC_simscape_NCR18650BD/
  |-- 04_analyse_HPPC_et_decharges_xlsx/
  |-- 05_identification_ECM_EIS_NCR18650PF/
  |-- 06_EKF_estimation_SOC/
  |-- 07_code_C_genere_EKF/
  |-- 08_deploiement_RaspberryPi_TCP/
  |-- 09_IA_estimation_SOC/
  |-- 10_digital_twin_RaspberryPi/        copie du Raspberry Pi
  |
  |-- 99_archives/                        anciennes versions (non utilisées)

  Dans certains dossiers :
    figures/     images générées par les scripts (.png)
    resultats/   résultats numériques (.csv, .mat)
    modeles/     modèles IA entraînés (dossier 09)

  Types de fichiers :
    .m      script MATLAB  -> ouvrir dans MATLAB puis cliquer "Run"
    .slx    modèle Simulink -> ouvrir puis cliquer "Run"
    .mat    données MATLAB
    .csv    tableau de données
    .py     script Python
    .ipynb  notebook Python (Jupyter / Kaggle)
    .keras  modèle de réseau de neurones (TensorFlow)


==============================================================================
 4. DÉTAIL DE CHAQUE DOSSIER
==============================================================================

  Conseil : avant de lancer un script, place-toi dans son dossier
  (MATLAB -> "Current Folder"), car les scripts lisent les fichiers
  qui sont à côté d'eux.

------------------------------------------------------------------------------
 [01] PROJET RL SIMSCAPE — Prise en main
------------------------------------------------------------------------------
  But      : apprendre Simscape sur un circuit simple (résistance +
             bobine) et générer un jeu de données.
  Modèle   : rl.slx
  Ordre    : 1) generer_dataset_RL_v5_final.m
             2) analyser_dataset_RL_metriques.m
  Résultat : RL_simscape_dataset.csv
  Note     : generer_dataset_RL_v1.m est une ancienne version.

------------------------------------------------------------------------------
 [02] MODÈLE ECM SAMSUNG 25R — Premier modèle de batterie
------------------------------------------------------------------------------
  But      : construire un premier modèle 1RC et ajuster ses
             paramètres sur une courbe de décharge.
  Modèle   : ECM_1RC_simscape_LUT.slx
  Ordre    : 1) optimiser_params_ECM_Samsung25R.m
             2) lancer la simulation ECM_1RC_simscape_LUT.slx
             3) valider_ECM_Samsung25R_metriques.m
  Autres   : projet_simscape_pulse/  -> variante avec impulsions
             +Batteries/, Batteries_lib.slx -> bibliothèque générée

------------------------------------------------------------------------------
 [03] SIMULATION HPPC — Test d'impulsions simulé
------------------------------------------------------------------------------
  But      : simuler un test HPPC (impulsions de courant) sur une
             cellule NCR18650BD, à plusieurs températures.
  Modèle   : modele_nmc.slx
  Ordre    : 1) generer_signal_HPPC.m
             2) simuler_HPPC_multi_temperature.m
             3) extraire_V_I_simulation.m
  Résultat : HPPC_data.mat

------------------------------------------------------------------------------
 [04] ANALYSE HPPC ET DÉCHARGES — Mesures réelles (Excel)
------------------------------------------------------------------------------
  But      : visualiser des mesures réelles et en tirer les premiers
             paramètres du modèle.
  Besoin   : hppc.xlsx et drive_cycles.xlsx  (voir partie 5)
  Scripts  : (indépendants, ordre libre)
             - visu_HPPC_drive_cycles.m
             - analyse_decharges_et_params_HPPC.m
             - comparaison_decharges_vs_datasheet.m
             - inspecter_pulse_HPPC.m
  Résultat : figures/ et resultats/

------------------------------------------------------------------------------
 [05] IDENTIFICATION ECM PAR EIS — Paramètres de la cellule
------------------------------------------------------------------------------
  But      : calculer R0, R1, C1 et OCV pour chaque niveau de charge
             à partir de mesures d'impédance (EIS), puis vérifier le
             modèle avec la datasheet.
  Besoin   : dossier Bureau\EIS  (voir partie 5)
  Ordre    : 1) visu_EIS_nyquist_bode.m
             2) identifier_ECM_EIS_decharge_1C.m
                (ou identifier_ECM_EIS_multi_Crates.m pour
                 comparer 0.2C / 1C / 2C)
             Puis, SANS FERMER MATLAB :
             3) preparer_LUT_simulink_ECM.m
             4) preparer_LUT_battery_table_based.m
             5) figure_validation_datasheet_matlab_simulink.m
  Modèles  : ECM_1RC_simulink_LUT.slx
             ECM_1RC_battery_table_based.slx
  Résultat : ECM_Parameters.mat, figures/, resultats/

------------------------------------------------------------------------------
 [06] EKF — Estimation du SOC   (partie principale du stage)
------------------------------------------------------------------------------
  But      : estimer le SOC avec un filtre de Kalman étendu et
             mesurer l'erreur sur des cycles de conduite réels.
  Modèles  : EKFSim.slx     -> modèle principal
             EKFSim_pi.slx  -> version pour le Raspberry Pi
  Ordre    : 1) construire_LUT_ECM_25degC.m
             2) preparer_LUT_pour_EKFSim.m
             3) preparer_entree_drive_cycle.m
             4) lancer la simulation EKFSim.slx
             5) analyser_erreur_EKF.m
  Outils   : - balayer_bruits_Q_R.m        réglage du filtre
             - valider_EKF_un_drive_cycle.m
             - valider_EKF_tous_drive_cycles.m
             - ajuster_polynomes_params_ECM.m
             - inspecter_fichier_dataset.m  voir le contenu d'un .mat
  Résultat : figures/ et resultats/

------------------------------------------------------------------------------
 [07] CODE C GÉNÉRÉ — L'EKF en langage C
------------------------------------------------------------------------------
  But      : tester sur PC le code C produit à partir d'EKFSim.slx.
  Ordre    : 1) build.bat         -> crée test_ekf.exe
             2) test_ekf.exe      -> lit test_input.csv,
                                     écrit test_output.csv
             3) tracer_resultats_EKF_exe.m  -> affiche le résultat

------------------------------------------------------------------------------
 [08] RASPBERRY PI — Déploiement
------------------------------------------------------------------------------
  But      : envoyer les mesures (courant, tension, température)
             du PC vers le Raspberry Pi, qui calcule le SOC.
  Ordre    : 1) lancer le serveur sur le Raspberry Pi
                (voir dossier 10)
             2) sur le PC : python envoyer_donnees_vers_RPi.py
  Avant    : vérifier l'adresse IP (RPI_IP) en haut du script.

------------------------------------------------------------------------------
 [09] IA — Estimation du SOC par apprentissage automatique
------------------------------------------------------------------------------
  But      : entraîner 3 modèles d'IA à estimer le SOC à partir de
             la tension, du courant et de la température, puis les
             comparer à l'EKF sur le même cycle de test.
  Notebook : notebook_SOC_LSTM_BiLSTM_XGBoost.ipynb
             (exécuté sur Kaggle, avec le dataset Panasonic à 25 °C)
  Données  : entraînement = Cycles 1 à 4, HWFTa, UDDS, LA92
             validation    = HWFTb
             test          = US06 (même fichier que pour l'EKF)
  Contenu  : modeles/      -> modèles finaux, prêts à réutiliser
               - lstm_soc_25degC.keras
               - bilstm_soc_25degC.keras
               - xgboost_soc_25degC.json
               - scaler_25degC.joblib (normalisation des entrées)
             checkpoints/  -> sauvegardes pendant l'entraînement
                              (pour reprendre un entraînement)
             figures/      -> 9 figures, numérotées dans l'ordre
                              du notebook
             resultats/    -> tableau de comparaison des méthodes

  Résultats sur le cycle de test US06 (25 °C) :

        Méthode     RMSE      MAE
        ---------   ------    ------
        EKF         0.86 %    0.70 %
        XGBoost     1.74 %    1.38 %
        LSTM        2.34 %    1.78 %
        BiLSTM      3.82 %    2.95 %

  -> L'EKF reste le plus précis. Parmi les modèles IA, XGBoost
     est le meilleur : c'est lui qui est retenu.

  Recharger un modèle sans réentraîner : voir la dernière cellule
  du notebook (en commentaire).

------------------------------------------------------------------------------
 [10] DIGITAL TWIN RASPBERRY PI — Le jumeau numérique final
------------------------------------------------------------------------------
  But      : copie du dossier ~/digital_twin du Raspberry Pi 5.
             Le Pi reçoit les mesures du PC (dossier 08), calcule
             le SOC avec l'EKF et avec XGBoost, fusionne les deux
             résultats et les affiche en temps réel.

  Principe :

     PC (dossier 08)                 Raspberry Pi (ce dossier)
     ---------------                 -------------------------
     envoie I, V, T   --- TCP --->   digital_twin_server.py
     (port 5005)                       |-- EKF      (ekf_src_pi)
                                       |-- XGBoost  (xgb_model)
                                       |-- fusion des deux SOC
                                       '-- tableau de bord

  Fichiers :
    digital_twin_server.py  programme principal (serveur TCP)
    xgb_features.py         calcule les 21 entrées de XGBoost sur
                            les 200 derniers échantillons
    calibrate_xgb_rmse.py   mesure une fois l'erreur de XGBoost et
                            l'écrit dans fusion_config.json
    fusion_config.json      réglage de la fusion
    ekf_src/                code C de l'EKF (version PC)
    ekf_src_pi/             code C de l'EKF pour le Pi (libekf.so)
    xgb_model/              modèle XGBoost
    scaler_25degC.joblib    normalisation des entrées de XGBoost
    dashboard/              tableau de bord temps réel
    test_input.csv          données envoyées pendant le test
    ground_truth_soc.csv    SOC de référence (pour calculer l'erreur)
    digital_twin_result.png capture des résultats
    test.png                capture d'un test
    digital_twin_log.csv    journal du serveur (vide sur ce run)
    venv/                   environnement Python du Pi
    __pycache__/            fichiers temporaires Python

  Comment marche la fusion :
    - L'EKF donne un SOC et son incertitude, qui change en direct.
    - XGBoost donne un SOC avec une erreur fixe, mesurée une fois.
    - Le SOC final est une moyenne pondérée : la méthode la plus
      sûre à l'instant t pèse le plus.
    - Pendant les 200 premiers échantillons, XGBoost n'a pas encore
      assez de données : seul l'EKF est utilisé.

  Lancer sur le Raspberry Pi :
    1) cd ~/digital_twin
    2) source venv/bin/activate
    3) (une seule fois) python calibrate_xgb_rmse.py
    4) python digital_twin_server.py
    5) sur le PC : lancer le script du dossier 08

  Résultats obtenus sur le Pi :
        Méthode     RMSE
        ---------   ------
        EKF         1.02 %
        XGBoost     1.75 %
        Fusion      1.01 %
    -> La fusion fait légèrement mieux que chaque méthode seule ;
       l'EKF reste la source principale.


==============================================================================
 5. POINTS D'ATTENTION
==============================================================================

  [!] Fichiers absents de ce dossier (à retrouver sur le PC)
      - EKF_UKF_Thev_v2.m  ............ dossier 06
      - hppc.xlsx  .................... dossier 04
      - drive_cycles.xlsx  ............ dossier 04
      - dossier Bureau\EIS  ........... dossier 05

  [!] Données de mesure
      Le fichier dataset.zip n'est pas inclus (trop lourd).
      Le placer dans 00_dataset_Panasonic_18650PF/ et l'extraire.

  [!] Chemins à adapter
      Certains scripts cherchent les données dans :
        C:\Users\SAT\Desktop\...
      Si les données sont ailleurs, modifier le chemin écrit
      en haut du script.

  [!] Ne pas renommer EKFSim.slx ni EKFSim_pi.slx
      Le code C (dossier 07) et le Raspberry Pi utilisent ce nom.

  [!] Notebook IA (dossier 09)
      Les chemins du notebook sont ceux de Kaggle
      (/kaggle/input/...). Pour l'exécuter sur PC, remplacer
      DATASET_DIR par le chemin local du dataset.

  [!] Dossier 10 : ne rien renommer à l'intérieur
      Le serveur charge ses fichiers par leur nom exact
      (xgb_features.py, fusion_config.json, scaler_25degC.joblib...).

  [!] Dossier 10 : venv/ et __pycache__/
      venv/ ne marche QUE sur le Raspberry Pi (Linux ARM), pas
      sur Windows. __pycache__/ peut être supprimé sans risque :
      Python le recrée tout seul.

  [!] Titres des figures IA
      Certains titres du notebook indiquent "Cycle_1", mais le
      fichier de test réellement utilisé est US06 (voir la
      variable test_file). À corriger dans le rapport si besoin.

  [!] Deux fichiers test_input.csv différents
      - dossier 06 : 2 colonnes (courant, tension)
      - dossier 08 : 3 colonnes (courant, tension, température)


==============================================================================
 6. CORRESPONDANCE ANCIEN NOM -> NOUVEAU NOM
==============================================================================

  Chaque script renommé indique aussi son ancien nom en 1re ligne.

  [01]  rlsc.m ..................... generer_dataset_RL_v1.m
        dataset_simulink.m ......... generer_dataset_RL_v5_final.m
        metriques.m ................ analyser_dataset_RL_metriques.m

  [02]  gen.m ...................... optimiser_params_ECM_Samsung25R.m
        metrique.m ................. valider_ECM_Samsung25R_metriques.m
        RCPulseGen.slx ............. ECM_1RC_simscape_LUT.slx

  [03]  hppc.m ..................... generer_signal_HPPC.m
        hppc_v2.m .................. simuler_HPPC_multi_temperature.m
        extrairevt.m ............... extraire_V_I_simulation.m

  [04]  visualisation.m ............ visu_HPPC_drive_cycles.m
        comp.m ..................... analyse_decharges_et_params_HPPC.m
        COMPARAISON.m .............. comparaison_decharges_vs_datasheet.m
        lut.m ...................... inspecter_pulse_HPPC.m

  [05]  dsicharge_datasheet.m ...... visu_EIS_nyquist_bode.m
        test.m ..................... identifier_ECM_EIS_decharge_1C.m
        diffcrates.m ............... identifier_ECM_EIS_multi_Crates.m
        S2_extraction.m ............ figure_validation_datasheet_
                                     matlab_simulink.m
        battery_model_generator.m .. preparer_LUT_simulink_ECM.m
        build_lut_1rc.m ............ preparer_LUT_battery_table_based.m
        extract_RC_lut.slx ......... ECM_1RC_simulink_LUT.slx
        untitled_recovered1.slx .... ECM_1RC_battery_table_based.slx

  [06]  build_ECM_LUTs.m ........... construire_LUT_ECM_25degC.m
        build_simulink_LUTs.m ...... preparer_LUT_pour_EKFSim.m
        build_tuvar.m .............. preparer_entree_drive_cycle.m
        ekf_erreur.m ............... analyser_erreur_EKF.m
        sweep_qr.m ................. balayer_bruits_Q_R.m
        RUN_drive_cycle.m .......... valider_EKF_un_drive_cycle.m
        RUN_drive_cycle_batch.m .... valider_EKF_tous_drive_cycles.m
        profile_courant_
          discharge1c.m ............ ajuster_polynomes_params_ECM.m
        inspect_dichage1c_
          dataset.m ................ inspecter_fichier_dataset.m

  [07]  plot_results.m ............. tracer_resultats_EKF_exe.m
        visul_outputc.m ............ tracer_SOC_EKF_exe.m
        find_missing.py ............ trouver_headers_manquants.py

  [08]  client_send.py ............. envoyer_donnees_vers_RPi.py

  [09]  notebooka8c71b4774.ipynb ... notebook_SOC_LSTM_BiLSTM_
                                     XGBoost.ipynb
        __results___14_0.png ....... 01_apercu_donnees_brutes.png
        __results___28_1.png ....... 02_LSTM_prediction_SOC.png
        __results___30_0.png ....... 03_LSTM_courbes_apprentissage.png
        __results___32_1.png ....... 04_LSTM_vs_EKF_SOC.png
        __results___32_2.png ....... 05_LSTM_vs_EKF_erreur.png
        __results___38_1.png ....... 06_BiLSTM_prediction_SOC.png
        __results___42_1.png ....... 07_XGBoost_importance_features.png
        __results___44_1.png ....... 08_comparaison_toutes_methodes.png
        __results___44_2.png ....... 09_comparaison_RMSE_MAE.png
        models/ .................... modeles/

  Anciens noms de dossiers :
        raseberry_pi/ .............. 10_digital_twin_RaspberryPi/
        EFK_SOC/ ................... 06_EKF_estimation_SOC/
        EKFSim_grt_rtw/ ............ 07_code_C_genere_EKF/
        tcp/ ....................... 08_deploiement_RaspberryPi_TCP/
        matlab/ .................... 01_projet_RL_simscape_prise_en_main/
        cell_battery/ .............. 02_modele_ECM_Samsung25R/
        sim_modele_cellule/ ........ 03_simulation_HPPC_simscape_NCR18650BD/


==============================================================================
 7. PETIT LEXIQUE
==============================================================================

  SOC    State of Charge : état de charge de la batterie (0 à 100 %)
  OCV    Open Circuit Voltage : tension de la batterie au repos
  ECM    Equivalent Circuit Model : modèle électrique de la batterie
  1RC    Modèle avec une résistance R0 + un circuit R1//C1
  HPPC   Test par impulsions de courant pour mesurer les résistances
  EIS    Spectroscopie d'impédance : mesure de l'impédance en fréquence
  EKF    Extended Kalman Filter : filtre qui estime le SOC
  LUT    Look-Up Table : tableau de valeurs utilisé dans Simulink
  C-rate Courant relatif à la capacité (1C = décharge en 1 heure)
  LSTM   Réseau de neurones qui apprend sur des séquences temporelles
  BiLSTM LSTM qui lit la séquence dans les deux sens
  XGBoost Modèle à base d'arbres de décision (boosting)
  RMSE   Erreur quadratique moyenne (plus c'est bas, mieux c'est)
  MAE    Erreur absolue moyenne (plus c'est bas, mieux c'est)
  Kaggle Plateforme en ligne pour exécuter des notebooks avec GPU
  Fusion Combinaison de deux estimations en une seule, plus fiable
  TCP    Protocole réseau utilisé entre le PC et le Raspberry Pi
  venv   Environnement Python isolé (paquets du projet)
  Digital twin  "Jumeau numérique" : copie logicielle de la batterie
                qui suit son état en temps réel

==============================================================================
