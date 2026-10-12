% [Fichier renommé lors du rangement — ancien nom : COMPARAISON.m]
%% =========================================================================
%  comparaison_decharges_vs_datasheet.m
%  Visualisation des courbes de décharge — NCR18650 (Panasonic)
%  Comparaison dataset mesuré (0.5C / 1C / 1.5C) vs datasheet
%
%  Fichier requis : hppc.xlsx (onglets 0.5C, 1.0C, 1.5C)
% =========================================================================
clc; clear; close all;

%% ── 1. Chargement des 3 courbes de décharge ──────────────────────────────
sheets   = {'0.5C','1.0C','1.5C'};
Q_nom    = 2900;     % mAh — NCR18650 typ. datasheet
colors   = {[0.18 0.62 0.42], [0.20 0.40 0.72], [0.86 0.20 0.25]};
styles   = {'-','-','-'};

data = struct();

for k = 1:length(sheets)
    sh  = sheets{k};
    raw = readtable('hppc.xlsx','Sheet',sh,'VariableNamingRule','preserve');
    raw = raw(:,1:5);
    raw.Properties.VariableNames = {'Time','Current','Voltage','Capacity','Energy'};
    raw = rmmissing(raw);

    t   = double(raw.Time);
    I   = double(raw.Current) / 1000;    % mA → A
    V   = double(raw.Voltage);
    Cap = double(raw.Capacity);          % mAh (cumulé)

    % SoC = 1 - Cap/Q_nom  (décharge → SoC décroissant)
    SoC = 100 * (1 - Cap / Q_nom);

    fname = strrep(sh,'.','p');
    data.(fname).t    = t;
    data.(fname).I    = I;
    data.(fname).V    = V;
    data.(fname).Cap  = Cap;
    data.(fname).SoC  = SoC;
    data.(fname).Iavg = mean(abs(I));
    data.(fname).Crate = sh;

    fprintf('%s : %d pts | I_avg=%.0f mA | Cap_max=%.1f mAh | V_end=%.4f V\n', ...
            sh, length(t), mean(abs(I*1000)), max(Cap), V(end));
end

%% ── 2. Courbes datasheet digitalisées (NCR18650, 25°C) ───────────────────
% Points extraits visuellement du datasheet Panasonic NCR18650
% Axe X = Discharge Capacity (mAh), Axe Y = Voltage (V)
% Courbes : 0.2C, 0.5C, 1C, 2C

ds_05C = [
      0,  4.050;  200,  3.900;  500,  3.780;  800,  3.720;
   1000,  3.700; 1500,  3.670; 2000,  3.630; 2300,  3.600;
   2500,  3.560; 2650,  3.500; 2750,  3.420; 2850,  3.200;
   2900,  2.900; 2920,  2.700; 2940,  2.600; 2960,  2.500];

ds_1C  = [
      0,  3.980;  200,  3.820;  500,  3.760;  800,  3.720;
   1000,  3.700; 1500,  3.660; 2000,  3.610; 2300,  3.570;
   2400,  3.530; 2500,  3.470; 2600,  3.340; 2700,  3.100;
   2750,  2.900; 2800,  2.700; 2830,  2.600; 2850,  2.500];

ds_2C  = [
      0,  3.930;  200,  3.730;  500,  3.680;  800,  3.640;
   1000,  3.620; 1500,  3.570; 2000,  3.510; 2200,  3.450;
   2300,  3.380; 2400,  3.250; 2500,  3.060; 2550,  2.900;
   2600,  2.700; 2620,  2.600; 2640,  2.500];

%% ── 3. FIGURE 1 : V vs Capacity — Mesure vs Datasheet ───────────────────
fig1 = figure('Name','Discharge V vs Cap','Position',[50 50 1200 650]);
hold on;

% Datasheet
plot(ds_05C(:,1), ds_05C(:,2), '--','Color',[0.6 0.6 0.6],'LineWidth',1.5, ...
     'DisplayName','Datasheet 0.5C');
plot(ds_1C(:,1),  ds_1C(:,2),  ':','Color',[0.4 0.4 0.4],'LineWidth',1.8, ...
     'DisplayName','Datasheet 1C');
plot(ds_2C(:,1),  ds_2C(:,2),  '-.','Color',[0.2 0.2 0.2],'LineWidth',1.5, ...
     'DisplayName','Datasheet 2C');

% Mesures
fnames = {'0p5C','1p0C','1p5C'};
labels = {'Mesuré 0.5C (~0.47C)','Mesuré 1.0C (~0.93C)','Mesuré 1.5C (~1.40C)'};
for k = 1:3
    fn = fnames{k};
    plot(data.(fn).Cap, data.(fn).V, styles{k}, ...
         'Color', colors{k}, 'LineWidth', 2.0, 'DisplayName', labels{k});
