% [Fichier renommé lors du rangement — ancien nom : test.m]
%% ========================================================================
%  NCR18650PF — Identification 1-RC ECM depuis données EIS réelles
%  + Simulation décharge 1C vs Datasheet Panasonic
%
%  ACTIA — Département Power Electronics / BMS Digital Twin
%  Auteur : Rami | Juin 2026
%
%  Format des fichiers EIS (Digatron / BaSyTec export) :
%    Préfixe : 3541_EIS00001.csv … 3541_EIS00014.csv
%    Séparateur : point-virgule (;)
%    Lignes 1-29  : métadonnées (ignorées)
%    Ligne 30     : en-têtes de colonnes
%    Ligne 31     : unités (ignorée)
%    Lignes 32+   : données
%    Colonnes utiles :
%      ActFreq  [Hz]   — fréquence mesurée
%      Zreal1   [mΩ]   — partie réelle de l'impédance
%      Zimg1    [mΩ]   — partie imaginaire (positive = inductif, négatif = capacitif)
%      Status   == 'EIS'  — filtre les lignes valides
%
%  Fichier TS (3541_TS003152.csv) :
%    Même format ; colonne AhAccu donne la capacité déchargée avant chaque EIS
%    SOC_k = 1 - |AhAccu_k| / C_nom
%    Correspondance : EIS00001→SOC100%, EIS00002→95%, …, EIS00014→5%
% ========================================================================

clear; clc; close all;

%% ── 0.  CHEMIN DOSSIER EIS ──────────────────────────────────────────────
EIS_FOLDER = fullfile('C:\Users\SAT\Desktop', 'EIS');

% Préfixe commun des fichiers EIS (ex : '3541_EIS')
EIS_PREFIX = '3541_EIS';

% Fichier de séquence de test (pour extraire les SOC)
TS_FILE = fullfile(EIS_FOLDER, '3541_TS003152.csv');

%% ── 1.  COURBE DE DÉCHARGE DATASHEET (1C, 25°C) — numérisée ────────────
cap_mAh_ds = [30.669 78.649 126.670 174.744 223.191 271.689 317.113 ...
    366.903 415.442 463.004 511.052 559.110 607.139 655.221 703.228 ...
    751.291 799.828 845.269 895.533 943.616 991.656 1039.692 1087.756 ...
    1135.805 1183.890 1231.926 1279.999 1328.013 1376.054 1424.124 ...
    1472.199 1520.298 1568.339 1616.389 1664.474 1712.571 1760.640 ...
    1808.696 1856.746 1904.804 1952.913 2000.975 2048.991 2095.770 ...
    2145.150 2193.641 2241.291 2289.333 2337.377 2385.432 2433.436 ...
    2481.460 2529.460 2577.389 2618.790 2655.719 2681.764 2701.214 ...
    2720.649 2737.889 2750.873]';

volt_ds = [4.035 3.989 3.959 3.949 3.915 3.900 3.880 3.858 3.840 ...
    3.820 3.801 3.785 3.758 3.751 3.716 3.702 3.702 3.689 3.680 ...
    3.674 3.652 3.627 3.614 3.594 3.589 3.565 3.554 3.522 3.500 ...
    3.488 3.479 3.479 3.457 3.438 3.432 3.431 3.420 3.403 3.384 ...
    3.368 3.372 3.358 3.326 3.323 3.311 3.293 3.288 3.266 3.245 ...
    3.228 3.192 3.163 3.125 3.060 3.006 2.915 2.841 2.755 2.662 ...
    2.566 2.515]';

C_nom = 2900;          % mAh — capacité nominale NCR18650PF
I_1C  = C_nom / 1000;  % A   = 2.90 A
SOC_ds = 1 - cap_mAh_ds / C_nom;

%% ── 2.  LECTURE DU FICHIER TS — EXTRACTION DES SOC ──────────────────────
fprintf('Lecture du fichier TS : %s\n', TS_FILE);
SOC_lut = read_soc_from_ts(TS_FILE, C_nom/1000);

if isempty(SOC_lut)
    error('Impossible de lire le fichier TS. Vérifier le chemin : %s', TS_FILE);
end

