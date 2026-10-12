% [Fichier renommé lors du rangement — ancien nom : hppc_v2.m]
%% simuler_HPPC_multi_temperature.m
% Lance la simulation HPPC pour plusieurs températures fixées,
% extrait R0, R1, C1, OCV = f(SOC) à chaque température,
% puis superpose les courbes pour comparaison.
%
% PRE-REQUIS :
%   - generer_signal_HPPC.m déjà exécuté (variable HPPC_signal en workspace)
%   - Le modèle Simulink "modele_nmc" a un bloc/port permettant de fixer
%     la température de la cellule (ex: bloc "Thermal Mass" ou
%     "Controlled Temperature Source" connecté au port thermique H du
%     bloc Battery Equivalent Circuit). Adapter le NOM du bloc temperature
%     ci-dessous à votre schéma exact.
%
% SORTIE :
%   - all_results : structure contenant, pour chaque température, la
%     table HPPC_params correspondante
%   - Figure comparative avec une courbe par température pour R0, R1, C1, OCV

clear all_results

%% ---------------- PARAMETRES ----------------
model_name   = 'modele_nmc';                 % nom de votre modèle Simulink
temp_block   = [model_name '/Temperature'];  % ADAPTER : chemin du bloc fixant T (°C ou K)
T_list_degC  = [0, 25, 45];                  % températures à tester (°C)
sim_stop_time = [];                          % laisser vide -> auto (durée de HPPC_signal)

% Charger le modèle si pas déjà ouvert
load_system(model_name);

% Durée de simulation = durée du profil HPPC_signal + marge
if isempty(sim_stop_time)
    sim_stop_time = HPPC_signal.Time(end) + 10;
end
set_param(model_name, 'StopTime', num2str(sim_stop_time));

%% ---------------- BOUCLE SUR LES TEMPERATURES ----------------
all_results = struct();

for kT = 1:length(T_list_degC)

    T_degC = T_list_degC(kT);
    T_K = T_degC + 273.15;

    fprintf('\n=== Simulation HPPC à T = %d°C ===\n', T_degC);

    % --- Fixer la température dans le modèle ---
    % ADAPTER cette ligne selon votre bloc : exemple si c'est une
    % "Constant" en Kelvin reliée au port thermique :
    try
        set_param(temp_block, 'Value', num2str(T_K));
    catch ME
        warning('Impossible de régler %s automatiquement : %s\nRéglez la température manuellement dans le modèle avant de continuer.', ...
            temp_block, ME.message);
    end

    % --- Lancer la simulation ---
    simOut = sim(model_name);

    % --- Récupérer les signaux ---
    % Adapter si vos signaux sont accessibles différemment
    out = simOut;   % pour compatibilité avec extract_HPPC_params.m

    % --- Extraction des paramètres pour cette température ---
    run('extract_HPPC_params.m');   % réutilise le script d'extraction, produit HPPC_params

    % --- Stockage ---
    field_name = sprintf('T_%ddegC', T_degC);
    all_results.(field_name) = HPPC_params;
    all_results.(field_name).Properties.UserData = struct('Temperature_degC', T_degC);

end

%% ---------------- TRACE COMPARATIF MULTI-TEMPERATURE ----------------
colors = lines(length(T_list_degC));

figure('Name','Parametres ECM vs SOC - multi-temperature','Position',[100 100 900 700]);

ax1 = subplot(2,2,1); hold(ax1,'on'); grid(ax1,'on');
ax2 = subplot(2,2,2); hold(ax2,'on'); grid(ax2,'on');
ax3 = subplot(2,2,3); hold(ax3,'on'); grid(ax3,'on');
ax4 = subplot(2,2,4); hold(ax4,'on'); grid(ax4,'on');

legend_labels = {};

for kT = 1:length(T_list_degC)
    T_degC = T_list_degC(kT);
    field_name = sprintf('T_%ddegC', T_degC);
    Tbl = all_results.(field_name);

    Tbl_dis = Tbl(strcmp(Tbl.type,"decharge"),:);
    Tbl_dis = sortrows(Tbl_dis,'SOC');

    plot(ax1, Tbl_dis.SOC, Tbl_dis.R0*1000, 'o-','Color',colors(kT,:),'LineWidth',1.3);
    plot(ax2, Tbl_dis.SOC, Tbl_dis.R1*1000, 'o-','Color',colors(kT,:),'LineWidth',1.3);
    plot(ax3, Tbl_dis.SOC, Tbl_dis.C1, 'o-','Color',colors(kT,:),'LineWidth',1.3);
    plot(ax4, Tbl_dis.SOC, Tbl_dis.OCV, 'o-','Color',colors(kT,:),'LineWidth',1.3);

    legend_labels{end+1} = sprintf('%d°C', T_degC); %#ok<SAGROW>
end

xlabel(ax1,'SOC (%)'); ylabel(ax1,'R0 (m\Omega)'); title(ax1,'R0 vs SOC'); legend(ax1, legend_labels,'Location','best');
xlabel(ax2,'SOC (%)'); ylabel(ax2,'R1 (m\Omega)'); title(ax2,'R1 vs SOC'); legend(ax2, legend_labels,'Location','best');
xlabel(ax3,'SOC (%)'); ylabel(ax3,'C1 (F)');       title(ax3,'C1 vs SOC'); legend(ax3, legend_labels,'Location','best');
xlabel(ax4,'SOC (%)'); ylabel(ax4,'OCV (V)');       title(ax4,'OCV vs SOC'); legend(ax4, legend_labels,'Location','best');

save('HPPC_multi_temperature_results.mat','all_results');
fprintf('\nTermine. Resultats sauvegardes dans HPPC_multi_temperature_results.mat\n');