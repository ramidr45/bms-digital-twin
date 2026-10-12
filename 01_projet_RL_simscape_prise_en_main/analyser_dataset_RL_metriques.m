% [Fichier renommé lors du rangement — ancien nom : metriques.m]
%% ============================================================
%%  DIGITAL TWIN — ETAPE 3
%%  Métriques + Visualisations + Ridge + Régression Linéaire
%% ============================================================
clc; clear; close all;

fprintf('=========================================\n');
fprintf('  ETAPE 3 — Métriques & Modèles\n');
fprintf('=========================================\n\n');

%% ============================================================
%%  SECTION 1 : CHARGEMENT
%% ============================================================
T        = readtable('RL_simscape_dataset.csv');
dat      = table2array(T);
t_col    = dat(:,1);
e_col    = dat(:,2);
s_col    = dat(:,3);
type_col = dat(:,4);
R_col    = dat(:,5);
L_col    = dat(:,6);
tau_col  = dat(:,7);

type_labels = {'Impulsion','Echelon','Rampe','Sin bas','Sin haut'};
tau_u       = unique(tau_col);
n_types     = 5;

fprintf('Dataset : %d lignes x %d colonnes\n\n', size(dat,1), size(dat,2));

%% ============================================================
%%  SECTION 2 : METRIQUES CONSOLE
%% ============================================================
fprintf('%-14s  %10s  %10s  %10s  %10s  %10s\n',...
        'Type','min s','max s','mean s','std s','RMS err');
fprintf('%s\n', repmat('-',1,70));
for k = 1:n_types
    idx = type_col==k;
    s_k = s_col(idx); e_k = e_col(idx);
    fprintf('%-14s  %10.5f  %10.5f  %10.5f  %10.5f  %10.5f\n',...
            type_labels{k},min(s_k),max(s_k),mean(s_k),std(s_k),rms(s_k-e_k));
end

fprintf('\nCorr e(t)/s(t) :\n');
for k = 1:n_types
    idx = type_col==k;
    c   = corrcoef(e_col(idx),s_col(idx));
    fprintf('  %-14s : r = %.4f\n', type_labels{k}, c(1,2));
end
fprintf('\nτ : min=%.6fs  max=%.6fs  nb configs=%d\n\n',...
        min(tau_u), max(tau_u), length(tau_u));

%% ============================================================
%%  SECTION 3 : PREPARATION MODELES
%% ============================================================
% Features normalisées
Rn  = (R_col   - mean(R_col))   / std(R_col);
Ln  = (L_col   - mean(L_col))   / std(L_col);
Tn  = (tau_col - mean(tau_col)) / std(tau_col);
X   = [e_col, Rn, Ln, Tn, type_col];
y   = s_col;

% Split 80/20 reproductible
rng(42);
n    = length(y);
idx  = randperm(n);
ntr  = round(0.8*n);
Xtr  = X(idx(1:ntr),:);     ytr = y(idx(1:ntr));
Xte  = X(idx(ntr+1:end),:); yte = y(idx(ntr+1:end));

%% ---- Régression Linéaire ----
mdl_lin    = fitlm(Xtr, ytr, 'linear');
yp_lin     = predict(mdl_lin, Xte);
mae_lin    = mean(abs(yte - yp_lin));
rmse_lin   = sqrt(mean((yte - yp_lin).^2));
r2_lin     = 1 - sum((yte-yp_lin).^2)/sum((yte-mean(yte)).^2);

fprintf('=== REGRESSION LINEAIRE ===\n');
fprintf('  MAE=%.6f  RMSE=%.6f  R²=%.4f\n\n', mae_lin, rmse_lin, r2_lin);

%% ---- Ridge ----
lambdas  = [0.0001, 0.001, 0.01, 0.1, 1, 10, 100];
Xtrn     = [ones(ntr,1), Xtr];
Xten     = [ones(size(Xte,1),1), Xte];
r2v      = zeros(size(lambdas));
maev     = zeros(size(lambdas));
betaM    = zeros(size(Xtrn,2), length(lambdas));

