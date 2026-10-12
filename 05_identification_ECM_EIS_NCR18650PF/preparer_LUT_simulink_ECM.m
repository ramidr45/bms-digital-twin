% [Fichier renommé lors du rangement — ancien nom : battery_model_generator.m]
% Conversion en vecteurs lignes pour Simulink
SOC_sim_lut = SOC_f(:)';       % ex: [0.05, 0.10, ..., 1.00]
R0_sim      = R0_f(:)';        % en Ohms
R1_sim      = R1_f(:)';        % en Ohms
C1_sim      = C1_f(:)';        % en Farads
OCV_sim     = OCV_s(:)';       % en Volts

% Calcul de la condition initiale de V_RC pour éviter un pic au démarrage
% V_RC(0) = I * R1(SOC=1)
V_RC_init = I_1C * interp1(SOC_f, R1_f, 0.99); 
fprintf('Condition initiale V_RC = %.4f V\n', V_RC_init);%% ── PRÉPARATION UNIFORMISÉE POUR SIMULINK ─────────────────────────────
% Toutes les Lookup Tables doivent avoir la MÊME taille de breakpoints

% Vecteur SOC commun (14 points, triés croissants)
SOC_sim_lut = sort(SOC_f(:))';   % Ligne : [0.05, 0.10, ..., 1.00]

% Paramètres R0, R1, C1 (déjà sur 14 points)
R0_sim = interp1(SOC_f, R0_f, SOC_sim_lut, 'linear', 'extrap');
R1_sim = interp1(SOC_f, R1_f, SOC_sim_lut, 'linear', 'extrap');
C1_sim = interp1(SOC_f, C1_f, SOC_sim_lut, 'linear', 'extrap');

% ️ CRITIQUE : Interpoler OCV sur les MÊMES 14 points SOC
OCV_sim = interp1(SOC_ds_s, OCV_s, SOC_sim_lut, 'pchip', 'extrap');

% Vérification des tailles
fprintf('✓  Taille SOC_sim_lut : %d points\n', length(SOC_sim_lut));
fprintf('✓  Taille R0_sim      : %d points\n', length(R0_sim));
fprintf('✓  Taille R1_sim      : %d points\n', length(R1_sim));
fprintf('✓  Taille C1_sim      : %d points\n', length(C1_sim));
fprintf('✓  Taille OCV_sim     : %d points\n', length(OCV_sim));

% Sauvegarde pour Simulink
save('ECM_Parameters.mat', 'SOC_sim_lut', 'R0_sim', 'R1_sim', 'C1_sim', 'OCV_sim');
fprintf('✅  Paramètres sauvegardés dans ECM_Parameters.mat\n');

% Affichage du tableau final
fprintf('\n%s\n', repmat('═',1,70));
fprintf('  TABLEAU FINAL POUR SIMULINK (14 points SOC)\n');
fprintf('%s\n', repmat('═',1,70));
fprintf('  %5s  %8s  %8s  %8s  %7s\n', 'SOC', 'R0 mΩ', 'R1 mΩ', 'C1 F', 'OCV V');
fprintf('%s\n', repmat('─',1,70));
for k = 1:length(SOC_sim_lut)
    fprintf('  %4.0f%%  %8.2f  %8.2f  %8.1f  %7.4f\n', ...
        SOC_sim_lut(k)*100, R0_sim(k)*1e3, R1_sim(k)*1e3, C1_sim(k), OCV_sim(k));
end
fprintf('%s\n', repmat('═',1,70));
