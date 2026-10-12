% [Fichier renommé lors du rangement — ancien nom : profile_courant_discharge1c.m]
%% ========================================================================
%  Ajustement polynomial R0, R1, C1, OCV en fonction du SOC
%  Cellule : Panasonic NCR18650PF - donnees EIS @ 25degC
%  Objectif : generer les coefficients a injecter dans Paras_Update (EKF)
%% ========================================================================
clear; clc; close all;

%% ---- 1. Donnees brutes (tableau EIS valide) ---------------------------
SOC = [5 10 15 20 25 30 40 50 60 70 80 90 95 100] / 100;   % SOC en fraction [0-1]

R0  = [33.20 28.17 33.48 30.71 29.10 29.06 27.36 26.92 27.52 27.37 27.57 28.89 30.66 24.33] * 1e-3; % Ohm
R1  = [110.45 59.02 50.61 45.79 42.40 37.46 34.27 36.13 54.07 45.39 42.15 37.49 34.46 40.52] * 1e-3; % Ohm
C1  = [35.3 14.3 614.0 1179.4 1456.7 1590.0 1623.5 1657.8 1295.6 1167.7 1050.3 866.8 554.4 3.7];      % Farad
OCV = [2.9263 3.2844 3.4141 3.4777 3.5074 3.5360 3.5985 3.6711 3.8220 3.8972 3.9753 4.0838 4.1418 4.2239]; % Volt

%% ---- 2. Choix de l'ordre des polynomes ---------------------------------
% OCV : ordre 6 minimum pour capturer les 2 plateaux + la chute finale
% R0, R1 : ordre 4-5 suffit (courbes plus lisses)
% C1 : ordre 6 (forte non-linearite, pic autour de 40-60% SOC)

n_OCV = 6;
n_R0  = 5;
n_R1  = 5;
n_C1  = 6;

p_OCV = polyfit(SOC, OCV, n_OCV);
p_R0  = polyfit(SOC, R0,  n_R0);
p_R1  = polyfit(SOC, R1,  n_R1);
p_C1  = polyfit(SOC, C1,  n_C1);

%% ---- 3. Verification visuelle -----------------------------------------
SOC_fine = linspace(0.01, 1, 500);

figure('Name','Validation des ajustements polynomiaux','Position',[100 100 1000 700]);

subplot(2,2,1);
plot(SOC*100, OCV, 'o', 'MarkerFaceColor','r'); hold on;
plot(SOC_fine*100, polyval(p_OCV, SOC_fine), 'b-','LineWidth',1.5);
xlabel('SOC (%)'); ylabel('OCV (V)'); title('OCV(SOC)'); grid on; legend('EIS','Fit poly','Location','best');

subplot(2,2,2);
plot(SOC*100, R0*1000, 'o', 'MarkerFaceColor','r'); hold on;
plot(SOC_fine*100, polyval(p_R0, SOC_fine)*1000, 'b-','LineWidth',1.5);
xlabel('SOC (%)'); ylabel('R0 (m\Omega)'); title('R0(SOC)'); grid on;

subplot(2,2,3);
plot(SOC*100, R1*1000, 'o', 'MarkerFaceColor','r'); hold on;
plot(SOC_fine*100, polyval(p_R1, SOC_fine)*1000, 'b-','LineWidth',1.5);
xlabel('SOC (%)'); ylabel('R1 (m\Omega)'); title('R1(SOC)'); grid on;

subplot(2,2,4);
plot(SOC*100, C1, 'o', 'MarkerFaceColor','r'); hold on;
plot(SOC_fine*100, polyval(p_C1, SOC_fine), 'b-','LineWidth',1.5);
xlabel('SOC (%)'); ylabel('C1 (F)'); title('C1(SOC)'); grid on;

%% ---- 4. Derivee analytique de OCV (necessaire pour la Jacobienne EKF) --
p_dOCV = polyder(p_OCV);   % coefficients de dOCV/dSOC

fprintf('\n=== Coefficients pretes a copier dans Simulink (ordre decroissant) ===\n\n');
fprintf('p_OCV  = %s\n', mat2str(p_OCV, 8));
fprintf('p_R0   = %s\n', mat2str(p_R0, 8));
fprintf('p_R1   = %s\n', mat2str(p_R1, 8));
fprintf('p_C1   = %s\n', mat2str(p_C1, 8));
fprintf('p_dOCV = %s   (derivee de p_OCV, pour matrice C de l''EKF)\n\n', mat2str(p_dOCV, 8));

%% ---- 5. Erreur d'ajustement (a verifier < erreur de mesure EIS) --------
err_OCV = OCV - polyval(p_OCV, SOC);
err_R0  = (R0  - polyval(p_R0,  SOC))*1000;
err_R1  = (R1  - polyval(p_R1,  SOC))*1000;
err_C1  = C1   - polyval(p_C1,  SOC);

fprintf('Erreur max ajustement OCV : %.4f V\n', max(abs(err_OCV)));
fprintf('Erreur max ajustement R0  : %.3f mOhm\n', max(abs(err_R0)));
fprintf('Erreur max ajustement R1  : %.3f mOhm\n', max(abs(err_R1)));
fprintf('Erreur max ajustement C1  : %.2f F\n', max(abs(err_C1)));

%% ---- 6. Sauvegarde pour reutilisation dans le modele Simulink ---------
save('ECM_NCR18650PF_params.mat', 'p_OCV','p_R0','p_R1','p_C1','p_dOCV','SOC','R0','R1','C1','OCV');