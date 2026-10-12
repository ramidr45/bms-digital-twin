@echo off
REM ================================================================
REM Build script for EKFSim standalone test executable
REM Run from a Visual Studio Developer Command Prompt
REM ================================================================

set MATLAB=C:\Program Files\MATLAB\R2025b
set PM=%MATLAB%\extern\physmod\win64

cl /nologo /O2 /MD ^
    main_test.c ^
    EKFSim.c ^
    EKFSim_data.c ^
    rt_nonfinite.c ^
    EKFSim_3bb8072c_49_ds_log.c ^
    EKFSim_3bb8072c_49_ds_obs_il.c ^
    EKFSim_3bb8072c_1_gateway.c ^
    EKFSim_3bb8072c_49_ds_obs_act.c ^
    EKFSim_3bb8072c_49.c ^
    EKFSim_3bb8072c_49_ds_obs_all.c ^
    EKFSim_3bb8072c_49_ds.c ^
    EKFSim_3bb8072c_49_ds_obs_exp.c ^
    rt_lu_real.c ^
    rt_matrixlib_dbl.c ^
    rt_backsubrr_dbl.c ^
    rt_forwardsubrr_dbl.c ^
    "%MATLAB%\rtw\c\src\rt_logging.c" ^
    /I. ^
    /I"%MATLAB%\extern\include" ^
    /I"%MATLAB%\simulink\include" ^
    /I"%MATLAB%\rtw\c\src" ^
    /I"%PM%\ex\include" ^
    /I"%PM%\mc\include" ^
    /I"%PM%\pd\include" ^
    /I"%PM%\pm\include" ^
    /I"%PM%\pm_log\include" ^
    /I"%PM%\pm_math\include" ^
    /I"%PM%\pm_st\include" ^
    /I"%PM%\simrf\include" ^
    /I"%PM%\sm\include" ^
    /I"%PM%\sm_discr\include" ^
    /I"%PM%\sm_ssci\include" ^
    /I"%PM%\ssc_core\include" ^
    /I"%PM%\ssc_dae\include" ^
    /I"%PM%\ssc_ds\include" ^
    /I"%PM%\ssc_sli\include" ^
    /Fe:test_ekf.exe ^
    "%PM%\ssc_core\lib\ssc_core_ert_vcx64.lib" ^
    "%PM%\ssc_sli\lib\ssc_sli_ert_vcx64.lib" ^
    "%PM%\ex\lib\ex_ert_vcx64.lib" ^
    "%PM%\mc\lib\mc_vcx64.lib" ^
    "%PM%\pm\lib\pm_ert_vcx64.lib" ^
    "%PM%\pm_math\lib\pm_math_ert_vcx64.lib" ^
    "%PM%\pm_st\lib\pm_st_ert_vcx64.lib" ^
    "%PM%\sm\lib\sm_ert_vcx64.lib" ^
    "%PM%\sm_discr\lib\sm_discr_ert_vcx64.lib" ^
    "%PM%\sm_ssci\lib\sm_ssci_ert_vcx64.lib"

if %ERRORLEVEL%==0 (
    echo.
    echo === Build successful! Run: test_ekf.exe ===
) else (
    echo.
    echo === Build FAILED ===
)
