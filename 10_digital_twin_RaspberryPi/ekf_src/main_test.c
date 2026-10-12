#include <stdio.h>
#include "EKFSim.h"

int main(void) {
    FILE *fin = fopen("test_input.csv", "r");
    FILE *fout = fopen("test_output.csv", "w");
    if (!fin) { printf("Erreur: test_input.csv introuvable\n"); return 1; }
    if (!fout) { printf("Erreur creation test_output.csv\n"); return 1; }

    EKFSim_initialize();

    double courant, tension;
    fprintf(fout, "SOC_upd,Up_upd,P_upd0,P_upd1,P_upd2,P_upd3\n");

    while (fscanf(fin, "%lf,%lf", &courant, &tension) == 2) {
        EKFSim_U.tuvar   = courant;
        EKFSim_U.UL_Real = tension;

        EKFSim_step();

        fprintf(fout, "%f,%f,%f,%f,%f,%f\n",
            EKFSim_B.SOC_upd,
            EKFSim_B.Up_upd,
            EKFSim_B.P_upd[0], EKFSim_B.P_upd[1],
            EKFSim_B.P_upd[2], EKFSim_B.P_upd[3]);
    }

    fclose(fin);
    fclose(fout);
    EKFSim_terminate();
    printf("Termine. Voir test_output.csv\n");
    return 0;
}