end

% Référence 2900 mAh
xline(2900,'k:','LineWidth',1.0,'HandleVisibility','off');
text(2910, 3.2,'Q_{typ}=2900mAh','FontSize',9,'Color',[0.3 0.3 0.3]);
yline(2.5,'r:','LineWidth',1.0,'HandleVisibility','off');
text(50, 2.52,'V_{cutoff}=2.5V','FontSize',9,'Color','r');

xlabel('Capacité déchargée (mAh)','FontSize',12);
ylabel('Tension (V)','FontSize',12);
title({'Courbes de Décharge — NCR18650 (Panasonic)', ...
       'Dataset mesuré vs Datasheet constructeur'},'FontSize',13,'FontWeight','bold');
legend('Location','southwest','FontSize',10);
grid on; grid minor;
xlim([-50 3200]); ylim([2.3 4.3]);

% Annotation C-rates réels
I_05 = data.('0p5C').Iavg * 1000;
I_1  = data.('1p0C').Iavg * 1000;
I_15 = data.('1p5C').Iavg * 1000;
text(100, 3.95, sprintf('I=%.0f mA (%.2fC)', I_05, I_05/Q_nom), ...
     'FontSize',9,'Color',colors{1},'FontWeight','bold');
text(100, 3.80, sprintf('I=%.0f mA (%.2fC)', I_1,  I_1/Q_nom), ...
     'FontSize',9,'Color',colors{2},'FontWeight','bold');
text(100, 3.65, sprintf('I=%.0f mA (%.2fC)', I_15, I_15/Q_nom), ...
     'FontSize',9,'Color',colors{3},'FontWeight','bold');

exportgraphics(fig1,'fig_discharge_V_vs_Cap.png','Resolution',150);
fprintf('✓ fig_discharge_V_vs_Cap.png\n');

%% ── 4. FIGURE 2 : V vs SoC ───────────────────────────────────────────────
fig2 = figure('Name','Discharge V vs SoC','Position',[80 80 1200 650]);
hold on;

for k = 1:3
    fn = fnames{k};
    plot(data.(fn).SoC, data.(fn).V, styles{k}, ...
         'Color', colors{k}, 'LineWidth', 2.0, 'DisplayName', labels{k});
end

yline(2.5,'r:','LineWidth',1.0,'HandleVisibility','off');
text(2, 2.52,'V_{cutoff}=2.5V','FontSize',9,'Color','r');

xlabel('SoC (%)', 'FontSize',12);
ylabel('Tension (V)','FontSize',12);
title({'Courbes de Décharge — NCR18650', ...
       'Tension vs SoC (Coulomb Counting, Q_{nom}=2900mAh)'},...
      'FontSize',13,'FontWeight','bold');
legend('Location','southwest','FontSize',10);
set(gca,'XDir','reverse');
grid on; grid minor;
xlim([-5 105]); ylim([2.3 4.3]);

exportgraphics(fig2,'fig_discharge_V_vs_SoC.png','Resolution',150);
fprintf('✓ fig_discharge_V_vs_SoC.png\n');

%% ── 5. FIGURE 3 : Comparaison Mesure vs Datasheet — écart quantifié ──────
fig3 = figure('Name','Ecart Mesure-Datasheet','Position',[100 100 1200 800]);
tiledlayout(2,1,'TileSpacing','compact','Padding','compact');

% V vs Cap — zoom comparaison 0.5C et 1C
nexttile;
hold on;

% 0.5C
plot(ds_05C(:,1), ds_05C(:,2),'--','Color',[0.5 0.5 0.5],'LineWidth',1.8,...
     'DisplayName','Datasheet 0.5C');
plot(data.('0p5C').Cap, data.('0p5C').V,'-','Color',colors{1},'LineWidth',2.0,...
     'DisplayName','Mesuré 0.5C');

% 1C
plot(ds_1C(:,1), ds_1C(:,2),'--','Color',[0.3 0.3 0.3],'LineWidth',1.8,...
     'DisplayName','Datasheet 1C');
plot(data.('1p0C').Cap, data.('1p0C').V,'-','Color',colors{2},'LineWidth',2.0,...
     'DisplayName','Mesuré 1C');

% Capacités mesurées
cap_05 = data.('0p5C').Cap(end);
cap_1  = data.('1p0C').Cap(end);
cap_15 = data.('1p5C').Cap(end);
xline(cap_05,':', 'Color',colors{1},'LineWidth',1.0,'HandleVisibility','off');
xline(cap_1,  ':', 'Color',colors{2},'LineWidth',1.0,'HandleVisibility','off');
text(cap_05+20, 2.65, sprintf('%.0f mAh',cap_05),'Color',colors{1},'FontSize',9);
text(cap_1 +20, 2.65, sprintf('%.0f mAh',cap_1), 'Color',colors{2},'FontSize',9);

