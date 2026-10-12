% [Fichier renommé lors du rangement — ancien nom : dsicharge_datasheet.m]
%% ========================================================================
%  VISUALISATION DATASET EIS — NCR18650PF (Digatron)
%  ACTIA — Département Power Electronics / BMS Digital Twin
%  Auteur : Rami | Juin 2026
%  Thème : fond blanc, présentation rapport
%
%  Génère 4 figures :
%    Fig 1 : Grille de diagrammes de Nyquist (tous les SOC)
%    Fig 2 : Évolution Re(Z) et -Im(Z) max vs SOC
%    Fig 3 : Diagrammes de Bode (magnitude et phase)
%    Fig 4 : Statistiques récapitulatives
% ========================================================================

clear; clc; close all;
warning('off', 'MATLAB:table:ModifiedDuplicateVarNames');

%% ── 0.  CHEMIN DOSSIER EIS ──────────────────────────────────────────────
EIS_FOLDER = fullfile('C:\Users\SAT\Desktop', 'EIS');
EIS_PREFIX = '3541_EIS';
TS_FILE    = fullfile(EIS_FOLDER, '3541_TS003152.csv');

if ~isfolder(EIS_FOLDER)
    error('Dossier EIS introuvable : %s', EIS_FOLDER);
end

files_eis = dir(fullfile(EIS_FOLDER, [EIS_PREFIX '*.csv']));
nb_files  = length(files_eis);
fprintf('📁  Dossier EIS : %s\n', EIS_FOLDER);
fprintf('📊  %d fichiers EIS trouvés\n\n', nb_files);

%% ── 1.  LECTURE DU FICHIER TS (pour les SOC) ────────────────────────────
C_nom = 2900;  % mAh
SOC_lut = read_soc_from_ts(TS_FILE, C_nom/1000);

if isempty(SOC_lut)
    warning('Fichier TS non lu, utilisation de SOC estimés (100% → 5%)');
    SOC_lut = linspace(1.0, 0.05, nb_files)';
else
    fprintf('✓  %d paliers SOC extraits du TS\n', length(SOC_lut));
end

%% ── 2.  CHARGEMENT DE TOUS LES FICHIERS EIS ─────────────────────────────
fprintf('\nChargement des données EIS...\n');
fprintf('%6s | %8s | %8s | %8s | %8s | %8s\n', ...
    'SOC', 'N pts', 'f_min Hz', 'f_max Hz', 'Re_max mΩ', '-Im_max mΩ');
fprintf('%s\n', repmat('-',1,65));

EIS_data = struct('soc',{}, 'freq',{}, 'Zre',{}, 'Zim',{}, ...
                  'fname',{}, 'Re_max',{}, 'Im_max',{});

for k = 1:nb_files
    fpath = fullfile(EIS_FOLDER, files_eis(k).name);
    [freq, Zre, Zim] = read_eis_digatron(fpath);
    
    if length(freq) < 5
        warning('Fichier %s : données insuffisantes', files_eis(k).name);
        continue;
    end
    
    soc = SOC_lut(k);
    EIS_data(k).soc    = soc;
    EIS_data(k).freq   = freq;
    EIS_data(k).Zre    = Zre;
    EIS_data(k).Zim    = Zim;
    EIS_data(k).fname  = files_eis(k).name;
    EIS_data(k).Re_max = max(Zre)*1e3;
    EIS_data(k).Im_max = max(-Zim)*1e3;
    
    fprintf('%5.1f%% | %8d | %8.2f | %8.1f | %8.3f | %8.3f\n', ...
        soc*100, length(freq), min(freq), max(freq), ...
        max(Zre)*1e3, max(-Zim)*1e3);
end

EIS_data = EIS_data(~cellfun('isempty', {EIS_data.freq}));
n_valid  = length(EIS_data);

%% ── 3.  COULEURS ET THÈME (FOND BLANC — RAPPORT) ────────────────────────
C_blue   = [0.000 0.447 0.741];
C_green  = [0.301 0.600 0.240];
C_orange = [0.850 0.325 0.098];
C_red    = [0.750 0.100 0.100];
C_purple = [0.494 0.184 0.556];
C_bg     = [1.000 1.000 1.000];   % fond figure blanc
C_ax     = [1.000 1.000 1.000];   % fond axes blanc
C_grid   = [0.850 0.850 0.850];   % grille gris clair
C_txt    = [0.100 0.100 0.100];   % texte quasi noir