fprintf('✓  %d paliers SOC trouvés dans TS :\n', length(SOC_lut));
for k = 1:length(SOC_lut)
    fprintf('   EIS%05d → SOC = %.0f%%\n', k, SOC_lut(k)*100);
end

%% ── 3.  CHARGEMENT ET FIT EIS SUR CHAQUE FICHIER ────────────────────────
fprintf('\n%6s | %8s | %8s | %8s | %7s | %9s\n', ...
    'SOC', 'R0 mΩ', 'R1 mΩ', 'C1 F', 'τ1 s', 'RMSE mΩ');
fprintf('%s\n', repmat('-',1,60));

nb_files = length(SOC_lut);
SOC_f  = zeros(nb_files,1);
R0_f   = zeros(nb_files,1);
R1_f   = zeros(nb_files,1);
C1_f   = zeros(nb_files,1);
tau1_f = zeros(nb_files,1);
RMSE_f = zeros(nb_files,1);

for k = 1:nb_files
    fname = fullfile(EIS_FOLDER, sprintf('%s%05d.csv', EIS_PREFIX, k));

    if ~isfile(fname)
        warning('Fichier manquant : %s — palier ignoré.', fname);
        SOC_f(k) = NaN;
        continue;
    end

    [freq, Zre, Zim] = read_eis_digatron(fname);

    if length(freq) < 5
        warning('Données insuffisantes dans %s — palier ignoré.', fname);
        SOC_f(k) = NaN;
        continue;
    end

    soc = SOC_lut(k);
    [R0,R1,C1,tau1,rmse] = fit_eis_1rc(freq, Zre, Zim);

    SOC_f(k)  = soc;
    R0_f(k)   = R0;
    R1_f(k)   = R1;
    C1_f(k)   = C1;
    tau1_f(k) = tau1;
    RMSE_f(k) = rmse;

    fprintf('%5.0f%% | %8.2f | %8.2f | %8.1f | %7.3f | %9.4f\n', ...
        soc*100, R0*1e3, R1*1e3, C1, tau1, rmse*1e3);
end

% Supprimer paliers manquants et trier par SOC croissant
valid = ~isnan(SOC_f);
SOC_f  = SOC_f(valid);  R0_f  = R0_f(valid);
R1_f   = R1_f(valid);   C1_f  = C1_f(valid);
tau1_f = tau1_f(valid); RMSE_f= RMSE_f(valid);

[SOC_f, idx_s] = sort(SOC_f);
R0_f = R0_f(idx_s); R1_f = R1_f(idx_s);
C1_f = C1_f(idx_s); tau1_f = tau1_f(idx_s);

%% ── 4.  OCV CALIBRÉ ─────────────────────────────────────────────────────
R0_at_ds = interp1(SOC_f, R0_f, clamp(SOC_ds(:), min(SOC_f), max(SOC_f)), ...
                   'linear', 'extrap');
R1_at_ds = interp1(SOC_f, R1_f, clamp(SOC_ds(:), min(SOC_f), max(SOC_f)), ...
                   'linear', 'extrap');

OCV_raw = volt_ds(:) + I_1C * (R0_at_ds + R1_at_ds);

[SOC_ds_s, ids] = sort(SOC_ds(:));
OCV_sorted = OCV_raw(ids);
[SOC_ds_s, iu] = unique(SOC_ds_s, 'last');
OCV_sorted = OCV_sorted(iu);

n_pts = length(OCV_sorted);
if n_pts >= 11
    OCV_smooth = sgolay_filter(OCV_sorted, 3, 9);
else
    OCV_smooth = OCV_sorted;
end

for ki = 2:length(OCV_smooth)
    if OCV_smooth(ki) < OCV_smooth(ki-1)
        OCV_smooth(ki) = OCV_smooth(ki-1) + 1e-5;
    end
end
OCV_s = OCV_smooth;

fprintf('\nOCV calibré : %.4f V (SOC=%.0f%%) → %.4f V (SOC=%.0f%%)\n', ...
    OCV_s(1), SOC_ds_s(1)*100, OCV_s(end), SOC_ds_s(end)*100);

%% ── 5.  SIMULATION DÉCHARGE 1C — EULER ARRIÈRE ──────────────────────────
fprintf('\nSimulation décharge 1C ...\n');

