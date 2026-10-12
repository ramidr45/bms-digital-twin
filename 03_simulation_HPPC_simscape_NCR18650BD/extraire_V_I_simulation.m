% [Fichier renommé lors du rangement — ancien nom : extrairevt.m]
%% Extraction des données de simulation
time_sim    = out.Vbatt.Time;
voltage_sim = out.Vbatt.Data;
current_sim = out.Ibatt.Data;

% Vérification
figure;
subplot(2,1,1)
plot(time_sim/3600, voltage_sim, 'b', 'LineWidth', 1.2)
xlabel('Temps (h)'); ylabel('Tension (V)')
title('Tension HPPC — NCR18650BD')
grid on

subplot(2,1,2)
plot(time_sim/3600, current_sim, 'r', 'LineWidth', 1.2)
xlabel('Temps (h)'); ylabel('Courant (A)')
title('Courant HPPC')
grid on

save('HPPC_data.mat', 'time_sim', 'voltage_sim', 'current_sim')
disp('Données sauvegardées ✓')