% Palette de couleurs pour les SOC (colormap lisible sur fond blanc)
cmap = parula(n_valid) * 0.85;   % assombrie légèrement pour contraste

%% ── FIGURE 1 : GRILLE DE NYQUIST ────────────────────────────────────────
fig1 = figure('Color', C_bg, 'Name', 'Nyquist plots — Tous les SOC', ...
    'Units','normalized', 'Position',[0.05 0.05 0.90 0.85]);

sgtitle('Diagrammes de Nyquist — NCR18650PF EIS vs SOC  @ 25°C', ...
    'Color', C_txt, 'FontSize', 14, 'FontWeight', 'bold');

ncols = 4;
nrows = ceil(n_valid / ncols);

for k = 1:n_valid
    ax = subplot(nrows, ncols, k);
    hold on;
    set(ax,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
        'GridAlpha',0.7,'Box','on','FontSize',8);
    grid on; axis equal;
    
    Zre = EIS_data(k).Zre;
    Zim = EIS_data(k).Zim;
    
    plot(Zre*1e3, -Zim*1e3, '-o', 'Color', cmap(k,:), ...
        'MarkerSize', 2.5, 'LineWidth', 1.2, 'MarkerFaceColor', cmap(k,:));
    
    plot(Zre(1)*1e3, -Zim(1)*1e3, 'p', 'Color', C_green, ...
        'MarkerSize', 8, 'MarkerFaceColor', C_green);
    plot(Zre(end)*1e3, -Zim(end)*1e3, 's', 'Color', C_red, ...
        'MarkerSize', 8, 'MarkerFaceColor', C_red);
    
    xlabel('Re(Z) [mΩ]', 'Color', C_txt, 'FontSize', 7);
    ylabel('-Im(Z) [mΩ]', 'Color', C_txt, 'FontSize', 7);
    title(sprintf('SOC = %.0f%%', EIS_data(k).soc*100), ...
        'Color', C_txt, 'FontSize', 9, 'FontWeight', 'bold');
    set(gca, 'FontSize', 7);
end

annotation('textbox', [0.85 0.02 0.1 0.05], ...
    'String', sprintf('● HF (vert)\n● BF (rouge)'), ...
    'Color', C_txt, 'BackgroundColor', C_ax, 'EdgeColor', C_grid, ...
    'FontSize', 8);

%% ── FIGURE 2 : ÉVOLUTION DES PARAMÈTRES vs SOC ─────────────────────────
fig2 = figure('Color', C_bg, 'Name', 'Paramètres EIS vs SOC', ...
    'Units','normalized', 'Position',[0.08 0.10 0.85 0.80]);

sgtitle('Évolution des paramètres EIS vs SOC — NCR18650PF', ...
    'Color', C_txt, 'FontSize', 14, 'FontWeight', 'bold');

socs = [EIS_data.soc] * 100;
Re_max = [EIS_data.Re_max];
Im_max = [EIS_data.Im_max];

