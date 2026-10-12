% [Fichier renommé lors du rangement — ancien nom : visul_outputc.m]
%% Lire le fichier CSV
data = readtable('test_output.csv');

%% Extraire le SOC
SOC = data.SOC_upd;

%% Axe des échantillons
k = 1:length(SOC);

%% Afficher le SOC en pourcentage
figure;

plot(k, SOC * 100, 'LineWidth', 1.5);

grid on;

xlabel('Numéro de l''échantillon');
ylabel('SOC (%)');

title('Estimation du SOC par EKF');

ylim([0 100]);