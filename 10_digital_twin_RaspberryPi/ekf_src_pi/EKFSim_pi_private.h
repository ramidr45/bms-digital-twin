/*
 * EKFSim_pi_private.h
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

#ifndef EKFSim_pi_private_h_
#define EKFSim_pi_private_h_
#include "rtwtypes.h"
#include "multiword_types.h"
#include "EKFSim_pi_types.h"
#include "EKFSim_pi.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);

/* private model entry point functions */
extern void EKFSim_pi_derivatives(void);

#endif                                 /* EKFSim_pi_private_h_ */
