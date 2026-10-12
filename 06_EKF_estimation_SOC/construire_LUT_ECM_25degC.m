% [Fichier renommé lors du rangement — ancien nom : build_ECM_LUTs.m]
%% construire_LUT_ECM_25degC.m
% Construit les LUT du modele Thevenin 1RC (R0, R1, C1, tau, OCV) pour la
% cellule Panasonic NCR18650PF a 25 degC, a partir des points EIS valides
% (voir table fournie par l'utilisateur, MAE=5.0mV / RMSE=6.2mV / MAX=15.5mV
% sur la decharge 1C reelle).
%
% Sortie: struct ECM contenant les breakpoints SOC + les LUT, plus les
% "piecewise polynomials" pchip pour OCV et sa derivee dOCV/dSOC, prets a
% etre utilises dans EKF_UKF_Thev.m (interp1(...,'pchip') ou ppval).

clear; clc;

%% --- Table EIS validee (SOC en fraction 0-1, R en Ohm, C en F, OCV en V) ---
SOC_table = [0.05 0.10 0.15 0.20 0.25 0.30 0.40 0.50 0.60 0.70 0.80 0.90 0.95 1.00];

R0_table  = [33.20 28.17 33.48 30.71 29.10 29.06 27.36 26.92 27.52 27.37 27.57 28.89 30.66 24.33] * 1e-3; % Ohm
R1_table  = [110.45 59.02 50.61 45.79 42.40 37.46 34.27 36.13 54.07 45.39 42.15 37.49 34.46 40.52] * 1e-3; % Ohm
C1_table  = [35.3 14.3 614.0 1179.4 1456.7 1590.0 1623.5 1657.8 1295.6 1167.7 1050.3 866.8 554.4 3.7]; % F
Tau_table = R1_table .* C1_table; % s  (recalcule pour coherence, cf. table fournie)

OCV_table = [2.9263 3.2844 3.4141 3.4777 3.5074 3.5360 3.5985 3.6711 3.8220 3.8972 3.9753 4.0838 4.1418 4.2239]; % V

%% --- Verification coherence tau = R1*C1 (doit matcher la colonne tau1 fournie) ---
Tau_reference = [2.9263 0.844 31.074 54.000 61.759 59.569 55.631 59.901 70.049 53.001 44.268 32.497 19.101 0.149];
% NB: la premiere valeur de Tau_reference (2.9263) est visiblement une
% coquille de recopie dans le tableau original (= la valeur OCV a 5%,
% pas un tau). On utilise Tau_table recalcule = R1*C1 comme verite.
fprintf('SOC%%   R1*C1 (s)   Tau fourni (s)   Ecart\n');
for i = 1:length(SOC_table)
    fprintf('%5.1f   %8.4f    %8.4f        %+.4f\n', SOC_table(i)*100, ...
        Tau_table(i), Tau_reference(i), Tau_table(i)-Tau_reference(i));
end

%% --- Construction des pchip (piecewise cubic hermite) ---
% OCV(SOC): utilise pour la prediction de tension UL_pre
pp_OCV = pchip(SOC_table, OCV_table);

% Derivee analytique de la pchip pour le Jacobien H = dOCV/dSOC (matrice C de l'EKF)
pp_dOCV = differentiate_pp(pp_OCV);

%% --- Sauvegarde dans un struct ECM reutilisable ---
ECM.SOC_table  = SOC_table;
ECM.R0_table   = R0_table;
ECM.R1_table   = R1_table;
ECM.C1_table   = C1_table;
ECM.Tau_table  = Tau_table;
ECM.OCV_table  = OCV_table;
ECM.pp_OCV     = pp_OCV;
ECM.pp_dOCV    = pp_dOCV;

save('ECM_NCR18650PF_25degC.mat', 'ECM');
fprintf('\nLUT sauvegardees dans ECM_NCR18650PF_25degC.mat\n');

%% --- Verification visuelle ---
soc_fine = linspace(0.05, 1.00, 500);
ocv_fine = ppval(pp_OCV, soc_fine);
docv_fine = ppval(pp_dOCV, soc_fine);

figure('Position',[100 100 1000 400]);
subplot(1,2,1);
plot(soc_fine*100, ocv_fine, 'b-', 'LineWidth', 1.5); hold on;
plot(SOC_table*100, OCV_table, 'ro', 'MarkerFaceColor','r');
xlabel('SOC (%)'); ylabel('OCV (V)'); grid on;
title('OCV(SOC) - interpolation pchip');
legend('pchip','points EIS','Location','southeast');

subplot(1,2,2);
plot(soc_fine*100, docv_fine, 'b-', 'LineWidth', 1.5);
xlabel('SOC (%)'); ylabel('dOCV/dSOC (V/unite SOC)'); grid on;
title('Derivee dOCV/dSOC (Jacobien EKF)');

saveas(gcf, 'OCV_pchip_check.png');

%% ================================================================
function dpp = differentiate_pp(pp)
% Derive analytiquement une structure piecewise-polynomial (pchip/spline)
% sans besoin de la Curve Fitting Toolbox (pas de fnder).
    [breaks, coefs, l, k, d] = unmkpp(pp);
    if k == 1
        dcoefs = zeros(size(coefs,1), 1);
    else
        power = (k-1):-1:1;
        dcoefs = coefs(:,1:k-1) .* power;
    end
    dpp = mkpp(breaks, dcoefs, d);
end
