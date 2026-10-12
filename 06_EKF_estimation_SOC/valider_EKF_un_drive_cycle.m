% [Fichier renommé lors du rangement — ancien nom : RUN_drive_cycle.m]
%% valider_EKF_un_drive_cycle.m
% Script principal : validation EKF/UKF sur un drive cycle reel mesure,
% pour la cellule Panasonic NCR18650PF.

clear; clc; close all;

%% --- Etape 1 : construire (ou charger) les LUT ECM ---
if ~isfile('ECM_NCR18650PF_25degC.mat')
    run('construire_LUT_ECM_25degC.m');   % genere ECM_NCR18650PF_25degC.mat
else
    load('ECM_NCR18650PF_25degC.mat', 'ECM');
end

%% --- Etape 2 : charger le fichier .mat du drive cycle ---
% ADAPTER CE CHEMIN vers ton fichier reel dans le dossier "Drive cycles"
drive_cycle_file = 'C:\Users\SAT\Desktop\dataset\25degC\25degC\Drive cycles\03-18-17_02.17 25degC_Cycle_1_Pan18650PF.mat';
data = load(drive_cycle_file);
meas = data.meas;

fprintf('Fichier charge : %s\n', drive_cycle_file);
fprintf('Nombre de points : %d\n', length(meas.Time));
fprintf('Duree totale : %.1f s (%.2f min)\n', meas.Time(end), meas.Time(end)/60);
fprintf('Temperature moyenne : %.2f degC\n', mean(meas.Battery_Temp_degC));
fprintf('Tension initiale : %.4f V / finale : %.4f V\n', meas.Voltage(1), meas.Voltage(end));
fprintf('Ah cumule (fin de cycle) : %.4f Ah\n', meas.Ah(end));

%% --- Etape 3 : parametres de l'essai ---
Capacity = 2.885;   % Ah, capacite mesuree (a confirmer/ajuster si besoin)

% IMPORTANT : verifier dans le README du dataset si ce drive cycle demarre
% a 100% SOC ou a une valeur de precondition differente.
SoC_init = 1.0;

%% --- Etape 4 : lancer l'estimation ---
results = EKF_UKF_Thev_v2(ECM, meas, Capacity, SoC_init);

%% --- Etape 5 : rapport ---
fprintf('\n=================== RESULTATS ===================\n');
fprintf('Comptage de coulombs naif : avr_err = %.4f %%  std_err = %.4f %%\n', ...
    results.avr_err_AH*100, results.std_err_AH*100);
fprintf('EKF                        : avr_err = %.4f %%  std_err = %.4f %%\n', ...
    results.avr_err_EKF*100, results.std_err_EKF*100);
fprintf('UKF                        : avr_err = %.4f %%  std_err = %.4f %%\n', ...
    results.avr_err_UKF*100, results.std_err_UKF*100);
