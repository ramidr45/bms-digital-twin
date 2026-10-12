/*
 * EKFSim_private.h
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

#ifndef EKFSim_private_h_
#define EKFSim_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "EKFSim_types.h"
#include "EKFSim.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"

/* Private macros used by the generated code to access rtModel */
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTFinal
#define rtmSetTFinal(rtm, val)         ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

extern real_T look1_binlcpw(real_T u0, const real_T bp0[], const real_T table[],
  uint32_T maxIndex);

/* private model entry point functions */
extern void EKFSim_derivatives(void);
extern void EKFSim_forcingfunction(void);
extern void EKFSim_massmatrix(void);

#endif                                 /* EKFSim_private_h_ */
