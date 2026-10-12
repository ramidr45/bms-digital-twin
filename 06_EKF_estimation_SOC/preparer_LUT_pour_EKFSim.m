% [Fichier renommé lors du rangement — ancien nom : build_simulink_LUTs.m]
%% preparer_LUT_pour_EKFSim.m
% Prepare les variables workspace necessaires pour remplacer les blocs
% Fcn (r0, rp, cp, uoc) du modele Simulink EKFSim.slx par des
% blocs "1-D Lookup Table", bases sur les donnees EIS reelles NCR18650PF.

if ~isfile('ECM_NCR18650PF_25degC.mat')
    run('construire_LUT_ECM_25degC.m');
else
    load('ECM_NCR18650PF_25degC.mat', 'ECM');
end

% Breakpoints fins (0.05 a 1.00, resolution 1%) via pchip - lisse et
% sans oscillation, comme etabli precedemment.
SOC_bp = (5:1:100)' / 100;   % colonne, fraction 0-1, de 5% a 100%

R0_bp  = interp1(ECM.SOC_table, ECM.R0_table, SOC_bp, 'pchip');  % Ohm
R1_bp  = interp1(ECM.SOC_table, ECM.R1_table, SOC_bp, 'pchip');  % Ohm
C1_bp  = interp1(ECM.SOC_table, ECM.C1_table, SOC_bp, 'pchip');  % F
OCV_bp = ppval(ECM.pp_OCV, SOC_bp);                              % V

fprintf('Variables crees dans le workspace :\n');
fprintf('  SOC_bp  (%d points, breakpoints, 0.05 a 1.00)\n', length(SOC_bp));
fprintf('  R0_bp, R1_bp, C1_bp, OCV_bp (valeurs correspondantes)\n');
fprintf('\nCes variables doivent rester dans le workspace MATLAB quand tu lances la simulation Simulink.\n');