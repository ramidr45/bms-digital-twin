% [Fichier renommé lors du rangement — ancien nom : RUN_drive_cycle_batch.m]
%% valider_EKF_tous_drive_cycles.m
% Traite automatiquement TOUS les fichiers .mat d'un dossier "Drive cycles"
% et produit un tableau recapitulatif des performances EKF/UKF.

clear; clc; close all;

%% --- Etape 1 : construire (ou charger) les LUT ECM ---
if ~isfile('ECM_NCR18650PF_25degC.mat')
    run('construire_LUT_ECM_25degC.m');
    close all;  % ferme la figure de controle OCV pour ne pas encombrer
else
    load('ECM_NCR18650PF_25degC.mat', 'ECM');
end

%% --- Etape 2 : parametres communs ---
Capacity = 2.885;   % Ah, capacite mesuree
SoC_init = 1.0;      % a verifier/ajuster selon le README du dataset

% ADAPTER CE CHEMIN vers ton dossier "Drive cycles"
drive_cycle_folder = 'C:\Users\SAT\Desktop\dataset\25degC\25degC\Drive cycles';

%% --- Etape 3 : lister tous les fichiers .mat du dossier ---
files = dir(fullfile(drive_cycle_folder, '*.mat'));
fprintf('%d fichier(s) trouve(s) dans %s\n\n', length(files), drive_cycle_folder);

if isempty(files)
    error('Aucun fichier .mat trouve. Verifie le chemin drive_cycle_folder.');
end

%% --- Etape 4 : boucle sur chaque fichier ---
n_files = length(files);
names        = cell(n_files,1);
avr_err_AH   = zeros(n_files,1);  std_err_AH  = zeros(n_files,1);
avr_err_EKF  = zeros(n_files,1);  std_err_EKF = zeros(n_files,1);
avr_err_UKF  = zeros(n_files,1);  std_err_UKF = zeros(n_files,1);

for f = 1:n_files
    fpath = fullfile(files(f).folder, files(f).name);
    fprintf('--- [%d/%d] Traitement : %s ---\n', f, n_files, files(f).name);

    try
        data = load(fpath);
        meas = data.meas;

        results = EKF_UKF_Thev_v2(ECM, meas, Capacity, SoC_init);

        names{f}       = files(f).name;
        avr_err_AH(f)  = results.avr_err_AH;   std_err_AH(f)  = results.std_err_AH;
        avr_err_EKF(f) = results.avr_err_EKF;  std_err_EKF(f) = results.std_err_EKF;
        avr_err_UKF(f) = results.avr_err_UKF;  std_err_UKF(f) = results.std_err_UKF;

        % Sauvegarde la figure individuelle pour ce fichier
        saveas(gcf, sprintf('SOC_result_%s.png', erase(files(f).name, '.mat')));
        close(gcf);

    catch ME
        fprintf('  ECHEC sur ce fichier : %s\n', ME.message);
        names{f} = [files(f).name ' (ECHEC)'];
        avr_err_AH(f) = NaN; std_err_AH(f) = NaN;
        avr_err_EKF(f) = NaN; std_err_EKF(f) = NaN;
        avr_err_UKF(f) = NaN; std_err_UKF(f) = NaN;
    end
end

%% --- Etape 5 : tableau recapitulatif ---
T = table(names, avr_err_AH*100, std_err_AH*100, avr_err_EKF*100, std_err_EKF*100, ...
    avr_err_UKF*100, std_err_UKF*100, ...
    'VariableNames', {'Fichier','AvrErr_AH_pct','StdErr_AH_pct', ...
                       'AvrErr_EKF_pct','StdErr_EKF_pct', ...
                       'AvrErr_UKF_pct','StdErr_UKF_pct'});

disp(T);
writetable(T, 'resultats_drive_cycles.csv');
fprintf('\nTableau recapitulatif sauvegarde dans resultats_drive_cycles.csv\n');
