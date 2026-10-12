/*
 * EKFSim_pi.h
 *
 * Code generation for model "EKFSim_pi".
 *
 * Model version              : 15.18
 * Simulink Coder version : 25.2 (R2025b) 28-Jul-2025
 * C source code generated on : Wed Aug 12 13:29:20 2026
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef EKFSim_pi_h_
#define EKFSim_pi_h_
#ifndef EKFSim_pi_COMMON_INCLUDES_
#define EKFSim_pi_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_nonfinite.h"
#include "math.h"
#endif                                 /* EKFSim_pi_COMMON_INCLUDES_ */

#include "EKFSim_pi_types.h"
#include "rtGetNaN.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

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

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef rtmGetTStart
#define rtmGetTStart(rtm)              ((rtm)->Timing.tStart)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T UL_Obs;                       /* '<Root>/Unit Delay' */
  real_T OCV;                          /* '<S3>/OCV' */
  real_T r0;                           /* '<S3>/r0' */
  real_T rp;                           /* '<S3>/rp' */
  real_T rp1;                          /* '<S3>/rp1' */
  real_T Up_pre;                       /* '<Root>/Up_pre' */
  real_T P_Old[4];                     /* '<Root>/P_upd' */
  real_T Sum;                          /* '<S5>/Sum' */
  real_T P_upd[4];                     /* '<Root>/EKF' */
  real_T SOC_upd;                      /* '<Root>/EKF' */
  real_T Up_upd;                       /* '<Root>/EKF' */
} B_EKFSim_pi_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T UnitDelay_DSTATE;             /* '<Root>/Unit Delay' */
  real_T UnitDelay_DSTATE_c;           /* '<S5>/Unit Delay' */
  real_T SOC_upd_PreviousInput;        /* '<Root>/SOC_upd' */
  real_T Up_pre_PreviousInput;         /* '<Root>/Up_pre' */
  real_T P_upd_PreviousInput[4];       /* '<Root>/P_upd' */
} DW_EKFSim_pi_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} X_EKFSim_pi_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S4>/Integrator' */
} XDot_EKFSim_pi_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S4>/Integrator' */
} XDis_EKFSim_pi_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T tuvar;                        /* '<Root>/tuvar' */
  real_T UL_Real;                      /* '<Root>/vuvar' */
} ExtU_EKFSim_pi_T;

/* Parameters (default storage) */
struct P_EKFSim_pi_T_ {
  real_T C1_bp[96];                    /* Variable: C1_bp
                                        * Referenced by: '<S3>/rp1'
                                        */
  real_T OCV_bp[96];                   /* Variable: OCV_bp
                                        * Referenced by: '<S3>/OCV'
                                        */
  real_T R0_bp[96];                    /* Variable: R0_bp
                                        * Referenced by: '<S3>/r0'
                                        */
  real_T R1_bp[96];                    /* Variable: R1_bp
                                        * Referenced by: '<S3>/rp'
                                        */
  real_T SOC_bp[96];                   /* Variable: SOC_bp
                                        * Referenced by:
                                        *   '<S3>/OCV'
                                        *   '<S3>/r0'
                                        *   '<S3>/rp'
                                        *   '<S3>/rp1'
                                        */
  real_T Noise_Value[2];               /* Expression: [1e-09,0.01]
                                        * Referenced by: '<Root>/Noise'
                                        */
  real_T UnitDelay_InitialCondition;   /* Expression: 4.107
                                        * Referenced by: '<Root>/Unit Delay'
                                        */
  real_T SOC_upd_InitialCondition;     /* Expression: 1
                                        * Referenced by: '<Root>/SOC_upd'
                                        */
  real_T Gain_Gain;                    /* Expression: -1
                                        * Referenced by: '<S6>/Gain'
                                        */
  real_T Up_pre_InitialCondition;      /* Expression: 0
                                        * Referenced by: '<Root>/Up_pre'
                                        */
  real_T P_upd_InitialCondition[4];    /* Expression: [0.02 0 0 0.01]
                                        * Referenced by: '<Root>/P_upd'
                                        */
  real_T UnitDelay_InitialCondition_j; /* Expression: 0
                                        * Referenced by: '<S5>/Unit Delay'
                                        */
  real_T Capacity_Value;               /* Expression: 2.885
                                        * Referenced by: '<S5>/Capacity'
                                        */
  real_T uH_Gain;                      /* Expression: 3600
                                        * Referenced by: '<S5>/1H'
                                        */
  real_T SampleT_Gain;                 /* Expression: 0.1
                                        * Referenced by: '<S5>/Sample T'
                                        */
  real_T Integrator_IC;                /* Expression: 0
                                        * Referenced by: '<S4>/Integrator'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_EKFSim_pi_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_EKFSim_pi_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  XDis_EKFSim_pi_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[1];
  real_T odeF[3][1];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tStart;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_EKFSim_pi_T EKFSim_pi_P;

/* Block signals (default storage) */
extern B_EKFSim_pi_T EKFSim_pi_B;

/* Continuous states (default storage) */
extern X_EKFSim_pi_T EKFSim_pi_X;

/* Disabled states (default storage) */
extern XDis_EKFSim_pi_T EKFSim_pi_XDis;

/* Block states (default storage) */
extern DW_EKFSim_pi_T EKFSim_pi_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_EKFSim_pi_T EKFSim_pi_U;

/* Model entry point functions */
extern void EKFSim_pi_initialize(void);
extern void EKFSim_pi_step(void);
extern void EKFSim_pi_terminate(void);

/* Real-time Model object */
extern RT_MODEL_EKFSim_pi_T *const EKFSim_pi_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'EKFSim_pi'
 * '<S1>'   : 'EKFSim_pi/AmpereHour'
 * '<S2>'   : 'EKFSim_pi/EKF'
 * '<S3>'   : 'EKFSim_pi/Paras_Update'
 * '<S4>'   : 'EKFSim_pi/SOC_Real'
 * '<S5>'   : 'EKFSim_pi/SOC_prediction'
 * '<S6>'   : 'EKFSim_pi/Thevenin ECM'
 * '<S7>'   : 'EKFSim_pi/Thevenin ECM/Up_prediction'
 */
#endif                                 /* EKFSim_pi_h_ */
