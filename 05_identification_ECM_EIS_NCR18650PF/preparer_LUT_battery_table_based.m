% [Fichier renommé lors du rangement — ancien nom : build_lut_1rc.m]
%% ========================================================================
%  Construction des variables workspace pour le bloc Simscape
%  "Battery (Table-Based)"
%
%  A executer APRES ton script d'identification EIS NCR18650PF (meme
%  session MATLAB -- reutilise SOC_f, R0_f, R1_f, tau1_f, SOC_ds_s,
%  OCV_s, C_nom deja en memoire).
%
%  Cree :
%    SOC_vec   -- vecteur SOC (grille commune, croissant, fraction 0-1)
%    OCV_vec   -- V0(SOC), depuis la courbe OCV calibree (plus lisse)
%    R0_vec    -- R0(SOC)
%    R1_vec    -- R1(SOC)
%    tau1_vec  -- tau1(SOC)
%    Cap_Ah    -- capacite nominale en Ah
% ========================================================================

%% ── 0. Verifier que les variables source existent ───────────────────────
required = {'SOC_f','R0_f','R1_f','tau1_f','SOC_ds_s','OCV_s','C_nom'};
for k = 1:length(required)
    if ~exist(required{k}, 'var')
        error(['Variable "%s" introuvable. Relance d''abord ton script ' ...
               'd''identification EIS NCR18650PF (meme session MATLAB).'], ...
               required{k});
    end
end

%% ── 1. Grille SOC commune (celle deja issue de l'identification EIS) ────
% SOC_f est deja trie croissant a la fin du script d'identification.
SOC_vec = SOC_f(:);

%% ── 2. R0, R1, tau1 : directement les valeurs identifiees par EIS ───────
R0_vec   = R0_f(:);      % Ohm
R1_vec   = R1_f(:);      % Ohm
tau1_vec = tau1_f(:);    % s

%% ── 3. OCV : interpole sur la meme grille SOC_vec depuis la courbe ──────
%      calibree (plus lisse / plus de points que les 14 paliers EIS)
OCV_vec = interp1(SOC_ds_s, OCV_s, SOC_vec, 'pchip', 'extrap');

%% ── 4. Capacite nominale en Ah ───────────────────────────────────────────
Cap_Ah = C_nom / 1000;   % C_nom etait en mAh dans le script EIS

%% ── 5. Verifications rapides ─────────────────────────────────────────────
fprintf('\n--- Variables pretes pour le bloc Battery (Table-Based) ---\n');
fprintf('SOC_vec  : %d points, %.0f%% -> %.0f%%\n', ...
    length(SOC_vec), SOC_vec(1)*100, SOC_vec(end)*100);
fprintf('OCV_vec  : %.4f V -> %.4f V\n', OCV_vec(1), OCV_vec(end));
fprintf('R0_vec   : %.4f -> %.4f Ohm\n', R0_vec(1), R0_vec(end));
fprintf('R1_vec   : %.4f -> %.4f Ohm\n', R1_vec(1), R1_vec(end));
fprintf('tau1_vec : %.3f -> %.3f s\n', tau1_vec(1), tau1_vec(end));
fprintf('Cap_Ah   : %.3f Ah\n', Cap_Ah);

if any(diff(SOC_vec) <= 0)
    warning('SOC_vec n''est pas strictement croissant -- le bloc Battery risque de rejeter la table.');
end

fprintf('\nVariables chargees dans le workspace. Rouvre le bloc "Battery (Table-Based)"\n');
fprintf('et clique Apply -- les erreurs SOC_vec/OCV_vec/R0_vec/R1_vec/tau1_vec/Cap_Ah\n');
fprintf('devraient disparaitre.\n');