#include "EKFSim.h"

void ekf_init_wrapper(void) {
    EKFSim_initialize();
}

void ekf_step_wrapper(double I, double V, double *soc_out, double *up_out, double *p_upd_out) {
    EKFSim_U.tuvar   = I;
    EKFSim_U.UL_Real = V;
    EKFSim_step();
    *soc_out   = EKFSim_B.SOC_upd;
    *up_out    = EKFSim_B.Up_upd;
    *p_upd_out = EKFSim_B.P_upd[0];
}

void ekf_terminate_wrapper(void) {
    EKFSim_terminate();
}
