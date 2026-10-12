/*
 * EKFSim_pi.c
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

#include "EKFSim_pi.h"
#include <math.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "EKFSim_pi_private.h"
#include <string.h>

/* Block signals (default storage) */
B_EKFSim_pi_T EKFSim_pi_B;

/* Continuous states */
X_EKFSim_pi_T EKFSim_pi_X;

/* Disabled State Vector */
XDis_EKFSim_pi_T EKFSim_pi_XDis;

/* Block states (default storage) */
DW_EKFSim_pi_T EKFSim_pi_DW;

/* External inputs (root inport signals with default storage) */
ExtU_EKFSim_pi_T EKFSim_pi_U;

/* Real-time model */
static RT_MODEL_EKFSim_pi_T EKFSim_pi_M_;
RT_MODEL_EKFSim_pi_T *const EKFSim_pi_M = &EKFSim_pi_M_;
real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T iLeft;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Clip'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Clip'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = 0.0;
  } else if (u0 < bp0[maxIndex]) {
    uint32_T bpIdx;
    uint32_T iRght;

    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = 1.0;
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  EKFSim_pi_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  EKFSim_pi_step();
  EKFSim_pi_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  EKFSim_pi_step();
  EKFSim_pi_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void EKFSim_pi_step(void)
{
  real_T A[4];
  real_T A_0[4];
  real_T P_pre[4];
  real_T A_1;
  real_T A_2;
  real_T A_3;
  real_T C_idx_0;
  real_T K_idx_0;
  real_T rtb_Gain;
  real_T rtb_SOC_upd;
  real_T rtb_Up_pre;
  real_T xloc;
  int32_T high_i;
  int32_T low_i;
  int32_T low_ip1;
  int32_T mid_i;
  static const real_T c[14] = { 0.05, 0.1, 0.15, 0.2, 0.25, 0.3, 0.4, 0.5, 0.6,
    0.7, 0.8, 0.9, 0.95, 1.0 };

  static const real_T d[52] = { 334.22910690380832, 14593.995900313206,
    -92.3813547387766, 1451.8518518518542, -21.279638135465451,
    -6.56719292463533, -714.99214053362675, -0.74285714285715854,
    728.00000000000068, -150.45997286295756, 86.754176276621621,
    -1000.0743699111182, -4.9309664694280952, -148.91145534519069,
    -878.61125036085082, 201.83072806647, -5.1851851851852757,
    3.7307819067733092, 7.1052102458501212, 101.32414239243964,
    -1.1514285714285812, -109.20000000000007, 31.695997286295746,
    -6.729420341366362, 94.760888667640145, -4.5069033530573277,
    -39.069999999999979, -51.454427232740485, -29.860583016476554,
    -10.370370370370374, 0.0, 0.21348090466134004, 1.4375071660923047,
    0.25257142857143094, 0.0, 0.0, 1.8254002713704203, 3.0821414913957956,
    5.05767258382643, 7.162, 4.878, 1.933, 0.933, 0.583, 0.589667, 0.6755,
    1.1175, 1.1305, 0.7665, 0.933, 1.135, 1.401 };

  if (rtmIsMajorTimeStep(EKFSim_pi_M)) {
    /* set solver stop time */
    if (!(EKFSim_pi_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&EKFSim_pi_M->solverInfo,
                            ((EKFSim_pi_M->Timing.clockTickH0 + 1) *
        EKFSim_pi_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&EKFSim_pi_M->solverInfo,
                            ((EKFSim_pi_M->Timing.clockTick0 + 1) *
        EKFSim_pi_M->Timing.stepSize0 + EKFSim_pi_M->Timing.clockTickH0 *
        EKFSim_pi_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(EKFSim_pi_M)) {
    EKFSim_pi_M->Timing.t[0] = rtsiGetT(&EKFSim_pi_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(EKFSim_pi_M)) {
    /* UnitDelay: '<Root>/Unit Delay' */
    EKFSim_pi_B.UL_Obs = EKFSim_pi_DW.UnitDelay_DSTATE;

    /* Lookup_n-D: '<S3>/OCV' incorporates:
     *  Memory: '<Root>/SOC_upd'
     */
    EKFSim_pi_B.OCV = look1_binlcpw(EKFSim_pi_DW.SOC_upd_PreviousInput,
      EKFSim_pi_P.SOC_bp, EKFSim_pi_P.OCV_bp, 95U);

    /* Lookup_n-D: '<S3>/r0' incorporates:
     *  Memory: '<Root>/SOC_upd'
     */
    EKFSim_pi_B.r0 = look1_binlcpw(EKFSim_pi_DW.SOC_upd_PreviousInput,
      EKFSim_pi_P.SOC_bp, EKFSim_pi_P.R0_bp, 95U);

    /* Lookup_n-D: '<S3>/rp' incorporates:
     *  Memory: '<Root>/SOC_upd'
     */
    EKFSim_pi_B.rp = look1_binlcpw(EKFSim_pi_DW.SOC_upd_PreviousInput,
      EKFSim_pi_P.SOC_bp, EKFSim_pi_P.R1_bp, 95U);

    /* Lookup_n-D: '<S3>/rp1' incorporates:
     *  Memory: '<Root>/SOC_upd'
     */
    EKFSim_pi_B.rp1 = look1_binlcpw(EKFSim_pi_DW.SOC_upd_PreviousInput,
      EKFSim_pi_P.SOC_bp, EKFSim_pi_P.C1_bp, 95U);

    /* Memory: '<Root>/Up_pre' */
    EKFSim_pi_B.Up_pre = EKFSim_pi_DW.Up_pre_PreviousInput;

    /* Memory: '<Root>/P_upd' */
    EKFSim_pi_B.P_Old[0] = EKFSim_pi_DW.P_upd_PreviousInput[0];
    EKFSim_pi_B.P_Old[1] = EKFSim_pi_DW.P_upd_PreviousInput[1];
    EKFSim_pi_B.P_Old[2] = EKFSim_pi_DW.P_upd_PreviousInput[2];
    EKFSim_pi_B.P_Old[3] = EKFSim_pi_DW.P_upd_PreviousInput[3];

    /* Sum: '<S5>/Sum' incorporates:
     *  Constant: '<S5>/Capacity'
     *  Gain: '<S5>/1H'
     *  Gain: '<S5>/Sample T'
     *  Memory: '<Root>/SOC_upd'
     *  Product: '<S5>/Divide'
     *  UnitDelay: '<S5>/Unit Delay'
     */
    EKFSim_pi_B.Sum = EKFSim_pi_DW.UnitDelay_DSTATE_c / (EKFSim_pi_P.uH_Gain *
      EKFSim_pi_P.Capacity_Value) * EKFSim_pi_P.SampleT_Gain +
      EKFSim_pi_DW.SOC_upd_PreviousInput;
  }

  /* Gain: '<S6>/Gain' incorporates:
   *  Inport: '<Root>/tuvar'
   */
  rtb_Gain = EKFSim_pi_P.Gain_Gain * EKFSim_pi_U.tuvar;

  /* MATLAB Function: '<S6>/Up_prediction' incorporates:
   *  MATLAB Function: '<Root>/EKF'
   */
  /* MATLAB Function 'Thevenin ECM/Up_prediction': '<S7>:1' */
  /* '<S7>:1:2' */
  /* '<S7>:1:3' */
  /* '<S7>:1:4' */
  xloc = exp(-0.1 / (EKFSim_pi_B.rp * EKFSim_pi_B.rp1));
  rtb_Up_pre = (1.0 - xloc) * EKFSim_pi_B.rp * rtb_Gain + xloc *
    EKFSim_pi_B.Up_pre;

  /* MATLAB Function: '<Root>/EKF' incorporates:
   *  Constant: '<Root>/Noise'
   *  Product: '<S6>/Product'
   *  Sum: '<S6>/Add'
   */
  /* MATLAB Function 'EKF': '<S2>:1' */
  /* '<S2>:1:8' */
  /* '<S2>:1:2' */
  /* '<S2>:1:3' */
  /* '<S2>:1:4' */
  /* '<S2>:1:7' */
  /* '<S2>:1:8' */
  A[1] = 0.0;
  A[3] = xloc;

  /* '<S2>:1:10' */
  /* '<S2>:1:11' */
  P_pre[0] = EKFSim_pi_B.P_Old[0];
  P_pre[2] = EKFSim_pi_B.P_Old[1];
  P_pre[1] = EKFSim_pi_B.P_Old[2];
  P_pre[3] = EKFSim_pi_B.P_Old[3];
  A[0] = 1.0;
  A_0[0] = 0.0;
  A_0[1] = 0.0;
  A[2] = 0.0;
  A_0[2] = 0.0;
  A_0[3] = 0.0;
  for (high_i = 0; high_i < 2; high_i++) {
    low_i = high_i << 1;
    K_idx_0 = P_pre[low_i];
    rtb_SOC_upd = A_0[low_i] + K_idx_0;
    C_idx_0 = A_0[low_i + 1] + 0.0 * K_idx_0;
    K_idx_0 = P_pre[low_i + 1];
    A_0[low_i] = 0.0 * K_idx_0 + rtb_SOC_upd;
    A_0[low_i + 1] = xloc * K_idx_0 + C_idx_0;
  }

  rtb_SOC_upd = A_0[0];
  C_idx_0 = A_0[1];
  xloc = A_0[2];
  A_3 = A_0[3];
  for (high_i = 0; high_i < 2; high_i++) {
    K_idx_0 = A[high_i];
    A_1 = rtb_SOC_upd * K_idx_0;
    A_2 = C_idx_0 * K_idx_0;
    K_idx_0 = A[high_i + 2];
    low_i = high_i << 1;
    A_0[low_i] = xloc * K_idx_0 + A_1;
    A_0[low_i + 1] = A_3 * K_idx_0 + A_2;
  }

  P_pre[0] = A_0[0] + EKFSim_pi_P.Noise_Value[0];
  P_pre[1] = A_0[1];
  P_pre[2] = A_0[2];
  P_pre[3] = EKFSim_pi_P.Noise_Value[0] + A_0[3];

  /* '<S2>:1:15' */
  if (rtIsNaN(EKFSim_pi_B.Sum)) {
    rtb_SOC_upd = (rtNaN);
  } else {
    high_i = 14;
    low_i = 0;
    low_ip1 = 2;
    while (high_i > low_ip1) {
      mid_i = ((low_i + high_i) + 1) >> 1;
      if (EKFSim_pi_B.Sum >= c[mid_i - 1]) {
        low_i = mid_i - 1;
        low_ip1 = mid_i + 1;
      } else {
        high_i = mid_i;
      }
    }

    xloc = EKFSim_pi_B.Sum - c[low_i];
    rtb_SOC_upd = ((xloc * d[low_i] + d[low_i + 13]) * xloc + d[low_i + 26]) *
      xloc + d[low_i + 39];
  }

  /* '<S2>:1:16' */
  C_idx_0 = rtb_SOC_upd;

  /* '<S2>:1:18' */
  /* '<S2>:1:19' */
  K_idx_0 = rtb_SOC_upd * P_pre[0];
  rtb_SOC_upd = 1.0 / (((K_idx_0 - A_0[1]) * rtb_SOC_upd - (rtb_SOC_upd * A_0[2]
    - P_pre[3])) + EKFSim_pi_P.Noise_Value[1]);
  K_idx_0 = (K_idx_0 - A_0[2]) * rtb_SOC_upd;
  rtb_SOC_upd *= A_0[1] * C_idx_0 - P_pre[3];

  /* '<S2>:1:20' */
  rtb_Gain = EKFSim_pi_B.UL_Obs - ((EKFSim_pi_B.OCV - rtb_Gain * EKFSim_pi_B.r0)
    - rtb_Up_pre);

  /* '<S2>:1:21' */
  A_0[0] = K_idx_0 * C_idx_0;
  A_0[1] = rtb_SOC_upd * C_idx_0;
  A_0[2] = -K_idx_0;
  A_0[3] = -rtb_SOC_upd;
  for (high_i = 0; high_i < 2; high_i++) {
    C_idx_0 = A_0[high_i + 2];
    xloc = A_0[high_i];
    A[high_i] = P_pre[high_i] - (C_idx_0 * P_pre[1] + xloc * P_pre[0]);
    A[high_i + 2] = P_pre[high_i + 2] - (C_idx_0 * P_pre[3] + xloc * P_pre[2]);
  }

  /* '<S2>:1:23' */
  EKFSim_pi_B.SOC_upd = K_idx_0 * rtb_Gain + EKFSim_pi_B.Sum;

  /* '<S2>:1:24' */
  EKFSim_pi_B.Up_upd = rtb_SOC_upd * rtb_Gain + rtb_Up_pre;

  /* '<S2>:1:25' */
  EKFSim_pi_B.P_upd[0] = A[0];
  EKFSim_pi_B.P_upd[1] = A[2];
  EKFSim_pi_B.P_upd[2] = A[1];
  EKFSim_pi_B.P_upd[3] = A[3];
  if (rtmIsMajorTimeStep(EKFSim_pi_M)) {
    if (rtmIsMajorTimeStep(EKFSim_pi_M)) {
      /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
       *  Inport: '<Root>/vuvar'
       */
      EKFSim_pi_DW.UnitDelay_DSTATE = EKFSim_pi_U.UL_Real;

      /* Update for Memory: '<Root>/SOC_upd' */
      EKFSim_pi_DW.SOC_upd_PreviousInput = EKFSim_pi_B.SOC_upd;

      /* Update for Memory: '<Root>/Up_pre' */
      EKFSim_pi_DW.Up_pre_PreviousInput = EKFSim_pi_B.Up_upd;

      /* Update for Memory: '<Root>/P_upd' */
      EKFSim_pi_DW.P_upd_PreviousInput[0] = EKFSim_pi_B.P_upd[0];
      EKFSim_pi_DW.P_upd_PreviousInput[1] = EKFSim_pi_B.P_upd[1];
      EKFSim_pi_DW.P_upd_PreviousInput[2] = EKFSim_pi_B.P_upd[2];
      EKFSim_pi_DW.P_upd_PreviousInput[3] = EKFSim_pi_B.P_upd[3];

      /* Update for UnitDelay: '<S5>/Unit Delay' incorporates:
       *  Inport: '<Root>/tuvar'
       */
      EKFSim_pi_DW.UnitDelay_DSTATE_c = EKFSim_pi_U.tuvar;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(EKFSim_pi_M)) {
    rt_ertODEUpdateContinuousStates(&EKFSim_pi_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++EKFSim_pi_M->Timing.clockTick0)) {
      ++EKFSim_pi_M->Timing.clockTickH0;
    }

    EKFSim_pi_M->Timing.t[0] = rtsiGetSolverStopTime(&EKFSim_pi_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.1s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.1, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      EKFSim_pi_M->Timing.clockTick1++;
      if (!EKFSim_pi_M->Timing.clockTick1) {
        EKFSim_pi_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void EKFSim_pi_derivatives(void)
{
  XDot_EKFSim_pi_T *_rtXdot;
  _rtXdot = ((XDot_EKFSim_pi_T *) EKFSim_pi_M->derivs);

  /* Derivatives for Integrator: '<S4>/Integrator' incorporates:
   *  Inport: '<Root>/tuvar'
   */
  _rtXdot->Integrator_CSTATE = EKFSim_pi_U.tuvar;
}

/* Model initialize function */
void EKFSim_pi_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)EKFSim_pi_M, 0,
                sizeof(RT_MODEL_EKFSim_pi_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&EKFSim_pi_M->solverInfo,
                          &EKFSim_pi_M->Timing.simTimeStep);
    rtsiSetTPtr(&EKFSim_pi_M->solverInfo, &rtmGetTPtr(EKFSim_pi_M));
    rtsiSetStepSizePtr(&EKFSim_pi_M->solverInfo, &EKFSim_pi_M->Timing.stepSize0);
    rtsiSetdXPtr(&EKFSim_pi_M->solverInfo, &EKFSim_pi_M->derivs);
    rtsiSetContStatesPtr(&EKFSim_pi_M->solverInfo, (real_T **)
                         &EKFSim_pi_M->contStates);
    rtsiSetNumContStatesPtr(&EKFSim_pi_M->solverInfo,
      &EKFSim_pi_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&EKFSim_pi_M->solverInfo,
      &EKFSim_pi_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&EKFSim_pi_M->solverInfo,
      &EKFSim_pi_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&EKFSim_pi_M->solverInfo,
      &EKFSim_pi_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&EKFSim_pi_M->solverInfo, (boolean_T**)
      &EKFSim_pi_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&EKFSim_pi_M->solverInfo, (&rtmGetErrorStatus
      (EKFSim_pi_M)));
    rtsiSetRTModelPtr(&EKFSim_pi_M->solverInfo, EKFSim_pi_M);
  }

  rtsiSetSimTimeStep(&EKFSim_pi_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&EKFSim_pi_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&EKFSim_pi_M->solverInfo, false);
  EKFSim_pi_M->intgData.y = EKFSim_pi_M->odeY;
  EKFSim_pi_M->intgData.f[0] = EKFSim_pi_M->odeF[0];
  EKFSim_pi_M->intgData.f[1] = EKFSim_pi_M->odeF[1];
  EKFSim_pi_M->intgData.f[2] = EKFSim_pi_M->odeF[2];
  EKFSim_pi_M->contStates = ((X_EKFSim_pi_T *) &EKFSim_pi_X);
  EKFSim_pi_M->contStateDisabled = ((XDis_EKFSim_pi_T *) &EKFSim_pi_XDis);
  EKFSim_pi_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&EKFSim_pi_M->solverInfo, (void *)&EKFSim_pi_M->intgData);
  rtsiSetSolverName(&EKFSim_pi_M->solverInfo,"ode3");
  rtmSetTPtr(EKFSim_pi_M, &EKFSim_pi_M->Timing.tArray[0]);
  EKFSim_pi_M->Timing.stepSize0 = 0.1;

  /* block I/O */
  (void) memset(((void *) &EKFSim_pi_B), 0,
                sizeof(B_EKFSim_pi_T));

  /* states (continuous) */
  {
    (void) memset((void *)&EKFSim_pi_X, 0,
                  sizeof(X_EKFSim_pi_T));
  }

  /* disabled states */
  {
    (void) memset((void *)&EKFSim_pi_XDis, 0,
                  sizeof(XDis_EKFSim_pi_T));
  }

  /* states (dwork) */
  (void) memset((void *)&EKFSim_pi_DW, 0,
                sizeof(DW_EKFSim_pi_T));

  /* external inputs */
  (void)memset(&EKFSim_pi_U, 0, sizeof(ExtU_EKFSim_pi_T));

  /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
  EKFSim_pi_DW.UnitDelay_DSTATE = EKFSim_pi_P.UnitDelay_InitialCondition;

  /* InitializeConditions for Memory: '<Root>/SOC_upd' */
  EKFSim_pi_DW.SOC_upd_PreviousInput = EKFSim_pi_P.SOC_upd_InitialCondition;

  /* InitializeConditions for Memory: '<Root>/Up_pre' */
  EKFSim_pi_DW.Up_pre_PreviousInput = EKFSim_pi_P.Up_pre_InitialCondition;

  /* InitializeConditions for Memory: '<Root>/P_upd' */
  EKFSim_pi_DW.P_upd_PreviousInput[0] = EKFSim_pi_P.P_upd_InitialCondition[0];
  EKFSim_pi_DW.P_upd_PreviousInput[1] = EKFSim_pi_P.P_upd_InitialCondition[1];
  EKFSim_pi_DW.P_upd_PreviousInput[2] = EKFSim_pi_P.P_upd_InitialCondition[2];
  EKFSim_pi_DW.P_upd_PreviousInput[3] = EKFSim_pi_P.P_upd_InitialCondition[3];

  /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
  EKFSim_pi_DW.UnitDelay_DSTATE_c = EKFSim_pi_P.UnitDelay_InitialCondition_j;

  /* InitializeConditions for Integrator: '<S4>/Integrator' */
  EKFSim_pi_X.Integrator_CSTATE = EKFSim_pi_P.Integrator_IC;
}

/* Model terminate function */
void EKFSim_pi_terminate(void)
{
  /* (no terminate code required) */
}
