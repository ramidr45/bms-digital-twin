% [Fichier renommé lors du rangement — ancien nom : hppc.m]
%% generer_signal_HPPC.m
% Génère le profil de courant HPPC pour le montage Simulink avec :
%   - bloc batterie NCR18650BD (port Ta, sortie bus <SOC,Current,Voltage>)
%   - pas de simulation discret fixe (Discrete, 1s)
%
% Remplace le bloc "Pulse 0.5C 10%" par un bloc "From Workspace" alimenté
% par la variable HPPC_signal générée ici.
%
% Convention de signe à VERIFIER sur votre source de courant contrôlée :
% ici, courant POSITIF = décharge (cellule perd de la capacité).
% Si votre source utilise la convention inverse, changez le signe de
% I_pulse_dis, I_pulse_chg, I_soc_adj ci-dessous.

clear; clc;

%% ---------------- PARAMETRES CELLULE NCR18650BD ----------------
Capacity_Ah = 3.35;          % Ah, capacité nominale
Crate_dis   = 1;             % 1C pour le pulse de décharge (standard HPPC)
Crate_chg   = 0.75;          % 0.75C pour le pulse de charge
Crate_adj   = 1/3;           % C/3 pour la décharge inter-palier

I_pulse_dis = Crate_dis * Capacity_Ah;
I_pulse_chg = Crate_chg * Capacity_Ah;
I_soc_adj   = Crate_adj * Capacity_Ah;

%% ---------------- PARAMETRES TEMPORELS ----------------
% IMPORTANT : votre modèle tourne en pas discret de 1s (bloc "Discrete, 1s").
% Le profil ci-dessous est donc généré directement avec dt = 1s pour
% coller exactement aux instants de simulation -> pas d'interpolation
% parasite dans le bloc From Workspace.
dt        = 1;       % s, doit correspondre au pas discret du modèle
t_pulse   = 10;       % s, durée de chaque impulsion
t_rest1   = 40;       % s, repos entre pulse décharge et pulse charge
t_rest2   = 40;       % s, repos après le pulse de charge
t_relax   = 3600;     % s, repos long entre paliers de SOC (1h)

SOC_start = 100;
SOC_end   = 0;
SOC_step  = 10;
SOC_vec   = SOC_start:-SOC_step:SOC_end;

t_soc_adj = (SOC_step/100) * Capacity_Ah * 3600 / I_soc_adj;  % s

%% ---------------- CONSTRUCTION DU PROFIL ----------------
t_list = []; i_list = []; t_now = 0;

for k = 1:length(SOC_vec)
    [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, 100, 0, dt);          % court repos avant pulse
    [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_pulse, I_pulse_dis, dt);   % pulse décharge
    [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_rest1, 0, dt);             % repos
    [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_pulse, -I_pulse_chg, dt);  % pulse charge
    [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_rest2, 0, dt);             % repos

    if k < length(SOC_vec)
        [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_soc_adj, I_soc_adj, dt);  % décharge inter-palier
        [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, t_relax, 0, dt);             % repos long
    end
end

time    = t_list(:);
current = i_list(:);

HPPC_signal = timeseries(current, time);

fprintf('Profil HPPC genere : %.0f s (%.2f h), %d points, %d paliers SOC, dt=%ds\n', ...
    time(end), time(end)/3600, length(time), length(SOC_vec), dt);

%% ---------------- VERIFICATION ----------------
figure('Name','Profil HPPC - pas discret 1s');
plot(time/3600, current, 'b-','LineWidth',1.1);
xlabel('Temps (h)'); ylabel('Courant (A)  [+ = décharge, - = charge]');
title('Profil HPPC NCR18650BD - dt = 1s');
grid on;

%% ---------------- FONCTION LOCALE ----------------
function [t_now, t_list, i_list] = add_segment(t_now, t_list, i_list, duration, current_value, dt)
    n = max(round(duration/dt), 1);
    t_seg = t_now + (0:n-1)'*dt;
    i_seg = current_value * ones(n,1);
    t_list = [t_list; t_seg];
    i_list = [i_list; i_seg];
    t_now  = t_now + n*dt;
end