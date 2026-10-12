% [Fichier renommé lors du rangement — ancien nom : inspect_dichage1c_dataset.m]
%% ========================================================================
%  Inspection de la structure d'un fichier .mat (dataset Panasonic 18650PF)
%% ========================================================================
clear; clc;

fpath = 'C:\Users\SAT\Desktop\dataset\25degC\25degC\Drive cycles\03-18-17_02.17 25degC_Cycle_1_Pan18650PF.mat';

fprintf('=== Variables contenues dans le fichier ===\n');
info = whos('-file', fpath);
for k = 1:length(info)
    fprintf('  %-20s  type=%-15s  taille=%s\n', info(k).name, info(k).class, mat2str(info(k).size));
end

fprintf('\n=== Chargement et inspection détaillée ===\n');
S = load(fpath);
varnames = fieldnames(S);

for k = 1:length(varnames)
    v = S.(varnames{k});
    fprintf('\n--- Variable "%s" (classe: %s) ---\n', varnames{k}, class(v));

    if isstruct(v)
        fn = fieldnames(v);
        fprintf('  Champs de la struct :\n');
        for j = 1:length(fn)
            val = v.(fn{j});
            sz = size(val);
            fprintf('    %-20s  size=%s  class=%s\n', fn{j}, mat2str(sz), class(val));
        end
        % Affiche les 5 premières valeurs de chaque champ numérique pour identification
        fprintf('\n  Aperçu des premières valeurs :\n');
        for j = 1:length(fn)
            val = v.(fn{j});
            if isnumeric(val) && numel(val) > 1
                preview = val(1:min(5,numel(val)));
                fprintf('    %s(1:5) = %s\n', fn{j}, mat2str(preview(:)', 4));
            end
        end
    elseif istimetable(v) || istable(v)
        fprintf('  Colonnes : %s\n', strjoin(v.Properties.VariableNames, ', '));
        disp(head(v, 5));
    elseif isnumeric(v)
        fprintf('  Matrice numérique, size=%s\n', mat2str(size(v)));
        disp(v(1:min(5,size(v,1)), :));
    else
        fprintf('  (type non géré automatiquement, inspecte manuellement)\n');
    end
end
function SOC_k = fcn(IL, SOC_k1)
    Ts = 1;      % ton Ts réel
    Cn = 2.9;    % Ah
    SOC_k = SOC_k1 - (Ts/(Cn*3600)) * IL;
end