# [Fichier renommé lors du rangement — ancien nom : find_missing.py]
import subprocess
import re

result = subprocess.run(
    ['cl', '/nologo', '/O2', '/MD', 'main_test.c', 'EKFSim.c', 'EKFSim_data.c',
     r'/IC:\Program Files\MATLAB\R2025b\extern\include',
     r'/IC:\Program Files\MATLAB\R2025b\simulink\include',
     r'/IC:\Program Files\MATLAB\R2025b\rtw\c\src',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\ssc_core\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\ssc_sli\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\ssc_dae\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\ssc_ds\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\ex\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\mc\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\pm\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\pm_math\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\pm_st\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\pm_log\include',
     r'/IC:\Program Files\MATLAB\R2025b\extern\physmod\win64\pd\include',
     '/I.', '/c'],
    capture_output=True, text=True,
    cwd=r'C:\Users\SAT\Desktop\stage_ing_organise\07_code_C_genere_EKF'
)
output = result.stdout + result.stderr

# Find all missing headers
missing = sorted(set(re.findall(r"'([^']+)' : No such file", output)))
print("Still missing headers:")
for h in missing:
    print(" ", h)

# Also search for them on disk
import os
base = r'C:\Program Files\MATLAB\R2025b\extern\physmod\win64'
print("\nSearching for them on disk...")
for mh in missing:
    hname = os.path.basename(mh)
    for root, dirs, files in os.walk(base):
        if hname in files:
            print(f"  {hname} -> {root}")
            break
    else:
        print(f"  {hname} -> NOT FOUND in physmod!")