xlabel('Capacité déchargée (mAh)','FontSize',11);
ylabel('Tension (V)','FontSize',11);
title('Comparaison directe — Mesure vs Datasheet (0.5C et 1C)','FontSize',11,'FontWeight','bold');
legend('Location','southwest','FontSize',9);
grid on; grid minor; ylim([2.3 4.3]);

% Écart de capacité
nexttile;
C_rates = [0.5, 1.0, 1.5];
caps_meas = [cap_05, cap_1, cap_15];
caps_ds   = [2900, 2850, NaN];   % approx datasheet @ 25°C

b = bar(C_rates, caps_meas, 0.4, 'FaceColor','flat');
b.CData = cell2mat(colors');
hold on;

% Ligne datasheet
plot([0.3 1.1], [2900 2850],'k--','LineWidth',1.5,'DisplayName','Datasheet (interpolé)');
plot([0.3 1.1], [2750 2750],'r:','LineWidth',1.2,'DisplayName','Min. rated (2750mAh)');

for i = 1:length(C_rates)
    delta = caps_meas(i) - 2900;
    text(C_rates(i), caps_meas(i)+20, ...
         sprintf('%.0f mAh\n(%.1f%%)', caps_meas(i), caps_meas(i)/2900*100), ...
         'HorizontalAlignment','center','FontSize',10,'FontWeight','bold');
end

xlabel('C-rate','FontSize',11);
ylabel('Capacité extraite (mAh)','FontSize',11);
title('Capacité extraite par C-rate vs référence datasheet','FontSize',11,'FontWeight','bold');
legend('Location','northeast','FontSize',9);
grid on; ylim([2000 3100]);
xticks(C_rates); xticklabels({'0.5C','1.0C','1.5C'});

sgtitle('Analyse comparative — Cellule NCR18650 vs Datasheet Panasonic',...
        'FontSize',13,'FontWeight','bold');
exportgraphics(fig3,'fig_discharge_vs_datasheet.png','Resolution',150);
fprintf('✓ fig_discharge_vs_datasheet.png\n');

%% ── 6. FIGURE 4 : Vue complète I + V pour chaque C-rate ─────────────────
fig4 = figure('Name','IV profiles','Position',[50 50 1400 900]);
tiledlayout(3,2,'TileSpacing','compact','Padding','compact');

for k = 1:3
    fn     = fnames{k};
    crate  = sheets{k};
    t_h    = data.(fn).t / 3600;

    % V(t)
    nexttile;
    plot(t_h, data.(fn).V,'Color',colors{k},'LineWidth',1.5);
    yline(2.5,'r:','LineWidth',1.0);
    xlabel('Temps (h)','FontSize',10);
    ylabel('Tension (V)','FontSize',10);
    title(sprintf('V(t) — %s | I≈%.0f mA', crate, data.(fn).Iavg*1000),...
          'FontSize',10,'FontWeight','bold','Color',colors{k});
    grid on; ylim([2.3 4.3]);

    % I(t)
    nexttile;
    area(t_h, abs(data.(fn).I)*1000,'FaceColor',colors{k},'EdgeColor','none','FaceAlpha',0.7);
    xlabel('Temps (h)','FontSize',10);
    ylabel('|I| (mA)','FontSize',10);
    title(sprintf('I(t) — %s', crate),'FontSize',10,'FontWeight','bold','Color',colors{k});
    grid on;
end

sgtitle('Profils Courant–Tension par C-rate — NCR18650','FontSize',13,'FontWeight','bold');
exportgraphics(fig4,'fig_IV_profiles.png','Resolution',150);
fprintf('✓ fig_IV_profiles.png\n');

%% ── 7. Résumé tableau ────────────────────────────────────────────────────
fprintf('\n%s\n', repmat('═',1,60));
fprintf('  RÉSUMÉ — Courbes de décharge NCR18650\n');
fprintf('%s\n', repmat('═',1,60));
fprintf('  %-8s %-12s %-14s %-10s %-10s\n', ...
        'C-rate','I_moy (mA)','Cap (mAh)','SoC_min%','V_fin (V)');
fprintf('%s\n', repmat('─',1,60));
for k = 1:3
    fn = fnames{k};
    fprintf('  %-8s %-12.0f %-14.1f %-10.1f %-10.4f\n', ...
            sheets{k}, data.(fn).Iavg*1000, max(data.(fn).Cap), ...
            min(data.(fn).SoC), data.(fn).V(end));
end
fprintf('%s\n', repmat('═',1,60));
fprintf('  Datasheet : Q_typ=2900mAh | V_nom=3.6V | V_cutoff=2.5V\n');
fprintf('%s\n', repmat('═',1,60));
fprintf('\n✅ Script 05 terminé — 4 figures exportées.\n');