fprintf('=== RIDGE — balayage λ ===\n');
for li = 1:length(lambdas)
    lam        = lambdas(li);
    Ir         = eye(size(Xtrn,2)); Ir(1,1)=0;
    beta       = (Xtrn'*Xtrn + lam*Ir) \ (Xtrn'*ytr);
    betaM(:,li)= beta;
    ypr        = Xten*beta;
    r2v(li)    = 1 - sum((yte-ypr).^2)/sum((yte-mean(yte)).^2);
    maev(li)   = mean(abs(yte-ypr));
    fprintf('  λ=%-8.4f  R²=%.4f  MAE=%.6f\n', lam, r2v(li), maev(li));
end

[~,bi]      = max(r2v);
lam_best    = lambdas(bi);
yp_ridge    = Xten * betaM(:,bi);
mae_ridge   = mean(abs(yte - yp_ridge));
rmse_ridge  = sqrt(mean((yte - yp_ridge).^2));
r2_ridge    = r2v(bi);

fprintf('\nMeilleur λ=%.4f  R²=%.4f  MAE=%.6f\n\n', lam_best, r2_ridge, mae_ridge);

%% ============================================================
%%  FIGURE 1 : Réponses par type d'entrée
%% ============================================================
figure('Name','Fig 1 — Réponses','NumberTitle','off',...
       'Position',[30 30 1350 650]);
clrs = lines(length(tau_u));

for k = 1:n_types
    subplot(2,3,k); hold on; grid on; box on;
    for ti = 1:length(tau_u)
        idx = type_col==k & abs(tau_col-tau_u(ti))<1e-12;
        if sum(idx)>1
            plot(t_col(idx)*1000, s_col(idx),...
                 'Color', clrs(ti,:), 'LineWidth',1.2);
        end
    end
    title(type_labels{k},'FontWeight','normal','FontSize',11);
    xlabel('t [ms]'); ylabel('i(t) [A]');
end
subplot(2,3,6); axis off;
text(0.5,0.6,sprintf('R² lin   = %.4f\nR² ridge = %.4f', r2_lin, r2_ridge),...
     'HorizontalAlignment','center','FontSize',12,...
     'Units','normalized','FontName','Courier');
sgtitle('Fig 1 — Réponses pour toutes les configurations τ','FontSize',13);

%% ============================================================
%%  FIGURE 2 : Distributions
%% ============================================================
figure('Name','Fig 2 — Distributions','NumberTitle','off',...
       'Position',[30 30 1350 420]);

subplot(1,4,1);
histogram(s_col,60,'FaceColor',[0.22 0.60 0.80],'EdgeColor','none');
title('Distribution s(t)'); xlabel('i(t) [A]'); ylabel('Nb pts'); grid on;

subplot(1,4,2);
histogram(e_col,60,'FaceColor',[0.12 0.62 0.46],'EdgeColor','none');
title('Distribution e(t)'); xlabel('e(t) [V]'); grid on;

subplot(1,4,3);
histogram(tau_col,40,'FaceColor',[0.85 0.36 0.19],'EdgeColor','none');
title('Distribution τ'); xlabel('τ [s]'); grid on;

subplot(1,4,4);
n_sc = min(5000,length(e_col));
idx_sc = round(linspace(1,length(e_col),n_sc));
scatter(e_col(idx_sc), s_col(idx_sc), 4,...
        tau_col(idx_sc),'filled','MarkerFaceAlpha',0.4);
colorbar; colormap(gca,'turbo');
title('e(t) vs s(t) coloré par τ');
xlabel('e(t) [V]'); ylabel('i(t) [A]'); grid on;

sgtitle('Fig 2 — Distributions du dataset','FontSize',13);

%% ============================================================
%%  FIGURE 3 : Régression Linéaire
%% ============================================================
figure('Name','Fig 3 — Régression Linéaire','NumberTitle','off',...
       'Position',[30 30 1350 500]);

n_show = min(4000, length(yte));
idx_show = round(linspace(1,length(yte),n_show));

% 3a. Parité
subplot(1,3,1);
scatter(yte(idx_show), yp_lin(idx_show), 5,...
        [0.22 0.60 0.80],'filled','MarkerFaceAlpha',0.3);
hold on;
lims = [min(yte) max(yte)];
plot(lims, lims, 'r-', 'LineWidth', 2);   % droite idéale y=x
xlabel('s(t) réel [A]'); ylabel('s(t) prédit [A]');
title(sprintf('Parité\nR²=%.4f  MAE=%.5f', r2_lin, mae_lin));
legend('Prédictions','Droite idéale y=x','Location','northwest','FontSize',9);
grid on; axis equal;

