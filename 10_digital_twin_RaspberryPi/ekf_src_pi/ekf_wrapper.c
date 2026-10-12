#include "EKFSim_pi.h"

void ekf_init_wrapper(void) {
    EKFSim_pi_initialize();
}

void ekf_step_wrapper(double I, double V, double *soc_out, double *up_out, double *p_upd_out) {
    EKFSim_pi_U.tuvar   = I;
    EKFSim_pi_U.UL_Real = V;
    EKFSim_pi_step();
    *soc_out   = EKFSim_pi_B.SOC_upd;
    *up_out    = EKFSim_pi_B.Up_upd;
    *p_upd_out = EKFSim_pi_B.P_upd[0];
}

void ekf_terminate_wrapper(void) {
    EKFSim_pi_terminate();
}
