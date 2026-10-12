% [Fichier renommé lors du rangement — ancien nom : build_tuvar.m]
%% preparer_entree_drive_cycle.m (version corrigee)
% Charge un fichier .mat de drive cycle reel (format meas.Time/Current/...)
% et construit tuvar/vuvar nettoyes + reechantillonnes pour Simulink
clear tuvar vuvar;

drive_cycle_file = 'C:\Users\SAT\Desktop\dataset\25degC\25degC\Drive cycles\03-20-17_01.43 25degC_US06_Pan18650PF.mat';
data = load(drive_cycle_file);
meas = data.meas;

%% ── Nettoyage des doublons temporels ---------------------------------------
t_raw = meas.Time(:);
V_raw = meas.Voltage(:);
I_raw = meas.Current(:);   % signe natif conserve (I<0 = decharge)

dt = diff(t_raw);
dup_idx = find(dt <= 0);
fprintf('Points dupliques supprimes : %d\n', length(dup_idx));

keep = true(size(t_raw));
keep(dup_idx+1) = false;
t_clean = t_raw(keep);
V_clean = V_raw(keep);
I_clean = I_raw(keep);

%% ── Re-echantillonnage uniforme ---------------------------------------------
Ts = 0.1;
t_uniform = (t_clean(1) : Ts : t_clean(end))';
I = interp1(t_clean, I_clean, t_uniform, 'linear');
V = interp1(t_clean, V_clean, t_uniform, 'linear');
Time = t_uniform;

%% ── Variables finales pour Simulink -------------------------------------------
tuvar = [Time, I];
vuvar = [Time, V];

fprintf('\ntuvar final : %d points, Ts=%.2fs uniforme, duree=%.1f min\n', ...
    length(Time), Ts, Time(end)/60);
fprintf('Courant : min=%.3f A, max=%.3f A (signe brut, negatif = decharge)\n', ...
    min(I), max(I));
fprintf('Tension : min=%.4f V, max=%.4f V\n', min(V), max(V));
% À la suite de ton script build_tuvar.m
writematrix([I, V], 'test_input.csv')