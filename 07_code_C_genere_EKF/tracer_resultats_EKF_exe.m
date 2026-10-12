% [Fichier renommé lors du rangement — ancien nom : plot_results.m]
%% tracer_resultats_EKF_exe.m — Visualisation des résultats EKF
% Charger et tracer test_output.csv généré par test_ekf.exe

clear; clc; close all;

%% 1. Charger le fichier CSV
data = readtable('test_output.csv');

% Créer un vecteur temps (pas = 1s par défaut, ajustez Ts si nécessaire)
Ts = 1;  % Période d'échantillonnage [s]
N  = height(data);
t  = (0:N-1)' * Ts;

%% 2. Plot SOC estimé
figure('Name','Résultats EKF','Color','w','Position',[100 100 900 700]);

subplot(3,1,1);
plot(t, data.SOC_upd, 'b-', 'LineWidth', 1.5);
xlabel('Temps [s]');
ylabel('SOC');
title('État de Charge estimé (SOC)');
grid on;
ylim([0 1]);

%% 3. Plot tension de polarisation Up
subplot(3,1,2);
plot(t, data.Up_upd, 'r-', 'LineWidth', 1.5);
xlabel('Temps [s]');
ylabel('Up [V]');
title('Tension de polarisation estimée (Up)');
grid on;

%% 4. Plot matrice de covariance P (diagonale)
subplot(3,1,3);
plot(t, data.P_upd0, 'g-', 'LineWidth', 1.5); hold on;
plot(t, data.P_upd3, 'm-', 'LineWidth', 1.5);
xlabel('Temps [s]');
ylabel('P');
title('Éléments diagonaux de la covariance P');
legend('P(1,1) — variance SOC', 'P(2,2) — variance Up', 'Location','best');
grid on;

sgtitle('Résultats du filtre de Kalman étendu (EKF)', 'FontSize', 14, 'FontWeight', 'bold');

%% 5. Charger aussi les entrées pour comparaison (optionnel)
if isfile('test_input.csv')
    input_data = readmatrix('test_input.csv');
    courant = input_data(:,1);
    tension = input_data(:,2);
    t_in = (0:length(courant)-1)' * Ts;

    figure('Name','Entrées','Color','w','Position',[100 100 900 500]);

    subplot(2,1,1);
    plot(t_in, courant, 'k-', 'LineWidth', 1);
    xlabel('Temps [s]'); ylabel('Courant [A]');
    title('Courant mesuré (entrée)');
    grid on;

    subplot(2,1,2);
    plot(t_in, tension, 'b-', 'LineWidth', 1);
    xlabel('Temps [s]'); ylabel('Tension [V]');
    title('Tension mesurée (entrée)');
    grid on;

    sgtitle('Signaux d''entrée', 'FontSize', 14, 'FontWeight', 'bold');
end

fprintf('Données chargées : %d échantillons\n', N);
fprintf('SOC final estimé : %.4f\n', data.SOC_upd(end));
