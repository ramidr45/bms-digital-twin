/*
 * EKFSim.c
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

#include "EKFSim.h"
#include "rtwtypes.h"
#include <math.h>
#include <float.h>
#include "rt_nonfinite.h"
#include <stddef.h>
#include "EKFSim_private.h"
#include <string.h>

/* Block signals (default storage) */
B_EKFSim_T EKFSim_B;

/* Continuous states */
X_EKFSim_T EKFSim_X;

/* Disabled State Vector */
XDis_EKFSim_T EKFSim_XDis;

/* Block states (default storage) */
DW_EKFSim_T EKFSim_DW;

/* External inputs (root inport signals with default storage) */
ExtU_EKFSim_T EKFSim_U;

/* Mass Matrices */
MassMatrix_EKFSim_T EKFSim_MassMatrix;

/* Real-time model */
static RT_MODEL_EKFSim_T EKFSim_M_;
RT_MODEL_EKFSim_T *const EKFSim_M = &EKFSim_M_;
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

/* ForcingFunction for root system: '<Root>' */
void EKFSim_forcingfunction(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  XDot_EKFSim_T *_rtXdot;
  char *msg;
  real_T tmp_0[16];
  real_T time;
  int32_T tmp_2;
  int_T tmp_1[5];
  boolean_T tmp;
  _rtXdot = ((XDot_EKFSim_T *) EKFSim_M->derivs);

  /* ForcingFunction for SimscapeExecutionBlock: '<S21>/STATE_1' */
  simulationData = (NeslSimulationData *)EKFSim_DW.STATE_1_SimData;
  time = EKFSim_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 1;
  simulationData->mData->mContStates.mX =
    &EKFSim_X.EKFSimThevenin_ECMVariable_R0v;
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &EKFSim_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 1;
  simulationData->mData->mModeVector.mX = &EKFSim_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mHadEvents = false;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(EKFSim_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&EKFSim_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&EKFSim_M->solverInfo);
  tmp_1[0] = 0;
  tmp_0[0] = EKFSim_B.INPUT_1_1_1[0];
  tmp_0[1] = EKFSim_B.INPUT_1_1_1[1];
  tmp_0[2] = EKFSim_B.INPUT_1_1_1[2];
  tmp_0[3] = EKFSim_B.INPUT_1_1_1[3];
  tmp_1[1] = 4;
  tmp_0[4] = EKFSim_B.INPUT_2_1_1[0];
  tmp_0[5] = EKFSim_B.INPUT_2_1_1[1];
  tmp_0[6] = EKFSim_B.INPUT_2_1_1[2];
  tmp_0[7] = EKFSim_B.INPUT_2_1_1[3];
  tmp_1[2] = 8;
  tmp_0[8] = EKFSim_B.INPUT_3_1_1[0];
  tmp_0[9] = EKFSim_B.INPUT_3_1_1[1];
  tmp_0[10] = EKFSim_B.INPUT_3_1_1[2];
  tmp_0[11] = EKFSim_B.INPUT_3_1_1[3];
  tmp_1[3] = 12;
  tmp_0[12] = EKFSim_B.INPUT_4_1_1[0];
  tmp_0[13] = EKFSim_B.INPUT_4_1_1[1];
  tmp_0[14] = EKFSim_B.INPUT_4_1_1[2];
  tmp_0[15] = EKFSim_B.INPUT_4_1_1[3];
  tmp_1[4] = 16;
  simulationData->mData->mInputValues.mN = 16;
  simulationData->mData->mInputValues.mX = &tmp_0[0];
  simulationData->mData->mInputOffsets.mN = 5;
  simulationData->mData->mInputOffsets.mX = &tmp_1[0];
  simulationData->mData->mDx.mN = 1;
  simulationData->mData->mDx.mX = &_rtXdot->EKFSimThevenin_ECMVariable_R0v;
  diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_2 = ne_simulator_method((NeslSimulator *)EKFSim_DW.STATE_1_Simulator,
    NESL_SIM_FORCINGFUNCTION, simulationData, diagnosticManager);
  if (tmp_2 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
    if (tmp) {
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(EKFSim_M, msg);
    }
  }

  /* End of ForcingFunction for SimscapeExecutionBlock: '<S21>/STATE_1' */

  /* ForcingFunction for Integrator: '<S4>/Integrator' incorporates:
   *  Inport: '<Root>/tuvar'
   */
  _rtXdot->Integrator_CSTATE = EKFSim_U.tuvar;
}

/* MassMatrix for root system: '<Root>' */
void EKFSim_massmatrix(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  char *msg;
  real_T tmp_0[16];
  real_T time;
  real_T *tmp_2;
  real_T *tmp_3;
  int32_T tmp_4;
  int_T tmp_1[5];
  boolean_T tmp;

  /* MassMatrix for SimscapeExecutionBlock: '<S21>/STATE_1' */
  simulationData = (NeslSimulationData *)EKFSim_DW.STATE_1_SimData;
  time = EKFSim_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 1;
  simulationData->mData->mContStates.mX =
    &EKFSim_X.EKFSimThevenin_ECMVariable_R0v;
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &EKFSim_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 1;
  simulationData->mData->mModeVector.mX = &EKFSim_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mHadEvents = false;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(EKFSim_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&EKFSim_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&EKFSim_M->solverInfo);
  tmp_1[0] = 0;
  tmp_0[0] = EKFSim_B.INPUT_1_1_1[0];
  tmp_0[1] = EKFSim_B.INPUT_1_1_1[1];
  tmp_0[2] = EKFSim_B.INPUT_1_1_1[2];
  tmp_0[3] = EKFSim_B.INPUT_1_1_1[3];
  tmp_1[1] = 4;
  tmp_0[4] = EKFSim_B.INPUT_2_1_1[0];
  tmp_0[5] = EKFSim_B.INPUT_2_1_1[1];
  tmp_0[6] = EKFSim_B.INPUT_2_1_1[2];
  tmp_0[7] = EKFSim_B.INPUT_2_1_1[3];
  tmp_1[2] = 8;
  tmp_0[8] = EKFSim_B.INPUT_3_1_1[0];
  tmp_0[9] = EKFSim_B.INPUT_3_1_1[1];
  tmp_0[10] = EKFSim_B.INPUT_3_1_1[2];
  tmp_0[11] = EKFSim_B.INPUT_3_1_1[3];
  tmp_1[3] = 12;
  tmp_0[12] = EKFSim_B.INPUT_4_1_1[0];
  tmp_0[13] = EKFSim_B.INPUT_4_1_1[1];
  tmp_0[14] = EKFSim_B.INPUT_4_1_1[2];
  tmp_0[15] = EKFSim_B.INPUT_4_1_1[3];
  tmp_1[4] = 16;
  simulationData->mData->mInputValues.mN = 16;
  simulationData->mData->mInputValues.mX = &tmp_0[0];
  simulationData->mData->mInputOffsets.mN = 5;
  simulationData->mData->mInputOffsets.mX = &tmp_1[0];
  tmp_2 = EKFSim_M->massMatrixPr;
  tmp_3 = double_pointer_shift(tmp_2, EKFSim_DW.STATE_1_MASS_MATRIX_PR);
  simulationData->mData->mMassMatrixPr.mN = 1;
  simulationData->mData->mMassMatrixPr.mX = tmp_3;
  diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_4 = ne_simulator_method((NeslSimulator *)EKFSim_DW.STATE_1_Simulator,
    NESL_SIM_MASSMATRIX, simulationData, diagnosticManager);
  if (tmp_4 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
    if (tmp) {
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(EKFSim_M, msg);
    }
  }

  /* End of MassMatrix for SimscapeExecutionBlock: '<S21>/STATE_1' */
}

void local_evaluateMassMatrix(RTWSolverInfo *si, real_T *Mdest )
{
  /* Refresh global mass matrix */
  EKFSim_massmatrix();

  /* Copy the mass matrix from system to the destination, if needed. */
  if (Mdest != rtsiGetSolverMassMatrixPr(si)) {
    real_T *Msrc = rtsiGetSolverMassMatrixPr(si);
    int_T nzmax = rtsiGetSolverMassMatrixNzMax(si);
    (void) memcpy(Mdest, Msrc,
                  (uint_T)nzmax*sizeof(real_T));
  }
}

