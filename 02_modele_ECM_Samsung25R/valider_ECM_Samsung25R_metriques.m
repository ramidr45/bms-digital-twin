% [Fichier renommé lors du rangement — ancien nom : metrique.m]

t   = out.V_out.Time;
V   = out.V_out.Data;
SOC = out.SOC_out.Data;

% Capacité déchargée 
Ah_sim = (1 - SOC) * 2.5;

Ah_ref = [0,   0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 2.25, 2.45];
V_ref  = [4.05, 3.88, 3.75, 3.66, 3.60, 3.55, 3.50, 3.44, 3.35, 3.10, 2.55];

%% Figure
figure('Name','Validation ECM 1RC','Position',[100 100 950 520]);
plot(Ah_sim, V, 'b-', 'LineWidth', 2.5, 'DisplayName','Modèle ECM 1RC');
hold on;
plot(Ah_ref, V_ref, 'r--o', 'LineWidth', 2, 'MarkerSize', 7, ...
     'MarkerFaceColor','r', 'DisplayName','Référence Samsung 25R 1C 20°C');
xlabel('Capacité déchargée (Ah)', 'FontSize', 13);
ylabel('Tension terminale (V)',   'FontSize', 13);
title('Validation Modèle ECM 1RC — Samsung INR18650-25R — 1C — 20°C','FontSize',13);
legend('Location','southwest','FontSize',12);
grid on; xlim([0 2.5]); ylim([2.4 4.3]);

%% Métriques RMSE / MAE
V_ref_interp = interp1(Ah_ref, V_ref, Ah_sim, 'linear', 'extrap');
RMSE = sqrt(mean((V - V_ref_interp).^2)) * 1000;
MAE  = mean(abs(V - V_ref_interp)) * 1000;
MaxE = max(abs(V - V_ref_interp)) * 1000;

fprintf('\n========= VALIDATION ECM 1RC =========\n');
fprintf('RMSE     : %.1f mV\n', RMSE);
fprintf('MAE      : %.1f mV\n', MAE);
fprintf('Max Error: %.1f mV\n', MaxE);
if RMSE < 50
    fprintf('STATUS   : MODELE VALIDE  (RMSE < 50 mV)\n');
elseif RMSE < 100
    fprintf('STATUS   : ACCEPTABLE     (ajustement R0/R1/C1 recommande)\n');
else
    fprintf('STATUS   : AJUSTEMENT NECESSAIRE\n');
end
fprintf('=======================================\n');