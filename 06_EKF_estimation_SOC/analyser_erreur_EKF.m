% [Fichier renommé lors du rangement — ancien nom : ekf_erreur.m]
%% ========================================================================
%  Analyse des resultats EKF : visualisation + metriques d'erreur
%  A executer APRES la simulation Simulink (les signaux doivent etre
%  loggues dans le workspace via des blocs "To Workspace")
%
%  PREREQUIS DANS SIMULINK : ajoute 3 blocs "To Workspace" connectes a
%  SOC_upd (EKF), SOC_Real, SOC_AH -- Format: "Array", coche "Save format"
%  Variable names : SOC_EKF_log, SOC_Real_log, SOC_AH_log
%  + un bloc "To Workspace" ou active "Time" dans Model Settings pour
%  recuperer le vecteur temps (tout.time ou "tout" simple)
%% ========================================================================
clear results; clc;

% ADAPTE ces noms de variables selon ce que tu as loggue dans Simulink
t        = tout(:);              % vecteur temps (active "Save simulation output" > "Time")
SOC_EKF  = SOC_EKF_log(:);
SOC_Real = SOC_Real_log(:);
SOC_AH   = SOC_AH_log(:);

% Securite : tronque au meme nombre de points si mismatch
n = min([length(t), length(SOC_EKF), length(SOC_Real), length(SOC_AH)]);
t = t(1:n); SOC_EKF = SOC_EKF(1:n); SOC_Real = SOC_Real(1:n); SOC_AH = SOC_AH(1:n);

%% ── 1. Erreurs globales -----------------------------------------------------
err_EKF = SOC_EKF - SOC_Real;
err_AH  = SOC_AH  - SOC_Real;

MAE_EKF  = mean(abs(err_EKF));   RMSE_EKF = sqrt(mean(err_EKF.^2));  MAX_EKF = max(abs(err_EKF));
MAE_AH   = mean(abs(err_AH));    RMSE_AH  = sqrt(mean(err_AH.^2));   MAX_AH  = max(abs(err_AH));

fprintf('\n%s\n', repmat('=',1,60));
fprintf('  COMPARAISON EKF vs COMPTAGE DE COULOMB (AH) — vs SOC_Real\n');
fprintf('%s\n', repmat('=',1,60));
fprintf('  %-25s %10s %10s\n', '', 'EKF', 'AH (sans EKF)');
fprintf('  %-25s %9.2f%% %9.2f%%\n', 'MAE',  MAE_EKF*100,  MAE_AH*100);
fprintf('  %-25s %9.2f%% %9.2f%%\n', 'RMSE', RMSE_EKF*100, RMSE_AH*100);
fprintf('  %-25s %9.2f%% %9.2f%%\n', 'MAX',  MAX_EKF*100,  MAX_AH*100);
fprintf('%s\n', repmat('=',1,60));

if RMSE_EKF < RMSE_AH
    fprintf('  ✓ L''EKF ameliore l''estimation de %.1f%% (RMSE) par rapport a AH seul\n', (1-RMSE_EKF/RMSE_AH)*100);
else
    fprintf('  ⚠ L''EKF est actuellement MOINS precis que le simple comptage AH — a corriger (Q/R)\n');
end

%% ── 2. Erreur par plage de SOC (identifie si le bruit vient du SOC bas) ----
soc_bins = [0 0.1 0.2 0.3 0.5 0.7 1.0];
fprintf('\n  Erreur EKF par plage de SOC :\n');
fprintf('  %-15s %10s %10s\n', 'Plage SOC', 'MAE', 'RMSE');
for k = 1:length(soc_bins)-1
    mask = SOC_Real >= soc_bins(k) & SOC_Real < soc_bins(k+1);
    if sum(mask) > 5
        mae_bin  = mean(abs(err_EKF(mask)));
        rmse_bin = sqrt(mean(err_EKF(mask).^2));
        fprintf('  %4.0f%% - %4.0f%%   %9.2f%% %9.2f%%\n', ...
            soc_bins(k)*100, soc_bins(k+1)*100, mae_bin*100, rmse_bin*100);
    end
end

%% ── 3. Visualisation ----------------------------------------------------------
figure('Name','Resultats EKF - NCR18650PF Drive Cycle','Position',[100 100 1100 800]);

subplot(3,1,1); hold on; grid on;
plot(t, SOC_Real*100, 'c-', 'LineWidth', 2, 'DisplayName','SOC Real');
plot(t, SOC_AH*100, 'b-.', 'LineWidth', 1.2, 'DisplayName','SOC AH (Coulomb counting)');
plot(t, SOC_EKF*100, 'R-', 'LineWidth', 1, 'DisplayName','SOC EKF');
xlabel('Temps (s)'); ylabel('SOC (%)');
title('Comparaison SOC : Real vs AH vs EKF');
legend('Location','best');

subplot(3,1,2); hold on; grid on;
plot(t, err_AH*100, 'm-', 'DisplayName','Erreur AH');
plot(t, err_EKF*100, 'R-', 'DisplayName','Erreur EKF');
yline(0,'w--');
xlabel('Temps (s)'); ylabel('Erreur SOC (%)');
title('Erreur d''estimation au cours du temps');
legend('Location','best');

subplot(3,1,3); hold on; grid on;
histogram(err_EKF*100, 50, 'FaceColor','g', 'FaceAlpha',0.6, 'DisplayName','Erreur EKF');
histogram(err_AH*100, 50, 'FaceColor','m', 'FaceAlpha',0.6, 'DisplayName','Erreur AH');
xlabel('Erreur SOC (%)'); ylabel('Occurrences');
title('Distribution des erreurs');
legend('Location','best');

sgtitle(sprintf('NCR18650PF - EKF SOC | MAE=%.2f%% RMSE=%.2f%% MAX=%.2f%%', ...
    MAE_EKF*100, RMSE_EKF*100, MAX_EKF*100), 'FontWeight','bold');