dt      = 1.0;
SOC_sim = 0.99;
V_cut   = 2.5;
t_now   = 0.0;

sc0   = clamp(SOC_sim, min(SOC_f), max(SOC_f));
V_rc  = I_1C * interp1(SOC_f, R1_f, sc0, 'linear', 'extrap');

t_arr   = zeros(1,4000);
soc_arr = zeros(1,4000);
Vt_arr  = zeros(1,4000);
OCV_arr = zeros(1,4000);
ns = 0;

while SOC_sim > 0.005 && t_now < 7200
    sc  = clamp(SOC_sim, min(SOC_f), max(SOC_f));
    R0k = interp1(SOC_f, R0_f, sc, 'linear', 'extrap');
    R1k = interp1(SOC_f, R1_f, sc, 'linear', 'extrap');
    C1k = interp1(SOC_f, C1_f, sc, 'linear', 'extrap');

    tau1k = R1k * C1k;
    V_rc  = (V_rc + I_1C*R1k*dt/tau1k) / (1 + dt/tau1k);

    sc_ocv = clamp(SOC_sim, min(SOC_ds_s), max(SOC_ds_s));
    OCV    = interp1(SOC_ds_s, OCV_s, sc_ocv, 'pchip');

    Vt = OCV - I_1C*R0k - V_rc;

    ns = ns+1;
    if ns > length(t_arr)
        t_arr   = [t_arr,   zeros(1,4000)]; %#ok<AGROW>
        soc_arr = [soc_arr, zeros(1,4000)]; %#ok<AGROW>
        Vt_arr  = [Vt_arr,  zeros(1,4000)]; %#ok<AGROW>
        OCV_arr = [OCV_arr, zeros(1,4000)]; %#ok<AGROW>
    end
    t_arr(ns)   = t_now;
    soc_arr(ns) = SOC_sim;
    Vt_arr(ns)  = Vt;
    OCV_arr(ns) = OCV;

    if Vt <= V_cut, break; end

    SOC_sim = SOC_sim - I_1C*dt / (C_nom/1e3*3600);
    t_now   = t_now + dt;
end

t_arr   = t_arr(1:ns);
soc_arr = soc_arr(1:ns);
Vt_arr  = Vt_arr(1:ns);
OCV_arr = OCV_arr(1:ns);
cap_sim = (1 - soc_arr) * C_nom;

fprintf('  Capacité délivrée : %.0f mAh\n', cap_sim(end));
fprintf('  Durée simulation  : %.1f min\n', t_arr(end)/60);

%% ── 6.  MÉTRIQUES vs DATASHEET ──────────────────────────────────────────
cap_sim    = cap_sim(:);
Vt_arr     = Vt_arr(:);
OCV_arr    = OCV_arr(:);
cap_mAh_ds = cap_mAh_ds(:);
volt_ds    = volt_ds(:);

[cap_sim_u, iu2] = unique(cap_sim);
Vt_arr_u = Vt_arr(iu2);

Vt_at_ds = interp1(cap_sim_u, Vt_arr_u, cap_mAh_ds, 'linear', 'extrap');

SOC_at_ds = 1 - cap_mAh_ds / C_nom;
mask = (cap_mAh_ds >= cap_sim_u(1))  & ...
       (cap_mAh_ds <= cap_sim_u(end)) & ...
       (SOC_at_ds  >= 0.05);

err_mV = (Vt_at_ds(mask) - volt_ds(mask)) * 1e3;

MAE  = mean(abs(err_mV));
RMSE = sqrt(mean(err_mV.^2));
MAXE = max(abs(err_mV));

fprintf('\n  Comparaison vs datasheet (SOC > 5%%) :\n');
fprintf('  MAE  = %.1f mV\n', MAE);
fprintf('  RMSE = %.1f mV\n', RMSE);
fprintf('  MAX  = %.1f mV\n', MAXE);

%% ── 7.  FIGURES (THÈME CLAIR & FENÊTRES SÉPARÉES) ───────────────────────
% Palette de couleurs pour fond blanc
C_bg     = [1.00 1.00 1.00]; % Fond blanc
C_ax     = [1.00 1.00 1.00]; % Fond des axes blanc
C_grid   = [0.85 0.85 0.85]; % Grille gris clair
C_txt    = [0.15 0.15 0.15]; % Texte gris très foncé / noir
C_blue   = [0.000 0.447 0.741];
C_green  = [0.466 0.674 0.188];
C_orange = [0.850 0.325 0.098];
C_red    = [0.800 0.200 0.200];
C_purple = [0.494 0.184 0.556];

