% [Fichier renommé lors du rangement — ancien nom : sweep_qr.m]
%% ========================================================================
%  Balayage automatique Q/R — trouve le couple qui minimise le RMSE EKF
%  PREREQUIS : le bloc Constant "Noise" doit etre pilote par une variable
%  workspace nommee "Noise" (pas une valeur codee en dur dans le bloc)
%% ========================================================================
clear results_qr; clc;

model_name = 'EKFSim';   % adapte si besoin
open_system(model_name);

% Grille de valeurs a tester (log-scale, ajuste selon tes ordres de grandeur actuels)
Q_values = [1e-9, 1e-8, 1e-7, 1e-6];
R_values = [1e-5, 1e-4, 1e-3, 1e-2];

n_combos = length(Q_values) * length(R_values);
results_qr = table('Size',[n_combos 4], ...
    'VariableTypes',{'double','double','double','double'}, ...
    'VariableNames',{'Q','R','RMSE_pct','MAE_pct'});

idx = 1;
for qi = 1:length(Q_values)
    for ri = 1:length(R_values)
        Noise = [Q_values(qi), R_values(ri)];  %#ok<NASGU> % variable lue par le bloc Constant

        try
            sim(model_name);   % les blocs "To Workspace" ecrivent directement dans le base workspace

            SOC_EKF  = evalin('base', 'SOC_EKF_log');
            SOC_Real = evalin('base', 'SOC_Real_log');
            n = min(length(SOC_EKF), length(SOC_Real));
            err = SOC_EKF(1:n) - SOC_Real(1:n);

            rmse = sqrt(mean(err.^2))*100;
            mae  = mean(abs(err))*100;
        catch ME
            fprintf('Erreur Q=%.1e R=%.1e : %s\n', Q_values(qi), R_values(ri), ME.message);
            rmse = NaN; mae = NaN;
        end

        results_qr.Q(idx) = Q_values(qi);
        results_qr.R(idx) = R_values(ri);
        results_qr.RMSE_pct(idx) = rmse;
        results_qr.MAE_pct(idx) = mae;

        fprintf('[%d/%d] Q=%.1e  R=%.1e  ->  RMSE=%.2f%%  MAE=%.2f%%\n', ...
            idx, n_combos, Q_values(qi), R_values(ri), rmse, mae);
        idx = idx + 1;
    end
end

%% ── Meilleur resultat ---------------------------------------------------------
[~, best_idx] = min(results_qr.RMSE_pct);
fprintf('\n%s\n', repmat('=',1,50));
fprintf('  MEILLEUR COUPLE : Q=%.2e  R=%.2e\n', results_qr.Q(best_idx), results_qr.R(best_idx));
fprintf('  RMSE = %.2f%%   MAE = %.2f%%\n', results_qr.RMSE_pct(best_idx), results_qr.MAE_pct(best_idx));
fprintf('%s\n', repmat('=',1,50));

disp(sortrows(results_qr, 'RMSE_pct'));

%% ── Heatmap visuelle -----------------------------------------------------------
figure('Name','Balayage Q/R');
Qmat = reshape(results_qr.RMSE_pct, length(R_values), length(Q_values));
imagesc(log10(Q_values), log10(R_values), Qmat);
colorbar; colormap('parula');
xlabel('log_{10}(Q)'); ylabel('log_{10}(R)');
title('RMSE (%) en fonction de Q et R');
set(gca,'YDir','normal');