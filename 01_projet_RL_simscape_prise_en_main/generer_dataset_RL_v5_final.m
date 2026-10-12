% [Fichier renommé lors du rangement — ancien nom : dataset_simulink.m]
%% ============================================================
%%  DIGITAL TWIN — ETAPE 2 (version finale v5)
%%  Méthode : Outport au lieu de To Workspace
%%  Ajoute un bloc Outport dans Simulink connecté après PS-Simulink
%%  → simOut.yout contient directement s(t)
%% ============================================================
clc; clear; close all;

fprintf('=====================================\n');
fprintf('  ETAPE 2 — Génération dataset\n');
fprintf('=====================================\n\n');

%% ---- PARAMETRES --------------------------------------------
mdl = 'rl';
load_system(mdl);

% Configuration simulation
set_param(mdl, 'SaveOutput',       'on');
set_param(mdl, 'OutputSaveName',   'yout');
set_param(mdl, 'SaveFormat',       'Array');
set_param(mdl, 'ReturnWorkspaceOutputsName', 'simOut');

Fs = 1e4;

%% ---- GRILLES -----------------------------------------------
R_c1   = 1000;
L_c1   = [0.01, 0.05, 0.1, 0.2, 0.5, 1.0];
L_c2   = 0.1;
R_c2   = [100, 500, 1000, 2000, 5000, 10000];
R_list = [R_c1*ones(1,6), R_c2];
L_list = [L_c1,           L_c2*ones(1,6)];
n_conf = length(R_list);

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

    % Vecteur temps — minimum 200 points
    N     = max(200, round(6*tau*Fs));
    t     = linspace(0, 6*tau, N)';
    dt    = t(2) - t(1);
    t_end = t(end);

    % Changer paramètres dans Simulink
    set_param('rl/Resistor', 'R', num2str(R));
    set_param('rl/Inductor', 'L', num2str(L));
    set_param(mdl, 'StopTime', num2str(t_end));

    % ---- Générer les 5 entrées ----
    f_c    = R / (2*pi*L);
    e_imp  = zeros(N,1); e_imp(1) = 1/dt;
    e_ech  = ones(N,1);
    e_ramp = linspace(0,1,N)';
    e_sinL = sin(2*pi*(f_c/2)*t);
    e_sinH = sin(2*pi*(f_c*5)*t);
    inputs = {e_imp, e_ech, e_ramp, e_sinL, e_sinH};

    for ki = 1:n_types
        cnt = cnt + 1;

        sig = inputs{ki};
        sig(~isfinite(sig)) = 0;

        % Injecter signal
        e_in = timeseries(double(sig), t);
        assignin('base','e_in', e_in);

        % Lancer simulation
        try
            simOut = sim(mdl, 'ReturnWorkspaceOutputs','on');
        catch ME
            fprintf('[%2d/%2d] ERREUR sim: %s\n', cnt, total, ME.message);
            continue;
        end

        % ---- Extraire la sortie depuis simOut ----
        s_vec = [];
        t_sim = [];

        % Essai 1 : simOut.yout (si Outport connecté)
        try
            yo = simOut.yout;
            if ~isempty(yo) && isnumeric(yo)
                s_vec = double(yo(:,end));
                t_sim = simOut.tout(:);
            end
        catch; end

        % Essai 2 : simOut.get('yout')
        if isempty(s_vec)
            try
                yo = simOut.get('yout');
                if isnumeric(yo) && numel(yo)>1
                    s_vec = double(yo(:));
                    t_sim = simOut.tout(:);
                end
            catch; end
        end

        % Essai 3 : simOut.logsout
        if isempty(s_vec)
            try
                lg    = simOut.get('logsout');
                names = lg.getElementNames();
                sig_s = lg.getElement(names{1});
                s_vec = double(sig_s.Values.Data(:));
                t_sim = sig_s.Values.Time(:);
            catch; end
        end

        % Essai 4 : lire tout le contenu de simOut
        if isempty(s_vec)
            try
                fields = fieldnames(simOut);
                for fi = 1:length(fields)
                    val = simOut.(fields{fi});
                    if isnumeric(val) && numel(val) > 10
                        s_vec = double(val(:));
                        t_sim = simOut.tout(:);
                        break;
                    end
                end
            catch; end
        end

        % Essai 5 : lire s_out depuis workspace base
        if isempty(s_vec)
            try
                raw = evalin('base','s_out');
                if isnumeric(raw) && numel(raw)>1
                    s_vec = double(raw(:));
                    t_sim = simOut.tout(:);
                    n_min = min(length(s_vec),length(t_sim));
                    s_vec = s_vec(1:n_min);
                    t_sim = t_sim(1:n_min);
                elseif isstruct(raw)
                    s_vec = double(raw.signals.values(:));
                    t_sim = raw.time(:);
                elseif isa(raw,'timeseries')
                    s_vec = double(raw.Data(:));
                    t_sim = raw.Time(:);
                end
            catch; end
        end

        % Vérification finale
        if isempty(s_vec) || length(s_vec) < 2
            fprintf('[%2d/%2d] %-12s — sortie non récupérée (%d pts)\n',...
                    cnt,total,input_labels{ki},length(s_vec));
            continue;
        end

        % Ajuster longueurs
        n_min = min(length(t_sim), length(s_vec));
        t_sim = t_sim(1:n_min);
        s_vec = s_vec(1:n_min);

        % Interpoler sur t uniforme
        s_uni = interp1(t_sim, s_vec, t, 'linear','extrap');

        % Stocker
        block = [t, sig, s_uni, ...
                 ki*ones(N,1), R*ones(N,1), ...
                 L*ones(N,1), tau*ones(N,1)];
        dataset = [dataset; block]; %#ok<AGROW>

        fprintf('[%2d/%2d] R=%6.0f  L=%.3f  τ=%.5f  %-12s → %d pts OK\n',...
                cnt,total,R,L,tau,input_labels{ki},N);
    end
end

%% ---- SAUVEGARDE --------------------------------------------
if isempty(dataset)
    fprintf('\nDataset vide — vérifie les messages ci-dessus.\n');
    fprintf('==> Solution : dans Simulink, connecte un bloc Outport\n');
    fprintf('    (Simulink->Sinks->Out1) après le PS-Simulink Converter.\n');
    return;
end

col_names = {'t','e_t','s_t','type_id','R','L','tau'};
T = array2table(dataset,'VariableNames',col_names);
writetable(T,'RL_simscape_dataset.csv');
fprintf('\nDataset : %d lignes — RL_simscape_dataset.csv\n',size(dataset,1));

%% ---- VISUALISATION -----------------------------------------
figure('Name','Dataset','Position',[50 50 1200 400]);
subplot(1,2,1); hold on; grid on;
clrs = lines(6);
for ci=1:min(6,n_conf)
    Ri=R_list(ci); Li=L_list(ci);
    idx=dataset(:,4)==2 & dataset(:,5)==Ri & dataset(:,6)==Li;
    if sum(idx)>1
        plot(dataset(idx,1)*1000,dataset(idx,3),...
             'Color',clrs(ci,:),'LineWidth',1.5,...
             'DisplayName',sprintf('τ=%.4f',Li/Ri));
    end
end
legend('FontSize',7,'Location','se');
title('Échelon — variation L'); xlabel('t [ms]'); ylabel('i(t) [A]');

subplot(1,2,2);
histogram(dataset(:,7),40,'FaceColor','#378ADD','EdgeColor','none');
title('Distribution τ'); xlabel('τ [s]'); grid on;
sgtitle('Étape 2 — Dataset Simscape');
fprintf('Terminé !\n');