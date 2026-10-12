% [Fichier renommé lors du rangement — ancien nom : visualisation.m]
%% =========================================================================
%  visu_HPPC_drive_cycles.m
%  HPPC Data Visualization — NCR18650BD (Panasonic)
%  Vue globale + zoom groupes + annotation ECM 1-RC
% =========================================================================
clc; clear; close all;

%% ── 1. Chargement des données ────────────────────────────────────────────
filename = 'C:\Users\SAT\Desktop\drive_cycles.xlsx';
sheet    = 'HPPC';

raw = readtable(filename, 'Sheet', sheet, 'VariableNamingRule', 'preserve');
raw = raw(:, 1:5);
raw.Properties.VariableNames = {'Time','Current','Voltage','Capacity','Energy'};

% Conversion en numériques (suppression NaN)
raw = rmmissing(raw);
Time     = raw.Time;
Current  = raw.Current;        % mA
Voltage  = raw.Voltage;        % V
Capacity = raw.Capacity;
Energy   = raw.Energy;

Current_A = Current / 1000;    % Conversion mA → A
N = length(Time);

%% ── 2. SoC par Coulomb Counting ─────────────────────────────────────────
Q_nom = 3200;   % mAh — NCR18650BD nominal
dt    = 1;      % s (pas de temps = 1 s)

% Seul le courant négatif (décharge) contribue au SoC consommé
discharge_mA = -min(Current, 0);                    % mA positif uniquement décharge
cum_discharge = cumsum(discharge_mA) * dt / 3600;   % mAh
SoC = 100 * (1 - cum_discharge / Q_nom);            % %

Time_h = Time / 3600;   % secondes → heures

%% ── 3. Détection des pulses ──────────────────────────────────────────────
is_nonzero      = Current_A ~= 0;
transitions     = diff(is_nonzero);
pulse_starts    = find(transitions ==  1) + 1;   % indices début pulse
pulse_ends      = find(transitions == -1);        % indices fin pulse

fprintf('Nombre de pulses détectés : %d\n', length(pulse_starts));
fprintf('Nombre de groupes HPPC    : %d\n', floor(length(pulse_starts)/3));

%% ── 4. FIGURE 1 : Vue globale ────────────────────────────────────────────
fig1 = figure('Name','HPPC Global','Position',[50 50 1400 800]);
tiledlayout(3,1,'TileSpacing','compact','Padding','compact');

% Courant
ax1 = nexttile;
area_pos = max(Current_A, 0);
area_neg = min(Current_A, 0);
hold on;
area(Time_h, area_neg, 'FaceColor',[0.90 0.22 0.27], 'EdgeColor','none', ...
     'FaceAlpha',0.75, 'DisplayName','Décharge');
area(Time_h, area_pos, 'FaceColor',[0.27 0.48 0.62], 'EdgeColor','none', ...
     'FaceAlpha',0.75, 'DisplayName','Charge');
yline(0,'k--','LineWidth',0.8,'HandleVisibility','off');
ylabel('Courant (A)', 'FontSize',11);
title('Profil de Courant HPPC', 'FontSize',11);
legend('Location','northeast','FontSize',9);
grid on; grid minor;
ylim([-6 6]);

% Tension
ax2 = nexttile;
plot(Time_h, Voltage, 'Color',[0.18 0.42 0.31], 'LineWidth',1.0);
ylabel('Tension (V)', 'FontSize',11);
title('Tension Terminale', 'FontSize',11);
grid on; grid minor;
ylim([2.3 4.5]);

% SoC
ax3 = nexttile;
plot(Time_h, SoC, 'Color',[0.96 0.64 0.38], 'LineWidth',1.5);
ylabel('SoC (%)', 'FontSize',11);
xlabel('Temps (h)', 'FontSize',11);
title('State of Charge — Coulomb Counting', 'FontSize',11);
grid on; grid minor;
ylim([0 110]);

