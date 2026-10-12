/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'EKFSim/Thevenin ECM/Solver Configuration'.
 */

#include "ne_ds.h"
#include "EKFSim_3bb8072c_49_ds_sys_struct.h"
#include "EKFSim_3bb8072c_49_ds_obs_all.h"
#include "EKFSim_3bb8072c_49_ds.h"
#include "EKFSim_3bb8072c_49_ds_externals.h"
#include "EKFSim_3bb8072c_49_ds_external_struct.h"
#include "ssc_ml_fun.h"

int32_T EKFSim_3bb8072c_49_ds_obs_all(const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t7, NeDsMethodOutput *out)
{
  real_T Thevenin_ECM_Up_p_v;
  real_T t3;
  Thevenin_ECM_Up_p_v = -(t7->mX.mX[0ULL] - t7->mU.mX[0ULL]);
  t3 = -(t7->mU.mX[1ULL] - Thevenin_ECM_Up_p_v);
  out->mOBS_ALL.mX[4ULL] = -t3;
  out->mOBS_ALL.mX[0ULL] = t3;
  out->mOBS_ALL.mX[1ULL] = t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[2ULL] = t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[3ULL] = 0.0;
  out->mOBS_ALL.mX[5ULL] = t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[6ULL] = 0.0;
  out->mOBS_ALL.mX[7ULL] = t7->mU.mX[0ULL];
  out->mOBS_ALL.mX[8ULL] = t7->mU.mX[0ULL];
  out->mOBS_ALL.mX[9ULL] = t7->mU.mX[0ULL];
  out->mOBS_ALL.mX[10ULL] = -t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[11ULL] = -t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[12ULL] = t3;
  out->mOBS_ALL.mX[13ULL] = t3;
  out->mOBS_ALL.mX[14ULL] = -t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[15ULL] = 0.0;
  out->mOBS_ALL.mX[16ULL] = t7->mU.mX[0ULL];
  out->mOBS_ALL.mX[17ULL] = t7->mU.mX[1ULL];
  out->mOBS_ALL.mX[18ULL] = t7->mU.mX[2ULL];
  out->mOBS_ALL.mX[19ULL] = t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[20ULL] = -t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[21ULL] = t3;
  out->mOBS_ALL.mX[22ULL] = Thevenin_ECM_Up_p_v;
  out->mOBS_ALL.mX[23ULL] = t7->mU.mX[1ULL];
  out->mOBS_ALL.mX[24ULL] = t7->mU.mX[1ULL];
  out->mOBS_ALL.mX[25ULL] = 0.0;
  out->mOBS_ALL.mX[26ULL] = t7->mU.mX[2ULL];
  out->mOBS_ALL.mX[27ULL] = 0.0;
  out->mOBS_ALL.mX[28ULL] = -t7->mU.mX[3ULL];
  out->mOBS_ALL.mX[29ULL] = Thevenin_ECM_Up_p_v;
  out->mOBS_ALL.mX[30ULL] = t7->mU.mX[0ULL];
  out->mOBS_ALL.mX[31ULL] = t7->mX.mX[0ULL];
  out->mOBS_ALL.mX[32ULL] = t3;
  out->mOBS_ALL.mX[33ULL] = 0.0;
  out->mOBS_ALL.mX[34ULL] = t3;
  out->mOBS_ALL.mX[35ULL] = t3;
  (void)sys;
  (void)out;
  return 0;
}
