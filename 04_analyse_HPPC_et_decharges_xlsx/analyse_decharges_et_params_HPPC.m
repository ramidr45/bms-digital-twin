% [Fichier renommé lors du rangement — ancien nom : comp.m]
%% =========================================================================
% ANALYSE BATTERIE NCR18650 - COURBES DE DECHARGE & PARAMETRES HPPC
% =========================================================================
clear; clc; close all;

%% 1. CHARGEMENT DES DONNEES
% -------------------------------------------------------------------------
fprintf('=== Chargement des fichiers ===\n');

% Fichier hppc.xlsx : courbes de décharge à différents C-rates
hppc_file = 'hppc.xlsx';
[~, sheetNames_hppc] = xlsfinfo(hppc_file);
fprintf('Onglets hppc.xlsx : %s\n', strjoin(sheetNames_hppc, ', '));

% Fichier drive_cycles.xlsx : tests HPPC avec relaxation
drive_file = 'drive_cycles.xlsx';
[~, sheetNames_drive] = xlsfinfo(drive_file);
fprintf('Onglets drive_cycles.xlsx : %s\n', strjoin(sheetNames_drive, ', '));

%% 2. VISUALISATION DES COURBES DE DECHARGE (Tension vs SOC)
% -------------------------------------------------------------------------
fprintf('\n=== Visualisation des courbes de décharge ===\n');

% Couleurs pour chaque C-rate
colors = {'b', 'r', 'g'};
c_rates = sheetNames_hppc;  % ex: {'1.5C', '1.0C', '0.5C'}

figure('Name', 'Courbes de décharge - Tension vs SOC', 'Position', [100 100 900 700]);

all_soc_data = {};
all_volt_data = {};

for idx = 1:length(c_rates)
    % Lire la feuille
    data = readtable(hppc_file, 'Sheet', c_rates{idx});
    
    % Identifier les colonnes (adapter selon le fichier)
    colNames = data.Properties.VariableNames;
    fprintf('Feuille %s - Colonnes : %s\n', c_rates{idx}, strjoin(colNames, ', '));
    
    % Extraire Voltage et SOC
    % Le SOC dans le fichier va de 0 (plein) à 100 (vide) -> on inverse
    if ismember('Voltage', colNames)
        V = data.Voltage;
    else
        V = data.(colNames{3});
    end
    
    % Chercher la colonne SOC
    socCol = colNames(contains(colNames, 'SOC'));
    if ~isempty(socCol)
        DOD = data.(socCol{1});  % Depth of Discharge (0=plein, 100=vide)
    else
        DOD = data.Capacity / max(data.Capacity) * 100;
    end
    
    % SOC conventionnel : 100% = plein, 0% = vide
    SOC = 100 - DOD;
    
    all_soc_data{idx} = SOC;
    all_volt_data{idx} = V;
    
    % Échantillonnage avec pas de 0.2% SOC
    SOC_grid = 100:-0.2:0;
    V_interp = interp1(SOC, V, SOC_grid, 'linear', 'extrap');
    
    subplot(3,1,idx);
    plot(SOC_grid, V_interp, colors{idx}, 'LineWidth', 2);
    hold on;
    plot(SOC, V, [colors{idx} '.'], 'MarkerSize', 3, 'MarkerFaceColor', colors{idx});
    xlabel('SOC (%)');
    ylabel('Tension (V)');
    title(sprintf('Courbe de décharge - %s', c_rates{idx}));
    legend('Interpolé (pas 0.2%)', 'Données brutes');
    grid on;
    xlim([0 100]);
    ylim([2.4 4.2]);
end

sgtitle('Tension vs SOC pour différents C-rates (NCR18650)');

%% 3. VISUALISATION SOC vs Temps
% -------------------------------------------------------------------------
fprintf('\n=== Visualisation SOC vs Temps ===\n');

figure('Name', 'Évolution SOC vs Temps', 'Position', [1050 100 900 700]);

