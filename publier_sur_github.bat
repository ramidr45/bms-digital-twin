@echo off
chcp 65001 >nul
REM ================================================================
REM  Publier le dossier de stage sur GitHub (dépôt PRIVÉ)
REM  A placer dans le dossier stage_ing_organise, puis double-cliquer.
REM ================================================================
cd /d "%~dp0"

set REPO=stage-actia-bms-digital-twin

if not exist "06_EKF_estimation_SOC" (
    echo ERREUR : ce fichier .bat doit etre DANS le dossier stage_ing_organise
    echo          ^(a cote de README.txt et des dossiers 00 a 09^).
    echo Dossier actuel : %CD%
    pause & exit /b
)

echo.
echo [1/6] Renommage du dossier raseberry_pi...
if exist "raseberry_pi" (
    ren "raseberry_pi" "10_digital_twin_RaspberryPi"
    echo      OK : raseberry_pi -^> 10_digital_twin_RaspberryPi
) else (
    echo      Deja fait ou dossier absent.
)

echo.
echo [2/6] Verification de git et de GitHub CLI...
where git >nul 2>nul || (echo      ERREUR : installe Git : https://git-scm.com & pause & exit /b)
where gh  >nul 2>nul || (echo      ERREUR : installe GitHub CLI : https://cli.github.com & pause & exit /b)
if exist "gitignore" ren "gitignore" ".gitignore"
if exist ".gitignore.txt" ren ".gitignore.txt" ".gitignore"
if exist "_gitignore" ren "_gitignore" ".gitignore"
if not exist ".gitignore" (
    echo      .gitignore absent : creation automatique...
    > ".gitignore" (
        echo venv/
        echo __pycache__/
        echo *.pyc
        echo slprj/
        echo *.slxc
        echo *.obj
        echo *.asv
        echo *.autosave
        echo dataset.zip
        echo 00_dataset_Panasonic_18650PF/*.zip
        echo 00_dataset_Panasonic_18650PF/*.mat
        echo Thumbs.db
        echo desktop.ini
    )
)
echo      OK

echo.
echo [3/6] Connexion a GitHub (une seule fois)...
gh auth status >nul 2>nul || gh auth login --web --git-protocol https

echo.
echo [4/6] Creation du depot local...
if not exist ".git" git init
git config user.name  >nul 2>nul || git config user.name "Rami Dridi"
git config user.email >nul 2>nul || git config user.email "rami.dridi@etudiant-enit.utm.tn"
git add .
git commit -m "Stage ACTIA - BMS Digital Twin (EKF, IA, Raspberry Pi)"
git branch -M main

echo.
echo [5/6] Recherche de fichiers trop lourds (plus de 100 Mo)...
powershell -NoProfile -Command "git ls-files | ForEach-Object { $f = Get-Item -LiteralPath $_ -ErrorAction SilentlyContinue; if ($f -and $f.Length -gt 100MB) { Write-Host ('      TROP LOURD : ' + $_) } }"

echo.
echo [6/6] Creation du depot PRIVE sur GitHub et envoi...
gh repo create %REPO% --private --source=. --remote=origin --push

echo.
echo Termine. Ouvre le depot avec : gh repo view %REPO% --web
pause