%% ── FIGURE 1 : DÉCHARGE 1C & OCV-SOC ────────────────────────────────────
fig1 = figure('Color', C_bg, 'Units','normalized', ...
    'Position',[0.05 0.1 0.45 0.8], 'Name','NCR18650PF – Décharge 1C & OCV');

sgtitle('NCR18650PF  |  Simulation Décharge 1C & OCV  @  25°C', ...
    'Color', C_txt, 'FontSize', 13, 'FontWeight', 'bold');

% P1 : Décharge 1C
ax1 = subplot(2,1,1); hold on;
set(ax1,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
fill([cap_mAh_ds(mask); flipud(cap_mAh_ds(mask))], ...
     [volt_ds(mask);    flipud(Vt_at_ds(mask))], ...
     C_red,'FaceAlpha',0.15,'EdgeColor','none');
p1 = plot(cap_mAh_ds, volt_ds, 'o', 'Color',C_orange, 'MarkerSize',6, ...
    'MarkerFaceColor',C_orange, 'DisplayName','Datasheet 1C (numérisé)');
p2 = plot(cap_sim_u, Vt_arr_u, '-', 'Color',C_blue, 'LineWidth',2.2, ...
    'DisplayName','ECM 1-RC simulation');
p3 = plot(cap_sim_u, OCV_arr(iu2),'--','Color',C_green,'LineWidth',1.5,...
    'DisplayName','OCV (ECM)');
yline(2.5,'Color',C_red,'LineStyle',':','LineWidth',1.2,'DisplayName','Seuil 2.5 V');
xlim([0 2900]); ylim([2.3 4.25]);
xlabel('Capacité déchargée [mAh]','Color',C_txt,'FontSize',11);
ylabel('Tension [V]','Color',C_txt,'FontSize',11);
title('Décharge 1C : simulation ECM vs Datasheet','Color',C_txt,...
    'FontWeight','bold','FontSize',12);
lg = legend([p1 p2 p3],'Location','southwest','FontSize',10);
set(lg,'Color',C_ax,'TextColor',C_txt,'EdgeColor',C_grid);
txt_m = sprintf('MAE = %.1f mV  |  RMSE = %.1f mV  |  MAX = %.1f mV', MAE, RMSE, MAXE);
text(50, 2.45, txt_m, 'Color',C_blue,'FontSize',11,'FontWeight','bold');

% P2 : OCV-SOC
ax2 = subplot(2,1,2); hold on;
set(ax2,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
soc_fine = linspace(0.04, 1.0, 400);
OCV_fine = interp1(SOC_ds_s, OCV_s, soc_fine, 'pchip', 'extrap');
plot(soc_fine*100, OCV_fine, '-','Color',C_blue,'LineWidth',2.2,...
    'DisplayName','OCV(SOC) interpolé');
scatter(SOC_ds*100, OCV_raw, 25, C_orange, 'filled',...
    'DisplayName','Points bruts (Vt+I(R0+R1))');
xlabel('SOC [%]','Color',C_txt,'FontSize',11);
ylabel('OCV [V]','Color',C_txt,'FontSize',11);
title('Caractéristique OCV – SOC','Color',C_txt,'FontWeight','bold','FontSize',12);
xlim([0 105]);
lg2 = legend('Location','northwest','FontSize',10);
set(lg2,'Color',C_ax,'TextColor',C_txt,'EdgeColor',C_grid);


%% ── FIGURE 2 : PARAMÈTRES ECM vs SOC ────────────────────────────────────
fig2 = figure('Color', C_bg, 'Units','normalized', ...
    'Position',[0.52 0.1 0.45 0.8], 'Name','NCR18650PF – Paramètres ECM 1-RC');

sgtitle('NCR18650PF  |  Paramètres ECM 1-RC vs SOC  @  25°C', ...
    'Color', C_txt, 'FontSize', 13, 'FontWeight', 'bold');

% P3 : R0 vs SOC
ax3 = subplot(2,2,1); hold on;
set(ax3,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
plot(SOC_f*100, R0_f*1e3, 'o-','Color',C_blue,'MarkerSize',7,...
    'MarkerFaceColor',C_blue,'LineWidth',1.8);
xlabel('SOC [%]','Color',C_txt,'FontSize',11);
ylabel('R₀ [mΩ]','Color',C_txt,'FontSize',11);
title('Résistance Ohmique  R₀','Color',C_txt,'FontWeight','bold','FontSize',12);
xlim([0 105]);

% P4 : R1 vs SOC
ax4 = subplot(2,2,2); hold on;
set(ax4,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
plot(SOC_f*100, R1_f*1e3, 's-','Color',C_purple,'MarkerSize',7,...
    'MarkerFaceColor',C_purple,'LineWidth',1.8);
xlabel('SOC [%]','Color',C_txt,'FontSize',11);
ylabel('R₁ [mΩ]','Color',C_txt,'FontSize',11);
title('Résistance de transfert  R₁','Color',C_txt,'FontWeight','bold','FontSize',12);
xlim([0 105]);

% P5 : τ1 vs SOC
ax5 = subplot(2,2,3); hold on;
set(ax5,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
plot(SOC_f*100, tau1_f, '^-','Color',C_green,'MarkerSize',7,...
    'MarkerFaceColor',C_green,'LineWidth',1.8);
xlabel('SOC [%]','Color',C_txt,'FontSize',11);
ylabel('τ₁ = R₁·C₁ [s]','Color',C_txt,'FontSize',11);
title('Constante de temps  τ₁','Color',C_txt,'FontWeight','bold','FontSize',12);
xlim([0 105]);

% P6 : C1 vs SOC
ax6 = subplot(2,2,4); hold on;
set(ax6,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,'GridAlpha',0.7,'Box','on','FontSize',10);
grid on;
plot(SOC_f*100, C1_f, 'd-','Color',C_orange,'MarkerSize',7,...
    'MarkerFaceColor',C_orange,'LineWidth',1.8);
xlabel('SOC [%]','Color',C_txt,'FontSize',11);
ylabel('C₁ [F]','Color',C_txt,'FontSize',11);
title('Capacité double couche  C₁','Color',C_txt,'FontWeight','bold','FontSize',12);
xlim([0 105]);

% Application du fond blanc à tous les axes des deux figures
set(findobj(fig1,'Type','axes'),'Color',C_ax);
set(findobj(fig2,'Type','axes'),'Color',C_ax);


%% ── 8.  TABLEAU RÉCAPITULATIF ────────────────────────────────────────────
fprintf('\n%s\n', repmat('═',1,72));
fprintf('  NCR18650PF  |  PARAMÈTRES ECM 1-RC  @  25°C  (données EIS réelles)\n');
fprintf('%s\n', repmat('═',1,72));
fprintf('  %5s  %8s  %8s  %8s  %8s  %7s\n', ...
    'SOC','R0 mΩ','R1 mΩ','C1 F','τ1 s','OCV V');
fprintf('%s\n', repmat('─',1,72));
for k = 1:length(SOC_f)
    sc = SOC_f(k);
    ocv_k = interp1(SOC_ds_s, OCV_s, clamp(sc, min(SOC_ds_s), max(SOC_ds_s)),'pchip','extrap');
    fprintf('  %4.0f%%  %8.2f  %8.2f  %8.1f  %8.3f  %7.4f\n', ...
        sc*100, R0_f(k)*1e3, R1_f(k)*1e3, C1_f(k), tau1_f(k), ocv_k);
end
fprintf('%s\n', repmat('═',1,72));
fprintf('  Décharge 1C = %.2f A  |  V_coupure = %.1f V\n', I_1C, V_cut);
fprintf('  Capacité délivrée : %.0f mAh\n', cap_sim_u(end));
fprintf('  MAE  = %.1f mV  |  RMSE = %.1f mV  |  MAX = %.1f mV\n', MAE, RMSE, MAXE);
fprintf('%s\n', repmat('═',1,72));


%% ════════════════════════════════════════════════════════════════════════
%                          FONCTIONS LOCALES
%% ════════════════════════════════════════════════════════════════════════

% ── Lecture SOC depuis fichier TS Digatron ────────────────────────────────
function SOC_lut = read_soc_from_ts(ts_path, C_nom_Ah)
    SOC_lut = [];
    if ~isfile(ts_path)
        warning('Fichier TS introuvable : %s', ts_path);
        return;
    end

    fid = fopen(ts_path, 'r', 'n', 'latin1');
    header_line = -1;
    line_num = 0;
    while ~feof(fid)
        line = fgetl(fid);
        line_num = line_num + 1;
        if contains(line, 'Time Stamp') && contains(line, 'AhAccu')
            header_line = line_num;
            break;
        end
    end
    fclose(fid);

    if header_line < 0
        warning('En-tête "Time Stamp;AhAccu" non trouvé dans TS.');
        return;
    end

    opts = detectImportOptions(ts_path, 'FileType','text', ...
        'Delimiter',';', 'Encoding','latin1');
    opts.DataLines         = [header_line+2, Inf];
    opts.VariableNamesLine = header_line;

    try
        T = readtable(ts_path, opts, 'VariableNamingRule', 'preserve');
    catch
        T = readtable(ts_path, opts);
    end

    col_names_orig = T.Properties.VariableDescriptions;
    col_names_var  = T.Properties.VariableNames;

    all_names = [col_names_var, col_names_orig];
    n_vars    = length(col_names_var);

    find_col = @(kw) find( ...
        contains(col_names_var, kw, 'IgnoreCase', true) | ...
        contains(col_names_orig, kw, 'IgnoreCase', true), 1);

    ah_col = find_col('AhAccu');
    st_col = find_col('Status');

    if isempty(ah_col)
        fid2 = fopen(ts_path, 'r', 'n', 'latin1');
        for li = 1:header_line-1, fgetl(fid2); end
        hdr_line = fgetl(fid2);
        fclose(fid2);
        hdr_parts = strsplit(hdr_line, ';');
        hdr_parts = strtrim(hdr_parts);
        ah_col = find(strcmpi(hdr_parts, 'AhAccu'), 1);
        st_col = find(strcmpi(hdr_parts, 'Status'), 1);
        if isempty(ah_col)
            warning('Colonne AhAccu non trouvée dans TS.');
            return;
        end
    end

    AhAccu = str2double(string(table2array(T(:, ah_col))));

    if ~isempty(st_col)
        Status = string(table2array(T(:, st_col)));
        mask   = strcmp(strtrim(Status), 'EIS');
    else
        mask = isfinite(AhAccu);
    end

    AhAccu_eis = AhAccu(mask);
    SOC_lut = 1 - abs(AhAccu_eis) / C_nom_Ah;
    SOC_lut = SOC_lut(:);
end

% ── Lecture fichier EIS Digatron ──────────────────────────────────────────
function [freq, Zre, Zim] = read_eis_digatron(fpath)
    freq = []; Zre = []; Zim = [];

    fid = fopen(fpath, 'r', 'n', 'latin1');
    header_line = -1;
    line_num = 0;
    while ~feof(fid)
        line = fgetl(fid);
        line_num = line_num + 1;
        if contains(line, 'ActFreq') && contains(line, 'Zreal1')
            header_line = line_num;
            break;
        end
    end
    fclose(fid);

    if header_line < 0
        warning('En-tête ActFreq/Zreal1 non trouvé dans : %s', fpath);
        return;
    end

    opts = detectImportOptions(fpath, 'FileType','text', ...
        'Delimiter',';', 'Encoding','latin1');
    opts.DataLines      = [header_line+2, Inf];
    opts.VariableNamesLine = header_line;

    try
        T = readtable(fpath, opts, 'VariableNamingRule', 'preserve');
    catch
        T = readtable(fpath, opts);
    end

    col_names_var  = T.Properties.VariableNames;
    col_names_orig = T.Properties.VariableDescriptions;

    find_col = @(kw) find( ...
        contains(col_names_var,  kw, 'IgnoreCase', true) | ...
        contains(col_names_orig, kw, 'IgnoreCase', true), 1);

    f_col  = find_col('ActFreq');
    zr_col = find_col('Zreal1');
    zi_col = find_col('Zimg1');
    st_col = find_col('Status');

    if isempty(f_col) || isempty(zr_col) || isempty(zi_col)
        fid2 = fopen(fpath, 'r', 'n', 'latin1');
        for li = 1:header_line-1, fgetl(fid2); end
        hdr_line = fgetl(fid2);
        fclose(fid2);
        hdr_parts = strtrim(strsplit(hdr_line, ';'));
        f_col  = find(strcmpi(hdr_parts, 'ActFreq'), 1);
        zr_col = find(strcmpi(hdr_parts, 'Zreal1'),  1);
        zi_col = find(strcmpi(hdr_parts, 'Zimg1'),   1);
        st_col = find(strcmpi(hdr_parts, 'Status'),  1);
        if isempty(f_col) || isempty(zr_col) || isempty(zi_col)
            warning('Colonnes ActFreq/Zreal1/Zimg1 manquantes : %s', fpath);
            return;
        end
    end

    F  = str2double(string(table2array(T(:, f_col))));
    ZR = str2double(string(table2array(T(:, zr_col))));
    ZI = str2double(string(table2array(T(:, zi_col))));

    if ~isempty(st_col)
        Status = string(table2array(T(:, st_col)));
        ok = strcmp(Status, 'EIS') & isfinite(F) & isfinite(ZR) & isfinite(ZI) & (F > 0);
    else
        ok = isfinite(F) & isfinite(ZR) & isfinite(ZI) & (F > 0);
    end

    if sum(ok) < 5
        warning('Moins de 5 points valides dans : %s', fpath);
        return;
    end

    freq = F(ok);
    Zre  = ZR(ok) / 1000;
    Zim  = ZI(ok) / 1000;

    [freq, ord] = sort(freq, 'descend');
    Zre = Zre(ord);
    Zim = Zim(ord);
end

% ── Modèle complexe 1-RC Z(f) ────────────────────────────────────────────
function Z = eis_model_complex(freq, R0, R1, C1)
    w = 2*pi*freq;
    Z = R0 + R1./(1 + 1j*w*R1*C1);
end

% ── Vecteur résidu pour optimisation ─────────────────────────────────────
function v = eis_residual_vec(params, freq, Zre, Zim)
    R0=params(1); R1=params(2); C1=params(3);
    if R0<=0||R1<=0||C1<=0, v=1e6*ones(2*length(freq),1); return; end
    Z = eis_model_complex(freq, R0, R1, C1);
    v = [real(Z)-Zre; imag(Z)-Zim];
end

% ── Fit 1-RC depuis données EIS ───────────────────────────────────────────
function [R0,R1,C1,tau1,rmse] = fit_eis_1rc(freq, Zre, Zim)
    [~, ihf] = max(freq);
    [~, ilf] = min(freq);
    R0_0 = Zre(ihf);
    R1_0 = max(0.001, Zre(ilf) - R0_0);
    C1_0 = 120;

    cost = @(p) sum(eis_residual_vec(p, freq, Zre, Zim).^2);

    opts = optimset('TolX',1e-9,'TolFun',1e-11,'MaxFunEvals',80000,...
        'MaxIter',80000,'Display','off');
    params = fminsearch(cost, [R0_0, R1_0, C1_0], opts);

    R0 = params(1); R1 = params(2); C1 = params(3);
    tau1 = R1 * C1;
    v    = eis_residual_vec(params, freq, Zre, Zim);
    rmse = sqrt(mean(v.^2));
end

% ── Clamp scalaire ───────────────────────────────────────────────────────
function y = clamp(x, lo, hi)
    y = max(lo, min(hi, x));
end

% ── Filtre de Savitzky-Golay ─────────────────────────────────────────────
function ys = sgolay_filter(y, p, w)
    y  = y(:);
    n  = length(y);
    ys = y;
    half = (w-1)/2;
    for i = 1:n
        i1 = max(1, i-half);
        i2 = min(n, i+half);
        seg  = y(i1:i2);
        xseg = (i1:i2)' - i;
        Aseg = ones(length(seg), p+1);
        for k = 1:p
            Aseg(:,k+1) = xseg.^k;
        end
        Hseg = (Aseg'*Aseg) \ Aseg';
        ys(i) = Hseg(1,:) * seg;
    end
end