/* Simplified version of numjac.cpp, for use with RTW. */
void local_numjac( RTWSolverInfo *si, real_T *y, const real_T *Fty, real_T *fac,
                  real_T *dFdy )
{
  /* constants */
  real_T THRESH = 1e-6;
  real_T EPS = 2.2e-16;                /* utGetEps(); */
  real_T BL = pow(EPS, 0.75);
  real_T BU = pow(EPS, 0.25);
  real_T FACMIN = pow(EPS, 0.78);
  real_T FACMAX = 0.1;
  int_T nx = 2;
  real_T *x = rtsiGetContStates(si);
  boolean_T *xdis = rtsiGetContStateDisabledPtr(si);
  real_T del;
  real_T difmax;
  real_T FdelRowmax;
  real_T temp;
  real_T Fdiff;
  real_T maybe;
  real_T xscale;
  real_T fscale;
  real_T *p;
  int_T rowmax;
  int_T i,j;
  if (x != y)
    (void) memcpy(x, y,
                  (uint_T)nx*sizeof(real_T));
  rtsiSetSolverComputingJacobian(si,true);
  for (p = dFdy, j = 0; j < nx; j++, p += nx) {
    /* Zero column j of dFdy if state j is currently disabled. */
    if (xdis[j]) {
      (void) memset(p, 0,
                    (uint_T)nx*sizeof(p[0]));
      continue;
    }

    /* Select an increment del for a difference approximation to
       column j of dFdy.  The vector fac accounts for experience
       gained in previous calls to numjac. */
    xscale = fabs(x[j]);
    if (xscale < THRESH)
      xscale = THRESH;
    temp = (x[j] + fac[j]*xscale);
    del = temp - y[j];
    while (del == 0.0) {
      if (fac[j] < FACMAX) {
        fac[j] *= 100.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
        temp = (x[j] + fac[j]*xscale);
        del = temp - x[j];
      } else {
        del = THRESH;                  /* thresh is nonzero */
        break;
      }
    }

    /* Keep del pointing into region. */
    if (Fty[j] >= 0.0)
      del = fabs(del);
    else
      del = -fabs(del);

    /* Form a difference approximation to column j of dFdy. */
    temp = x[j];
    x[j] += del;
    EKFSim_step();
    rtsiSetdX(si,p);
    EKFSim_forcingfunction();
    x[j] = temp;
    difmax = 0.0;
    rowmax = 0;
    FdelRowmax = p[0];
    temp = 1.0 / del;
    for (i = 0; i < nx; i++) {
      Fdiff = p[i] - Fty[i];
      maybe = fabs(Fdiff);
      if (maybe > difmax) {
        difmax = maybe;
        rowmax = i;
        FdelRowmax = p[i];
      }

      p[i] = temp * Fdiff;
    }

    /* Adjust fac for next call to numjac. */
    if (((FdelRowmax != 0.0) && (Fty[rowmax] != 0.0)) || (difmax == 0.0)) {
      fscale = fabs(FdelRowmax);
      if (fscale < fabs(Fty[rowmax]))
        fscale = fabs(Fty[rowmax]);
      if (difmax <= BL*fscale) {
        /* The difference is small, so increase the increment. */
        fac[j] *= 10.0;
        if (fac[j] > FACMAX)
          fac[j] = FACMAX;
      } else if (difmax > BU*fscale) {
        /* The difference is large, so reduce the increment. */
        fac[j] *= 0.1;
        if (fac[j] < FACMIN)
          fac[j] = FACMIN;
      }
    }
  }

  rtsiSetSolverComputingJacobian(si,false);
}                                      /* end local_numjac */