for idx = 1:length(c_rates)
    data = readtable(hppc_file, 'Sheet', c_rates{idx});
    colNames = data.Properties.VariableNames;
    
    if ismember('Time', colNames)
        T = data.Time;
    else
        T = (1:height(data))';
    end
    
    socCol = colNames(contains(colNames, 'SOC'));
    if ~isempty(socCol)
        DOD = data.(socCol{1});
    else
        DOD = data.Capacity / max(data.Capacity) * 100;
    end
    SOC = 100 - DOD;
    
    subplot(3,1,idx);
    plot(T, SOC, colors{idx}, 'LineWidth', 1.5);
    xlabel('Temps (s)');
    ylabel('SOC (%)');
    title(sprintf('Évolution SOC - %s', c_rates{idx}));
    grid on;
end

%% 4. EXTRACTION DES PARAMETRES R0, R1, C1 DEPUIS HPPC
% -------------------------------------------------------------------------
fprintf('\n=== Extraction des paramètres R0, R1, C1 ===\n');

% Lire le fichier drive_cycles (HPPC avec relaxation)
% Adapter selon la structure réelle du fichier
drive_data = readtable(drive_file);
colNames = drive_data.Properties.VariableNames;
fprintf('Colonnes drive_cycles : %s\n', strjoin(colNames, ', '));

% Identifier les colonnes Time, Current, Voltage
% (adapter les noms selon votre fichier)
timeCol = colNames(contains(colNames, 'Time', 'IgnoreCase', true));
currCol = colNames(contains(colNames, 'Current', 'IgnoreCase', true));
voltCol = colNames(contains(colNames, 'Voltage', 'IgnoreCase', true));
capCol  = colNames(contains(colNames, 'Capacity', 'IgnoreCase', true));

if isempty(timeCol), timeCol = {colNames{1}}; end
if isempty(currCol), currCol = {colNames{2}}; end
if isempty(voltCol), voltCol = {colNames{3}}; end

T_hppc   = drive_data.(timeCol{1});
I_hppc   = drive_data.(currCol{1});
V_hppc   = drive_data.(voltCol{1});

if ~isempty(capCol)
    Cap_hppc = drive_data.(capCol{1});
else
    Cap_hppc = cumsum(abs(I_hppc)) / 3600;  % estimation en Ah
end

% Capacité totale de la cellule (NCR18650 ~ 3.2 Ah)
Q_total = max(Cap_hppc);
fprintf('Capacité totale estimée : %.3f Ah\n', Q_total);

% Calcul du SOC
SOC_hppc = 100 * (1 - Cap_hppc / Q_total);

%% 4a. Détection des pulses et phases de relaxation
% -------------------------------------------------------------------------
% Seuil pour détecter les pulses (courant élevé)
I_threshold = 50;  % A

is_pulse = abs(I_hppc) > I_threshold;

% Trouver les transitions
transitions = diff(double(is_pulse));
pulse_starts = find(transitions == 1) + 1;
pulse_ends   = find(transitions == -1);

% S'assurer que pulse_starts et pulse_ends sont de même longueur
n_pulses = min(length(pulse_starts), length(pulse_ends));
fprintf('Nombre de pulses détectés : %d\n', n_pulses);

%% 4b. Extraction R0, R1, C1 pour chaque pulse
% -------------------------------------------------------------------------
R0_list = [];
R1_list = [];
C1_list = [];
SOC_list = [];
Vocv_list = [];
tau_list = [];

% Fonction de relaxation : V(t) = Vocv + A * exp(-t/tau)
relax_model = @(p, t) p(1) + p(2) * exp(-t / p(3));

