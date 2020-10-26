# include <stdlib.h>
# include <math.h>
# include "walltime.h"
# include <omp.h>


int main ( int argc, char *argv[] ) {
    int N = 2000000000;
    double up = 1.00000001;
    double Sn = 1.00000001;
    double Sn_loop = 1.00000001;
    int n, n_new;
    n_new = -2;

    /* allocate memory for the recursion */
    double* opt = (double*) malloc ((N + 1) * sizeof(double));


    if (opt == NULL)  die ("failed to allocate problem size");

    double time_start = wall_time();


    #pragma omp parallel private(n) firstprivate(n_new)
    {
        #pragma omp for lastprivate(Sn)
        for (n = 0; n <= N; ++n) {
            if (n_new != n - 1) {
                Sn = Sn_loop * pow(up, n);
            } else {
                Sn *= up;
            }
            opt[n] = Sn;
            n_new = n;
        }

    }
    Sn *= up;

    printf("Parallel RunTime   :  %f seconds\n", wall_time() - time_start);
    printf("Final Result Sn    :  %.17g \n", Sn);


    double temp = 0.0;
    for (n = 0; n <= N; ++n) {
        temp +=  opt[n] * opt[n];
    }
    printf("Result ||opt||^2_2 :  %f\n", temp / (double) N);
    printf ( "\n" );

    return 0;
}