% Annotations groupes sur SoC
N_groups = floor(length(pulse_starts)/3);
hold on;
for g = 1:N_groups
    p_dis = (g-1)*3 + 1;
    if p_dis > length(pulse_starts); break; end
    t_g   = Time_h(pulse_starts(p_dis));
    soc_g = SoC(pulse_starts(p_dis));
    xline(ax1, t_g, ':','Color',[0.5 0.5 0.5],'LineWidth',0.6,'HandleVisibility','off');
    xline(ax2, t_g, ':','Color',[0.5 0.5 0.5],'LineWidth',0.6,'HandleVisibility','off');
    xline(ax3, t_g, ':','Color',[0.5 0.5 0.5],'LineWidth',0.6,'HandleVisibility','off');
    text(t_g+0.05, soc_g+3, sprintf('G%d\n%.0f%%',g,soc_g), ...
         'FontSize',7, 'Color',[0.3 0.3 0.3], 'Parent',ax3);
end

linkaxes([ax1 ax2 ax3], 'x');
sgtitle('HPPC Dataset — NCR18650BD (Panasonic) | Vue Globale', ...
        'FontSize',14,'FontWeight','bold');

exportgraphics(fig1, 'fig1_hppc_global.png', 'Resolution',150);
fprintf('✓ fig1_hppc_global.png exportée\n');

%% ── 5. FIGURE 2 : Zoom sur les 10 groupes ───────────────────────────────
fig2 = figure('Name','Zoom Groupes','Position',[50 50 1400 1600]);
tiledlayout(5,2,'TileSpacing','compact','Padding','compact');

for g = 1:N_groups
    p_dis  = (g-1)*3 + 1;
    p_chg  = (g-1)*3 + 2;
    p_step = (g-1)*3 + 3;
    if p_step > length(pulse_starts); break; end

    i_start = max(1, pulse_starts(p_dis) - 60);
    i_end   = min(N, pulse_ends(p_step)  + 300);

    t_w   = Time(i_start:i_end) - Time(pulse_starts(p_dis));
    I_w   = Current_A(i_start:i_end);
    V_w   = Voltage(i_start:i_end);
    soc_g = SoC(pulse_starts(p_dis));

    ax = nexttile;
    yyaxis left
    area_n = min(I_w, 0);
    area_p = max(I_w, 0);
    hold on;
    area(t_w, area_n, 'FaceColor',[0.90 0.22 0.27], 'EdgeColor','none','FaceAlpha',0.6);
    area(t_w, area_p, 'FaceColor',[0.27 0.48 0.62], 'EdgeColor','none','FaceAlpha',0.6);
    yline(0,'k--','LineWidth',0.5);
    ylabel('I (A)','FontSize',9,'Color',[0.90 0.22 0.27]);
    ylim([-6 6]);
    ax.YColor = [0.90 0.22 0.27];

    yyaxis right
    plot(t_w, V_w, 'Color',[0.18 0.42 0.31], 'LineWidth',1.5);
    ylabel('V (V)','FontSize',9,'Color',[0.18 0.42 0.31]);
    ax.YColor = [0.18 0.42 0.31];

    % Lignes de transition
    t_chg_rel  = Time(pulse_starts(p_chg))  - Time(pulse_starts(p_dis));
    t_step_rel = Time(pulse_starts(p_step)) - Time(pulse_starts(p_dis));
    xline(0,          ':','Color',[0.5 0.5 0.5],'LineWidth',0.8);
    xline(t_chg_rel,  ':','Color',[0.27 0.48 0.62],'LineWidth',0.8);
    xline(t_step_rel, ':','Color',[0.55 0.27 0.68],'LineWidth',0.8);

    title(sprintf('Groupe %d — SoC ≈ %.1f%%', g, soc_g), ...
          'FontSize',10,'FontWeight','bold');
    xlabel('Δt (s)','FontSize',9);
    grid on;
end