for i = 1:n_pulses
    p_start = pulse_starts(i);
    p_end   = pulse_ends(i);
    
    % SOC au début du pulse
    soc_val = SOC_hppc(p_start);
    
    % --- Tension au repos AVANT le pulse ---
    n_rest_before = min(20, p_start - 1);
    if n_rest_before > 0
        V_rest_before = mean(V_hppc(p_start - n_rest_before : p_start - 1));
    else
        V_rest_before = V_hppc(p_start);
    end
    
    % --- Courant du pulse ---
    I_pulse = I_hppc(p_start);
    if abs(I_pulse) < 1
        continue;
    end
    
    % --- R0 : chute instantanée au début du pulse ---
    % Prendre la moyenne sur les premiers points du pulse
    n_pulse_start = min(5, p_end - p_start + 1);
    V_pulse_start = mean(V_hppc(p_start : p_start + n_pulse_start - 1));
    
    R0 = (V_rest_before - V_pulse_start) / I_pulse;
    
    % --- Relaxation après le pulse ---
    relax_start = p_end + 1;
    
    % Fin de la relaxation : prochain pulse ou fin des données
    if i < n_pulses
        relax_end = pulse_starts(i + 1) - 1;
    else
        relax_end = min(length(T_hppc), relax_start + 5000);
    end
    
    % Durée de relaxation
    relax_duration = T_hppc(relax_end) - T_hppc(relax_start);
    
    if relax_duration < 5  % au moins 5 secondes
        continue;
    end
    
    % Données de relaxation
    t_relax = T_hppc(relax_start:relax_end) - T_hppc(relax_start);
    V_relax = V_hppc(relax_start:relax_end);
    
    % Tension à la fin du pulse (moyenne sur les derniers points)
    n_pulse_end = min(5, p_end - p_start + 1);
    V_pulse_end = mean(V_hppc(p_end - n_pulse_end + 1 : p_end));
    
    % Tension OCV estimée (fin de relaxation)
    Vocv_est = mean(V_relax(max(1,end-50):end));
    
    % Amplitude initiale
    A_init = V_pulse_end - Vocv_est;
    tau_init = relax_duration / 3;
    
    % Fit exponentiel
    p0 = [Vocv_est, A_init, tau_init];
    options = optimoptions('lsqcurvefit', 'Display', 'off', 'MaxFunctionEvaluations', 10000);
    
    try
        p_fit = lsqcurvefit(relax_model, p0, t_relax, V_relax, ...
            [-Inf, -Inf, 0.01], [Inf, 0, 1000], options);
        
        Vocv_fit = p_fit(1);
        A_fit    = p_fit(2);
        tau_fit  = p_fit(3);
        
        % R1 = |A| / |I|
        R1 = abs(A_fit) / abs(I_pulse);
        
        % C1 = tau / R1
        if R1 > 1e-6
            C1 = tau_fit / R1;
        else
            C1 = 0;
        end
        
        R0_list = [R0_list; R0];
        R1_list = [R1_list; R1];
        C1_list = [C1_list; C1];
        SOC_list = [SOC_list; soc_val];
        Vocv_list = [Vocv_list; Vocv_fit];
        tau_list = [tau_list; tau_fit];
        
    catch
        % Fit échoué, on passe
    end
end

fprintf('Nombre de points extraits : %d\n', length(SOC_list));

%% 4c. Visualisation des paramètres R0, R1, C1 vs SOC
% -------------------------------------------------------------------------
figure('Name', 'Paramètres R0, R1, C1 vs SOC', 'Position', [100 850 1200 900]);

% R0 vs SOC
subplot(2,2,1);
scatter(SOC_list, R0_list, 40, 'b', 'filled');
xlabel('SOC (%)');
ylabel('R0 (Ω)');
title('Résistance ohmique R0 vs SOC');
grid on;

% R1 vs SOC
subplot(2,2,2);
scatter(SOC_list, R1_list, 40, 'r', 'filled');
xlabel('SOC (%)');
ylabel('R1 (Ω)');
title('Résistance de polarisation R1 vs SOC');
grid on;

% C1 vs SOC
subplot(2,2,3);
scatter(SOC_list, C1_list, 40, 'g', 'filled');
xlabel('SOC (%)');
ylabel('C1 (F)');
title('Capacité C1 vs SOC');
grid on;

% V_OCV vs SOC
subplot(2,2,4);
scatter(SOC_list, Vocv_list, 40, 'm', 'filled');
xlabel('SOC (%)');
ylabel('V_{OCV} (V)');
title('Tension circuit ouvert vs SOC');
grid on;

sgtitle('Paramètres du modèle RC extrait par HPPC');

