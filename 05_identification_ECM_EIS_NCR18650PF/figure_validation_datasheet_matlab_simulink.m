% [Fichier renommé lors du rangement — ancien nom : S2_extraction.m]
%% ── COMPARAISON TRIPLE : DATASHEET vs MATLAB vs SIMULINK ──────────────
figure('Color', 'w', 'Position', [100 100 1000 700]);

% ── 1. Points Datasheet Panasonic (référence) ─────────────────────────
p1 = plot(cap_mAh_ds, volt_ds, 'o', ...
    'Color', [1.0 0.5 0.0], 'MarkerSize', 6, ...
    'MarkerFaceColor', [1.0 0.5 0.0], ...
    'DisplayName', 'Datasheet Panasonic (1C, 25°C)');
hold on;

% ── 2. Script MATLAB (Euler arrière) ──────────────────────────────────
p2 = plot(cap_sim, Vt_arr, 'b-', 'LineWidth', 2.0, ...
    'DisplayName', 'Script MATLAB (Euler arrière, dt=1s)');

% ── 3. Simulink (ode23t) ──────────────────────────────────────────────
p3 = plot(cap_sim, Vt_sim', 'r--', 'LineWidth', 2.0, ...
    'DisplayName', 'Simulink (ode23t, Variable-step)');

% ── Mise en forme ─────────────────────────────────────────────────────
xlabel('Capacité déchargée [mAh]', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Tension terminale V_t [V]', 'FontSize', 12, 'FontWeight', 'bold');
title('Validation croisée : Datasheet vs Script MATLAB vs Simulink  |  NCR18650PF 1C @ 25°C', ...
    'FontSize', 13, 'FontWeight', 'bold');
legend('Location', 'southwest', 'FontSize', 11);
grid on;
xlim([0 2900]);
ylim([2.3 4.3]);

% Ligne de coupure
yline(2.5, 'k:', 'LineWidth', 1.5, 'DisplayName', 'Seuil coupure 2.5V');

% ── 4. Calcul des erreurs ─────────────────────────────────────────────
% Interpoler MATLAB et Simulink sur les points datasheet
Vt_matlab_at_ds = interp1(cap_sim, Vt_arr, cap_mAh_ds, 'linear', 'extrap');
Vt_sim_at_ds    = interp1(cap_sim, Vt_sim', cap_mAh_ds, 'linear', 'extrap');

% Erreurs vs datasheet
err_matlab_mV = (Vt_matlab_at_ds - volt_ds) * 1000;  % mV
err_sim_mV    = (Vt_sim_at_ds - volt_ds) * 1000;     % mV

% Erreur entre MATLAB et Simulink
err_cross_mV  = (Vt_sim_at_ds - Vt_matlab_at_ds) * 1000;  % mV

% ── 5. Affichage des métriques dans la figure ─────────────────────────
% Masque : SOC > 5% (zone stable)
mask = cap_mAh_ds >= 100;  % exclut les premiers 100 mAh (transitoire)

MAE_matlab = mean(abs(err_matlab_mV(mask)));
RMSE_matlab = sqrt(mean(err_matlab_mV(mask).^2));
MAX_matlab = max(abs(err_matlab_mV(mask)));

MAE_sim = mean(abs(err_sim_mV(mask)));
RMSE_sim = sqrt(mean(err_sim_mV(mask).^2));
MAX_sim = max(abs(err_sim_mV(mask)));

MAE_cross = mean(abs(err_cross_mV(mask)));

txt_metrics = sprintf([...
    '─── Erreurs vs Datasheet (SOC > 5%%) ───\\n', ...
    'MATLAB : MAE = %.1f mV | RMSE = %.1f mV | MAX = %.1f mV\\n', ...
    'Simulink : MAE = %.1f mV | RMSE = %.1f mV | MAX = %.1f mV\\n', ...
    '─── Cohérence MATLAB vs Simulink ───\\n', ...
    'MAE cross = %.1f mV'], ...
    MAE_matlab, RMSE_matlab, MAX_matlab, ...
    MAE_sim, RMSE_sim, MAX_sim, ...
    MAE_cross);

annotation('textbox', [0.55 0.15 0.40 0.20], ...
    'String', txt_metrics, ...
    'FontSize', 10, 'FontWeight', 'bold', ...
    'BackgroundColor', [0.95 0.95 0.95], ...
    'EdgeColor', 'k', 'Margin', 10, ...
    'FitBoxToText', 'on');

fprintf('\n%s\n', repmat('═',1,70));
fprintf('  VALIDATION CROISÉE : DATASHEET vs MATLAB vs SIMULINK\n');
fprintf('%s\n', repmat('═',1,70));
fprintf('  Erreurs vs Datasheet Panasonic (SOC > 5%%) :\n');
fprintf('    MATLAB  : MAE = %5.1f mV | RMSE = %5.1f mV | MAX = %5.1f mV\n', ...
    MAE_matlab, RMSE_matlab, MAX_matlab);
fprintf('    Simulink: MAE = %5.1f mV | RMSE = %5.1f mV | MAX = %5.1f mV\n', ...
    MAE_sim, RMSE_sim, MAX_sim);
fprintf('  Cohérence MATLAB vs Simulink :\n');
fprintf('    MAE cross = %.1f mV\n', MAE_cross);
fprintf('%s\n', repmat('═',1,70));

%% ── FIGURE SUPPLÉMENTAIRE : ERREURS DÉTAILLÉES ───────────────────────
figure('Color', 'w', 'Position', [150 150 900 600]);

% P1 : Erreur MATLAB vs Datasheet
subplot(2,1,1);
plot(cap_mAh_ds(mask), err_matlab_mV(mask), 'b-o', 'LineWidth', 1.5, 'MarkerSize', 4);
hold on;
yline(0, 'k--', 'LineWidth', 1);
yline(20, 'r:', 'LineWidth', 1);
yline(-20, 'r:', 'LineWidth', 1);
xlabel('Capacité déchargée [mAh]', 'FontSize', 11);
ylabel('Erreur [mV]', 'FontSize', 11);
title(sprintf('Erreur Script MATLAB vs Datasheet (MAE = %.1f mV)', MAE_matlab), ...
    'FontSize', 12, 'FontWeight', 'bold');
grid on;
ylim([-50 50]);

% P2 : Erreur Simulink vs Datasheet
subplot(2,1,2);
plot(cap_mAh_ds(mask), err_sim_mV(mask), 'r-s', 'LineWidth', 1.5, 'MarkerSize', 4);
hold on;
yline(0, 'k--', 'LineWidth', 1);
yline(20, 'r:', 'LineWidth', 1);
yline(-20, 'r:', 'LineWidth', 1);
xlabel('Capacité déchargée [mAh]', 'FontSize', 11);
ylabel('Erreur [mV]', 'FontSize', 11);
title(sprintf('Erreur Simulink vs Datasheet (MAE = %.1f mV)', MAE_sim), ...
    'FontSize', 12, 'FontWeight', 'bold');
grid on;
ylim([-50 50]);