sgtitle('HPPC — Zoom sur chaque groupe (Dis 10s / Chg 10s / Dis 720s)', ...
        'FontSize',13,'FontWeight','bold');
exportgraphics(fig2, 'fig2_hppc_zoom_groupes.png', 'Resolution',150);
fprintf('✓ fig2_hppc_zoom_groupes.png exportée\n');

%% ── 6. FIGURE 3 : Zoom détaillé Groupe 1 — annotation ECM ───────────────
g = 1;
p_dis = 1;
p_chg = 2;

i_start = max(1, pulse_starts(p_dis) - 30);
i_end   = min(N, pulse_ends(p_chg) + 50);

t_w = Time(i_start:i_end) - Time(pulse_starts(p_dis));
I_w = Current_A(i_start:i_end);
V_w = Voltage(i_start:i_end);

fig3 = figure('Name','Annotation ECM G1','Position',[100 100 1300 700]);
tiledlayout(2,1,'TileSpacing','compact','Padding','compact');

% Courant
nexttile;
hold on;
area(t_w, min(I_w,0),'FaceColor',[0.90 0.22 0.27],'EdgeColor','none','FaceAlpha',0.7,'DisplayName','Décharge');
area(t_w, max(I_w,0),'FaceColor',[0.27 0.48 0.62],'EdgeColor','none','FaceAlpha',0.7,'DisplayName','Charge');
yline(0,'k--','LineWidth',0.7,'HandleVisibility','off');
ylabel('Courant (A)','FontSize',11);
legend('FontSize',9,'Location','northeast');
title('Courant','FontSize',10);
grid on;

% Tension avec annotations
nexttile;
plot(t_w, V_w, 'Color',[0.18 0.42 0.31], 'LineWidth',2, 'DisplayName','Tension terminale');
hold on;

V_OCV    = Voltage(pulse_starts(p_dis) - 1);
V_drop1  = Voltage(pulse_starts(p_dis));
V_end_d  = Voltage(pulse_ends(p_dis));
t_end_d  = Time(pulse_ends(p_dis)) - Time(pulse_starts(p_dis));

yline(V_OCV,'--','Color',[0.96 0.64 0.38],'LineWidth',1.2,...
      'DisplayName',sprintf('OCV = %.4f V', V_OCV));

% Annotation ΔV_R0
annotation_x1 = 0;
plot([annotation_x1 annotation_x1], [V_drop1 V_OCV], 'r-', 'LineWidth',2,'HandleVisibility','off');
text(1, (V_OCV+V_drop1)/2, sprintf('\\DeltaV_{R_0} = %.4f V', V_OCV-V_drop1), ...
     'Color','red','FontSize',9,'FontWeight','bold');

% Annotation ΔV_RC
plot([0 t_end_d], [V_drop1 V_drop1], 'b--','LineWidth',1,'HandleVisibility','off');
plot([0 t_end_d], [V_end_d V_end_d], 'b--','LineWidth',1,'HandleVisibility','off');
text(t_end_d/2, (V_drop1+V_end_d)/2, ...
     sprintf('\\DeltaV_{RC} = %.4f V', V_drop1-V_end_d), ...
     'Color',[0.55 0.27 0.68],'FontSize',9,'FontWeight','bold');

ylabel('Tension (V)','FontSize',11);
xlabel('Δt depuis début pulse (s)','FontSize',11);
legend('FontSize',9,'Location','southeast');
title('Tension — Identification visuelle R_0 et R_1C_1','FontSize',10);
grid on;

sgtitle('HPPC — Zoom Détaillé Pulse Groupe 1 (SoC ≈ 100%)', ...
        'FontSize',13,'FontWeight','bold');
exportgraphics(fig3, 'fig3_hppc_annotation_ecm.png', 'Resolution',150);
fprintf('✓ fig3_hppc_annotation_ecm.png exportée\n');

fprintf('\n✅ Visualisation HPPC terminée — 3 figures exportées.\n');