%% 4d. Exemple de fit sur un pulse individuel
% -------------------------------------------------------------------------
if length(SOC_list) > 0
    % Choisir un pulse au milieu
    mid_idx = round(length(SOC_list) / 2);
    
    % Retrouver le pulse correspondant
    p_start = pulse_starts(mid_idx);
    p_end   = pulse_ends(mid_idx);
    relax_start = p_end + 1;
    if mid_idx < length(pulse_starts)
        relax_end = pulse_starts(mid_idx + 1) - 1;
    else
        relax_end = min(length(T_hppc), relax_start + 5000);
    end
    
    t_relax = T_hppc(relax_start:relax_end) - T_hppc(relax_start);
    V_relax = V_hppc(relax_start:relax_end);
    V_fit = relax_model([Vocv_list(mid_idx), ...
        (V_hppc(p_end) - Vocv_list(mid_idx)), ...
        tau_list(mid_idx)], t_relax);
    
    figure('Name', 'Exemple de fit relaxation', 'Position', [1350 850 900 500]);
    plot(t_relax, V_relax, 'b.', 'MarkerSize', 4);
    hold on;
    plot(t_relax, V_fit, 'r-', 'LineWidth', 2);
    yline(Vocv_list(mid_idx), 'g--', sprintf('V_{OCV} = %.3f V', Vocv_list(mid_idx)));
    xlabel('Temps de relaxation (s)');
    ylabel('Tension (V)');
    title(sprintf('Fit exponentiel - Pulse %d, SOC ≈ %.1f%%\nR0=%.4fΩ, R1=%.4fΩ, C1=%.2fF, τ=%.2fs', ...
        mid_idx, SOC_list(mid_idx), R0_list(mid_idx), R1_list(mid_idx), ...
        C1_list(mid_idx), tau_list(mid_idx)));
    legend('Données mesurées', 'Fit exponentiel', 'V_{OCV}');
    grid on;
end

%% 5. TABLEAU RECAPITULATIF
% -------------------------------------------------------------------------
fprintf('\n=== TABLEAU DES PARAMETRES EXTRAITS ===\n');
results_table = table(SOC_list, Vocv_list, R0_list, R1_list, C1_list, tau_list, ...
    'VariableNames', {'SOC_pct', 'Vocv_V', 'R0_Ohm', 'R1_Ohm', 'C1_F', 'tau_s'});
disp(results_table);

% Sauvegarder en CSV
writetable(results_table, 'hppc_parameters_extracted.csv');
fprintf('\nRésultats sauvegardés dans hppc_parameters_extracted.csv\n');

%% 6. INTERPOLATION DES PARAMETRES SUR UNE GRILLE SOC REGULIERE
% -------------------------------------------------------------------------
fprintf('\n=== Interpolation sur grille SOC régulière ===\n');

SOC_grid_regular = (0:0.2:100)';  % pas de 0.2%

% Tri des données par SOC
[SOC_sorted, idx_sort] = sort(SOC_list);
R0_sorted = R0_list(idx_sort);
R1_sorted = R1_list(idx_sort);
C1_sorted = C1_list(idx_sort);
Vocv_sorted = Vocv_list(idx_sort);

% Interpolation (avec extrapolation constante aux bords)
R0_interp = interp1(SOC_sorted, R0_sorted, SOC_grid_regular, 'linear', 'extrap');
R1_interp = interp1(SOC_sorted, R1_sorted, SOC_grid_regular, 'linear', 'extrap');
C1_interp = interp1(SOC_sorted, C1_sorted, SOC_grid_regular, 'linear', 'extrap');
Vocv_interp = interp1(SOC_sorted, Vocv_sorted, SOC_grid_regular, 'linear', 'extrap');

% Sauvegarder
interp_table = table(SOC_grid_regular, Vocv_interp, R0_interp, R1_interp, C1_interp, ...
    'VariableNames', {'SOC_pct', 'Vocv_V', 'R0_Ohm', 'R1_Ohm', 'C1_F'});
writetable(interp_table, 'hppc_parameters_interpolated.csv');
fprintf('Données interpolées sauvegardées dans hppc_parameters_interpolated.csv\n');

fprintf('\n=== Analyse terminée ===\n');