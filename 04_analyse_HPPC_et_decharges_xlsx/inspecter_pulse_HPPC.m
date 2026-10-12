% [Fichier renommé lors du rangement — ancien nom : lut.m]
load('HPPC_data.mat')

% Inspecter les fronts
dI = diff(I);
pulse_on = find(dI > 0.2*max(abs(dI)));
ip = pulse_on(1);

fprintf('t=%.1f  I_avant=%.4f  I_apres=%.4f  dV=%.4f  V_avant=%.4f  V_apres=%.4f\n', ...
    t(ip), I(ip), I(ip+1), V(ip)-V(ip+1), V(ip), V(ip+1))

% Voir la relaxation qui suit
ip_off = find(dI(ip:end) < -0.2*max(abs(dI)), 1) + ip;
fprintf('Fin pulse t=%.1f\n', t(ip_off))
fprintf('I pendant repos: mean=%.6f  max=%.6f\n', ...
    mean(abs(I(ip_off+1:min(ip_off+100,end)))), ...
    max(abs(I(ip_off+1:min(ip_off+100,end)))))

% Voir la relaxation brute
t_rel = t(ip_off+1:ip_off+50) - t(ip_off+1);
V_rel = V(ip_off+1:ip_off+50);
disp([t_rel, V_rel])