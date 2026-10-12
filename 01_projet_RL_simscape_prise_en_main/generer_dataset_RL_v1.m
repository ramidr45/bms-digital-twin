% [Fichier renommé lors du rangement — ancien nom : rlsc.m]
%% ============================================================
%%  DIGITAL TWIN — ETAPE 2
%%  Génération du dataset via Simulink Simscape
%%  - 5 types d'entrée
%%  - Campagne 1 : R fixe, L varie (6 valeurs)
%%  - Campagne 2 : L fixe, R varie (6 valeurs)
%%  Sortie : RL_simscape_dataset.csv
%% ============================================================
clc; clear; close all;

fprintf('=====================================\n');
fprintf('  ETAPE 2 — Génération dataset\n');
fprintf('=====================================\n\n');

%% ---- PARAMETRES DE BASE ------------------------------------
mdl = 'rl';          % nom de ton fichier Simulink (sans .slx)
load_system(mdl);

Fs  = 1e4;           % fréquence d'échantillonnage [Hz]

%% ---- GRILLES DE PARAMETRES ---------------------------------
% Campagne 1 : R fixe, L varie
R_c1 = 1000;
L_c1 = [0.01, 0.05, 0.1, 0.2, 0.5, 1.0];

% Campagne 2 : L fixe, R varie
L_c2 = 0.1;
R_c2 = [100, 500, 1000, 2000, 5000, 10000];

% Fusion des deux campagnes
R_list = [R_c1*ones(1,6),  R_c2];
L_list = [L_c1,             L_c2*ones(1,6)];
n_conf = length(R_list);

% Types d'entrée
input_labels = {'impulsion','echelon','rampe','sin_bas','sin_haut'};
n_types = 5;

%% ---- BOUCLE PRINCIPALE -------------------------------------
dataset = [];
total   = n_conf * n_types;
cnt     = 0;

for ci = 1:n_conf
    R   = R_list(ci);
    L   = L_list(ci);
    tau = L / R;
    t   = (0 : 1/Fs : 6*tau)';
    N   = length(t);

    % Configurer R et L dans le modèle Simulink
    set_param([mdl '/Resistor'],  'R', num2str(R));
    set_param([mdl '/Inductor'],  'L', num2str(L));
    set_param(mdl, 'StopTime',    num2str(6*tau));
    set_param(mdl, 'Solver',      'ode23t');

    % Générer les 5 signaux d'entrée
    f_c    = R / (2*pi*L);
    inputs = {
        [zeros(N,1); 0],  ...   % placeholder impulsion
        ones(N,1),        ...   % échelon
        t/max(t),         ...   % rampe
        sin(2*pi*(f_c/2)*t), ...  % sin basse fréq
        sin(2*pi*(f_c*5)*t)  ...  % sin haute fréq
    };
    % Impulsion : premier échantillon = Fs, reste = 0
    inputs{1} = zeros(N,1); inputs{1}(1) = Fs;

    for ki = 1:n_types
        cnt = cnt + 1;

        % Injecter le signal dans From Workspace
        e_in = timeseries(inputs{ki}, t);
        assignin('base', 'e_in', e_in);

        % Lancer la simulation
        sim(mdl);

        % Récupérer la sortie
        try
            s_k = s_out.Data(:);
            t_k = s_out.Time(:);
        catch
            s_k = s_out(:);
            t_k = t(1:length(s_k));
        end

        % Uniformiser la longueur (interpolation si nécessaire)
        s_uni = interp1(t_k, s_k, t, 'linear', 'extrap');

        % Ajouter au dataset
        block = [t, inputs{ki}, s_uni, ...
                 ki*ones(N,1), R*ones(N,1), ...
                 L*ones(N,1), tau*ones(N,1)];
        dataset = [dataset; block]; %#ok<AGROW>

        fprintf('[%2d/%2d] R=%5.0f Ω  L=%.3f H  tau=%.5f s  entrée=%-12s → %d pts\n', ...
                cnt, total, R, L, tau, input_labels{ki}, N);
    end
end

%% ---- SAUVEGARDE CSV ----------------------------------------
col_names = {'t','e_t','s_t','type_id','R','L','tau'};
T = array2table(dataset, 'VariableNames', col_names);
writetable(T, 'RL_simscape_dataset.csv');
fprintf('\nDataset sauvegardé : RL_simscape_dataset.csv\n');
fprintf('Taille : %d lignes × %d colonnes\n\n', size(dataset,1), size(dataset,2));

%% ---- VISUALISATION RAPIDE ----------------------------------
figure('Name','Aperçu dataset','Position',[100 100 1200 400]);

% Réponse échelon pour 3 configurations
configs_idx = [2, 8, 9];   % échelon, 3 valeurs de tau différentes
colors = {[0.2 0.6 0.8], [0.2 0.7 0.4], [0.85 0.36 0.19]};
subplot(1,2,1); hold on;
for i = 1:3
    ci  = configs_idx(i);
    R_i = R_list(ci); L_i = L_list(ci);
    idx = dataset(:,4)==2 & dataset(:,5)==R_i & dataset(:,6)==L_i;
    t_i = dataset(idx,1); s_i = dataset(idx,3);
    plot(t_i*1000, s_i, 'Color', colors{i}, 'LineWidth', 2, ...
         'DisplayName', sprintf('R=%d L=%.2f τ=%.4f', R_i, L_i, L_i/R_i));
end
legend('Location','southeast','FontSize',8);
title('Réponses échelon — 3 configurations');
xlabel('t [ms]'); ylabel('i(t) [A]'); grid on;

% Distribution de tau dans le dataset
subplot(1,2,2);
histogram(dataset(:,7), 40, 'FaceColor','#378ADD', 'EdgeColor','none');
title('Distribution τ dans le dataset');
xlabel('τ [s]'); ylabel('Nb échantillons'); grid on;

sgtitle('Étape 2 — Dataset Simscape généré');


