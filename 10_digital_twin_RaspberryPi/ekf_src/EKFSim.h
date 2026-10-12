/*
 * EKFSim.h
 *
 * Code generation for model "EKFSim".
 *
 * Model version              : 15.14
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Fri Jul 31 13:26:49 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef EKFSim_h_
#define EKFSim_h_

#include <stddef.h>
#include <stdbool.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "EKFSim_types.h"
#include "rt_nonfinite.h"
#include "nesl_rtw.h"
#include "rt_logging.h"

/* Forward declaration */
extern void EKFSim_3bb8072c_1_gateway(void);

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* ODE14X Integration Data structure */
typedef struct {
  real_T *x0;
  real_T *f0;
  real_T *x1start;
  real_T *f1;
  real_T *Delta;
  real_T *E;
  real_T *fac;
  real_T *DFDX;
  real_T *W;
  int_T *pivots;
  real_T *xtmp;
  real_T *ztmp;
  real_T *M;
  boolean_T isFirstStep;
} ODE14X_IntgData;

/* Block signals (default storage) */
typedef struct {
  real_T INPUT_1_1_1[4];               /* '<S21>/INPUT_1_1_1' */
  real_T INPUT_2_1_1[4];               /* '<S21>/INPUT_2_1_1' */
  real_T INPUT_3_1_1[4];               /* '<S21>/INPUT_3_1_1' */
  real_T INPUT_4_1_1[4];               /* '<S21>/INPUT_4_1_1' */
  real_T UL_Obs;                       /* '<Root>/Unit Delay' */
  real_T OCV;                          /* '<S3>/OCV' */
  real_T rp;                           /* '<S3>/rp' */
  real_T rp1;                          /* '<S3>/rp1' */
  real_T Up_pre;                       /* '<Root>/Up_pre' */
  real_T r0;                           /* '<S3>/r0' */
  real_T Gain;                         /* '<S6>/Gain' */
  real_T Up_pre_o;                     /* '<S6>/EKF' */
  real_T STATE_1[2];                   /* '<S21>/STATE_1' */
  real_T OUTPUT_1_1;                   /* '<S21>/OUTPUT_1_1' */
  real_T P_Old[4];                     /* '<Root>/P_upd' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T SOC_upd;                      /* '<S6>/EKF' */
  real_T Up_upd;                       /* '<S6>/EKF' */
  real_T P_upd[4];                     /* '<S6>/EKF' */
  real_T Integrator;                   /* '<S4>/Integrator' */
  real_T Sum_p;                        /* '<S4>/Sum' */
  real_T OUTPUT_1_0;                   /* '<S21>/OUTPUT_1_0' */
} B_EKFSim_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  void *STATE_1_SimData;               /* '<S21>/STATE_1' */
  real_T STATE_1_Discrete;             /* '<S21>/STATE_1' */
  int_T STATE_1_Modes;                 /* '<S21>/STATE_1' */
  void *STATE_1_DiagMgr;               /* '<S21>/STATE_1' */
  void *STATE_1_Simulator;             /* '<S21>/STATE_1' */
  int_T STATE_1_MASS_MATRIX_PR;        /* '<S21>/STATE_1' */
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  real_T SOC_upd_PreviousInput;        /* '<Root>/SOC_upd' */
  real_T INPUT_1_1_1_Discrete_2796830670[2];/* '<S21>/INPUT_1_1_1' */
  real_T Up_pre_PreviousInput;         /* '<Root>/Up_pre' */
  real_T INPUT_3_1_1_Discrete_3698617518[2];/* '<S21>/INPUT_3_1_1' */
  void *OUTPUT_1_1_SimData;            /* '<S21>/OUTPUT_1_1' */
  real_T OUTPUT_1_1_Discrete;          /* '<S21>/OUTPUT_1_1' */
  int_T OUTPUT_1_1_Modes;              /* '<S21>/OUTPUT_1_1' */
  void *OUTPUT_1_1_DiagMgr;            /* '<S21>/OUTPUT_1_1' */
  void *OUTPUT_1_1_Simulator;          /* '<S21>/OUTPUT_1_1' */
  real_T P_upd_PreviousInput[4];       /* '<Root>/P_upd' */
  real_T UnitDelay_DSTATE_c;           /* '<S5>/Unit Delay' */
  struct {
    void *LoggedData;
  } SOC_EKF_log_PWORK;                 /* '<Root>/SOC_EKF_log' */

  real_T UnitDelay_DSTATE_m;           /* '<S1>/Unit Delay' */
  real_T SOC_upd1_PreviousInput;       /* '<Root>/SOC_upd1' */
  struct {
    void *LoggedData;
  } ToWorkspace_PWORK;                 /* '<Root>/To Workspace' */

  struct {
    void *LoggedData;
  } ToWorkspace2_PWORK;                /* '<Root>/To Workspace2' */

  void *OUTPUT_1_0_SimData;            /* '<S21>/OUTPUT_1_0' */
  real_T OUTPUT_1_0_Discrete;          /* '<S21>/OUTPUT_1_0' */
  int_T OUTPUT_1_0_Modes;              /* '<S21>/OUTPUT_1_0' */
  void *OUTPUT_1_0_DiagMgr;            /* '<S21>/OUTPUT_1_0' */
  void *OUTPUT_1_0_Simulator;          /* '<S21>/OUTPUT_1_0' */
} DW_EKFSim_T;