% P1 : Re(Z) max vs SOC
ax1 = subplot(2,2,1); hold on;
set(ax1,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on');
grid on;
plot(socs, Re_max, 'o-', 'Color', C_blue, 'LineWidth', 2, ...
    'MarkerSize', 8, 'MarkerFaceColor', C_blue);
xlabel('SOC [%]', 'Color', C_txt, 'FontSize', 10);
ylabel('Re(Z)_{max} [mΩ]', 'Color', C_txt, 'FontSize', 10);
title('Résistance totale (BF) vs SOC', 'Color', C_txt, 'FontWeight', 'bold');
xlim([0 105]);

% P2 : -Im(Z) max vs SOC
ax2 = subplot(2,2,2); hold on;
set(ax2,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on');
grid on;
plot(socs, Im_max, 's-', 'Color', C_orange, 'LineWidth', 2, ...
    'MarkerSize', 8, 'MarkerFaceColor', C_orange);
xlabel('SOC [%]', 'Color', C_txt, 'FontSize', 10);
ylabel('-Im(Z)_{max} [mΩ]', 'Color', C_txt, 'FontSize', 10);
title('Hauteur du demi-cercle vs SOC', 'Color', C_txt, 'FontWeight', 'bold');
xlim([0 105]);

% P3 : Superposition Nyquist (tous les SOC)
ax3 = subplot(2,2,3); hold on;
set(ax3,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on');
grid on; axis equal;
for k = 1:n_valid
    plot(EIS_data(k).Zre*1e3, -EIS_data(k).Zim*1e3, '-', ...
        'Color', cmap(k,:), 'LineWidth', 1.5);
end
xlabel('Re(Z) [mΩ]', 'Color', C_txt, 'FontSize', 10);
ylabel('-Im(Z) [mΩ]', 'Color', C_txt, 'FontSize', 10);
title('Superposition Nyquist — Tous les SOC', 'Color', C_txt, 'FontWeight', 'bold');

col_vals = linspace(min(socs), max(socs), n_valid);
scatter(Re_max(end), Im_max(end), 1, col_vals, 'filled', 'Marker', 'none');
cb = colorbar;
cb.Label.String = 'SOC [%]';
cb.Label.Color  = C_txt;
cb.Color = C_txt;

% P4 : Re(Z) à HF vs SOC (R0 approximatif)
ax4 = subplot(2,2,4); hold on;
set(ax4,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on');
grid on;

Re_HF = zeros(n_valid, 1);
for k = 1:n_valid
    [~, ihf] = max(EIS_data(k).freq);
    Re_HF(k) = EIS_data(k).Zre(ihf) * 1e3;
end
plot(socs, Re_HF, '^-', 'Color', C_green, 'LineWidth', 2, ...
    'MarkerSize', 8, 'MarkerFaceColor', C_green);
xlabel('SOC [%]', 'Color', C_txt, 'FontSize', 10);
ylabel('Re(Z)_{HF} [mΩ] ≈ R_0', 'Color', C_txt, 'FontSize', 10);
title('Résistance ohmique R_0 vs SOC', 'Color', C_txt, 'FontWeight', 'bold');
xlim([0 105]);

%% ── FIGURE 3 : DIAGRAMMES DE BODE ──────────────────────────────────────
fig3 = figure('Color', C_bg, 'Name', 'Diagrammes de Bode', ...
    'Units','normalized', 'Position',[0.08 0.10 0.85 0.80]);

sgtitle('Diagrammes de Bode — NCR18650PF EIS vs SOC  @ 25°C', ...
    'Color', C_txt, 'FontSize', 14, 'FontWeight', 'bold');

% P1 : Magnitude |Z| vs freq
ax_b1 = subplot(2,1,1); hold on;
set(ax_b1,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on','XScale','log');
grid on;

for k = 1:n_valid
    freq = EIS_data(k).freq;
    Zmag = sqrt(EIS_data(k).Zre.^2 + EIS_data(k).Zim.^2) * 1e3;
    semilogx(freq, Zmag, '-', 'Color', cmap(k,:), 'LineWidth', 1.5, ...
        'DisplayName', sprintf('SOC %.0f%%', EIS_data(k).soc*100));
end
xlabel('Fréquence [Hz]', 'Color', C_txt, 'FontSize', 10);
ylabel('|Z| [mΩ]', 'Color', C_txt, 'FontSize', 10);
title('Magnitude de l''impédance', 'Color', C_txt, 'FontWeight', 'bold');
lg1 = legend('Location','best','FontSize',7,'NumColumns',3);
set(lg1,'Color',C_ax,'TextColor',C_txt,'EdgeColor',C_grid);

% P2 : Phase vs freq
ax_b2 = subplot(2,1,2); hold on;
set(ax_b2,'Color',C_ax,'XColor',C_txt,'YColor',C_txt,'GridColor',C_grid,...
    'GridAlpha',0.7,'Box','on','XScale','log');
grid on;

for k = 1:n_valid
    freq = EIS_data(k).freq;
    Z    = EIS_data(k).Zre + 1j*EIS_data(k).Zim;
    phase = angle(Z) * 180/pi;
    semilogx(freq, phase, '-', 'Color', cmap(k,:), 'LineWidth', 1.5);
end
xlabel('Fréquence [Hz]', 'Color', C_txt, 'FontSize', 10);
ylabel('Phase [°]', 'Color', C_txt, 'FontSize', 10);
title('Phase de l''impédance', 'Color', C_txt, 'FontWeight', 'bold');
yline(0, 'Color', C_txt, 'LineStyle', '--', 'LineWidth', 0.8);

%% ── FIGURE 4 : STATISTIQUES ET TABLEAU ──────────────────────────────────
fig4 = figure('Color', C_bg, 'Name', 'Statistiques EIS', ...
    'Units','normalized', 'Position',[0.15 0.15 0.70 0.70]);

T = table();
T.SOC = [EIS_data.soc]' * 100;
T.N_Pts = cellfun(@length, {EIS_data.freq});
T.f_min = cellfun(@min, {EIS_data.freq});
T.f_max = cellfun(@max, {EIS_data.freq});
T.Re_max_mOhm = [EIS_data.Re_max]';
T.Im_max_mOhm = [EIS_data.Im_max]';
T.R0_mOhm = zeros(n_valid, 1);
for k = 1:n_valid
    [~, ihf] = max(EIS_data(k).freq);
    T.R0_mOhm(k) = EIS_data(k).Zre(ihf) * 1e3;
end

fprintf('\n%s\n', repmat('═',1,85));
fprintf('  STATISTIQUES DATASET EIS — NCR18650PF  @  25°C\n');
fprintf('%s\n', repmat('═',1,85));
fprintf('  %5s | %6s | %9s | %9s | %9s | %9s | %9s\n', ...
    'SOC', 'N pts', 'f_min Hz', 'f_max Hz', 'Re_max', 'Im_max', 'R0 (HF)');
fprintf('%s\n', repmat('─',1,85));
for k = 1:n_valid
    fprintf('  %4.1f%% | %6d | %9.2f | %9.1f | %8.2f | %8.2f | %8.2f\n', ...
        T.SOC(k), T.N_Pts(k), T.f_min(k), T.f_max(k), ...
        T.Re_max_mOhm(k), T.Im_max_mOhm(k), T.R0_mOhm(k));
end
fprintf('%s\n', repmat('═',1,85));

ax_t = axes('Position', [0.05 0.05 0.90 0.85]);
set(ax_t, 'Color', C_bg, 'Visible', 'off');

text(0.5, 0.95, 'STATISTIQUES DATASET EIS — NCR18650PF', ...
    'Units','normalized', 'HorizontalAlignment','center', ...
    'Color', C_txt, 'FontSize', 14, 'FontWeight', 'bold');

text(0.5, 0.88, sprintf('Dossier : %s', EIS_FOLDER), ...
    'Units','normalized', 'HorizontalAlignment','center', ...
    'Color', C_orange, 'FontSize', 10);

text(0.5, 0.82, sprintf('Nombre de fichiers : %d', n_valid), ...
    'Units','normalized', 'HorizontalAlignment','center', ...
    'Color', C_txt, 'FontSize', 11);

txt_stats = sprintf(['Plage de fréquence : %.2f Hz — %.0f Hz\n', ...
                     'SOC couverts : %.0f%% — %.0f%%\n', ...
                     'Re(Z) max : %.2f — %.2f mΩ\n', ...
                     '-Im(Z) max : %.2f — %.2f mΩ\n', ...
                     'R0 (HF) : %.2f — %.2f mΩ'], ...
    min(T.f_min), max(T.f_max), ...
    min(T.SOC), max(T.SOC), ...
    min(T.Re_max_mOhm), max(T.Re_max_mOhm), ...
    min(T.Im_max_mOhm), max(T.Im_max_mOhm), ...
    min(T.R0_mOhm), max(T.R0_mOhm));

text(0.5, 0.55, txt_stats, ...
    'Units','normalized', 'HorizontalAlignment','center', ...
    'Color', C_txt, 'FontSize', 11, 'FontWeight', 'bold', ...
    'BackgroundColor', [0.95 0.95 0.95], 'EdgeColor', C_grid, 'Margin', 10);

%% ── EXPORT AUTOMATIQUE HAUTE RÉSOLUTION (pour rapport) ──────────────────
exportgraphics(fig1, 'figures/nyquist_grille_soc.png', 'Resolution', 300);
exportgraphics(fig2, 'figures/parametres_eis_vs_soc.png', 'Resolution', 300);
exportgraphics(fig3, 'figures/bode_eis_vs_soc.png', 'Resolution', 300);
exportgraphics(fig4, 'figures/statistiques_eis.png', 'Resolution', 300);
fprintf('\n✓  Figures exportées en 300 dpi dans le dossier figures/\n');

%% ════════════════════════════════════════════════════════════════════════
%                          FONCTIONS LOCALES
%% ════════════════════════════════════════════════════════════════════════

function SOC_lut = read_soc_from_ts(ts_path, C_nom_Ah)
    SOC_lut = [];
    if ~isfile(ts_path), return; end

    fid = fopen(ts_path, 'r', 'n', 'latin1');
    header_line = -1; ln = 0;
    while ~feof(fid)
        ln = ln + 1; line = fgetl(fid);
        if contains(line, 'Time Stamp') && contains(line, 'AhAccu')
            header_line = ln; break;
        end
    end
    fclose(fid);
    if header_line < 0, return; end

    fid = fopen(ts_path, 'r', 'n', 'latin1');
    for i=1:header_line-1, fgetl(fid); end
    hdr = fgetl(fid); fclose(fid);
    hdr_cols = strtrim(strsplit(hdr, ';'));

    ah_idx = find(strcmpi(hdr_cols, 'AhAccu'), 1);
    st_idx = find(strcmpi(hdr_cols, 'Status'), 1);

    if isempty(ah_idx) || isempty(st_idx), return; end

    opts = detectImportOptions(ts_path, 'Delimiter',';', 'Encoding','latin1');
    opts.DataLines = [header_line+2, Inf];
    T = readtable(ts_path, opts);

    AhAccu_all = str2double(string(T{:, ah_idx}));
    Status_all = string(T{:, st_idx});

    mask = strcmp(strtrim(Status_all), 'EIS');
    SOC_lut = 1 - abs(AhAccu_all(mask)) / C_nom_Ah;
    SOC_lut = SOC_lut(:);
end

function [freq, Zre, Zim] = read_eis_digatron(fpath)
    freq = []; Zre = []; Zim = [];

    fid = fopen(fpath, 'r', 'n', 'latin1');
    header_line = -1; ln = 0;
    while ~feof(fid)
        ln = ln + 1; line = fgetl(fid);
        if contains(line, 'ActFreq') && contains(line, 'Zreal1')
            header_line = ln; break;
        end
    end
    fclose(fid);
    if header_line < 0, return; end

    fid = fopen(fpath, 'r', 'n', 'latin1');
    for i=1:header_line-1, fgetl(fid); end
    hdr = fgetl(fid); fclose(fid);
    hdr_cols = strtrim(strsplit(hdr, ';'));

    f_idx  = find(strcmpi(hdr_cols, 'ActFreq'), 1);
    zr_idx = find(strcmpi(hdr_cols, 'Zreal1'), 1);
    zi_idx = find(strcmpi(hdr_cols, 'Zimg1'), 1);
    st_idx = find(strcmpi(hdr_cols, 'Status'), 1);

    if isempty(f_idx) || isempty(zr_idx) || isempty(zi_idx), return; end

    opts = detectImportOptions(fpath, 'Delimiter',';', 'Encoding','latin1');
    opts.DataLines = [header_line+2, Inf];
    T = readtable(fpath, opts);

    F  = str2double(string(T{:, f_idx}));
    ZR = str2double(string(T{:, zr_idx}));
    ZI = str2double(string(T{:, zi_idx}));

    if ~isempty(st_idx)
        Status = string(T{:, st_idx});
        ok = strcmp(Status, 'EIS') & isfinite(F) & isfinite(ZR) & isfinite(ZI) & (F > 0);
    else
        ok = isfinite(F) & isfinite(ZR) & isfinite(ZI) & (F > 0);
    end

    if sum(ok) < 5, return; end

    freq = F(ok);
    Zre  = ZR(ok) / 1000;
    Zim  = ZI(ok) / 1000;

    [freq, ord] = sort(freq, 'descend');
    Zre = Zre(ord); Zim = Zim(ord);
end