/*
 * This function updates continuous states using the ODE14X fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static int_T rt_ODE14x_N[4] = { 12, 8, 6, 4 };

  time_T t0 = rtsiGetT(si);
  time_T t1 = t0;
  time_T h = rtsiGetStepSize(si);
  real_T *x1 = rtsiGetContStates(si);
  int_T order = rtsiGetSolverExtrapolationOrder(si);
  int_T numIter = rtsiGetSolverNumberNewtonIterations(si);
  ODE14X_IntgData *id = (ODE14X_IntgData *)rtsiGetSolverData(si);
  real_T *x0 = id->x0;
  real_T *f0 = id->f0;
  real_T *x1start = id->x1start;
  real_T *f1 = id->f1;
  real_T *Delta = id->Delta;
  real_T *E = id->E;
  real_T *fac = id->fac;
  real_T *dfdx = id->DFDX;
  real_T *W = id->W;
  int_T *pivots = id->pivots;
  real_T *xtmp = id->xtmp;
  real_T *ztmp = id->ztmp;
  boolean_T *xdis = rtsiGetContStateDisabledPtr(si);
  int_T *Mpattern_ir = rtsiGetSolverMassMatrixIr(si);
  int_T *Mpattern_jc = rtsiGetSolverMassMatrixJc(si);
  real_T *M = id->M;
  int_T col,row,rowidx;
  int_T *N = &(rt_ODE14x_N[0]);
  int_T i,j,k,iter;
  int_T nx = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(x0, x1,
                (uint_T)nx*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  if (id->isFirstStep) {
    local_evaluateMassMatrix(si,M );
    id->isFirstStep = false;
  }

  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  EKFSim_forcingfunction();
  local_numjac(si,x0,f0,fac,dfdx );
  for (j = 0; j < order; j++) {
    real_T *p;
    real_T hN = h/N[j];

    /* Get the iteration matrix and solution at t0 */

    /* [L,U] = lu(M - hN*J) */
    (void) memcpy(W, dfdx,
                  (uint_T)nx*(uint_T)nx*sizeof(real_T));
    for (p = W, i = 0; i < nx*nx; i++, p++) {
      *p *= (-hN);
    }

    for (col = 0, p = W; col < nx; col++, p += nx) {
      if (xdis[col]) {
        (void) memset(p, 0,
                      (uint_T)nx*sizeof(p[0]));
        p[col] = 1.0;
      } else {
        for (rowidx = Mpattern_jc[col]; rowidx < Mpattern_jc[col+1]; rowidx++) {
          real_T m_row_col = M[rowidx];
          row = Mpattern_ir[rowidx];
          p[row] += m_row_col;
        }
      }
    }

    rt_lu_real(W, nx,
               pivots);

    /* First Newton's iteration at t0. */
    /* rhs = hN*f0 */
    for (i = 0; i < nx; i++) {
      Delta[i] = hN*f0[i];
    }

    /* Delta = (U \ (L \ rhs)) */
    rt_ForwardSubstitutionRR_Dbl(W, Delta,
      f1, nx,
      1, pivots,
      1);
    rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
      Delta, nx,
      1, 0);

    /* ytmp = y0 + Delta
       ztmp = (ytmp-y0)/h
     */
    (void) memcpy(x1, x0,
                  (uint_T)nx*sizeof(real_T));
    for (i = 0; i < nx; i++) {
      x1[i] += Delta[i];
      ztmp[i] = Delta[i]/hN;
    }

    /* Additional Newton's iterations, if desired.
       for iter = 2:NewtIter
       rhs = hN*feval(odefun,tn,ytmp,extraArgs{:}) - M*(ytmp - yn);
       if statedepM   % only for state dep. Mdel ~= 0
       Mdel = M - feval(massfun,tn,ytmp);
       rhs = rhs + Mdel*ztmp*h;
       end
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       ztmp = (ytmp - yn)/h
       end
     */
    rtsiSetT(si, t0);
    rtsiSetdX(si, f1);
    for (iter = 1; iter < numIter; iter++) {
      EKFSim_step();
      EKFSim_forcingfunction();
      for (i = 0; i < nx; i++) {
        Delta[i] = hN*f1[i];
        xtmp[i] = x1[i] - x0[i];
      }

      /* rhs = hN*f(tn,ytmp) - M*(ytmp-yn) */
      for (col = 0; col < nx; col++) {
        for (rowidx = Mpattern_jc[col]; rowidx < Mpattern_jc[col+1]; rowidx++) {
          real_T m_row_col = M[rowidx];
          row = Mpattern_ir[rowidx];
          Delta[row] -= m_row_col*xtmp[col];
        }
      }

      rt_ForwardSubstitutionRR_Dbl(W, Delta,
        f1, nx,
        1, pivots,
        1);
      rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
        Delta, nx,
        1, 0);

      /* ytmp = ytmp + delta
         ztmp = (ytmp - yn)/h
       */
      for (i = 0; i < nx; i++) {
        x1[i] += Delta[i];
        ztmp[i] = (x1[i] - x0[i])/hN;
      }
    }

    /* Steps from t0+hN to t1 -- subintegration of N(j) steps for extrapolation
       ttmp = t0;
       for i = 2:N(j)
       ttmp = ttmp + hN
       ytmp0 = ytmp;
       for iter = 1:NewtIter
       rhs = (ytmp0 - ytmp) + hN*feval(odefun,ttmp,ytmp,extraArgs{:});
       Delta = ( U \ ( L \ rhs ) );
       ytmp = ytmp + Delta;
       end
       end
     */
    for (k = 1; k < N[j]; k++) {
      t1 = t0 + k*hN;
      (void) memcpy(x1start, x1,
                    (uint_T)nx*sizeof(real_T));
      rtsiSetT(si, t1);
      rtsiSetdX(si, f1);
      for (iter = 0; iter < numIter; iter++) {
        EKFSim_step();
        EKFSim_forcingfunction();
        if (iter == 0) {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
          }
        } else {
          for (i = 0; i < nx; i++) {
            Delta[i] = hN*f1[i];
            xtmp[i] = (x1[i]-x1start[i]);
          }

          /* rhs = hN*f(tn,ytmp) - M*(ytmp-yn) */
          for (col = 0; col < nx; col++) {
            for (rowidx = Mpattern_jc[col]; rowidx < Mpattern_jc[col+1]; rowidx
                 ++) {
              real_T m_row_col = M[rowidx];
              row = Mpattern_ir[rowidx];
              Delta[row] -= m_row_col*xtmp[col];
            }
          }
        }

        rt_ForwardSubstitutionRR_Dbl(W, Delta,
          f1, nx,
          1, pivots,
          1);
        rt_BackwardSubstitutionRR_Dbl(W+nx*nx-1, f1+nx-1,
          Delta, nx,
          1, 0);

        /* ytmp = ytmp + Delta
           ztmp = (ytmp - ytmp0)/h
         */
        for (i = 0; i < nx; i++) {
          x1[i] += Delta[i];
          ztmp[i] = (x1[i] - x1start[i])/hN;
        }
      }
    }

    /* Extrapolate to order j
       E(:,j) = ytmp
       for k = j:-1:2
       coef = N(k-1)/(N(j) - N(k-1))
       E(:,k-1) = E(:,k) + coef*( E(:,k) - E(:,k-1) )
       end
     */
    (void) memcpy(&(E[nx*j]), x1,
                  (uint_T)nx*sizeof(real_T));
    for (k = j; k > 0; k--) {
      real_T coef = (real_T)(N[k-1]) / (N[j]-N[k-1]);
      for (i = 0; i < nx; i++) {
        x1[i] = E[nx*k+i] + coef*(E[nx*k+i] - E[nx*(k-1)+i]);
      }

      (void) memcpy(&(E[nx*(k-1)]), x1,
                    (uint_T)nx*sizeof(real_T));
    }
  }

  /* x1 = E(:,1); */
  (void) memcpy(x1, E,
                (uint_T)nx*sizeof(real_T));

  /* t1 = t0 + h; */
  rtsiSetT(si,rtsiGetSolverStopTime(si));
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void EKFSim_step(void)
{
  /* local block i/o variables */
  real_T rtb_Sum;
  if (rtmIsMajorTimeStep(EKFSim_M)) {
    /* set solver stop time */
    if (!(EKFSim_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&EKFSim_M->solverInfo,
                            ((EKFSim_M->Timing.clockTickH0 + 1) *
        EKFSim_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&EKFSim_M->solverInfo, ((EKFSim_M->Timing.clockTick0
        + 1) * EKFSim_M->Timing.stepSize0 + EKFSim_M->Timing.clockTickH0 *
        EKFSim_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(EKFSim_M)) {
    EKFSim_M->Timing.t[0] = rtsiGetT(&EKFSim_M->solverInfo);
  }

  {
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    NeuDiagnosticTree *diagnosticTree_0;
    NeuDiagnosticTree *diagnosticTree_1;
    char *msg;
    char *msg_0;
    char *msg_1;
    real_T tmp_3[18];
    real_T tmp_5[18];
    real_T tmp_0[16];
    real_T A[4];
    real_T A_0[4];
    real_T P_pre[4];
    real_T A_1;
    real_T A_2;
    real_T A_3;
    real_T K_idx_0;
    real_T K_idx_1;
    real_T rtb_SOC_upd1;
    real_T time;
    real_T time_0;
    real_T time_1;
    real_T time_2;
    real_T time_3;
    real_T time_4;
    real_T time_tmp;
    real_T time_tmp_0;
    real_T xloc;
    int32_T high_i;
    int32_T low_i;
    int32_T low_ip1;
    int32_T mid_i;
    int_T tmp_4[6];
    int_T tmp_6[6];
    int_T tmp_1[5];
    boolean_T tmp;
    boolean_T tmp_2;
    boolean_T tmp_7;
    boolean_T tmp_8;
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

    tmp_7 = rtmIsMajorTimeStep(EKFSim_M);
    if (tmp_7) {
      /* UnitDelay: '<Root>/Unit Delay' */
      EKFSim_B.UL_Obs = EKFSim_DW.UnitDelay_DSTATE;

      /* Memory: '<Root>/SOC_upd' */
      rtb_SOC_upd1 = EKFSim_DW.SOC_upd_PreviousInput;

      /* Lookup_n-D: '<S3>/OCV' incorporates:
       *  Memory: '<Root>/SOC_upd'
       */
      EKFSim_B.OCV = look1_binlcpw(EKFSim_DW.SOC_upd_PreviousInput,
        EKFSim_P.SOC_bp, EKFSim_P.OCV_bp, 95U);
    }

    /* SimscapeInputBlock: '<S21>/INPUT_1_1_1' incorporates:
     *  SimscapeExecutionBlock: '<S21>/OUTPUT_1_0'
     *  SimscapeExecutionBlock: '<S21>/OUTPUT_1_1'
     *  SimscapeExecutionBlock: '<S21>/STATE_1'
     *  SimscapeInputBlock: '<S21>/INPUT_3_1_1'
     */
    EKFSim_B.INPUT_1_1_1[0] = EKFSim_B.OCV;
    EKFSim_B.INPUT_1_1_1[1] = 0.0;
    EKFSim_B.INPUT_1_1_1[2] = 0.0;
    tmp_8 = rtmIsMajorTimeStep(EKFSim_M);
    if (tmp_8) {
      EKFSim_DW.INPUT_1_1_1_Discrete_2796830670[0] = !(EKFSim_B.INPUT_1_1_1[0] ==
        EKFSim_DW.INPUT_1_1_1_Discrete_2796830670[1]);
      EKFSim_DW.INPUT_1_1_1_Discrete_2796830670[1] = EKFSim_B.INPUT_1_1_1[0];
    }

    EKFSim_B.INPUT_1_1_1[0] = EKFSim_DW.INPUT_1_1_1_Discrete_2796830670[1];
    EKFSim_B.INPUT_1_1_1[3] = EKFSim_DW.INPUT_1_1_1_Discrete_2796830670[0];

    /* End of SimscapeInputBlock: '<S21>/INPUT_1_1_1' */
    if (tmp_7) {
      /* Lookup_n-D: '<S3>/rp' incorporates:
       *  Memory: '<Root>/SOC_upd1'
       */
      EKFSim_B.rp = look1_binlcpw(rtb_SOC_upd1, EKFSim_P.SOC_bp, EKFSim_P.R1_bp,
        95U);

      /* Lookup_n-D: '<S3>/rp1' incorporates:
       *  Memory: '<Root>/SOC_upd1'
       */
      EKFSim_B.rp1 = look1_binlcpw(rtb_SOC_upd1, EKFSim_P.SOC_bp, EKFSim_P.C1_bp,
        95U);

      /* Memory: '<Root>/Up_pre' */
      EKFSim_B.Up_pre = EKFSim_DW.Up_pre_PreviousInput;

      /* Lookup_n-D: '<S3>/r0' incorporates:
       *  Memory: '<Root>/SOC_upd1'
       */
      EKFSim_B.r0 = look1_binlcpw(rtb_SOC_upd1, EKFSim_P.SOC_bp, EKFSim_P.R0_bp,
        95U);
    }

    /* Gain: '<S6>/Gain' incorporates:
     *  Inport: '<Root>/tuvar'
     */
    EKFSim_B.Gain = EKFSim_P.Gain_Gain * EKFSim_U.tuvar;

    /* MATLAB Function: '<S6>/Up_prediction' incorporates:
     *  MATLAB Function: '<Root>/EKF'
     */
    /* MATLAB Function 'Thevenin ECM/Up_prediction': '<S14>:1' */
    /* '<S14>:1:2' */
    /* '<S14>:1:3' */
    /* '<S14>:1:4' */
    xloc = exp(-0.1 / (EKFSim_B.rp * EKFSim_B.rp1));
    EKFSim_B.Up_pre_o = (1.0 - xloc) * EKFSim_B.rp * EKFSim_B.Gain + xloc *
      EKFSim_B.Up_pre;

    /* SimscapeInputBlock: '<S21>/INPUT_2_1_1' */
    EKFSim_B.INPUT_2_1_1[0] = EKFSim_B.Up_pre_o;
    EKFSim_B.INPUT_2_1_1[1] = 0.0;
    EKFSim_B.INPUT_2_1_1[2] = 0.0;
    EKFSim_B.INPUT_2_1_1[3] = 0.0;

    /* SimscapeInputBlock: '<S21>/INPUT_3_1_1' */
    EKFSim_B.INPUT_3_1_1[0] = EKFSim_B.r0;
    EKFSim_B.INPUT_3_1_1[1] = 0.0;
    EKFSim_B.INPUT_3_1_1[2] = 0.0;
    if (tmp_8) {
      EKFSim_DW.INPUT_3_1_1_Discrete_3698617518[0] = !(EKFSim_B.INPUT_3_1_1[0] ==
        EKFSim_DW.INPUT_3_1_1_Discrete_3698617518[1]);
      EKFSim_DW.INPUT_3_1_1_Discrete_3698617518[1] = EKFSim_B.INPUT_3_1_1[0];
    }

    EKFSim_B.INPUT_3_1_1[0] = EKFSim_DW.INPUT_3_1_1_Discrete_3698617518[1];
    EKFSim_B.INPUT_3_1_1[3] = EKFSim_DW.INPUT_3_1_1_Discrete_3698617518[0];

    /* SimscapeInputBlock: '<S21>/INPUT_4_1_1' incorporates:
     *  Inport: '<Root>/tuvar'
     */
    EKFSim_B.INPUT_4_1_1[0] = EKFSim_U.tuvar;
    EKFSim_B.INPUT_4_1_1[1] = 0.0;
    EKFSim_B.INPUT_4_1_1[2] = 0.0;
    EKFSim_B.INPUT_4_1_1[3] = 0.0;

    /* SimscapeExecutionBlock: '<S21>/STATE_1' incorporates:
     *  SimscapeExecutionBlock: '<S21>/OUTPUT_1_0'
     *  SimscapeExecutionBlock: '<S21>/OUTPUT_1_1'
     */
    simulationData = (NeslSimulationData *)EKFSim_DW.STATE_1_SimData;
    time_tmp = EKFSim_M->Timing.t[0];
    time = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 1;
    simulationData->mData->mContStates.mX =
      &EKFSim_X.EKFSimThevenin_ECMVariable_R0v;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &EKFSim_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 1;
    simulationData->mData->mModeVector.mX = &EKFSim_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mHadEvents = false;
    simulationData->mData->mIsMajorTimeStep = tmp_8;
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp = rtsiIsSolverComputingJacobian(&EKFSim_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    tmp = rtsiIsModeUpdateTimeStep(&EKFSim_M->solverInfo);
    simulationData->mData->mIsModeUpdateTimeStep = tmp;
    tmp_1[0] = 0;
    tmp_0[0] = EKFSim_B.INPUT_1_1_1[0];
    tmp_0[1] = EKFSim_B.INPUT_1_1_1[1];
    tmp_0[2] = EKFSim_B.INPUT_1_1_1[2];
    tmp_0[3] = EKFSim_B.INPUT_1_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = EKFSim_B.INPUT_2_1_1[0];
    tmp_0[5] = EKFSim_B.INPUT_2_1_1[1];
    tmp_0[6] = EKFSim_B.INPUT_2_1_1[2];
    tmp_0[7] = EKFSim_B.INPUT_2_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = EKFSim_B.INPUT_3_1_1[0];
    tmp_0[9] = EKFSim_B.INPUT_3_1_1[1];
    tmp_0[10] = EKFSim_B.INPUT_3_1_1[2];
    tmp_0[11] = EKFSim_B.INPUT_3_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = EKFSim_B.INPUT_4_1_1[0];
    tmp_0[13] = EKFSim_B.INPUT_4_1_1[1];
    tmp_0[14] = EKFSim_B.INPUT_4_1_1[2];
    tmp_0[15] = EKFSim_B.INPUT_4_1_1[3];
    tmp_1[4] = 16;
    simulationData->mData->mInputValues.mN = 16;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 5;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    simulationData->mData->mOutputs.mN = 2;
    simulationData->mData->mOutputs.mX = &EKFSim_B.STATE_1[0];
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    simulationData->mData->mDstateHasChanged = false;
    time_tmp_0 = EKFSim_M->Timing.t[0];
    time_0 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_0;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    simulationData->mData->mHadEvents = false;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    high_i = ne_simulator_method((NeslSimulator *)EKFSim_DW.STATE_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (high_i != 0) {
      tmp_2 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_2) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(EKFSim_M, msg);
      }
    }

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */
    simulationData = (NeslSimulationData *)EKFSim_DW.OUTPUT_1_1_SimData;
    time_1 = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_1;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &EKFSim_DW.OUTPUT_1_1_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &EKFSim_DW.OUTPUT_1_1_Modes;
    tmp_2 = false;
    simulationData->mData->mFoundZcEvents = tmp_2;
    simulationData->mData->mHadEvents = false;
    simulationData->mData->mIsMajorTimeStep = tmp_8;
    tmp_2 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_2;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = tmp;
    tmp_4[0] = 0;
    tmp_3[0] = EKFSim_B.INPUT_1_1_1[0];
    tmp_3[1] = EKFSim_B.INPUT_1_1_1[1];
    tmp_3[2] = EKFSim_B.INPUT_1_1_1[2];
    tmp_3[3] = EKFSim_B.INPUT_1_1_1[3];
    tmp_4[1] = 4;
    tmp_3[4] = EKFSim_B.INPUT_2_1_1[0];
    tmp_3[5] = EKFSim_B.INPUT_2_1_1[1];
    tmp_3[6] = EKFSim_B.INPUT_2_1_1[2];
    tmp_3[7] = EKFSim_B.INPUT_2_1_1[3];
    tmp_4[2] = 8;
    tmp_3[8] = EKFSim_B.INPUT_3_1_1[0];
    tmp_3[9] = EKFSim_B.INPUT_3_1_1[1];
    tmp_3[10] = EKFSim_B.INPUT_3_1_1[2];
    tmp_3[11] = EKFSim_B.INPUT_3_1_1[3];
    tmp_4[3] = 12;
    tmp_3[12] = EKFSim_B.INPUT_4_1_1[0];
    tmp_3[13] = EKFSim_B.INPUT_4_1_1[1];
    tmp_3[14] = EKFSim_B.INPUT_4_1_1[2];
    tmp_3[15] = EKFSim_B.INPUT_4_1_1[3];
    tmp_4[4] = 16;
    tmp_3[16] = EKFSim_B.STATE_1[0];
    tmp_3[17] = EKFSim_B.STATE_1[1];
    tmp_4[5] = 18;
    simulationData->mData->mInputValues.mN = 18;
    simulationData->mData->mInputValues.mX = &tmp_3[0];
    simulationData->mData->mInputOffsets.mN = 6;
    simulationData->mData->mInputOffsets.mX = &tmp_4[0];
    simulationData->mData->mOutputs.mN = 1;

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */
    simulationData->mData->mOutputs.mX = &EKFSim_B.OUTPUT_1_1;

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    simulationData->mData->mDstateHasChanged = false;
    time_2 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_2;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    simulationData->mData->mHadEvents = false;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.OUTPUT_1_1_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    high_i = ne_simulator_method((NeslSimulator *)EKFSim_DW.OUTPUT_1_1_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (high_i != 0) {
      tmp_2 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_2) {
        msg_0 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(EKFSim_M, msg_0);
      }
    }

    if (tmp_7) {
      /* Memory: '<Root>/P_upd' */
      EKFSim_B.P_Old[0] = EKFSim_DW.P_upd_PreviousInput[0];
      EKFSim_B.P_Old[1] = EKFSim_DW.P_upd_PreviousInput[1];
      EKFSim_B.P_Old[2] = EKFSim_DW.P_upd_PreviousInput[2];
      EKFSim_B.P_Old[3] = EKFSim_DW.P_upd_PreviousInput[3];

      /* Sum: '<S5>/Sum' incorporates:
       *  Constant: '<S5>/Capacity'
       *  Gain: '<S5>/1H'
       *  Gain: '<S5>/Sample T'
       *  Product: '<S5>/Divide'
       *  UnitDelay: '<S5>/Unit Delay'
       */
      EKFSim_B.Sum = EKFSim_DW.UnitDelay_DSTATE_c / (EKFSim_P.uH_Gain *
        EKFSim_P.Capacity_Value) * EKFSim_P.SampleT_Gain + rtb_SOC_upd1;
    }

    /* MATLAB Function: '<Root>/EKF' incorporates:
     *  Constant: '<Root>/Noise'
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
    P_pre[0] = EKFSim_B.P_Old[0];
    P_pre[2] = EKFSim_B.P_Old[1];
    P_pre[1] = EKFSim_B.P_Old[2];
    P_pre[3] = EKFSim_B.P_Old[3];
    A[0] = 1.0;
    A_0[0] = 0.0;
    A_0[1] = 0.0;
    A[2] = 0.0;
    A_0[2] = 0.0;
    A_0[3] = 0.0;
    for (high_i = 0; high_i < 2; high_i++) {
      low_i = high_i << 1;
      rtb_SOC_upd1 = P_pre[low_i];
      K_idx_0 = A_0[low_i] + rtb_SOC_upd1;
      K_idx_1 = A_0[low_i + 1] + 0.0 * rtb_SOC_upd1;
      rtb_SOC_upd1 = P_pre[low_i + 1];
      A_0[low_i] = 0.0 * rtb_SOC_upd1 + K_idx_0;
      A_0[low_i + 1] = xloc * rtb_SOC_upd1 + K_idx_1;
    }

    K_idx_0 = A_0[0];
    K_idx_1 = A_0[1];
    xloc = A_0[2];
    A_3 = A_0[3];
    for (high_i = 0; high_i < 2; high_i++) {
      rtb_SOC_upd1 = A[high_i];
      A_1 = K_idx_0 * rtb_SOC_upd1;
      A_2 = K_idx_1 * rtb_SOC_upd1;
      rtb_SOC_upd1 = A[high_i + 2];
      low_i = high_i << 1;
      A_0[low_i] = xloc * rtb_SOC_upd1 + A_1;
      A_0[low_i + 1] = A_3 * rtb_SOC_upd1 + A_2;
    }

    P_pre[0] = A_0[0] + EKFSim_P.Noise_Value[0];
    P_pre[1] = A_0[1];
    P_pre[2] = A_0[2];
    P_pre[3] = EKFSim_P.Noise_Value[0] + A_0[3];

    /* '<S2>:1:15' */
    if (rtIsNaN(EKFSim_B.Sum)) {
      rtb_SOC_upd1 = EKFSim_B.Sum;
    } else {
      high_i = 14;
      low_i = 0;
      low_ip1 = 2;
      while (high_i > low_ip1) {
        mid_i = ((low_i + high_i) + 1) >> 1;
        if (EKFSim_B.Sum >= c[mid_i - 1]) {
          low_i = mid_i - 1;
          low_ip1 = mid_i + 1;
        } else {
          high_i = mid_i;
        }
      }

      xloc = EKFSim_B.Sum - c[low_i];
      rtb_SOC_upd1 = ((xloc * d[low_i] + d[low_i + 13]) * xloc + d[low_i + 26]) *
        xloc + d[low_i + 39];
    }

    /* '<S2>:1:16' */
    xloc = rtb_SOC_upd1;

    /* '<S2>:1:18' */
    /* '<S2>:1:19' */
    K_idx_0 = rtb_SOC_upd1 * P_pre[0];
    rtb_SOC_upd1 = 1.0 / (((K_idx_0 - A_0[1]) * rtb_SOC_upd1 - (rtb_SOC_upd1 *
      A_0[2] - P_pre[3])) + EKFSim_P.Noise_Value[1]);
    K_idx_0 = (K_idx_0 - A_0[2]) * rtb_SOC_upd1;
    K_idx_1 = (A_0[1] * xloc - P_pre[3]) * rtb_SOC_upd1;

    /* '<S2>:1:20' */
    rtb_SOC_upd1 = EKFSim_B.UL_Obs - EKFSim_B.OUTPUT_1_1;

    /* '<S2>:1:21' */
    A_0[0] = K_idx_0 * xloc;
    A_0[1] = K_idx_1 * xloc;
    A_0[2] = -K_idx_0;
    A_0[3] = -K_idx_1;
    for (high_i = 0; high_i < 2; high_i++) {
      xloc = A_0[high_i + 2];
      A_3 = A_0[high_i];
      A[high_i] = P_pre[high_i] - (xloc * P_pre[1] + A_3 * P_pre[0]);
      A[high_i + 2] = P_pre[high_i + 2] - (xloc * P_pre[3] + A_3 * P_pre[2]);
    }

    /* '<S2>:1:23' */
    EKFSim_B.SOC_upd = K_idx_0 * rtb_SOC_upd1 + EKFSim_B.Sum;

    /* '<S2>:1:24' */
    EKFSim_B.Up_upd = K_idx_1 * rtb_SOC_upd1 + EKFSim_B.Up_pre_o;

    /* '<S2>:1:25' */
    EKFSim_B.P_upd[0] = A[0];
    EKFSim_B.P_upd[1] = A[2];
    EKFSim_B.P_upd[2] = A[1];
    EKFSim_B.P_upd[3] = A[3];
    if (tmp_7) {
      /* ToWorkspace: '<Root>/SOC_EKF_log' */
      if (rtmIsMajorTimeStep(EKFSim_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (EKFSim_DW.SOC_EKF_log_PWORK.LoggedData),
                        &EKFSim_B.SOC_upd, 0);
      }
    }

    /* Integrator: '<S4>/Integrator' */
    EKFSim_B.Integrator = EKFSim_X.Integrator_CSTATE;

    /* Sum: '<S4>/Sum' incorporates:
     *  Constant: '<Root>/int_soc'
     *  Gain: '<S4>/Gain'
     */
    EKFSim_B.Sum_p = EKFSim_P.Gain_Gain_c * EKFSim_B.Integrator +
      EKFSim_P.int_soc_Value;
    if (tmp_7) {
      /* Sum: '<S1>/Sum' incorporates:
       *  Constant: '<S1>/Capacity'
       *  Gain: '<S1>/1H'
       *  Gain: '<S1>/Sample T'
       *  Memory: '<Root>/SOC_upd1'
       *  Product: '<S1>/Divide'
       *  UnitDelay: '<S1>/Unit Delay'
       */
      rtb_Sum = EKFSim_DW.UnitDelay_DSTATE_m / (EKFSim_P.uH_Gain_j *
        EKFSim_P.Capacity_Value_c) * EKFSim_P.SampleT_Gain_i +
        EKFSim_DW.SOC_upd1_PreviousInput;

      /* ToWorkspace: '<Root>/To Workspace' */
      if (rtmIsMajorTimeStep(EKFSim_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (EKFSim_DW.ToWorkspace_PWORK.LoggedData),
                        &EKFSim_B.Sum_p, 0);
      }

      /* ToWorkspace: '<Root>/To Workspace2' */
      if (rtmIsMajorTimeStep(EKFSim_M)) {
        rt_UpdateLogVar((LogVar *)(LogVar*)
                        (EKFSim_DW.ToWorkspace2_PWORK.LoggedData), &rtb_Sum, 0);
      }
    }

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
    simulationData = (NeslSimulationData *)EKFSim_DW.OUTPUT_1_0_SimData;
    time_3 = time_tmp;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_3;
    simulationData->mData->mContStates.mN = 0;
    simulationData->mData->mContStates.mX = NULL;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &EKFSim_DW.OUTPUT_1_0_Discrete;
    simulationData->mData->mModeVector.mN = 0;
    simulationData->mData->mModeVector.mX = &EKFSim_DW.OUTPUT_1_0_Modes;
    tmp_2 = false;
    simulationData->mData->mFoundZcEvents = tmp_2;
    simulationData->mData->mHadEvents = false;
    simulationData->mData->mIsMajorTimeStep = tmp_8;
    tmp_8 = false;
    simulationData->mData->mIsSolverAssertCheck = tmp_8;
    simulationData->mData->mIsSolverCheckingCIC = false;
    simulationData->mData->mIsComputingJacobian = false;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = tmp;
    tmp_6[0] = 0;
    tmp_5[0] = EKFSim_B.INPUT_1_1_1[0];
    tmp_5[1] = EKFSim_B.INPUT_1_1_1[1];
    tmp_5[2] = EKFSim_B.INPUT_1_1_1[2];
    tmp_5[3] = EKFSim_B.INPUT_1_1_1[3];
    tmp_6[1] = 4;
    tmp_5[4] = EKFSim_B.INPUT_2_1_1[0];
    tmp_5[5] = EKFSim_B.INPUT_2_1_1[1];
    tmp_5[6] = EKFSim_B.INPUT_2_1_1[2];
    tmp_5[7] = EKFSim_B.INPUT_2_1_1[3];
    tmp_6[2] = 8;
    tmp_5[8] = EKFSim_B.INPUT_3_1_1[0];
    tmp_5[9] = EKFSim_B.INPUT_3_1_1[1];
    tmp_5[10] = EKFSim_B.INPUT_3_1_1[2];
    tmp_5[11] = EKFSim_B.INPUT_3_1_1[3];
    tmp_6[3] = 12;
    tmp_5[12] = EKFSim_B.INPUT_4_1_1[0];
    tmp_5[13] = EKFSim_B.INPUT_4_1_1[1];
    tmp_5[14] = EKFSim_B.INPUT_4_1_1[2];
    tmp_5[15] = EKFSim_B.INPUT_4_1_1[3];
    tmp_6[4] = 16;
    tmp_5[16] = EKFSim_B.STATE_1[0];
    tmp_5[17] = EKFSim_B.STATE_1[1];
    tmp_6[5] = 18;
    simulationData->mData->mInputValues.mN = 18;
    simulationData->mData->mInputValues.mX = &tmp_5[0];
    simulationData->mData->mInputOffsets.mN = 6;
    simulationData->mData->mInputOffsets.mX = &tmp_6[0];
    simulationData->mData->mOutputs.mN = 1;

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
    simulationData->mData->mOutputs.mX = &EKFSim_B.OUTPUT_1_0;

    /* SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
    simulationData->mData->mTolerances.mN = 0;
    simulationData->mData->mTolerances.mX = NULL;
    simulationData->mData->mCstateHasChanged = false;
    simulationData->mData->mDstateHasChanged = false;
    time_4 = time_tmp_0;
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time_4;
    simulationData->mData->mSampleHits.mN = 0;
    simulationData->mData->mSampleHits.mX = NULL;
    simulationData->mData->mIsFundamentalSampleHit = false;
    simulationData->mData->mHadEvents = false;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree_1 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    high_i = ne_simulator_method((NeslSimulator *)EKFSim_DW.OUTPUT_1_0_Simulator,
      NESL_SIM_OUTPUTS, simulationData, diagnosticManager);
    if (high_i != 0) {
      tmp_8 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_8) {
        msg_1 = rtw_diagnostics_msg(diagnosticTree_1);
        rtmSetErrorStatus(EKFSim_M, msg_1);
      }
    }

    if (tmp_7) {
    }
  }

  if (rtmIsMajorTimeStep(EKFSim_M)) {
    /* Matfile logging */
    rt_UpdateTXYLogVars(EKFSim_M->rtwLogInfo, (EKFSim_M->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(EKFSim_M)) {
    NeslSimulationData *simulationData;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    char *msg;
    real_T tmp_0[16];
    real_T time;
    int32_T tmp_2;
    int_T tmp_1[5];
    boolean_T tmp;
    boolean_T tmp_3;
    tmp_3 = rtmIsMajorTimeStep(EKFSim_M);
    if (tmp_3) {
      /* Update for UnitDelay: '<Root>/Unit Delay' incorporates:
       *  Inport: '<Root>/vuvar'
       */
      EKFSim_DW.UnitDelay_DSTATE = EKFSim_U.UL_Real;

      /* Update for Memory: '<Root>/SOC_upd' */
      EKFSim_DW.SOC_upd_PreviousInput = EKFSim_B.SOC_upd;

      /* Update for Memory: '<Root>/Up_pre' */
      EKFSim_DW.Up_pre_PreviousInput = EKFSim_B.Up_upd;
    }

    /* Update for SimscapeExecutionBlock: '<S21>/STATE_1' */
    simulationData = (NeslSimulationData *)EKFSim_DW.STATE_1_SimData;
    time = EKFSim_M->Timing.t[0];
    simulationData->mData->mTime.mN = 1;
    simulationData->mData->mTime.mX = &time;
    simulationData->mData->mContStates.mN = 1;
    simulationData->mData->mContStates.mX =
      &EKFSim_X.EKFSimThevenin_ECMVariable_R0v;
    simulationData->mData->mDiscStates.mN = 0;
    simulationData->mData->mDiscStates.mX = &EKFSim_DW.STATE_1_Discrete;
    simulationData->mData->mModeVector.mN = 1;
    simulationData->mData->mModeVector.mX = &EKFSim_DW.STATE_1_Modes;
    tmp = false;
    simulationData->mData->mFoundZcEvents = tmp;
    simulationData->mData->mHadEvents = false;
    simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(EKFSim_M);
    tmp = false;
    simulationData->mData->mIsSolverAssertCheck = tmp;
    simulationData->mData->mIsSolverCheckingCIC = false;
    tmp = rtsiIsSolverComputingJacobian(&EKFSim_M->solverInfo);
    simulationData->mData->mIsComputingJacobian = tmp;
    simulationData->mData->mIsEvaluatingF0 = false;
    simulationData->mData->mIsSolverRequestingReset = false;
    simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
      (&EKFSim_M->solverInfo);
    tmp_1[0] = 0;
    tmp_0[0] = EKFSim_B.INPUT_1_1_1[0];
    tmp_0[1] = EKFSim_B.INPUT_1_1_1[1];
    tmp_0[2] = EKFSim_B.INPUT_1_1_1[2];
    tmp_0[3] = EKFSim_B.INPUT_1_1_1[3];
    tmp_1[1] = 4;
    tmp_0[4] = EKFSim_B.INPUT_2_1_1[0];
    tmp_0[5] = EKFSim_B.INPUT_2_1_1[1];
    tmp_0[6] = EKFSim_B.INPUT_2_1_1[2];
    tmp_0[7] = EKFSim_B.INPUT_2_1_1[3];
    tmp_1[2] = 8;
    tmp_0[8] = EKFSim_B.INPUT_3_1_1[0];
    tmp_0[9] = EKFSim_B.INPUT_3_1_1[1];
    tmp_0[10] = EKFSim_B.INPUT_3_1_1[2];
    tmp_0[11] = EKFSim_B.INPUT_3_1_1[3];
    tmp_1[3] = 12;
    tmp_0[12] = EKFSim_B.INPUT_4_1_1[0];
    tmp_0[13] = EKFSim_B.INPUT_4_1_1[1];
    tmp_0[14] = EKFSim_B.INPUT_4_1_1[2];
    tmp_0[15] = EKFSim_B.INPUT_4_1_1[3];
    tmp_1[4] = 16;
    simulationData->mData->mInputValues.mN = 16;
    simulationData->mData->mInputValues.mX = &tmp_0[0];
    simulationData->mData->mInputOffsets.mN = 5;
    simulationData->mData->mInputOffsets.mX = &tmp_1[0];
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_2 = ne_simulator_method((NeslSimulator *)EKFSim_DW.STATE_1_Simulator,
      NESL_SIM_UPDATE, simulationData, diagnosticManager);
    if (tmp_2 != 0) {
      tmp = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(EKFSim_M, msg);
      }
    }

    /* End of Update for SimscapeExecutionBlock: '<S21>/STATE_1' */
    if (tmp_3) {
      /* Update for Memory: '<Root>/P_upd' */
      EKFSim_DW.P_upd_PreviousInput[0] = EKFSim_B.P_upd[0];
      EKFSim_DW.P_upd_PreviousInput[1] = EKFSim_B.P_upd[1];
      EKFSim_DW.P_upd_PreviousInput[2] = EKFSim_B.P_upd[2];
      EKFSim_DW.P_upd_PreviousInput[3] = EKFSim_B.P_upd[3];

      /* Update for UnitDelay: '<S5>/Unit Delay' incorporates:
       *  Inport: '<Root>/tuvar'
       */
      EKFSim_DW.UnitDelay_DSTATE_c = EKFSim_U.tuvar;

      /* Update for UnitDelay: '<S1>/Unit Delay' incorporates:
       *  Inport: '<Root>/tuvar'
       */
      EKFSim_DW.UnitDelay_DSTATE_m = EKFSim_U.tuvar;

      /* Update for Memory: '<Root>/SOC_upd1' */
      EKFSim_DW.SOC_upd1_PreviousInput = rtb_Sum;
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(EKFSim_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(EKFSim_M)!=-1) &&
          !((rtmGetTFinal(EKFSim_M)-(((EKFSim_M->Timing.clockTick1+
               EKFSim_M->Timing.clockTickH1* 4294967296.0)) * 0.1)) >
            (((EKFSim_M->Timing.clockTick1+EKFSim_M->Timing.clockTickH1*
               4294967296.0)) * 0.1) * (DBL_EPSILON))) {
        rtmSetErrorStatus(EKFSim_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&EKFSim_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++EKFSim_M->Timing.clockTick0)) {
      ++EKFSim_M->Timing.clockTickH0;
    }

    EKFSim_M->Timing.t[0] = rtsiGetSolverStopTime(&EKFSim_M->solverInfo);

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
      EKFSim_M->Timing.clockTick1++;
      if (!EKFSim_M->Timing.clockTick1) {
        EKFSim_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void EKFSim_derivatives(void)
{
  NeslSimulationData *simulationData;
  NeuDiagnosticManager *diagnosticManager;
  NeuDiagnosticTree *diagnosticTree;
  XDot_EKFSim_T *_rtXdot;
  char *msg;
  real_T tmp_0[16];
  real_T time;
  int32_T tmp_2;
  int_T tmp_1[5];
  boolean_T tmp;
  _rtXdot = ((XDot_EKFSim_T *) EKFSim_M->derivs);

  /* Derivatives for SimscapeExecutionBlock: '<S21>/STATE_1' */
  simulationData = (NeslSimulationData *)EKFSim_DW.STATE_1_SimData;
  time = EKFSim_M->Timing.t[0];
  simulationData->mData->mTime.mN = 1;
  simulationData->mData->mTime.mX = &time;
  simulationData->mData->mContStates.mN = 1;
  simulationData->mData->mContStates.mX =
    &EKFSim_X.EKFSimThevenin_ECMVariable_R0v;
  simulationData->mData->mDiscStates.mN = 0;
  simulationData->mData->mDiscStates.mX = &EKFSim_DW.STATE_1_Discrete;
  simulationData->mData->mModeVector.mN = 1;
  simulationData->mData->mModeVector.mX = &EKFSim_DW.STATE_1_Modes;
  tmp = false;
  simulationData->mData->mFoundZcEvents = tmp;
  simulationData->mData->mHadEvents = false;
  simulationData->mData->mIsMajorTimeStep = rtmIsMajorTimeStep(EKFSim_M);
  tmp = false;
  simulationData->mData->mIsSolverAssertCheck = tmp;
  simulationData->mData->mIsSolverCheckingCIC = false;
  tmp = rtsiIsSolverComputingJacobian(&EKFSim_M->solverInfo);
  simulationData->mData->mIsComputingJacobian = tmp;
  simulationData->mData->mIsEvaluatingF0 = false;
  simulationData->mData->mIsSolverRequestingReset = false;
  simulationData->mData->mIsModeUpdateTimeStep = rtsiIsModeUpdateTimeStep
    (&EKFSim_M->solverInfo);
  tmp_1[0] = 0;
  tmp_0[0] = EKFSim_B.INPUT_1_1_1[0];
  tmp_0[1] = EKFSim_B.INPUT_1_1_1[1];
  tmp_0[2] = EKFSim_B.INPUT_1_1_1[2];
  tmp_0[3] = EKFSim_B.INPUT_1_1_1[3];
  tmp_1[1] = 4;
  tmp_0[4] = EKFSim_B.INPUT_2_1_1[0];
  tmp_0[5] = EKFSim_B.INPUT_2_1_1[1];
  tmp_0[6] = EKFSim_B.INPUT_2_1_1[2];
  tmp_0[7] = EKFSim_B.INPUT_2_1_1[3];
  tmp_1[2] = 8;
  tmp_0[8] = EKFSim_B.INPUT_3_1_1[0];
  tmp_0[9] = EKFSim_B.INPUT_3_1_1[1];
  tmp_0[10] = EKFSim_B.INPUT_3_1_1[2];
  tmp_0[11] = EKFSim_B.INPUT_3_1_1[3];
  tmp_1[3] = 12;
  tmp_0[12] = EKFSim_B.INPUT_4_1_1[0];
  tmp_0[13] = EKFSim_B.INPUT_4_1_1[1];
  tmp_0[14] = EKFSim_B.INPUT_4_1_1[2];
  tmp_0[15] = EKFSim_B.INPUT_4_1_1[3];
  tmp_1[4] = 16;
  simulationData->mData->mInputValues.mN = 16;
  simulationData->mData->mInputValues.mX = &tmp_0[0];
  simulationData->mData->mInputOffsets.mN = 5;
  simulationData->mData->mInputOffsets.mX = &tmp_1[0];
  simulationData->mData->mDx.mN = 1;
  simulationData->mData->mDx.mX = &_rtXdot->EKFSimThevenin_ECMVariable_R0v;
  diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
  diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
  tmp_2 = ne_simulator_method((NeslSimulator *)EKFSim_DW.STATE_1_Simulator,
    NESL_SIM_DERIVATIVES, simulationData, diagnosticManager);
  if (tmp_2 != 0) {
    tmp = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
    if (tmp) {
      msg = rtw_diagnostics_msg(diagnosticTree);
      rtmSetErrorStatus(EKFSim_M, msg);
    }
  }

  /* End of Derivatives for SimscapeExecutionBlock: '<S21>/STATE_1' */

  /* Derivatives for Integrator: '<S4>/Integrator' incorporates:
   *  Inport: '<Root>/tuvar'
   */
  _rtXdot->Integrator_CSTATE = EKFSim_U.tuvar;
}

/* Model initialize function */
void EKFSim_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)EKFSim_M, 0,
                sizeof(RT_MODEL_EKFSim_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&EKFSim_M->solverInfo, &EKFSim_M->Timing.simTimeStep);
    rtsiSetTPtr(&EKFSim_M->solverInfo, &rtmGetTPtr(EKFSim_M));
    rtsiSetStepSizePtr(&EKFSim_M->solverInfo, &EKFSim_M->Timing.stepSize0);
    rtsiSetdXPtr(&EKFSim_M->solverInfo, &EKFSim_M->derivs);
    rtsiSetContStatesPtr(&EKFSim_M->solverInfo, (real_T **)
                         &EKFSim_M->contStates);
    rtsiSetNumContStatesPtr(&EKFSim_M->solverInfo,
      &EKFSim_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&EKFSim_M->solverInfo,
      &EKFSim_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&EKFSim_M->solverInfo,
      &EKFSim_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&EKFSim_M->solverInfo,
      &EKFSim_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&EKFSim_M->solverInfo, (boolean_T**)
      &EKFSim_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&EKFSim_M->solverInfo, (&rtmGetErrorStatus(EKFSim_M)));
    rtsiSetSolverMassMatrixIr(&EKFSim_M->solverInfo, EKFSim_MassMatrix.ir);
    rtsiSetSolverMassMatrixJc(&EKFSim_M->solverInfo, EKFSim_MassMatrix.jc);
    rtsiSetSolverMassMatrixPr(&EKFSim_M->solverInfo, EKFSim_MassMatrix.pr);
    rtsiSetRTModelPtr(&EKFSim_M->solverInfo, EKFSim_M);
  }

  rtsiSetSimTimeStep(&EKFSim_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&EKFSim_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&EKFSim_M->solverInfo, false);
  EKFSim_M->intgData.x0 = EKFSim_M->odeX0;
  EKFSim_M->intgData.f0 = EKFSim_M->odeF0;
  EKFSim_M->intgData.x1start = EKFSim_M->odeX1START;
  EKFSim_M->intgData.f1 = EKFSim_M->odeF1;
  EKFSim_M->intgData.Delta = EKFSim_M->odeDELTA;
  EKFSim_M->intgData.E = EKFSim_M->odeE;
  EKFSim_M->intgData.fac = EKFSim_M->odeFAC;

  /* initialize */
  {
    int_T i;
    real_T *f = EKFSim_M->intgData.fac;
    for (i = 0; i < (int_T)(sizeof(EKFSim_M->odeFAC)/sizeof(real_T)); i++) {
      f[i] = 1.5e-8;
    }
  }

  EKFSim_M->intgData.DFDX = EKFSim_M->odeDFDX;
  EKFSim_M->intgData.W = EKFSim_M->odeW;
  EKFSim_M->intgData.pivots = EKFSim_M->odePIVOTS;
  EKFSim_M->intgData.xtmp = EKFSim_M->odeXTMP;
  EKFSim_M->intgData.ztmp = EKFSim_M->odeZTMP;
  EKFSim_M->intgData.M = EKFSim_M->odeMASSMATRIX_M;
  EKFSim_M->intgData.isFirstStep = true;
  rtsiSetSolverExtrapolationOrder(&EKFSim_M->solverInfo, 4);
  rtsiSetSolverNumberNewtonIterations(&EKFSim_M->solverInfo, 1);
  EKFSim_M->contStates = ((X_EKFSim_T *) &EKFSim_X);
  EKFSim_M->contStateDisabled = ((XDis_EKFSim_T *) &EKFSim_XDis);
  EKFSim_M->Timing.tStart = (0.0);
  EKFSim_M->massMatrixType = ((ssMatrixType)1);
  EKFSim_M->massMatrixNzMax = (2);
  EKFSim_M->massMatrixIr = (EKFSim_MassMatrix.ir);
  EKFSim_M->massMatrixJc = (EKFSim_MassMatrix.jc);
  EKFSim_M->massMatrixPr = (EKFSim_MassMatrix.pr);
  rtsiSetSolverMassMatrixType(&EKFSim_M->solverInfo, (ssMatrixType)1);
  rtsiSetSolverMassMatrixNzMax(&EKFSim_M->solverInfo, 2);
  rtsiSetSolverData(&EKFSim_M->solverInfo, (void *)&EKFSim_M->intgData);
  rtsiSetSolverName(&EKFSim_M->solverInfo,"ode14x");
  rtmSetTPtr(EKFSim_M, &EKFSim_M->Timing.tArray[0]);
  rtmSetTFinal(EKFSim_M, 4500.0);
  EKFSim_M->Timing.stepSize0 = 0.1;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    EKFSim_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(EKFSim_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(EKFSim_M->rtwLogInfo, (NULL));
    rtliSetLogT(EKFSim_M->rtwLogInfo, "tout");
    rtliSetLogX(EKFSim_M->rtwLogInfo, "");
    rtliSetLogXFinal(EKFSim_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(EKFSim_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(EKFSim_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(EKFSim_M->rtwLogInfo, 0);
    rtliSetLogDecimation(EKFSim_M->rtwLogInfo, 1);
    rtliSetLogY(EKFSim_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(EKFSim_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(EKFSim_M->rtwLogInfo, (NULL));
  }

  /* block I/O */
  (void) memset(((void *) &EKFSim_B), 0,
                sizeof(B_EKFSim_T));

  /* states (continuous) */
  {
    (void) memset((void *)&EKFSim_X, 0,
                  sizeof(X_EKFSim_T));
  }

  /* disabled states */
  {
    (void) memset((void *)&EKFSim_XDis, 0,
                  sizeof(XDis_EKFSim_T));
  }

  /* global mass matrix */
  {
    int_T *ir = EKFSim_MassMatrix.ir;
    int_T *jc = EKFSim_MassMatrix.jc;
    real_T *pr = EKFSim_MassMatrix.pr;
    (void) memset((void *)ir, 0,
                  2*sizeof(int_T));
    (void) memset((void *)jc, 0,
                  (2+1)*sizeof(int_T));
    (void) memset((void *)pr, 0,
                  2*sizeof(real_T));
  }

  /* states (dwork) */
  (void) memset((void *)&EKFSim_DW, 0,
                sizeof(DW_EKFSim_T));

  /* external inputs */
  (void)memset(&EKFSim_U, 0, sizeof(ExtU_EKFSim_T));

  /* Root-level init GlobalMassMatrixPr offset */
  {
    EKFSim_DW.STATE_1_MASS_MATRIX_PR = 0;/* '<S21>/STATE_1' */
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(EKFSim_M->rtwLogInfo, 0.0, rtmGetTFinal
    (EKFSim_M), EKFSim_M->Timing.stepSize0, (&rtmGetErrorStatus(EKFSim_M)));

  {
    NeModelParameters modelParameters;
    NeModelParameters modelParameters_0;
    NeModelParameters modelParameters_1;
    NeslSimulationData *tmp_1;
    NeslSimulator *tmp;
    NeuDiagnosticManager *diagnosticManager;
    NeuDiagnosticTree *diagnosticTree;
    NeuDiagnosticTree *diagnosticTree_0;
    NeuDiagnosticTree *diagnosticTree_1;
    char *msg;
    char *msg_0;
    char *msg_1;
    real_T tmp_2;
    int32_T tmp_3;
    boolean_T tmp_0;

    /* SetupRuntimeResources for ToWorkspace: '<Root>/SOC_EKF_log' */
    {
      int_T dimensions[1] = { 1 };

      EKFSim_DW.SOC_EKF_log_PWORK.LoggedData = rt_CreateLogVar(
        EKFSim_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(EKFSim_M),
        EKFSim_M->Timing.stepSize0,
        (&rtmGetErrorStatus(EKFSim_M)),
        "SOC_EKF_log",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        0.1,
        1);
      if (EKFSim_DW.SOC_EKF_log_PWORK.LoggedData == (NULL))
        return;
    }

    /* SetupRuntimeResources for ToWorkspace: '<Root>/To Workspace' */
    {
      int_T dimensions[1] = { 1 };

      EKFSim_DW.ToWorkspace_PWORK.LoggedData = rt_CreateLogVar(
        EKFSim_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(EKFSim_M),
        EKFSim_M->Timing.stepSize0,
        (&rtmGetErrorStatus(EKFSim_M)),
        "SOC_Real_log",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        0.1,
        1);
      if (EKFSim_DW.ToWorkspace_PWORK.LoggedData == (NULL))
        return;
    }

    /* SetupRuntimeResources for ToWorkspace: '<Root>/To Workspace2' */
    {
      int_T dimensions[1] = { 1 };

      EKFSim_DW.ToWorkspace2_PWORK.LoggedData = rt_CreateLogVar(
        EKFSim_M->rtwLogInfo,
        0.0,
        rtmGetTFinal(EKFSim_M),
        EKFSim_M->Timing.stepSize0,
        (&rtmGetErrorStatus(EKFSim_M)),
        "SOC_AH_log",
        SS_DOUBLE,
        0,
        0,
        0,
        1,
        1,
        dimensions,
        NO_LOGVALDIMS,
        (NULL),
        (NULL),
        0,
        1,
        0.1,
        1);
      if (EKFSim_DW.ToWorkspace2_PWORK.LoggedData == (NULL))
        return;
    }

    /* Start for SimscapeExecutionBlock: '<S21>/STATE_1' */
    tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 0,
      0);
    EKFSim_DW.STATE_1_Simulator = (void *)tmp;
    tmp_0 = pointer_is_null(EKFSim_DW.STATE_1_Simulator);
    if (tmp_0) {
      EKFSim_3bb8072c_1_gateway();
      tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 0,
        0);
      EKFSim_DW.STATE_1_Simulator = (void *)tmp;
    }

    tmp_1 = nesl_create_simulation_data();
    EKFSim_DW.STATE_1_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    EKFSim_DW.STATE_1_DiagMgr = (void *)diagnosticManager;
    modelParameters.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters.mSolverTolerance = 0.001;
    modelParameters.mSolverAbsTol = 0.001;
    modelParameters.mSolverRelTol = 0.001;
    modelParameters.mVariableStepSolver = false;
    modelParameters.mIsUsingODEN = false;
    modelParameters.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters.mFixedStepSize = 0.001;
    modelParameters.mStartTime = 0.0;
    modelParameters.mLoadInitialState = false;
    modelParameters.mUseSimState = false;
    modelParameters.mLinTrimCompile = false;
    modelParameters.mLoggingMode = SSC_LOGGING_OFF;
    modelParameters.mRTWModifiedTimeStamp = 7.07401041E+8;
    modelParameters.mZcDisabled = true;
    modelParameters.mUseModelRefSolver = false;
    modelParameters.mTargetFPGAHIL = false;
    tmp_2 = 0.001;
    modelParameters.mSolverTolerance = tmp_2;
    tmp_2 = 0.1;
    modelParameters.mFixedStepSize = tmp_2;
    tmp_0 = false;
    modelParameters.mVariableStepSolver = tmp_0;
    tmp_0 = false;
    modelParameters.mIsUsingODEN = tmp_0;
    modelParameters.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.STATE_1_DiagMgr;
    diagnosticTree = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)
      EKFSim_DW.STATE_1_Simulator, &modelParameters, diagnosticManager);
    if (tmp_3 != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_0) {
        msg = rtw_diagnostics_msg(diagnosticTree);
        rtmSetErrorStatus(EKFSim_M, msg);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S21>/STATE_1' */

    /* Start for SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */
    tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 1,
      1);
    EKFSim_DW.OUTPUT_1_1_Simulator = (void *)tmp;
    tmp_0 = pointer_is_null(EKFSim_DW.OUTPUT_1_1_Simulator);
    if (tmp_0) {
      EKFSim_3bb8072c_1_gateway();
      tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 1,
        1);
      EKFSim_DW.OUTPUT_1_1_Simulator = (void *)tmp;
    }

    tmp_1 = nesl_create_simulation_data();
    EKFSim_DW.OUTPUT_1_1_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    EKFSim_DW.OUTPUT_1_1_DiagMgr = (void *)diagnosticManager;
    modelParameters_0.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_0.mSolverTolerance = 0.001;
    modelParameters_0.mSolverAbsTol = 0.001;
    modelParameters_0.mSolverRelTol = 0.001;
    modelParameters_0.mVariableStepSolver = false;
    modelParameters_0.mIsUsingODEN = false;
    modelParameters_0.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters_0.mFixedStepSize = 0.001;
    modelParameters_0.mStartTime = 0.0;
    modelParameters_0.mLoadInitialState = false;
    modelParameters_0.mUseSimState = false;
    modelParameters_0.mLinTrimCompile = false;
    modelParameters_0.mLoggingMode = SSC_LOGGING_OFF;
    modelParameters_0.mRTWModifiedTimeStamp = 7.07401041E+8;
    modelParameters_0.mZcDisabled = true;
    modelParameters_0.mUseModelRefSolver = false;
    modelParameters_0.mTargetFPGAHIL = false;
    tmp_2 = 0.001;
    modelParameters_0.mSolverTolerance = tmp_2;
    tmp_2 = 0.1;
    modelParameters_0.mFixedStepSize = tmp_2;
    tmp_0 = false;
    modelParameters_0.mVariableStepSolver = tmp_0;
    tmp_0 = false;
    modelParameters_0.mIsUsingODEN = tmp_0;
    modelParameters_0.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.OUTPUT_1_1_DiagMgr;
    diagnosticTree_0 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)
      EKFSim_DW.OUTPUT_1_1_Simulator, &modelParameters_0, diagnosticManager);
    if (tmp_3 != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_0) {
        msg_0 = rtw_diagnostics_msg(diagnosticTree_0);
        rtmSetErrorStatus(EKFSim_M, msg_0);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */

    /* Start for SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
    tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 1,
      0);
    EKFSim_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    tmp_0 = pointer_is_null(EKFSim_DW.OUTPUT_1_0_Simulator);
    if (tmp_0) {
      EKFSim_3bb8072c_1_gateway();
      tmp = nesl_lease_simulator("EKFSim/Thevenin ECM/Solver Configuration_1", 1,
        0);
      EKFSim_DW.OUTPUT_1_0_Simulator = (void *)tmp;
    }

    tmp_1 = nesl_create_simulation_data();
    EKFSim_DW.OUTPUT_1_0_SimData = (void *)tmp_1;
    diagnosticManager = rtw_create_diagnostics();
    EKFSim_DW.OUTPUT_1_0_DiagMgr = (void *)diagnosticManager;
    modelParameters_1.mSolverType = NE_SOLVER_TYPE_DAE;
    modelParameters_1.mSolverTolerance = 0.001;
    modelParameters_1.mSolverAbsTol = 0.001;
    modelParameters_1.mSolverRelTol = 0.001;
    modelParameters_1.mVariableStepSolver = false;
    modelParameters_1.mIsUsingODEN = false;
    modelParameters_1.mSolverModifyAbsTol = NE_MODIFY_ABS_TOL_NO;
    modelParameters_1.mFixedStepSize = 0.001;
    modelParameters_1.mStartTime = 0.0;
    modelParameters_1.mLoadInitialState = false;
    modelParameters_1.mUseSimState = false;
    modelParameters_1.mLinTrimCompile = false;
    modelParameters_1.mLoggingMode = SSC_LOGGING_OFF;
    modelParameters_1.mRTWModifiedTimeStamp = 7.07401041E+8;
    modelParameters_1.mZcDisabled = true;
    modelParameters_1.mUseModelRefSolver = false;
    modelParameters_1.mTargetFPGAHIL = false;
    tmp_2 = 0.001;
    modelParameters_1.mSolverTolerance = tmp_2;
    tmp_2 = 0.1;
    modelParameters_1.mFixedStepSize = tmp_2;
    tmp_0 = false;
    modelParameters_1.mVariableStepSolver = tmp_0;
    tmp_0 = false;
    modelParameters_1.mIsUsingODEN = tmp_0;
    modelParameters_1.mZcDisabled = true;
    diagnosticManager = (NeuDiagnosticManager *)EKFSim_DW.OUTPUT_1_0_DiagMgr;
    diagnosticTree_1 = neu_diagnostic_manager_get_initial_tree(diagnosticManager);
    tmp_3 = nesl_initialize_simulator((NeslSimulator *)
      EKFSim_DW.OUTPUT_1_0_Simulator, &modelParameters_1, diagnosticManager);
    if (tmp_3 != 0) {
      tmp_0 = error_buffer_is_empty(rtmGetErrorStatus(EKFSim_M));
      if (tmp_0) {
        msg_1 = rtw_diagnostics_msg(diagnosticTree_1);
        rtmSetErrorStatus(EKFSim_M, msg_1);
      }
    }

    /* End of Start for SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
  }

  {
    int_T tmp_1;
    int_T tmp_2;
    int_T tmp_3;
    int_T tmp_4;
    int_T tmp_5;
    int_T tmp_6;
    boolean_T tmp;
    boolean_T tmp_0;

    /* InitializeConditions for UnitDelay: '<Root>/Unit Delay' */
    EKFSim_DW.UnitDelay_DSTATE = EKFSim_P.UnitDelay_InitialCondition;

    /* InitializeConditions for Memory: '<Root>/SOC_upd' */
    EKFSim_DW.SOC_upd_PreviousInput = EKFSim_P.SOC_upd_InitialCondition;

    /* InitializeConditions for Memory: '<Root>/Up_pre' */
    EKFSim_DW.Up_pre_PreviousInput = EKFSim_P.Up_pre_InitialCondition;

    /* InitializeConditions for SimscapeExecutionBlock: '<S21>/STATE_1' */
    tmp = false;
    tmp_0 = false;
    if (tmp_0 || tmp) {
      tmp_1 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "daessc");
      tmp_2 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "ode14x");
      tmp_3 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "ode15s");
      tmp_4 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "ode1be");
      tmp_5 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "ode23t");
      tmp_6 = strcmp(rtsiGetSolverName(&EKFSim_M->solverInfo), "odeN");
      if ((boolean_T)((tmp_1 != 0) & (tmp_2 != 0) & (tmp_3 != 0) & (tmp_4 != 0)
                      & (tmp_5 != 0) & (tmp_6 != 0))) {
        rtmSetErrorStatus(EKFSim_M,
                          "Detected inconsistent solvers in the model reference hierarchy. Model built with ode14x requires one of {daessc, ode14x, ode15s, ode1be, ode23t, odeN} solvers to run. Use one of the required solvers in the top model.");
      }
    }

    /* End of InitializeConditions for SimscapeExecutionBlock: '<S21>/STATE_1' */

    /* InitializeConditions for Memory: '<Root>/P_upd' */
    EKFSim_DW.P_upd_PreviousInput[0] = EKFSim_P.P_upd_InitialCondition[0];
    EKFSim_DW.P_upd_PreviousInput[1] = EKFSim_P.P_upd_InitialCondition[1];
    EKFSim_DW.P_upd_PreviousInput[2] = EKFSim_P.P_upd_InitialCondition[2];
    EKFSim_DW.P_upd_PreviousInput[3] = EKFSim_P.P_upd_InitialCondition[3];

    /* InitializeConditions for UnitDelay: '<S5>/Unit Delay' */
    EKFSim_DW.UnitDelay_DSTATE_c = EKFSim_P.UnitDelay_InitialCondition_j;

    /* InitializeConditions for Integrator: '<S4>/Integrator' */
    EKFSim_X.Integrator_CSTATE = EKFSim_P.Integrator_IC;

    /* InitializeConditions for UnitDelay: '<S1>/Unit Delay' */
    EKFSim_DW.UnitDelay_DSTATE_m = EKFSim_P.UnitDelay_InitialCondition_h;

    /* InitializeConditions for Memory: '<Root>/SOC_upd1' */
    EKFSim_DW.SOC_upd1_PreviousInput = EKFSim_P.SOC_upd1_InitialCondition;

    /* Root-level InitSystemMatrices */
    {
      static int_T modelMassMatrixIr[2] = { 0, 1 };

      static int_T modelMassMatrixJc[3] = { 0, 1, 2 };

      static real_T modelMassMatrixPr[2] = { 1.0, 1.0 };

      (void) memcpy(EKFSim_MassMatrix.ir, modelMassMatrixIr,
                    2*sizeof(int_T));
      (void) memcpy(EKFSim_MassMatrix.jc, modelMassMatrixJc,
                    3*sizeof(int_T));
      (void) memcpy(EKFSim_MassMatrix.pr, modelMassMatrixPr,
                    2*sizeof(real_T));
    }
  }
}