/* Continuous states (default storage) */
typedef struct {
  real_T EKFSimThevenin_ECMVariable_R0v;/* '<S21>/STATE_1' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} X_EKFSim_T;

/* State derivatives (default storage) */
typedef struct {
  real_T EKFSimThevenin_ECMVariable_R0v;/* '<S21>/STATE_1' */
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} XDot_EKFSim_T;

/* State disabled */
typedef struct {
  boolean_T EKFSimThevenin_ECMVariable_R0v;/* '<S21>/STATE_1' */
  boolean_T Integrator_CSTATE;         /* '<S4>/Integrator' */
} XDis_EKFSim_T;

/* Mass Matrix Static Data */
typedef struct {
  int_T ir[2];
  int_T jc[3];
  real_T pr[2];
} MassMatrix_EKFSim_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T tuvar;                        /* '<Root>/tuvar' */
  real_T UL_Real;                      /* '<Root>/UL_Real' */
} ExtU_EKFSim_T;

/* Parameters (default storage) */
struct P_EKFSim_T_ {
  real_T C1_bp[96];
  real_T OCV_bp[96];
  real_T R0_bp[96];
  real_T R1_bp[96];
  real_T SOC_bp[96];
  real_T Noise_Value[2];
  real_T UnitDelay_InitialCondition;
  real_T SOC_upd_InitialCondition;
  real_T Up_pre_InitialCondition;
  real_T Gain_Gain;
  real_T P_upd_InitialCondition[4];
  real_T UnitDelay_InitialCondition_j;
  real_T Capacity_Value;
  real_T uH_Gain;
  real_T SampleT_Gain;
  real_T Integrator_IC;
  real_T Gain_Gain_c;
  real_T int_soc_Value;
  real_T UnitDelay_InitialCondition_h;
  real_T Capacity_Value_c;
  real_T uH_Gain_j;
  real_T SampleT_Gain_i;
  real_T SOC_upd1_InitialCondition;
};

/* Real-time Model Data Structure */
struct tag_RTM_EKFSim_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_EKFSim_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_EKFSim_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeX0[2];
  real_T odeF0[2];
  real_T odeX1START[2];
  real_T odeF1[2];
  real_T odeDELTA[2];
  real_T odeE[4][2];
  real_T odeFAC[2];
  real_T odeDFDX[2][2];
  real_T odeW[2][2];
  int_T odePIVOTS[2];
  real_T odeXTMP[2];
  real_T odeZTMP[2];
  real_T odeMASSMATRIX_M[2][2];
  ODE14X_IntgData intgData;
  ssMatrixType massMatrixType;
  int_T massMatrixNzMax;
  int_T *massMatrixIr;
  int_T *massMatrixJc;
  real_T *massMatrixPr;
  RTWLogInfo *rtwLogInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, workspace, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information of the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    real_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    real_T tStart;
    real_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_EKFSim_T EKFSim_P;

/* Block signals (default storage) */
extern B_EKFSim_T EKFSim_B;

/* Continuous states (default storage) */
extern X_EKFSim_T EKFSim_X;

/* Disabled States */
extern XDis_EKFSim_T EKFSim_XDis;

/* Block states (default storage) */
extern DW_EKFSim_T EKFSim_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_EKFSim_T EKFSim_U;

/* Model entry points _includes */
extern void EKFSim_initialize(void);
extern void EKFSim_step(void);
extern void EKFSim_terminate(void);

/* Real-time Model object */
extern RT_MODEL_EKFSim_T *const EKFSim_M;

#endif                                 /* EKFSim_h_ */
