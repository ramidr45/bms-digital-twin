/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'EKFSim/Thevenin ECM/Solver Configuration'.
 */

#include "ne_ds.h"
#include "EKFSim_3bb8072c_49_ds_sys_struct.h"
#include "EKFSim_3bb8072c_49_ds_log.h"
#include "EKFSim_3bb8072c_49_ds.h"
#include "EKFSim_3bb8072c_49_ds_externals.h"
#include "EKFSim_3bb8072c_49_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T EKFSim_3bb8072c_49_ds_log(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t7, NeDsMethodOutput *out)
{
  real_T Thevenin_ECM_Up_p_v;
  real_T t3;
  Thevenin_ECM_Up_p_v = -(t7->mX.mX[0ULL] - t7->mU.mX[0ULL]);
  t3 = -(t7->mU.mX[1ULL] - Thevenin_ECM_Up_p_v);
  out->mLOG.mX[3ULL] = -t3;
  out->mLOG.mX[27ULL] = -(t7->mX.mX[0ULL] * t7->mU.mX[3ULL]);
  out->mLOG.mX[0ULL] = t3;
  out->mLOG.mX[1ULL] = t7->mU.mX[3ULL];
  out->mLOG.mX[2ULL] = t7->mU.mX[3ULL];
  out->mLOG.mX[4ULL] = t7->mU.mX[3ULL];
  out->mLOG.mX[5ULL] = t7->mU.mX[0ULL];
  out->mLOG.mX[6ULL] = t7->mU.mX[0ULL];
  out->mLOG.mX[7ULL] = t7->mU.mX[0ULL];
  out->mLOG.mX[8ULL] = -t7->mU.mX[3ULL];
  out->mLOG.mX[9ULL] = -t7->mU.mX[3ULL];
  out->mLOG.mX[10ULL] = t3;
  out->mLOG.mX[11ULL] = t3;
  out->mLOG.mX[12ULL] = -t7->mU.mX[3ULL];
  out->mLOG.mX[13ULL] = t7->mU.mX[0ULL];
  out->mLOG.mX[14ULL] = t7->mU.mX[1ULL];
  out->mLOG.mX[15ULL] = t7->mU.mX[2ULL];
  out->mLOG.mX[16ULL] = t7->mU.mX[3ULL];
  out->mLOG.mX[17ULL] = -t7->mU.mX[3ULL];
  out->mLOG.mX[18ULL] = t3;
  out->mLOG.mX[19ULL] = Thevenin_ECM_Up_p_v;
  out->mLOG.mX[20ULL] = t7->mU.mX[1ULL];
  out->mLOG.mX[21ULL] = t7->mU.mX[1ULL];
  out->mLOG.mX[22ULL] = t7->mU.mX[2ULL];
  out->mLOG.mX[23ULL] = -t7->mU.mX[3ULL];
  out->mLOG.mX[24ULL] = Thevenin_ECM_Up_p_v;
  out->mLOG.mX[25ULL] = t7->mU.mX[0ULL];
  out->mLOG.mX[26ULL] = t7->mX.mX[0ULL];
  out->mLOG.mX[28ULL] = t3;
  out->mLOG.mX[29ULL] = t3;
  out->mLOG.mX[30ULL] = t3;
  (void)sys;
  (void)out;
  return 0;
}