% 3b. Résidus vs prédit
subplot(1,3,2);
resid = yte - yp_lin;
scatter(yp_lin(idx_show), resid(idx_show), 5,...
        [0.22 0.60 0.80],'filled','MarkerFaceAlpha',0.3);
hold on;
yline(0,'r-','LineWidth',2);
xlabel('s(t) prédit [A]'); ylabel('Résidu [A]');
title('Résidus vs prédit');
grid on;

% 3c. Histogramme résidus
subplot(1,3,3);
histogram(resid, 60, 'FaceColor',[0.22 0.60 0.80],'EdgeColor','none');
xline(0,'r-','LineWidth',2);
xline(mean(resid),'k--','LineWidth',1.5,...
      'Label',sprintf('moy=%.5f',mean(resid)));
title(sprintf('Distribution résidus\nRMSE=%.5f', rmse_lin));
xlabel('Résidu [A]'); ylabel('Nb pts'); grid on;

sgtitle('Fig 3 — Régression Linéaire','FontSize',13);

%% ============================================================
%%  FIGURE 4 : Ridge Regression
%% ============================================================
figure('Name','Fig 4 — Ridge Regression','NumberTitle','off',...
       'Position',[30 30 1350 500]);

% 4a. Parité Ridge
subplot(1,4,1);
scatter(yte(idx_show), yp_ridge(idx_show), 5,...
        [0.12 0.62 0.46],'filled','MarkerFaceAlpha',0.3);
hold on;
plot(lims, lims, 'r-', 'LineWidth', 2);
xlabel('s(t) réel [A]'); ylabel('s(t) prédit [A]');
title(sprintf('Parité Ridge\nR²=%.4f  MAE=%.5f', r2_ridge, mae_ridge));
legend('Prédictions','Droite idéale y=x','Location','northwest','FontSize',9);
grid on; axis equal;

% 4b. R² vs lambda
subplot(1,4,2);
semilogx(lambdas, r2v, 'o-','Color',[0.85 0.36 0.19],...
         'LineWidth',2,'MarkerSize',8,'MarkerFaceColor',[0.85 0.36 0.19]);
hold on;
xline(lam_best,'k--','LineWidth',1.5,...
      'Label',sprintf('λ*=%.4f',lam_best),'LabelVerticalAlignment','bottom');
title('R² vs λ'); xlabel('λ (log)'); ylabel('R²'); grid on;

% 4c. MAE vs lambda
subplot(1,4,3);
semilogx(lambdas, maev, 's-','Color',[0.53 0.29 0.72],...
         'LineWidth',2,'MarkerSize',8,'MarkerFaceColor',[0.53 0.29 0.72]);
hold on;
xline(lam_best,'k--','LineWidth',1.5);
title('MAE vs λ'); xlabel('λ (log)'); ylabel('MAE [A]'); grid on;

% 4d. Comparaison finale
subplot(1,4,4);
b = bar([mae_lin, mae_ridge; rmse_lin, rmse_ridge],...
        'grouped','FaceColor','flat');
b(1).CData = repmat([0.22 0.60 0.80],2,1);
b(2).CData = repmat([0.12 0.62 0.46],2,1);
set(gca,'XTickLabel',{'MAE','RMSE'});
legend('Linéaire','Ridge','Location','northeast');
title('Comparaison finale'); ylabel('Erreur [A]'); grid on;
for i=1:2
    text(i-0.2, mae_lin+0.00001,  sprintf('%.5f',mae_lin),  'FontSize',8,'HorizontalAlignment','center');
    text(i+0.2, mae_ridge+0.00001,sprintf('%.5f',mae_ridge),'FontSize',8,'HorizontalAlignment','center');
end

sgtitle('Fig 4 — Ridge Regression','FontSize',13);

%% ============================================================
%%  RESUME FINAL
%% ============================================================
fprintf('=== RESUME COMPARAISON ===\n');
fprintf('%-20s  %10s  %10s  %8s\n','Modèle','MAE','RMSE','R²');
fprintf('%s\n',repmat('-',1,55));
fprintf('%-20s  %10.6f  %10.6f  %8.4f\n','Linéaire', mae_lin,   rmse_lin,   r2_lin);
fprintf('%-20s  %10.6f  %10.6f  %8.4f\n','Ridge',     mae_ridge, rmse_ridge, r2_ridge);
fprintf('\n→ Baseline établie. Lance l''étape 4 : LSTM Python.\n');