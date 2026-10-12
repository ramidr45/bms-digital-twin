% [Fichier renommé lors du rangement — ancien nom : gen.m]

Ah_ref = [0, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 1.75, 2.00, 2.25, 2.45];
V_ref  = [4.05, 3.88, 3.75, 3.66, 3.60, 3.55, 3.50, 3.44, 3.35, 3.10, 2.55];
I_dis  = 2.5;   % A — courant 1C

SOC_bp = [0 0.01 0.02 0.03 0.04 0.05 0.06 0.07 0.08 0.09 0.1 0.11 0.12 0.13 0.14 0.15 0.16 0.17 0.18 0.19 0.2 0.21 0.22 0.23 0.24 0.25 0.26 0.27 0.28 0.29 0.3 0.31 0.32 0.33 0.34 0.35 0.36 0.37 0.38 0.39 0.4 0.41 0.42 0.43 0.44 0.45 0.46 0.47 0.48 0.49 0.5 0.51 0.52 0.53 0.54 0.55 0.56 0.57 0.58 0.59 0.6 0.61 0.62 0.63 0.64 0.65 0.66 0.67 0.68 0.69 0.7 0.71 0.72 0.73 0.74 0.75 0.76 0.77 0.78 0.79 0.8 0.81 0.82 0.83 0.84 0.85 0.86 0.87 0.88 0.89 0.9 0.91 0.92 0.93 0.94 0.95 0.96 0.97 0.98 0.99 1];
OCV_bp = [2.80555 2.85959 2.91363 3.00304 3.0606 3.09933 3.12978 3.18381 3.23096 3.26469 3.2911 3.31202 3.33368 3.35023 3.3665 3.38187 3.39652 3.40935 3.42296 3.43602 3.4475 3.45894 3.46943 3.47583 3.48131 3.48929 3.49863 3.50723 3.51419 3.52064 3.52703 3.53288 3.5383 3.54248 3.54635 3.55067 3.55538 3.56162 3.56772 3.57355 3.57907 3.58466 3.59099 3.59795 3.60491 3.61176 3.61856 3.62438 3.62996 3.63625 3.64309 3.64978 3.65633 3.66344 3.67149 3.67995 3.68883 3.69977 3.7106 3.72128 3.72977 3.73862 3.74839 3.75854 3.76808 3.77731 3.78691 3.79724 3.80748 3.817 3.82465 3.83227 3.8402 3.84937 3.85948 3.87001 3.88001 3.88909 3.89708 3.90554 3.91623 3.9276 3.9408 3.95458 3.96671 3.97597 3.98588 3.99921 4.01279 4.02654 4.03959 4.05214 4.06294 4.07257 4.08033 4.08863 4.09953 4.11328 4.13091 4.15201 4.17387];

function V_sim = simulate_ecm(params, Ah_ref, I_dis, SOC_bp, OCV_bp)
    R0 = params(1); R1 = params(2); C1 = params(3);
    tau = R1 * C1;
    t_ref = Ah_ref / I_dis * 3600;   % temps en secondes
    SOC   = 1 - Ah_ref / 2.5;
    OCV   = interp1(SOC_bp, OCV_bp, SOC, 'linear');
    V_RC  = I_dis * R1 * (1 - exp(-t_ref / tau));
    V_sim = OCV - I_dis*R0 - V_RC;
end

% Fonction coût
cost = @(p) sum((simulate_ecm(p, Ah_ref, I_dis, SOC_bp, OCV_bp) - V_ref).^2);

% Optimisation
p0      = [0.013, 0.008, 2500];          % valeurs initiales
lb      = [0.005, 0.001,  100];          % bornes inf
ub      = [0.050, 0.050, 50000];         % bornes sup
options = optimset('Display','iter','TolFun',1e-8,'TolX',1e-8);
p_opt   = fminsearch(cost, p0, options);

fprintf('\n===== PARAMÈTRES IDENTIFIÉS =====\n');
fprintf('R0 = %.4f Ω  (%.2f mΩ)\n', p_opt(1), p_opt(1)*1000);
fprintf('R1 = %.4f Ω  (%.2f mΩ)\n', p_opt(2), p_opt(2)*1000);
fprintf('C1 = %.1f F  (τ = %.1f s)\n', p_opt(3), p_opt(2)*p_opt(3));
fprintf('=================================\n');

V_fit = simulate_ecm(p_opt, Ah_ref, I_dis, SOC_bp, OCV_bp);
figure;
plot(Ah_ref, V_ref, 'r--o', 'LineWidth',2, 'DisplayName','Référence');
hold on;
plot(Ah_ref, V_fit, 'b-',   'LineWidth',2, 'DisplayName','Modèle optimisé');
xlabel('Ah'); ylabel('V'); grid on; legend;
title('Identification R0 R1 C1 — Samsung INR18650-25R');
RMSE = sqrt(mean((V_fit - V_ref).^2))*1000;
fprintf('RMSE final : %.1f mV\n', RMSE);