/* Model terminate function */
void EKFSim_terminate(void)
{
  /* Terminate for SimscapeExecutionBlock: '<S21>/STATE_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    EKFSim_DW.STATE_1_DiagMgr);
  nesl_destroy_simulation_data((NeslSimulationData *)EKFSim_DW.STATE_1_SimData);
  nesl_erase_simulator("EKFSim/Thevenin ECM/Solver Configuration_1");
  nesl_destroy_registry();

  /* Terminate for SimscapeExecutionBlock: '<S21>/OUTPUT_1_1' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    EKFSim_DW.OUTPUT_1_1_DiagMgr);
  nesl_destroy_simulation_data((NeslSimulationData *)
    EKFSim_DW.OUTPUT_1_1_SimData);
  nesl_erase_simulator("EKFSim/Thevenin ECM/Solver Configuration_1");
  nesl_destroy_registry();

  /* Terminate for SimscapeExecutionBlock: '<S21>/OUTPUT_1_0' */
  neu_destroy_diagnostic_manager((NeuDiagnosticManager *)
    EKFSim_DW.OUTPUT_1_0_DiagMgr);
  nesl_destroy_simulation_data((NeslSimulationData *)
    EKFSim_DW.OUTPUT_1_0_SimData);
  nesl_erase_simulator("EKFSim/Thevenin ECM/Solver Configuration_1");
  nesl_destroy_registry();
}
