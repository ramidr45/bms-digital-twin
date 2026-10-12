/* Simscape target specific file.
 * This file is generated for the Simscape network associated with the solver block 'EKFSim/Thevenin ECM/Solver Configuration'.
 */
/* EKFSim_3bb8072c_49_ds.c - body for module EKFSim_3bb8072c_49_ds */

#include "ne_ds.h"
#include "EKFSim_3bb8072c_49_ds_log.h"
#include "EKFSim_3bb8072c_49_ds_obs_act.h"
#include "EKFSim_3bb8072c_49_ds_obs_il.h"
#include "EKFSim_3bb8072c_49_ds_obs_all.h"
#include "EKFSim_3bb8072c_49_ds_obs_exp.h"
#include "EKFSim_3bb8072c_49_ds.h"
#include "ssc_ml_fun.h"
#include "EKFSim_3bb8072c_49_ds_external_struct.h"
#include "EKFSim_3bb8072c_49_ds_externals.h"
#include "EKFSim_3bb8072c_49_ds_sys_struct.h"

static int32_T ds_mcon_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_mcon(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_mpar_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_mpar(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_mnl_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_mnl(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_vmm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dxm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_ddm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dum_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dum(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dtm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dtm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dpm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dpm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_acon_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_acon(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_apar_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_apar(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_bcon_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_bcon(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_bpar_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_bpar(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_ccon_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ccon(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_cpar_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_cpar(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_f(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                    NeDsMethodOutput *out);
static int32_T ds_vdf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_vmf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_vpf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_vsf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_slf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_slf0(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dxf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_duf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_duf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dtf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dtf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_ddf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dpdxf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_dpdxf(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dwf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dwf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_tduf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_tdxf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dnf_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dnf(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dnf_v_x(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_cer(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dxcer(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxcer_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_ddcer(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddcer_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_ic(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_icr(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_icr_im(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_icr_id(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_icr_il(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxicr(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxicr_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_ddicr(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddicr_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_tduicr_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_icrm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_icrm(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dxicrm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxicrm(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddicrm_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_ddicrm(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_freqs(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_solverhits(const NeDynamicSystem *ds, const
  NeDynamicSystemInput *in, NeDsMethodOutput *out);
static int32_T ds_mduy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_mdxy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_tduy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_tdxy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_y(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                    NeDsMethodOutput *out);
static int32_T ds_dxy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxy(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_duy_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_duy(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_dty_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dty(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_mode(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_zc(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_cache_r(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_cache_i(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_update_r(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_update_i(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_update2_r(const NeDynamicSystem *ds, const
  NeDynamicSystemInput *in, NeDsMethodOutput *out);
static int32_T ds_update2_i(const NeDynamicSystem *ds, const
  NeDynamicSystemInput *in, NeDsMethodOutput *out);
static int32_T ds_lock_r(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_lock_i(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_lock2_r(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_lock2_i(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_sfo(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_sfp(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_init_r(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_init_i(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_assert(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_passert(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_iassert(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_del_t(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_del_v(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_del_v0(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_del_tmax(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxdelt_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dxdelt(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dudelt_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dudelt(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dtdelt_p(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dtdelt(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dp_l(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dp_i(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dp_j(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dp_r(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_qx(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_qu(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_qt(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_q1(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_qx_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_qu_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_qt_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_q1_p(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_var_tol(const NeDynamicSystem *ds, const NeDynamicSystemInput *
  in, NeDsMethodOutput *out);
static int32_T ds_eq_tol(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_lv(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                     NeDsMethodOutput *out);
static int32_T ds_slv(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                      NeDsMethodOutput *out);
static int32_T ds_nldv(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_sclv(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_imin(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_imax(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
  NeDsMethodOutput *out);
static int32_T ds_dimin(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static int32_T ds_dimax(const NeDynamicSystem *ds, const NeDynamicSystemInput
  *in, NeDsMethodOutput *out);
static NeDsMethodOutput *ds_output_mcon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mcon(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mpar(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mnl_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_mnl(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_vmm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dxm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_ddm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_ddm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dum_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dum(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dtm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dtm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dpm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dpm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_acon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_acon(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_apar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_apar(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_bcon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_bcon(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_bpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_bpar(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_ccon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_ccon(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_cpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_cpar(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_f(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_vdf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_vmf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_vpf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_vsf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_slf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_slf0(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dxf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_duf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_duf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dtf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dtf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_ddf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_ddf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dpdxf_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dpdxf(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dwf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dwf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_tduf_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_tdxf_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dnf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dnf(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dnf_v_x(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_cer(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxcer(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dxcer_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_ddcer(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_ddcer_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_ic(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_icr(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_icr_im(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_icr_id(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_icr_il(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxicr(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dxicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_ddicr(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_ddicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_tduicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_icrm_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_icrm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxicrm_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dxicrm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_ddicrm_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_ddicrm(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_freqs(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_solverhits(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_mduy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mdxy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_tduy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_tdxy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_y(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dxy_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dxy(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_duy_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_duy(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dty_p(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dty(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_mode(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_zc(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_cache_r(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_cache_i(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_update_r(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_update_i(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_update2_r(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_update2_i(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_lock_r(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_lock_i(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_lock2_r(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_lock2_i(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_sfo(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_sfp(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_init_r(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_init_i(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_log(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_assert(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_passert(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_iassert(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_del_t(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_del_v(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_del_v0(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_del_tmax(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dxdelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dxdelt(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dudelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dudelt(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dtdelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_dtdelt(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_obs_exp(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_obs_act(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_obs_all(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_obs_il(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dp_l(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dp_i(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dp_j(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dp_r(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qx(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qu(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qt(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_q1(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qx_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qu_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_qt_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_q1_p(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_var_tol(const NeDynamicSystem *ds,
  PmAllocator *allocator);
static NeDsMethodOutput *ds_output_eq_tol(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_lv(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_slv(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_nldv(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_sclv(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_imin(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_imax(const NeDynamicSystem *ds, PmAllocator
  *allocator);
static NeDsMethodOutput *ds_output_dimin(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static NeDsMethodOutput *ds_output_dimax(const NeDynamicSystem *ds, PmAllocator *
  allocator);
static void release_reference(NeDynamicSystem *ds);
static void get_reference(NeDynamicSystem *ds);
static NeDynamicSystem *diagnostics(NeDynamicSystem *ds, boolean_T);
static void expand(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                   PmRealVector *out, boolean_T kp);
static void rtpmap(const NeDynamicSystem * ds, const PmIntVector* inl, const
                   PmIntVector* ini, const PmIntVector* inj, const PmRealVector*
                   inr, PmIntVector* outl, PmIntVector* outi, PmIntVector* outj,
                   PmRealVector* outr);
static NeEquationData s_equation_data[1] = { { "", 0U, 8,
    NE_EQUATION_DOMAIN_TIME, "EKFSim/Thevenin ECM/Variable R0", 3U, 0U, FALSE,
    1.0, "1", } };

static NeCERData *s_cer_data = NULL;
static NeICRData *s_icr_data = NULL;
static NeVariableData s_variable_data[1] = { { "Thevenin_ECM.Variable_R0.v", 0U,
    0, "EKFSim/Thevenin ECM/Variable R0", 1.0, "1", 0.0, FALSE, FALSE, { 1,
      "1x1" }, NE_INIT_MODE_NONE, "Voltage", } };

static NeVariableData *s_discrete_data = NULL;
static NeObservableData s_observable_data[37] = { {
    "Thevenin_ECM.Controlled_Current_Source.head.v",
    "EKFSim/Thevenin ECM/Controlled Current Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Controlled_Current_Source.i",
    "EKFSim/Thevenin ECM/Controlled Current Source", { 1, "1x1" }, "A", 1.0, "A",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "i", }, {
    "Thevenin_ECM.Controlled_Current_Source.iT",
    "EKFSim/Thevenin ECM/Controlled Current Source", { 1, "1x1" }, "A", 1.0, "A",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "iT", }, {
    "Thevenin_ECM.Controlled_Current_Source.tail.v",
    "EKFSim/Thevenin ECM/Controlled Current Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, TRUE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Controlled_Current_Source.v",
    "EKFSim/Thevenin ECM/Controlled Current Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "v", }, {
    "Thevenin_ECM.Controlled_Voltage_Source.i",
    "EKFSim/Thevenin ECM/Controlled Voltage Source", { 1, "1x1" }, "A", 1.0, "A",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "i", }, {
    "Thevenin_ECM.Controlled_Voltage_Source.n.v",
    "EKFSim/Thevenin ECM/Controlled Voltage Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, TRUE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Controlled_Voltage_Source.p.v",
    "EKFSim/Thevenin ECM/Controlled Voltage Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Controlled_Voltage_Source.v",
    "EKFSim/Thevenin ECM/Controlled Voltage Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "v", }, {
    "Thevenin_ECM.Controlled_Voltage_Source.vT",
    "EKFSim/Thevenin ECM/Controlled Voltage Source", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "vT", }, {
    "Thevenin_ECM.Current_Sensor.I", "EKFSim/Thevenin ECM/Current Sensor", { 1,
      "1x1" }, "A", 1.0, "A", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "I", }, {
    "Thevenin_ECM.Current_Sensor.i1", "EKFSim/Thevenin ECM/Current Sensor", { 1,
      "1x1" }, "A", 1.0, "A", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Current", }, {
    "Thevenin_ECM.Current_Sensor.n.v", "EKFSim/Thevenin ECM/Current Sensor", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Current_Sensor.p.v", "EKFSim/Thevenin ECM/Current Sensor", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Current_Sensor_I0",
    "EKFSim/Thevenin ECM/PS-Simulink\nConverter", { 1, "1x1" }, "A", 1.0, "A",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Current_Sensor_I0", }, {
    "Thevenin_ECM.GND.V.v", "EKFSim/Thevenin ECM/GND", { 1, "1x1" }, "V", 1.0,
    "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, TRUE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Simulink_PS_Converter1_output0",
    "EKFSim/Thevenin ECM/Simulink-PS\nConverter1", { 1, "1x1" }, "1", 1.0, "1",
    NE_NOMINAL_SOURCE_FIXED, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Simulink_PS_Converter1_output0", }, {
    "Thevenin_ECM.Simulink_PS_Converter2_output0",
    "EKFSim/Thevenin ECM/Simulink-PS\nConverter2", { 1, "1x1" }, "1", 1.0, "1",
    NE_NOMINAL_SOURCE_FIXED, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Simulink_PS_Converter2_output0", }, {
    "Thevenin_ECM.Simulink_PS_Converter4_output0",
    "EKFSim/Thevenin ECM/Simulink-PS\nConverter4", { 1, "1x1" }, "1", 1.0, "1",
    NE_NOMINAL_SOURCE_FIXED, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Simulink_PS_Converter4_output0", }, {
    "Thevenin_ECM.Simulink_PS_Converter5_output0",
    "EKFSim/Thevenin ECM/Simulink-PS\nConverter5", { 1, "1x1" }, "1", 1.0, "1",
    NE_NOMINAL_SOURCE_FIXED, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Simulink_PS_Converter5_output0", }, {
    "Thevenin_ECM.Up.i", "EKFSim/Thevenin ECM/Up", { 1, "1x1" }, "A", 1.0, "A",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "i", }, { "Thevenin_ECM.Up.n.v",
    "EKFSim/Thevenin ECM/Up", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, { "Thevenin_ECM.Up.p.v",
    "EKFSim/Thevenin ECM/Up", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, { "Thevenin_ECM.Up.v",
    "EKFSim/Thevenin ECM/Up", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "v", }, { "Thevenin_ECM.Up.vT",
    "EKFSim/Thevenin ECM/Up", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "vT", }, { "Thevenin_ECM.Variable_R0.H.T",
    "EKFSim/Thevenin ECM/Variable R0", { 1, "1x1" }, "K", 1.0, "K",
    NE_NOMINAL_SOURCE_DERIVED, NE_INIT_MODE_NONE, TRUE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Temperature", }, {
    "Thevenin_ECM.Variable_R0.R", "EKFSim/Thevenin ECM/Variable R0", { 1, "1x1"
    }, "Ohm", 1.0, "kg*m^2/(C^2*s)", NE_NOMINAL_SOURCE_DERIVED,
    NE_INIT_MODE_NONE, FALSE, FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "R", },
    { "Thevenin_ECM.Variable_R0.T", "EKFSim/Thevenin ECM/Variable R0", { 1,
      "1x1" }, "K", 1.0, "K", NE_NOMINAL_SOURCE_DERIVED, NE_INIT_MODE_NONE, TRUE,
    FALSE, NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Temperature", }, {
    "Thevenin_ECM.Variable_R0.i", "EKFSim/Thevenin ECM/Variable R0", { 1, "1x1"
    }, "A", 1.0, "A", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Current", }, {
    "Thevenin_ECM.Variable_R0.n.v", "EKFSim/Thevenin ECM/Variable R0", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Variable_R0.p.v", "EKFSim/Thevenin ECM/Variable R0", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Variable_R0.v", "EKFSim/Thevenin ECM/Variable R0", { 1, "1x1"
    }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Variable_R0.power_dissipated",
    "EKFSim/Thevenin ECM/Variable R0", { 1, "1x1" }, "A*V", 1.0, "A*V",
    NE_NOMINAL_SOURCE_NONE, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, TRUE, FALSE, "Dissipated power", }, {
    "Thevenin_ECM.Voltage_Sensor.V", "EKFSim/Thevenin ECM/Voltage Sensor", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "V", }, {
    "Thevenin_ECM.Voltage_Sensor.n.v", "EKFSim/Thevenin ECM/Voltage Sensor", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, TRUE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Voltage_Sensor.p.v", "EKFSim/Thevenin ECM/Voltage Sensor", { 1,
      "1x1" }, "V", 1.0, "V", NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE,
    FALSE, NE_FREQTIME_TYPE_TIME, TRUE, TRUE, "Voltage", }, {
    "Thevenin_ECM.Voltage_Sensor_V0",
    "EKFSim/Thevenin ECM/PS-Simulink\nConverter1", { 1, "1x1" }, "V", 1.0, "V",
    NE_NOMINAL_SOURCE_MODEL, NE_INIT_MODE_NONE, FALSE, FALSE,
    NE_FREQTIME_TYPE_TIME, FALSE, TRUE, "Voltage_Sensor_V0", } };

static NeModeData *s_major_mode_data = NULL;
static NeZCData s_zc_data[1] = { { "EKFSim/Thevenin ECM/Variable R0", 1U, 0U,
    "Thevenin_ECM.Variable_R0",
    "foundation.electrical.elements.variable_resistor", NE_ZC_TYPE_FALSE, } };

static NeRange s_range[1] = { {
    "foundation.electrical.elements.variable_resistor", 58U, 8U, 58U, 16U,
    NE_RANGE_TYPE_NORMAL, } };

static NeAssertData *s_assert_data = NULL;
static NeRange *s_assert_range = NULL;
static NeAssertData *s_param_assert_data = NULL;
static NeRange *s_param_assert_range = NULL;
static NeAssertData *s_initial_assert_data = NULL;
static NeRange *s_initial_assert_range = NULL;
static NeRange s_equation_range[3] = { {
    "foundation.electrical.elements.variable_resistor", 58U, 8U, 58U, 16U,
    NE_RANGE_TYPE_NORMAL, }, {
    "foundation.electrical.elements.variable_resistor", 59U, 9U, 59U, 17U,
    NE_RANGE_TYPE_NORMAL, }, {
    "foundation.electrical.elements.variable_resistor", 61U, 9U, 61U, 20U,
    NE_RANGE_TYPE_NORMAL, } };

static NeRange *s_cer_range = NULL;
static NeRange *s_icr_range = NULL;
static NeParameterData *s_logical_parameter_data = NULL;
static NeParameterData *s_integer_parameter_data = NULL;
static NeParameterData *s_index_parameter_data = NULL;
static NeParameterData *s_real_parameter_data = NULL;
static NeDsMethodOutput *ds_output_mcon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMCON_P.mNumCol = 1;
  out->mMCON_P.mNumRow = 1;
  out->mMCON_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mMCON_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_mcon(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMCON.mN = 0;
  out->mMCON.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_mpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMPAR_P.mNumCol = 1;
  out->mMPAR_P.mNumRow = 1;
  out->mMPAR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mMPAR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_mpar(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMPAR.mN = 0;
  out->mMPAR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_mnl_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMNL_P.mNumCol = 1;
  out->mMNL_P.mNumRow = 1;
  out->mMNL_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mMNL_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_mnl(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMNL.mN = 0;
  out->mMNL.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_vmm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVMM.mN = 0;
  out->mVMM.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dxm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXM_P.mNumCol = 1;
  out->mDXM_P.mNumRow = 0;
  out->mDXM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDXM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dxm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXM.mN = 0;
  out->mDXM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDM_P.mNumCol = 0;
  out->mDDM_P.mNumRow = 0;
  out->mDDM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  out->mDDM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_ddm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDM.mN = 0;
  out->mDDM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dum_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUM_P.mNumCol = 4;
  out->mDUM_P.mNumRow = 0;
  out->mDUM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mDUM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dum(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUM.mN = 0;
  out->mDUM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dtm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTM_P.mNumCol = 1;
  out->mDTM_P.mNumRow = 0;
  out->mDTM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDTM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dtm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTM.mN = 0;
  out->mDTM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dpm_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDPM_P.mNumCol = 0;
  out->mDPM_P.mNumRow = 0;
  out->mDPM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  out->mDPM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dpm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDPM.mN = 0;
  out->mDPM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_acon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mACON_P.mNumCol = 1;
  out->mACON_P.mNumRow = 1;
  out->mACON_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mACON_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_acon(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mACON.mN = 0;
  out->mACON.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_apar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mAPAR_P.mNumCol = 1;
  out->mAPAR_P.mNumRow = 1;
  out->mAPAR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mAPAR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_apar(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mAPAR.mN = 0;
  out->mAPAR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_bcon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mBCON_P.mNumCol = 4;
  out->mBCON_P.mNumRow = 1;
  out->mBCON_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mBCON_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_bcon(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mBCON.mN = 0;
  out->mBCON.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_bpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mBPAR_P.mNumCol = 4;
  out->mBPAR_P.mNumRow = 1;
  out->mBPAR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mBPAR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_bpar(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mBPAR.mN = 0;
  out->mBPAR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ccon_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCCON_P.mNumCol = 1;
  out->mCCON_P.mNumRow = 1;
  out->mCCON_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mCCON_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_ccon(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCCON.mN = 0;
  out->mCCON.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_cpar_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCPAR_P.mNumCol = 1;
  out->mCPAR_P.mNumRow = 1;
  out->mCPAR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mCPAR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_cpar(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCPAR.mN = 0;
  out->mCPAR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_f(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mF.mN = 1;
  out->mF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_vdf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVDF.mN = 1;
  out->mVDF.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_vmf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVMF.mN = 1;
  out->mVMF.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_vpf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVPF.mN = 1;
  out->mVPF.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_vsf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVSF.mN = 1;
  out->mVSF.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_slf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSLF.mN = 1;
  out->mSLF.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_slf0(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSLF0.mN = 1;
  out->mSLF0.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_dxf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXF_P.mNumCol = 1;
  out->mDXF_P.mNumRow = 1;
  out->mDXF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDXF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_dxf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXF.mN = 1;
  out->mDXF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_duf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUF_P.mNumCol = 4;
  out->mDUF_P.mNumRow = 1;
  out->mDUF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mDUF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  return out;
}

static NeDsMethodOutput *ds_output_duf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUF.mN = 2;
  out->mDUF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 2);
  return out;
}

static NeDsMethodOutput *ds_output_dtf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTF_P.mNumCol = 1;
  out->mDTF_P.mNumRow = 1;
  out->mDTF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDTF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dtf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTF.mN = 0;
  out->mDTF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDF_P.mNumCol = 0;
  out->mDDF_P.mNumRow = 1;
  out->mDDF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  out->mDDF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_ddf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDF.mN = 0;
  out->mDDF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dpdxf_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDPDXF_P.mNumCol = 0;
  out->mDPDXF_P.mNumRow = 1;
  out->mDPDXF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 1);
  out->mDPDXF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dpdxf(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDPDXF.mN = 0;
  out->mDPDXF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dwf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDWF_P.mNumCol = 0;
  out->mDWF_P.mNumRow = 1;
  out->mDWF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  out->mDWF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dwf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDWF.mN = 0;
  out->mDWF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_tduf_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mTDUF_P.mNumCol = 4;
  out->mTDUF_P.mNumRow = 1;
  out->mTDUF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mTDUF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  return out;
}

static NeDsMethodOutput *ds_output_tdxf_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mTDXF_P.mNumCol = 1;
  out->mTDXF_P.mNumRow = 1;
  out->mTDXF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mTDXF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_dnf_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDNF_P.mNumCol = 1;
  out->mDNF_P.mNumRow = 1;
  out->mDNF_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDNF_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dnf(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDNF.mN = 0;
  out->mDNF.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dnf_v_x(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDNF_V_X.mN = 1;
  out->mDNF_V_X.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_cer(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCER.mN = 0;
  out->mCER.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxcer(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXCER.mN = 0;
  out->mDXCER.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxcer_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXCER_P.mNumCol = 1;
  out->mDXCER_P.mNumRow = 0;
  out->mDXCER_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 2);
  out->mDXCER_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddcer(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDCER.mN = 0;
  out->mDDCER.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddcer_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDCER_P.mNumCol = 0;
  out->mDDCER_P.mNumRow = 0;
  out->mDDCER_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 1);
  out->mDDCER_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ic(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mIC.mN = 1;
  out->mIC.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_icr(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICR.mN = 0;
  out->mICR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_icr_im(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICR_IM.mN = 0;
  out->mICR_IM.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_icr_id(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICR_ID.mN = 0;
  out->mICR_ID.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_icr_il(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICR_IL.mN = 0;
  out->mICR_IL.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxicr(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXICR.mN = 0;
  out->mDXICR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXICR_P.mNumCol = 1;
  out->mDXICR_P.mNumRow = 0;
  out->mDXICR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 2);
  out->mDXICR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddicr(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDICR.mN = 0;
  out->mDDICR.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDICR_P.mNumCol = 0;
  out->mDDICR_P.mNumRow = 0;
  out->mDDICR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 1);
  out->mDDICR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_tduicr_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mTDUICR_P.mNumCol = 4;
  out->mTDUICR_P.mNumRow = 0;
  out->mTDUICR_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 5);
  out->mTDUICR_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_icrm_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICRM_P.mNumCol = 1;
  out->mICRM_P.mNumRow = 0;
  out->mICRM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mICRM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_icrm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mICRM.mN = 0;
  out->mICRM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxicrm_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXICRM_P.mNumCol = 1;
  out->mDXICRM_P.mNumRow = 0;
  out->mDXICRM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 2);
  out->mDXICRM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxicrm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXICRM.mN = 0;
  out->mDXICRM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_ddicrm_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDICRM_P.mNumCol = 0;
  out->mDDICRM_P.mNumRow = 0;
  out->mDDICRM_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 1);
  out->mDDICRM_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_ddicrm(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDDICRM.mN = 0;
  out->mDDICRM.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_freqs(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mFREQS.mN = 0;
  out->mFREQS.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_solverhits(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSOLVERHITS.mN = 0;
  out->mSOLVERHITS.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof
    (real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_mduy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMDUY_P.mNumCol = 4;
  out->mMDUY_P.mNumRow = 2;
  out->mMDUY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mMDUY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_mdxy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMDXY_P.mNumCol = 1;
  out->mMDXY_P.mNumRow = 2;
  out->mMDXY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mMDXY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_tduy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mTDUY_P.mNumCol = 4;
  out->mTDUY_P.mNumRow = 2;
  out->mTDUY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mTDUY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    3);
  return out;
}

static NeDsMethodOutput *ds_output_tdxy_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mTDXY_P.mNumCol = 1;
  out->mTDXY_P.mNumRow = 2;
  out->mTDXY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mTDXY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_y(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mY.mN = 2;
  out->mY.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 2);
  return out;
}

static NeDsMethodOutput *ds_output_dxy_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXY_P.mNumCol = 1;
  out->mDXY_P.mNumRow = 2;
  out->mDXY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDXY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_dxy(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXY.mN = 1;
  out->mDXY.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_duy_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUY_P.mNumCol = 4;
  out->mDUY_P.mNumRow = 2;
  out->mDUY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mDUY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    3);
  return out;
}

static NeDsMethodOutput *ds_output_duy(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUY.mN = 3;
  out->mDUY.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 3);
  return out;
}

static NeDsMethodOutput *ds_output_dty_p(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTY_P.mNumCol = 1;
  out->mDTY_P.mNumRow = 2;
  out->mDTY_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mDTY_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dty(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTY.mN = 0;
  out->mDTY.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_mode(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mMODE.mN = 1;
  out->mMODE.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_zc(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mZC.mN = 1;
  out->mZC.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_cache_r(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCACHE_R.mN = 0;
  out->mCACHE_R.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_cache_i(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mCACHE_I.mN = 0;
  out->mCACHE_I.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_update_r(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mUPDATE_R.mN = 0;
  out->mUPDATE_R.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_update_i(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mUPDATE_I.mN = 0;
  out->mUPDATE_I.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_update2_r(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mUPDATE2_R.mN = 0;
  out->mUPDATE2_R.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_update2_i(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mUPDATE2_I.mN = 0;
  out->mUPDATE2_I.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_lock_r(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLOCK_R.mN = 0;
  out->mLOCK_R.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_lock_i(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLOCK_I.mN = 0;
  out->mLOCK_I.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_lock2_r(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLOCK2_R.mN = 0;
  out->mLOCK2_R.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_lock2_i(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLOCK2_I.mN = 0;
  out->mLOCK2_I.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_sfo(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSFO.mN = 0;
  out->mSFO.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_sfp(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSFP.mN = 0;
  out->mSFP.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_init_r(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mINIT_R.mN = 0;
  out->mINIT_R.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_init_i(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mINIT_I.mN = 0;
  out->mINIT_I.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_log(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLOG.mN = 31;
  out->mLOG.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 31);
  return out;
}

static NeDsMethodOutput *ds_output_assert(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mASSERT.mN = 0;
  out->mASSERT.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_passert(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mPASSERT.mN = 0;
  out->mPASSERT.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_iassert(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mIASSERT.mN = 0;
  out->mIASSERT.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_del_t(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDEL_T.mN = 0;
  out->mDEL_T.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_del_v(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDEL_V.mN = 0;
  out->mDEL_V.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_del_v0(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDEL_V0.mN = 0;
  out->mDEL_V0.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_del_tmax(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDEL_TMAX.mN = 0;
  out->mDEL_TMAX.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dxdelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXDELT_P.mNumCol = 1;
  out->mDXDELT_P.mNumRow = 0;
  out->mDXDELT_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 2);
  out->mDXDELT_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dxdelt(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDXDELT.mN = 0;
  out->mDXDELT.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dudelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUDELT_P.mNumCol = 4;
  out->mDUDELT_P.mNumRow = 0;
  out->mDUDELT_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 5);
  out->mDUDELT_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dudelt(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDUDELT.mN = 0;
  out->mDUDELT.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dtdelt_p(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTDELT_P.mNumCol = 1;
  out->mDTDELT_P.mNumRow = 0;
  out->mDTDELT_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 2);
  out->mDTDELT_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof
    (int32_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dtdelt(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDTDELT.mN = 0;
  out->mDTDELT.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_obs_exp(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mOBS_EXP.mN = 36;
  out->mOBS_EXP.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    36);
  return out;
}

static NeDsMethodOutput *ds_output_obs_act(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mOBS_ACT.mN = 36;
  out->mOBS_ACT.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    36);
  return out;
}

static NeDsMethodOutput *ds_output_obs_all(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mOBS_ALL.mN = 36;
  out->mOBS_ALL.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    36);
  return out;
}

static NeDsMethodOutput *ds_output_obs_il(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mOBS_IL.mN = 36;
  out->mOBS_IL.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 36);
  return out;
}

static NeDsMethodOutput *ds_output_dp_l(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDP_L.mN = 0;
  out->mDP_L.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dp_i(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDP_I.mN = 0;
  out->mDP_I.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dp_j(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDP_J.mN = 0;
  out->mDP_J.mX = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_dp_r(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDP_R.mN = 0;
  out->mDP_R.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_qx(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQX.mN = 0;
  out->mQX.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_qu(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQU.mN = 0;
  out->mQU.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_qt(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQT.mN = 0;
  out->mQT.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_q1(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQ1.mN = 0;
  out->mQ1.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_qx_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQX_P.mNumCol = 1;
  out->mQX_P.mNumRow = 1;
  out->mQX_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mQX_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_qu_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQU_P.mNumCol = 4;
  out->mQU_P.mNumRow = 1;
  out->mQU_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    5);
  out->mQU_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_qt_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQT_P.mNumCol = 1;
  out->mQT_P.mNumRow = 1;
  out->mQT_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mQT_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_q1_p(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mQ1_P.mNumCol = 1;
  out->mQ1_P.mNumRow = 1;
  out->mQ1_P.mJc = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    2);
  out->mQ1_P.mIr = (int32_T *) allocator->mCallocFcn(allocator, sizeof(int32_T),
    0);
  return out;
}

static NeDsMethodOutput *ds_output_var_tol(const NeDynamicSystem *ds,
  PmAllocator *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mVAR_TOL.mN = 1;
  out->mVAR_TOL.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_eq_tol(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mEQ_TOL.mN = 1;
  out->mEQ_TOL.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_lv(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mLV.mN = 1;
  out->mLV.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_slv(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSLV.mN = 1;
  out->mSLV.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof(boolean_T),
    1);
  return out;
}

static NeDsMethodOutput *ds_output_nldv(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mNLDV.mN = 1;
  out->mNLDV.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_sclv(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mSCLV.mN = 1;
  out->mSCLV.mX = (boolean_T *) allocator->mCallocFcn(allocator, sizeof
    (boolean_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_imin(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mIMIN.mN = 1;
  out->mIMIN.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_imax(const NeDynamicSystem *ds, PmAllocator
  *allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mIMAX.mN = 1;
  out->mIMAX.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 1);
  return out;
}

static NeDsMethodOutput *ds_output_dimin(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDIMIN.mN = 0;
  out->mDIMIN.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static NeDsMethodOutput *ds_output_dimax(const NeDynamicSystem *ds, PmAllocator *
  allocator)
{
  NeDsMethodOutput *out;
  (void)ds;
  out = (NeDsMethodOutput *) allocator->mCallocFcn(allocator, sizeof
    (NeDsMethodOutput), 1);
  out->mDIMAX.mN = 0;
  out->mDIMAX.mX = (real_T *) allocator->mCallocFcn(allocator, sizeof(real_T), 0);
  return out;
}

static void release_reference(NeDynamicSystem *ds)
{
  _NeDynamicSystem *_ds;
  _ds = (_NeDynamicSystem *)ds;
  if (--_ds->mRefCnt == 0) {
    _ds->mAlloc.mFreeFcn(&_ds->mAlloc, _ds);
  }
}

static void get_reference(NeDynamicSystem *ds)
{
  _NeDynamicSystem *_ds;
  _ds = (_NeDynamicSystem *)ds;
  ++_ds->mRefCnt;
}

static NeDynamicSystem *diagnostics(NeDynamicSystem *ds, boolean_T kp)
{
  _NeDynamicSystem *_ds = (_NeDynamicSystem *)ds;
  (void) kp;
  ne_ds_get_reference(&_ds->mBase);
  return &_ds->mBase;
}

static void expand(const NeDynamicSystem *ds, const NeDynamicSystemInput *in,
                   PmRealVector *out, boolean_T kp)
{
  (void)ds;
  (void)kp;
  memcpy(out->mX, in->mX.mX, sizeof(real_T)*out->mN);
}

static void rtpmap(const NeDynamicSystem * ds, const PmIntVector* inl, const
                   PmIntVector* ini, const PmIntVector* inj, const PmRealVector*
                   inr, PmIntVector* outl, PmIntVector* outi, PmIntVector* outj,
                   PmRealVector* outr)
{
  (void)ds;
  memcpy(outl->mX, inl->mX, sizeof(int32_T)*inl->mN);
  memcpy(outi->mX, ini->mX, sizeof(int32_T)*ini->mN);
  memcpy(outj->mX, inj->mX, sizeof(int32_T)*inj->mN);
  memcpy(outr->mX, inr->mX, sizeof(real_T)*inr->mN);
}

NeDynamicSystem *EKFSim_3bb8072c_49_dae_ds(PmAllocator *allocator)
{
  NeDynamicSystem *ds;
  _NeDynamicSystem *_ds;
  static SscIoInfo input_info[4];
  static SscIoInfo output_info[2];

  /* allocate dynamic system data and extended data */
  _ds = (_NeDynamicSystem *)allocator->mCallocFcn( allocator, sizeof
    (_NeDynamicSystem), 1);
  _ds->mAlloc = *allocator;
  _ds->mRefCnt = 1;
  ds = &_ds->mBase;

  /* setup sizes */
  ds->mNumVariables = 1;
  ds->mNumDiscreteRealVariables = 0;
  ds->mNumDifferentialVariables = 0;
  ds->mNumEquations = 1;
  ds->mNumCEResiduals = 0;
  ds->mNumICResiduals = 0;
  ds->mNumFreqs = 0;
  ds->mNumSolverHits = 0;
  ds->mNumModes = 1;
  ds->mNumMajorModes = 0;
  ds->mNumRealCache = 0;
  ds->mNumIntCache = 0;
  ds->mNumObservables = 37;
  ds->mNumObservableElements = 36;
  ds->mNumZcs = 1;
  ds->mNumAsserts = 0;
  ds->mNumAssertRanges = 0;
  ds->mNumParamAsserts = 0;
  ds->mNumParamAssertRanges = 0;
  ds->mNumInitialAsserts = 0;
  ds->mNumInitialAssertRanges = 0;
  ds->mNumRanges = 1;
  ds->mNumEquationRanges = 3;
  ds->mNumCERRanges = 0;
  ds->mNumICRRanges = 0;
  ds->mNumFundamentalSamples = 0;
  ds->mNumDelays = 0;
  ds->mNumLogicalParameters = 0;
  ds->mNumIntegerParameters = 0;
  ds->mNumIndexParameters = 0;
  ds->mNumRealParameters = 0;
  ds->mNumLogicalDerivedParameters = 0;
  ds->mNumIntegerDerivedParameters = 0;
  ds->mNumIndexDerivedParameters = 0;
  ds->mNumRealDerivedParameters = 0;
  ds->mIsOutputLinear = TRUE;
  ds->mIsOutputSwitchedLinear = TRUE;
  ds->mIsScalable = FALSE;

  /* setup ios */
  ds->mNumIo[SSC_INPUT_IO_TYPE] = 4;
  input_info[0].identifier = "Thevenin_ECM.Simulink_PS_Converter1_output0";
  input_info[0].size.numElements = 1;
  input_info[0].size.encodedDimensions = "1x1";
  input_info[0].name = "Thevenin_ECM.Simulink_PS_Converter1_output0";
  input_info[0].unit = "1";
  input_info[1].identifier = "Thevenin_ECM.Simulink_PS_Converter2_output0";
  input_info[1].size.numElements = 1;
  input_info[1].size.encodedDimensions = "1x1";
  input_info[1].name = "Thevenin_ECM.Simulink_PS_Converter2_output0";
  input_info[1].unit = "1";
  input_info[2].identifier = "Thevenin_ECM.Simulink_PS_Converter4_output0";
  input_info[2].size.numElements = 1;
  input_info[2].size.encodedDimensions = "1x1";
  input_info[2].name = "Thevenin_ECM.Simulink_PS_Converter4_output0";
  input_info[2].unit = "1";
  input_info[3].identifier = "Thevenin_ECM.Simulink_PS_Converter5_output0";
  input_info[3].size.numElements = 1;
  input_info[3].size.encodedDimensions = "1x1";
  input_info[3].name = "Thevenin_ECM.Simulink_PS_Converter5_output0";
  input_info[3].unit = "1";
  ds->mIo[SSC_INPUT_IO_TYPE] = input_info;
  ds->mNumIo[SSC_OUTPUT_IO_TYPE] = 2;
  output_info[0].identifier = "Thevenin_ECM.Current_Sensor_I0";
  output_info[0].size.numElements = 1;
  output_info[0].size.encodedDimensions = "1x1";
  output_info[0].name = "Thevenin_ECM.Current_Sensor_I0";
  output_info[0].unit = "A";
  output_info[1].identifier = "Thevenin_ECM.Voltage_Sensor_V0";
  output_info[1].size.numElements = 1;
  output_info[1].size.encodedDimensions = "1x1";
  output_info[1].name = "Thevenin_ECM.Voltage_Sensor_V0";
  output_info[1].unit = "V";
  ds->mIo[SSC_OUTPUT_IO_TYPE] = output_info;

  /* setup administration methods */
  ds->mReleaseReference = release_reference;
  ds->mGetReference = get_reference;
  ds->mDiagnosticsDsFcn = diagnostics;
  ds->mExpandFcn = expand;
  ds->mRtpMapFcn = rtpmap;
  ds->mMethods[NE_DS_METHOD_MCON_P] = ds_mcon_p;
  ds->mMakeOutput[NE_DS_METHOD_MCON_P] = ds_output_mcon_p;
  ds->mMethods[NE_DS_METHOD_MCON] = ds_mcon;
  ds->mMakeOutput[NE_DS_METHOD_MCON] = ds_output_mcon;
  ds->mMethods[NE_DS_METHOD_MPAR_P] = ds_mpar_p;
  ds->mMakeOutput[NE_DS_METHOD_MPAR_P] = ds_output_mpar_p;
  ds->mMethods[NE_DS_METHOD_MPAR] = ds_mpar;
  ds->mMakeOutput[NE_DS_METHOD_MPAR] = ds_output_mpar;
  ds->mMethods[NE_DS_METHOD_MNL_P] = ds_mnl_p;
  ds->mMakeOutput[NE_DS_METHOD_MNL_P] = ds_output_mnl_p;
  ds->mMethods[NE_DS_METHOD_MNL] = ds_mnl;
  ds->mMakeOutput[NE_DS_METHOD_MNL] = ds_output_mnl;
  ds->mMethods[NE_DS_METHOD_VMM] = ds_vmm;
  ds->mMakeOutput[NE_DS_METHOD_VMM] = ds_output_vmm;
  ds->mMethods[NE_DS_METHOD_DXM_P] = ds_dxm_p;
  ds->mMakeOutput[NE_DS_METHOD_DXM_P] = ds_output_dxm_p;
  ds->mMethods[NE_DS_METHOD_DXM] = ds_dxm;
  ds->mMakeOutput[NE_DS_METHOD_DXM] = ds_output_dxm;
  ds->mMethods[NE_DS_METHOD_DDM_P] = ds_ddm_p;
  ds->mMakeOutput[NE_DS_METHOD_DDM_P] = ds_output_ddm_p;
  ds->mMethods[NE_DS_METHOD_DDM] = ds_ddm;
  ds->mMakeOutput[NE_DS_METHOD_DDM] = ds_output_ddm;
  ds->mMethods[NE_DS_METHOD_DUM_P] = ds_dum_p;
  ds->mMakeOutput[NE_DS_METHOD_DUM_P] = ds_output_dum_p;
  ds->mMethods[NE_DS_METHOD_DUM] = ds_dum;
  ds->mMakeOutput[NE_DS_METHOD_DUM] = ds_output_dum;
  ds->mMethods[NE_DS_METHOD_DTM_P] = ds_dtm_p;
  ds->mMakeOutput[NE_DS_METHOD_DTM_P] = ds_output_dtm_p;
  ds->mMethods[NE_DS_METHOD_DTM] = ds_dtm;
  ds->mMakeOutput[NE_DS_METHOD_DTM] = ds_output_dtm;
  ds->mMethods[NE_DS_METHOD_DPM_P] = ds_dpm_p;
  ds->mMakeOutput[NE_DS_METHOD_DPM_P] = ds_output_dpm_p;
  ds->mMethods[NE_DS_METHOD_DPM] = ds_dpm;
  ds->mMakeOutput[NE_DS_METHOD_DPM] = ds_output_dpm;
  ds->mMethods[NE_DS_METHOD_ACON_P] = ds_acon_p;
  ds->mMakeOutput[NE_DS_METHOD_ACON_P] = ds_output_acon_p;
  ds->mMethods[NE_DS_METHOD_ACON] = ds_acon;
  ds->mMakeOutput[NE_DS_METHOD_ACON] = ds_output_acon;
  ds->mMethods[NE_DS_METHOD_APAR_P] = ds_apar_p;
  ds->mMakeOutput[NE_DS_METHOD_APAR_P] = ds_output_apar_p;
  ds->mMethods[NE_DS_METHOD_APAR] = ds_apar;
  ds->mMakeOutput[NE_DS_METHOD_APAR] = ds_output_apar;
  ds->mMethods[NE_DS_METHOD_BCON_P] = ds_bcon_p;
  ds->mMakeOutput[NE_DS_METHOD_BCON_P] = ds_output_bcon_p;
  ds->mMethods[NE_DS_METHOD_BCON] = ds_bcon;
  ds->mMakeOutput[NE_DS_METHOD_BCON] = ds_output_bcon;
  ds->mMethods[NE_DS_METHOD_BPAR_P] = ds_bpar_p;
  ds->mMakeOutput[NE_DS_METHOD_BPAR_P] = ds_output_bpar_p;
  ds->mMethods[NE_DS_METHOD_BPAR] = ds_bpar;
  ds->mMakeOutput[NE_DS_METHOD_BPAR] = ds_output_bpar;
  ds->mMethods[NE_DS_METHOD_CCON_P] = ds_ccon_p;
  ds->mMakeOutput[NE_DS_METHOD_CCON_P] = ds_output_ccon_p;
  ds->mMethods[NE_DS_METHOD_CCON] = ds_ccon;
  ds->mMakeOutput[NE_DS_METHOD_CCON] = ds_output_ccon;
  ds->mMethods[NE_DS_METHOD_CPAR_P] = ds_cpar_p;
  ds->mMakeOutput[NE_DS_METHOD_CPAR_P] = ds_output_cpar_p;
  ds->mMethods[NE_DS_METHOD_CPAR] = ds_cpar;
  ds->mMakeOutput[NE_DS_METHOD_CPAR] = ds_output_cpar;
  ds->mMethods[NE_DS_METHOD_F] = ds_f;
  ds->mMakeOutput[NE_DS_METHOD_F] = ds_output_f;
  ds->mMethods[NE_DS_METHOD_VDF] = ds_vdf;
  ds->mMakeOutput[NE_DS_METHOD_VDF] = ds_output_vdf;
  ds->mMethods[NE_DS_METHOD_VMF] = ds_vmf;
  ds->mMakeOutput[NE_DS_METHOD_VMF] = ds_output_vmf;
  ds->mMethods[NE_DS_METHOD_VPF] = ds_vpf;
  ds->mMakeOutput[NE_DS_METHOD_VPF] = ds_output_vpf;
  ds->mMethods[NE_DS_METHOD_VSF] = ds_vsf;
  ds->mMakeOutput[NE_DS_METHOD_VSF] = ds_output_vsf;
  ds->mMethods[NE_DS_METHOD_SLF] = ds_slf;
  ds->mMakeOutput[NE_DS_METHOD_SLF] = ds_output_slf;
  ds->mMethods[NE_DS_METHOD_SLF0] = ds_slf0;
  ds->mMakeOutput[NE_DS_METHOD_SLF0] = ds_output_slf0;
  ds->mMethods[NE_DS_METHOD_DXF_P] = ds_dxf_p;
  ds->mMakeOutput[NE_DS_METHOD_DXF_P] = ds_output_dxf_p;
  ds->mMethods[NE_DS_METHOD_DXF] = ds_dxf;
  ds->mMakeOutput[NE_DS_METHOD_DXF] = ds_output_dxf;
  ds->mMethods[NE_DS_METHOD_DUF_P] = ds_duf_p;
  ds->mMakeOutput[NE_DS_METHOD_DUF_P] = ds_output_duf_p;
  ds->mMethods[NE_DS_METHOD_DUF] = ds_duf;
  ds->mMakeOutput[NE_DS_METHOD_DUF] = ds_output_duf;
  ds->mMethods[NE_DS_METHOD_DTF_P] = ds_dtf_p;
  ds->mMakeOutput[NE_DS_METHOD_DTF_P] = ds_output_dtf_p;
  ds->mMethods[NE_DS_METHOD_DTF] = ds_dtf;
  ds->mMakeOutput[NE_DS_METHOD_DTF] = ds_output_dtf;
  ds->mMethods[NE_DS_METHOD_DDF_P] = ds_ddf_p;
  ds->mMakeOutput[NE_DS_METHOD_DDF_P] = ds_output_ddf_p;
  ds->mMethods[NE_DS_METHOD_DDF] = ds_ddf;
  ds->mMakeOutput[NE_DS_METHOD_DDF] = ds_output_ddf;
  ds->mMethods[NE_DS_METHOD_DPDXF_P] = ds_dpdxf_p;
  ds->mMakeOutput[NE_DS_METHOD_DPDXF_P] = ds_output_dpdxf_p;
  ds->mMethods[NE_DS_METHOD_DPDXF] = ds_dpdxf;
  ds->mMakeOutput[NE_DS_METHOD_DPDXF] = ds_output_dpdxf;
  ds->mMethods[NE_DS_METHOD_DWF_P] = ds_dwf_p;
  ds->mMakeOutput[NE_DS_METHOD_DWF_P] = ds_output_dwf_p;
  ds->mMethods[NE_DS_METHOD_DWF] = ds_dwf;
  ds->mMakeOutput[NE_DS_METHOD_DWF] = ds_output_dwf;
  ds->mMethods[NE_DS_METHOD_TDUF_P] = ds_tduf_p;
  ds->mMakeOutput[NE_DS_METHOD_TDUF_P] = ds_output_tduf_p;
  ds->mMethods[NE_DS_METHOD_TDXF_P] = ds_tdxf_p;
  ds->mMakeOutput[NE_DS_METHOD_TDXF_P] = ds_output_tdxf_p;
  ds->mMethods[NE_DS_METHOD_DNF_P] = ds_dnf_p;
  ds->mMakeOutput[NE_DS_METHOD_DNF_P] = ds_output_dnf_p;
  ds->mMethods[NE_DS_METHOD_DNF] = ds_dnf;
  ds->mMakeOutput[NE_DS_METHOD_DNF] = ds_output_dnf;
  ds->mMethods[NE_DS_METHOD_DNF_V_X] = ds_dnf_v_x;
  ds->mMakeOutput[NE_DS_METHOD_DNF_V_X] = ds_output_dnf_v_x;
  ds->mMethods[NE_DS_METHOD_CER] = ds_cer;
  ds->mMakeOutput[NE_DS_METHOD_CER] = ds_output_cer;
  ds->mMethods[NE_DS_METHOD_DXCER] = ds_dxcer;
  ds->mMakeOutput[NE_DS_METHOD_DXCER] = ds_output_dxcer;
  ds->mMethods[NE_DS_METHOD_DXCER_P] = ds_dxcer_p;
  ds->mMakeOutput[NE_DS_METHOD_DXCER_P] = ds_output_dxcer_p;
  ds->mMethods[NE_DS_METHOD_DDCER] = ds_ddcer;
  ds->mMakeOutput[NE_DS_METHOD_DDCER] = ds_output_ddcer;
  ds->mMethods[NE_DS_METHOD_DDCER_P] = ds_ddcer_p;
  ds->mMakeOutput[NE_DS_METHOD_DDCER_P] = ds_output_ddcer_p;
  ds->mMethods[NE_DS_METHOD_IC] = ds_ic;
  ds->mMakeOutput[NE_DS_METHOD_IC] = ds_output_ic;
  ds->mMethods[NE_DS_METHOD_ICR] = ds_icr;
  ds->mMakeOutput[NE_DS_METHOD_ICR] = ds_output_icr;
  ds->mMethods[NE_DS_METHOD_ICR_IM] = ds_icr_im;
  ds->mMakeOutput[NE_DS_METHOD_ICR_IM] = ds_output_icr_im;
  ds->mMethods[NE_DS_METHOD_ICR_ID] = ds_icr_id;
  ds->mMakeOutput[NE_DS_METHOD_ICR_ID] = ds_output_icr_id;
  ds->mMethods[NE_DS_METHOD_ICR_IL] = ds_icr_il;
  ds->mMakeOutput[NE_DS_METHOD_ICR_IL] = ds_output_icr_il;
  ds->mMethods[NE_DS_METHOD_DXICR] = ds_dxicr;
  ds->mMakeOutput[NE_DS_METHOD_DXICR] = ds_output_dxicr;
  ds->mMethods[NE_DS_METHOD_DXICR_P] = ds_dxicr_p;
  ds->mMakeOutput[NE_DS_METHOD_DXICR_P] = ds_output_dxicr_p;
  ds->mMethods[NE_DS_METHOD_DDICR] = ds_ddicr;
  ds->mMakeOutput[NE_DS_METHOD_DDICR] = ds_output_ddicr;
  ds->mMethods[NE_DS_METHOD_DDICR_P] = ds_ddicr_p;
  ds->mMakeOutput[NE_DS_METHOD_DDICR_P] = ds_output_ddicr_p;
  ds->mMethods[NE_DS_METHOD_TDUICR_P] = ds_tduicr_p;
  ds->mMakeOutput[NE_DS_METHOD_TDUICR_P] = ds_output_tduicr_p;
  ds->mMethods[NE_DS_METHOD_ICRM_P] = ds_icrm_p;
  ds->mMakeOutput[NE_DS_METHOD_ICRM_P] = ds_output_icrm_p;
  ds->mMethods[NE_DS_METHOD_ICRM] = ds_icrm;
  ds->mMakeOutput[NE_DS_METHOD_ICRM] = ds_output_icrm;
  ds->mMethods[NE_DS_METHOD_DXICRM_P] = ds_dxicrm_p;
  ds->mMakeOutput[NE_DS_METHOD_DXICRM_P] = ds_output_dxicrm_p;
  ds->mMethods[NE_DS_METHOD_DXICRM] = ds_dxicrm;
  ds->mMakeOutput[NE_DS_METHOD_DXICRM] = ds_output_dxicrm;
  ds->mMethods[NE_DS_METHOD_DDICRM_P] = ds_ddicrm_p;
  ds->mMakeOutput[NE_DS_METHOD_DDICRM_P] = ds_output_ddicrm_p;
  ds->mMethods[NE_DS_METHOD_DDICRM] = ds_ddicrm;
  ds->mMakeOutput[NE_DS_METHOD_DDICRM] = ds_output_ddicrm;
  ds->mMethods[NE_DS_METHOD_FREQS] = ds_freqs;
  ds->mMakeOutput[NE_DS_METHOD_FREQS] = ds_output_freqs;
  ds->mMethods[NE_DS_METHOD_SOLVERHITS] = ds_solverhits;
  ds->mMakeOutput[NE_DS_METHOD_SOLVERHITS] = ds_output_solverhits;
  ds->mMethods[NE_DS_METHOD_MDUY_P] = ds_mduy_p;
  ds->mMakeOutput[NE_DS_METHOD_MDUY_P] = ds_output_mduy_p;
  ds->mMethods[NE_DS_METHOD_MDXY_P] = ds_mdxy_p;
  ds->mMakeOutput[NE_DS_METHOD_MDXY_P] = ds_output_mdxy_p;
  ds->mMethods[NE_DS_METHOD_TDUY_P] = ds_tduy_p;
  ds->mMakeOutput[NE_DS_METHOD_TDUY_P] = ds_output_tduy_p;
  ds->mMethods[NE_DS_METHOD_TDXY_P] = ds_tdxy_p;
  ds->mMakeOutput[NE_DS_METHOD_TDXY_P] = ds_output_tdxy_p;
  ds->mMethods[NE_DS_METHOD_Y] = ds_y;
  ds->mMakeOutput[NE_DS_METHOD_Y] = ds_output_y;
  ds->mMethods[NE_DS_METHOD_DXY_P] = ds_dxy_p;
  ds->mMakeOutput[NE_DS_METHOD_DXY_P] = ds_output_dxy_p;
  ds->mMethods[NE_DS_METHOD_DXY] = ds_dxy;
  ds->mMakeOutput[NE_DS_METHOD_DXY] = ds_output_dxy;
  ds->mMethods[NE_DS_METHOD_DUY_P] = ds_duy_p;
  ds->mMakeOutput[NE_DS_METHOD_DUY_P] = ds_output_duy_p;
  ds->mMethods[NE_DS_METHOD_DUY] = ds_duy;
  ds->mMakeOutput[NE_DS_METHOD_DUY] = ds_output_duy;
  ds->mMethods[NE_DS_METHOD_DTY_P] = ds_dty_p;
  ds->mMakeOutput[NE_DS_METHOD_DTY_P] = ds_output_dty_p;
  ds->mMethods[NE_DS_METHOD_DTY] = ds_dty;
  ds->mMakeOutput[NE_DS_METHOD_DTY] = ds_output_dty;
  ds->mMethods[NE_DS_METHOD_MODE] = ds_mode;
  ds->mMakeOutput[NE_DS_METHOD_MODE] = ds_output_mode;
  ds->mMethods[NE_DS_METHOD_ZC] = ds_zc;
  ds->mMakeOutput[NE_DS_METHOD_ZC] = ds_output_zc;
  ds->mMethods[NE_DS_METHOD_CACHE_R] = ds_cache_r;
  ds->mMakeOutput[NE_DS_METHOD_CACHE_R] = ds_output_cache_r;
  ds->mMethods[NE_DS_METHOD_CACHE_I] = ds_cache_i;
  ds->mMakeOutput[NE_DS_METHOD_CACHE_I] = ds_output_cache_i;
  ds->mMethods[NE_DS_METHOD_UPDATE_R] = ds_update_r;
  ds->mMakeOutput[NE_DS_METHOD_UPDATE_R] = ds_output_update_r;
  ds->mMethods[NE_DS_METHOD_UPDATE_I] = ds_update_i;
  ds->mMakeOutput[NE_DS_METHOD_UPDATE_I] = ds_output_update_i;
  ds->mMethods[NE_DS_METHOD_UPDATE2_R] = ds_update2_r;
  ds->mMakeOutput[NE_DS_METHOD_UPDATE2_R] = ds_output_update2_r;
  ds->mMethods[NE_DS_METHOD_UPDATE2_I] = ds_update2_i;
  ds->mMakeOutput[NE_DS_METHOD_UPDATE2_I] = ds_output_update2_i;
  ds->mMethods[NE_DS_METHOD_LOCK_R] = ds_lock_r;
  ds->mMakeOutput[NE_DS_METHOD_LOCK_R] = ds_output_lock_r;
  ds->mMethods[NE_DS_METHOD_LOCK_I] = ds_lock_i;
  ds->mMakeOutput[NE_DS_METHOD_LOCK_I] = ds_output_lock_i;
  ds->mMethods[NE_DS_METHOD_LOCK2_R] = ds_lock2_r;
  ds->mMakeOutput[NE_DS_METHOD_LOCK2_R] = ds_output_lock2_r;
  ds->mMethods[NE_DS_METHOD_LOCK2_I] = ds_lock2_i;
  ds->mMakeOutput[NE_DS_METHOD_LOCK2_I] = ds_output_lock2_i;
  ds->mMethods[NE_DS_METHOD_SFO] = ds_sfo;
  ds->mMakeOutput[NE_DS_METHOD_SFO] = ds_output_sfo;
  ds->mMethods[NE_DS_METHOD_SFP] = ds_sfp;
  ds->mMakeOutput[NE_DS_METHOD_SFP] = ds_output_sfp;
  ds->mMethods[NE_DS_METHOD_INIT_R] = ds_init_r;
  ds->mMakeOutput[NE_DS_METHOD_INIT_R] = ds_output_init_r;
  ds->mMethods[NE_DS_METHOD_INIT_I] = ds_init_i;
  ds->mMakeOutput[NE_DS_METHOD_INIT_I] = ds_output_init_i;
  ds->mMethods[NE_DS_METHOD_LOG] = EKFSim_3bb8072c_49_ds_log;
  ds->mMakeOutput[NE_DS_METHOD_LOG] = ds_output_log;
  ds->mMethods[NE_DS_METHOD_ASSERT] = ds_assert;
  ds->mMakeOutput[NE_DS_METHOD_ASSERT] = ds_output_assert;
  ds->mMethods[NE_DS_METHOD_PASSERT] = ds_passert;
  ds->mMakeOutput[NE_DS_METHOD_PASSERT] = ds_output_passert;
  ds->mMethods[NE_DS_METHOD_IASSERT] = ds_iassert;
  ds->mMakeOutput[NE_DS_METHOD_IASSERT] = ds_output_iassert;
  ds->mMethods[NE_DS_METHOD_DEL_T] = ds_del_t;
  ds->mMakeOutput[NE_DS_METHOD_DEL_T] = ds_output_del_t;
  ds->mMethods[NE_DS_METHOD_DEL_V] = ds_del_v;
  ds->mMakeOutput[NE_DS_METHOD_DEL_V] = ds_output_del_v;
  ds->mMethods[NE_DS_METHOD_DEL_V0] = ds_del_v0;
  ds->mMakeOutput[NE_DS_METHOD_DEL_V0] = ds_output_del_v0;
  ds->mMethods[NE_DS_METHOD_DEL_TMAX] = ds_del_tmax;
  ds->mMakeOutput[NE_DS_METHOD_DEL_TMAX] = ds_output_del_tmax;
  ds->mMethods[NE_DS_METHOD_DXDELT_P] = ds_dxdelt_p;
  ds->mMakeOutput[NE_DS_METHOD_DXDELT_P] = ds_output_dxdelt_p;
  ds->mMethods[NE_DS_METHOD_DXDELT] = ds_dxdelt;
  ds->mMakeOutput[NE_DS_METHOD_DXDELT] = ds_output_dxdelt;
  ds->mMethods[NE_DS_METHOD_DUDELT_P] = ds_dudelt_p;
  ds->mMakeOutput[NE_DS_METHOD_DUDELT_P] = ds_output_dudelt_p;
  ds->mMethods[NE_DS_METHOD_DUDELT] = ds_dudelt;
  ds->mMakeOutput[NE_DS_METHOD_DUDELT] = ds_output_dudelt;
  ds->mMethods[NE_DS_METHOD_DTDELT_P] = ds_dtdelt_p;
  ds->mMakeOutput[NE_DS_METHOD_DTDELT_P] = ds_output_dtdelt_p;
  ds->mMethods[NE_DS_METHOD_DTDELT] = ds_dtdelt;
  ds->mMakeOutput[NE_DS_METHOD_DTDELT] = ds_output_dtdelt;
  ds->mMethods[NE_DS_METHOD_OBS_EXP] = EKFSim_3bb8072c_49_ds_obs_exp;
  ds->mMakeOutput[NE_DS_METHOD_OBS_EXP] = ds_output_obs_exp;
  ds->mMethods[NE_DS_METHOD_OBS_ACT] = EKFSim_3bb8072c_49_ds_obs_act;
  ds->mMakeOutput[NE_DS_METHOD_OBS_ACT] = ds_output_obs_act;
  ds->mMethods[NE_DS_METHOD_OBS_ALL] = EKFSim_3bb8072c_49_ds_obs_all;
  ds->mMakeOutput[NE_DS_METHOD_OBS_ALL] = ds_output_obs_all;
  ds->mMethods[NE_DS_METHOD_OBS_IL] = EKFSim_3bb8072c_49_ds_obs_il;
  ds->mMakeOutput[NE_DS_METHOD_OBS_IL] = ds_output_obs_il;
  ds->mMethods[NE_DS_METHOD_DP_L] = ds_dp_l;
  ds->mMakeOutput[NE_DS_METHOD_DP_L] = ds_output_dp_l;
  ds->mMethods[NE_DS_METHOD_DP_I] = ds_dp_i;
  ds->mMakeOutput[NE_DS_METHOD_DP_I] = ds_output_dp_i;
  ds->mMethods[NE_DS_METHOD_DP_J] = ds_dp_j;
  ds->mMakeOutput[NE_DS_METHOD_DP_J] = ds_output_dp_j;
  ds->mMethods[NE_DS_METHOD_DP_R] = ds_dp_r;
  ds->mMakeOutput[NE_DS_METHOD_DP_R] = ds_output_dp_r;
  ds->mMethods[NE_DS_METHOD_QX] = ds_qx;
  ds->mMakeOutput[NE_DS_METHOD_QX] = ds_output_qx;
  ds->mMethods[NE_DS_METHOD_QU] = ds_qu;
  ds->mMakeOutput[NE_DS_METHOD_QU] = ds_output_qu;
  ds->mMethods[NE_DS_METHOD_QT] = ds_qt;
  ds->mMakeOutput[NE_DS_METHOD_QT] = ds_output_qt;
  ds->mMethods[NE_DS_METHOD_Q1] = ds_q1;
  ds->mMakeOutput[NE_DS_METHOD_Q1] = ds_output_q1;
  ds->mMethods[NE_DS_METHOD_QX_P] = ds_qx_p;
  ds->mMakeOutput[NE_DS_METHOD_QX_P] = ds_output_qx_p;
  ds->mMethods[NE_DS_METHOD_QU_P] = ds_qu_p;
  ds->mMakeOutput[NE_DS_METHOD_QU_P] = ds_output_qu_p;
  ds->mMethods[NE_DS_METHOD_QT_P] = ds_qt_p;
  ds->mMakeOutput[NE_DS_METHOD_QT_P] = ds_output_qt_p;
  ds->mMethods[NE_DS_METHOD_Q1_P] = ds_q1_p;
  ds->mMakeOutput[NE_DS_METHOD_Q1_P] = ds_output_q1_p;
  ds->mMethods[NE_DS_METHOD_VAR_TOL] = ds_var_tol;
  ds->mMakeOutput[NE_DS_METHOD_VAR_TOL] = ds_output_var_tol;
  ds->mMethods[NE_DS_METHOD_EQ_TOL] = ds_eq_tol;
  ds->mMakeOutput[NE_DS_METHOD_EQ_TOL] = ds_output_eq_tol;
  ds->mMethods[NE_DS_METHOD_LV] = ds_lv;
  ds->mMakeOutput[NE_DS_METHOD_LV] = ds_output_lv;
  ds->mMethods[NE_DS_METHOD_SLV] = ds_slv;
  ds->mMakeOutput[NE_DS_METHOD_SLV] = ds_output_slv;
  ds->mMethods[NE_DS_METHOD_NLDV] = ds_nldv;
  ds->mMakeOutput[NE_DS_METHOD_NLDV] = ds_output_nldv;
  ds->mMethods[NE_DS_METHOD_SCLV] = ds_sclv;
  ds->mMakeOutput[NE_DS_METHOD_SCLV] = ds_output_sclv;
  ds->mMethods[NE_DS_METHOD_IMIN] = ds_imin;
  ds->mMakeOutput[NE_DS_METHOD_IMIN] = ds_output_imin;
  ds->mMethods[NE_DS_METHOD_IMAX] = ds_imax;
  ds->mMakeOutput[NE_DS_METHOD_IMAX] = ds_output_imax;
  ds->mMethods[NE_DS_METHOD_DIMIN] = ds_dimin;
  ds->mMakeOutput[NE_DS_METHOD_DIMIN] = ds_output_dimin;
  ds->mMethods[NE_DS_METHOD_DIMAX] = ds_dimax;
  ds->mMakeOutput[NE_DS_METHOD_DIMAX] = ds_output_dimax;

  /* equation data */
  ds->mEquationData = s_equation_data;

  /* cer data */
  ds->mCERData = s_cer_data;

  /* icr data */
  ds->mICRData = s_icr_data;

  /* continuous variable data */
  ds->mVariableData = s_variable_data;

  /* discrete variable data */
  ds->mDiscreteData = s_discrete_data;

  /* observable data */
  ds->mObservableData = s_observable_data;

  /* major mode data */
  ds->mMajorModeData = s_major_mode_data;

  /* zc data */
  ds->mZCData = s_zc_data;

  /* ranges */
  ds->mRanges = s_range;

  /* assert data */
  ds->mAssertData = s_assert_data;

  /* assert ranges */
  ds->mAssertRanges = s_assert_range;

  /* param assert data */
  ds->mParamAssertData = s_param_assert_data;

  /* param assert ranges */
  ds->mParamAssertRanges = s_param_assert_range;

  /* initial assert data */
  ds->mInitialAssertData = s_initial_assert_data;

  /* initial assert ranges */
  ds->mInitialAssertRanges = s_initial_assert_range;

  /* equation ranges */
  ds->mEquationRanges = s_equation_range;

  /* cer ranges */
  ds->mCERRanges = s_cer_range;

  /* icr ranges */
  ds->mICRRanges = s_icr_range;

  /* parameters */
  ds->mLogicalParameters = s_logical_parameter_data;
  ds->mIntegerParameters = s_integer_parameter_data;
  ds->mIndexParameters = s_index_parameter_data;
  ds->mRealParameters = s_real_parameter_data;

  /* constant tables */
  ds->mNumLargeArray = 0;
  return (NeDynamicSystem *)_ds;
}

static int32_T ds_assert (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_passert (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_iassert (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_cer (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxcer (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxcer_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXCER_P.mNumCol = 1ULL;
  out->mDXCER_P.mNumRow = 0ULL;
  out->mDXCER_P.mJc[0] = 0;
  out->mDXCER_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddcer (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddcer_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDDCER_P.mNumCol = 0ULL;
  out->mDDCER_P.mNumRow = 0ULL;
  out->mDDCER_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_del_v (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_del_v0 (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_del_tmax (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_del_t (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxdelt (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxdelt_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXDELT_P.mNumCol = 1ULL;
  out->mDXDELT_P.mNumRow = 0ULL;
  out->mDXDELT_P.mJc[0] = 0;
  out->mDXDELT_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dudelt (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dudelt_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDUDELT_P.mNumCol = 4ULL;
  out->mDUDELT_P.mNumRow = 0ULL;
  out->mDUDELT_P.mJc[0] = 0;
  out->mDUDELT_P.mJc[1] = 0;
  out->mDUDELT_P.mJc[2] = 0;
  out->mDUDELT_P.mJc[3] = 0;
  out->mDUDELT_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtdelt (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtdelt_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDTDELT_P.mNumCol = 1ULL;
  out->mDTDELT_P.mNumRow = 0ULL;
  out->mDTDELT_P.mJc[0] = 0;
  out->mDTDELT_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_cache_r (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_init_r (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_update_r (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_lock_r (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_cache_i (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_init_i (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_update_i (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_lock_i (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_update2_r (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_lock2_r (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_update2_i (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_lock2_i (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_sfp (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_sfo (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_f (const NeDynamicSystem *sys, const NeDynamicSystemInput *t2,
                     NeDsMethodOutput *out)
{
  if (t2->mM.mX[0ULL] != 0) {
    out->mF.mX[0ULL] = t2->mX.mX[0ULL] - (-(t2->mU.mX[2ULL] * t2->mU.mX[3ULL]));
  } else {
    out->mF.mX[0ULL] = t2->mX.mX[0ULL];
  }

  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXF.mX[0] = 1.0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXF_P.mNumCol = 1ULL;
  out->mDXF_P.mNumRow = 1ULL;
  out->mDXF_P.mJc[0] = 0;
  out->mDXF_P.mJc[1] = 1;
  out->mDXF_P.mIr[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_duf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t3, NeDsMethodOutput *out)
{
  if (t3->mM.mX[0ULL] != 0) {
    out->mDUF.mX[0ULL] = t3->mU.mX[3ULL];
  } else {
    out->mDUF.mX[0ULL] = 0.0;
  }

  if (t3->mM.mX[0ULL] != 0) {
    out->mDUF.mX[1ULL] = t3->mU.mX[2ULL];
  } else {
    out->mDUF.mX[1ULL] = 0.0;
  }

  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_duf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  static int32_T _cg_const_1[5] = { 0, 0, 0, 1, 2 };

  (void)t1;
  out->mDUF_P.mNumCol = 4ULL;
  out->mDUF_P.mNumRow = 1ULL;
  out->mDUF_P.mJc[0] = _cg_const_1[0];
  out->mDUF_P.mJc[1] = _cg_const_1[1];
  out->mDUF_P.mJc[2] = _cg_const_1[2];
  out->mDUF_P.mJc[3] = _cg_const_1[3];
  out->mDUF_P.mJc[4] = _cg_const_1[4];
  out->mDUF_P.mIr[0] = 0;
  out->mDUF_P.mIr[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDTF_P.mNumCol = 1ULL;
  out->mDTF_P.mNumRow = 1ULL;
  out->mDTF_P.mJc[0] = 0;
  out->mDTF_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDDF_P.mNumCol = 0ULL;
  out->mDDF_P.mNumRow = 1ULL;
  out->mDDF_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_acon (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_acon_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mACON_P.mNumCol = 1ULL;
  out->mACON_P.mNumRow = 1ULL;
  out->mACON_P.mJc[0] = 0;
  out->mACON_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_apar (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_apar_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mAPAR_P.mNumCol = 1ULL;
  out->mAPAR_P.mNumRow = 1ULL;
  out->mAPAR_P.mJc[0] = 0;
  out->mAPAR_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_bcon (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_bcon_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mBCON_P.mNumCol = 4ULL;
  out->mBCON_P.mNumRow = 1ULL;
  out->mBCON_P.mJc[0] = 0;
  out->mBCON_P.mJc[1] = 0;
  out->mBCON_P.mJc[2] = 0;
  out->mBCON_P.mJc[3] = 0;
  out->mBCON_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_bpar (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_bpar_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mBPAR_P.mNumCol = 4ULL;
  out->mBPAR_P.mNumRow = 1ULL;
  out->mBPAR_P.mJc[0] = 0;
  out->mBPAR_P.mJc[1] = 0;
  out->mBPAR_P.mJc[2] = 0;
  out->mBPAR_P.mJc[3] = 0;
  out->mBPAR_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ccon (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ccon_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mCCON_P.mNumCol = 1ULL;
  out->mCCON_P.mNumRow = 1ULL;
  out->mCCON_P.mJc[0] = 0;
  out->mCCON_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_cpar (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_cpar_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mCPAR_P.mNumCol = 1ULL;
  out->mCPAR_P.mNumRow = 1ULL;
  out->mCPAR_P.mJc[0] = 0;
  out->mCPAR_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_tduf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  static int32_T _cg_const_1[5] = { 0, 0, 0, 1, 2 };

  (void)t1;
  out->mTDUF_P.mNumCol = 4ULL;
  out->mTDUF_P.mNumRow = 1ULL;
  out->mTDUF_P.mJc[0] = _cg_const_1[0];
  out->mTDUF_P.mJc[1] = _cg_const_1[1];
  out->mTDUF_P.mJc[2] = _cg_const_1[2];
  out->mTDUF_P.mJc[3] = _cg_const_1[3];
  out->mTDUF_P.mJc[4] = _cg_const_1[4];
  out->mTDUF_P.mIr[0] = 0;
  out->mTDUF_P.mIr[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_tdxf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mTDXF_P.mNumCol = 1ULL;
  out->mTDXF_P.mNumRow = 1ULL;
  out->mTDXF_P.mJc[0] = 0;
  out->mTDXF_P.mJc[1] = 1;
  out->mTDXF_P.mIr[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dwf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dwf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDWF_P.mNumCol = 0ULL;
  out->mDWF_P.mNumRow = 1ULL;
  out->mDWF_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dpdxf (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dpdxf_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDPDXF_P.mNumCol = 0ULL;
  out->mDPDXF_P.mNumRow = 1ULL;
  out->mDPDXF_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_vdf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mVDF.mX[0] = true;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_vmf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mVMF.mX[0] = true;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_slf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mSLF.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dnf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dnf_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDNF_P.mNumCol = 1ULL;
  out->mDNF_P.mNumRow = 1ULL;
  out->mDNF_P.mJc[0] = 0;
  out->mDNF_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dnf_v_x (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDNF_V_X.mX[0] = true;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_slf0 (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mSLF0.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_vpf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mVPF.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_vsf (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mVSF.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_freqs (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ic (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  out->mIC.mX[0] = 0.0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icr (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icr_im (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icr_id (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icr_il (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxicr (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxicr_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXICR_P.mNumCol = 1ULL;
  out->mDXICR_P.mNumRow = 0ULL;
  out->mDXICR_P.mJc[0] = 0;
  out->mDXICR_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddicr (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddicr_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDDICR_P.mNumCol = 0ULL;
  out->mDDICR_P.mNumRow = 0ULL;
  out->mDDICR_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_tduicr_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mTDUICR_P.mNumCol = 4ULL;
  out->mTDUICR_P.mNumRow = 0ULL;
  out->mTDUICR_P.mJc[0] = 0;
  out->mTDUICR_P.mJc[1] = 0;
  out->mTDUICR_P.mJc[2] = 0;
  out->mTDUICR_P.mJc[3] = 0;
  out->mTDUICR_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icrm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_icrm_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mICRM_P.mNumCol = 1ULL;
  out->mICRM_P.mNumRow = 0ULL;
  out->mICRM_P.mJc[0] = 0;
  out->mICRM_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxicrm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxicrm_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXICRM_P.mNumCol = 1ULL;
  out->mDXICRM_P.mNumRow = 0ULL;
  out->mDXICRM_P.mJc[0] = 0;
  out->mDXICRM_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddicrm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddicrm_p (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDDICRM_P.mNumCol = 0ULL;
  out->mDDICRM_P.mNumRow = 0ULL;
  out->mDDICRM_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_imin (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mIMIN.mX[0] = -pmf_get_inf();
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_imax (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mIMAX.mX[0] = pmf_get_inf();
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dimin (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dimax (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mcon (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mcon_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mMCON_P.mNumCol = 1ULL;
  out->mMCON_P.mNumRow = 1ULL;
  out->mMCON_P.mJc[0] = 0;
  out->mMCON_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mpar (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mpar_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mMPAR_P.mNumCol = 1ULL;
  out->mMPAR_P.mNumRow = 1ULL;
  out->mMPAR_P.mJc[0] = 0;
  out->mMPAR_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mnl (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mnl_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mMNL_P.mNumCol = 1ULL;
  out->mMNL_P.mNumRow = 1ULL;
  out->mMNL_P.mJc[0] = 0;
  out->mMNL_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxm_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXM_P.mNumCol = 1ULL;
  out->mDXM_P.mNumRow = 0ULL;
  out->mDXM_P.mJc[0] = 0;
  out->mDXM_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_ddm_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDDM_P.mNumCol = 0ULL;
  out->mDDM_P.mNumRow = 0ULL;
  out->mDDM_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dum (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dum_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDUM_P.mNumCol = 4ULL;
  out->mDUM_P.mNumRow = 0ULL;
  out->mDUM_P.mJc[0] = 0;
  out->mDUM_P.mJc[1] = 0;
  out->mDUM_P.mJc[2] = 0;
  out->mDUM_P.mJc[3] = 0;
  out->mDUM_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dtm_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDTM_P.mNumCol = 1ULL;
  out->mDTM_P.mNumRow = 0ULL;
  out->mDTM_P.mJc[0] = 0;
  out->mDTM_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dpm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dpm_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDPM_P.mNumCol = 0ULL;
  out->mDPM_P.mNumRow = 0ULL;
  out->mDPM_P.mJc[0] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_vmm (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mode (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  out->mMODE.mX[0ULL] = (int32_T)(t1->mU.mX[2ULL] > 0.0);
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dp_l (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dp_i (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dp_j (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dp_r (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qx (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qu (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qt (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_q1 (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qx_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mQX_P.mNumCol = 1ULL;
  out->mQX_P.mNumRow = 1ULL;
  out->mQX_P.mJc[0] = 0;
  out->mQX_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qu_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mQU_P.mNumCol = 4ULL;
  out->mQU_P.mNumRow = 1ULL;
  out->mQU_P.mJc[0] = 0;
  out->mQU_P.mJc[1] = 0;
  out->mQU_P.mJc[2] = 0;
  out->mQU_P.mJc[3] = 0;
  out->mQU_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_qt_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mQT_P.mNumCol = 1ULL;
  out->mQT_P.mNumRow = 1ULL;
  out->mQT_P.mJc[0] = 0;
  out->mQT_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_q1_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mQ1_P.mNumCol = 1ULL;
  out->mQ1_P.mNumRow = 1ULL;
  out->mQ1_P.mJc[0] = 0;
  out->mQ1_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_solverhits (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_var_tol (const NeDynamicSystem *sys, const
  NeDynamicSystemInput *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mVAR_TOL.mX[0] = 1.0E-9;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_eq_tol (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mEQ_TOL.mX[0] = 1.0E-9;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_lv (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  (void)t1;
  out->mLV.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_slv (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mSLV.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_nldv (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mNLDV.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_sclv (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mSCLV.mX[0] = false;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_y (const NeDynamicSystem *sys, const NeDynamicSystemInput *t3,
                     NeDsMethodOutput *out)
{
  out->mY.mX[1ULL] = -(t3->mU.mX[1ULL] - (-(t3->mX.mX[0ULL] - t3->mU.mX[0ULL])));
  out->mY.mX[0ULL] = -t3->mU.mX[3ULL];
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxy (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t3, NeDsMethodOutput *out)
{
  (void)t3;
  out->mDXY.mX[0ULL] = -1.0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dxy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDXY_P.mNumCol = 1ULL;
  out->mDXY_P.mNumRow = 2ULL;
  out->mDXY_P.mJc[0] = 0;
  out->mDXY_P.mJc[1] = 1;
  out->mDXY_P.mIr[0] = 1;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_duy (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t7, NeDsMethodOutput *out)
{
  (void)t7;
  out->mDUY.mX[1ULL] = -1.0;
  out->mDUY.mX[0ULL] = 1.0;
  out->mDUY.mX[2ULL] = -1.0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_duy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  static int32_T _cg_const_1[5] = { 0, 1, 2, 2, 3 };

  static int32_T _cg_const_2[3] = { 1, 1, 0 };

  (void)t1;
  out->mDUY_P.mNumCol = 4ULL;
  out->mDUY_P.mNumRow = 2ULL;
  out->mDUY_P.mJc[0] = _cg_const_1[0];
  out->mDUY_P.mJc[1] = _cg_const_1[1];
  out->mDUY_P.mJc[2] = _cg_const_1[2];
  out->mDUY_P.mJc[3] = _cg_const_1[3];
  out->mDUY_P.mJc[4] = _cg_const_1[4];
  out->mDUY_P.mIr[0] = _cg_const_2[0];
  out->mDUY_P.mIr[1] = _cg_const_2[1];
  out->mDUY_P.mIr[2] = _cg_const_2[2];
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mduy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mMDUY_P.mNumCol = 4ULL;
  out->mMDUY_P.mNumRow = 2ULL;
  out->mMDUY_P.mJc[0] = 0;
  out->mMDUY_P.mJc[1] = 0;
  out->mMDUY_P.mJc[2] = 0;
  out->mMDUY_P.mJc[3] = 0;
  out->mMDUY_P.mJc[4] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_mdxy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mMDXY_P.mNumCol = 1ULL;
  out->mMDXY_P.mNumRow = 2ULL;
  out->mMDXY_P.mJc[0] = 0;
  out->mMDXY_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_tduy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  static int32_T _cg_const_1[5] = { 0, 1, 2, 2, 3 };

  static int32_T _cg_const_2[3] = { 1, 1, 0 };

  (void)t1;
  out->mTDUY_P.mNumCol = 4ULL;
  out->mTDUY_P.mNumRow = 2ULL;
  out->mTDUY_P.mJc[0] = _cg_const_1[0];
  out->mTDUY_P.mJc[1] = _cg_const_1[1];
  out->mTDUY_P.mJc[2] = _cg_const_1[2];
  out->mTDUY_P.mJc[3] = _cg_const_1[3];
  out->mTDUY_P.mJc[4] = _cg_const_1[4];
  out->mTDUY_P.mIr[0] = _cg_const_2[0];
  out->mTDUY_P.mIr[1] = _cg_const_2[1];
  out->mTDUY_P.mIr[2] = _cg_const_2[2];
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_tdxy_p (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mTDXY_P.mNumCol = 1ULL;
  out->mTDXY_P.mNumRow = 2ULL;
  out->mTDXY_P.mJc[0] = 0;
  out->mTDXY_P.mJc[1] = 1;
  out->mTDXY_P.mIr[0] = 1;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dty (const NeDynamicSystem *sys, const NeDynamicSystemInput
  *t1, NeDsMethodOutput *out)
{
  (void)t1;
  (void)out;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_dty_p (const NeDynamicSystem *sys, const NeDynamicSystemInput *
  t1, NeDsMethodOutput *out)
{
  (void)t1;
  out->mDTY_P.mNumCol = 1ULL;
  out->mDTY_P.mNumRow = 2ULL;
  out->mDTY_P.mJc[0] = 0;
  out->mDTY_P.mJc[1] = 0;
  (void)sys;
  (void)out;
  return 0;
}

static int32_T ds_zc (const NeDynamicSystem *sys, const NeDynamicSystemInput *t1,
                      NeDsMethodOutput *out)
{
  out->mZC.mX[0ULL] = t1->mU.mX[2ULL];
  (void)sys;
  (void)out;
  return 0;
}
