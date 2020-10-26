// #include <omp.h>
#include <iostream>
#include "walltime.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>

#define NUM_ITERATIONS 100 // era 100

// Example benchmarks
// 0.008s ~0.8MB
#define N 100000
// 0.1s ~8MB
//#define N 1000000
// 1.1s ~80MB
//#define N 10000000
// 13s ~800MB
//#define N 100000000
// 127s 16GB
//#define N 1000000000
#define EPSILON 0.1


using namespace std;

int main() {
    for (int j = 1; j <= 24; j++) {

        int myId, numTdreads;
        double time_serial, time_start = 0.0;
        long double dotProduct;
        double *a, *b;

        // Allocate memory for the vectors as 1-D arrays
        a = new double[N];
        b = new double[N];

        // Initialize the vectors with some values
        for (int i = 0; i < N; i++) {
            a[i] = i;
            b[i] = i / 10.0;
        }



        long double alpha = 0;
        // serial execution
        // Note that we do extra iterations to reduce relative timing overhead
        time_start = wall_time();
        for ( int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
            alpha = 0.0;
            for ( int i = 0; i < N; i ++) {
                alpha += a[i] * b[i];
            }
        }
        time_serial = wall_time() - time_start;
        cout << "Serial execution time = " << time_serial << " sec" << endl;




        long double alpha_parallel = 0;
        double time_red = 0;
        double time_critical = 0;

        //   TODO: Write parallel version (2 ways!)
        //   i.  Using reduction pragma
        //   ii. Using  critical pragma



        double time_start_red = 0.0; //list = 0.0;
        time_start_red = wall_time();
        #pragma omp parallel for reduction(+: alpha_parallel) num_threads(j)
        for ( int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
            alpha_parallel = 0.0;
            for ( int i = 0; i < N; i ++) {
                alpha_parallel += a[i] * b[i];
            }
        }
        time_red = wall_time() - time_start_red;


        long double alpha_private = 0;
        double time_start_critical = 0.0;
        #pragma omp barrier


        time_start_critical = wall_time();
        #pragma omp parallel firstprivate(alpha_private) num_threads(j)
        for ( int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
            alpha_parallel = 0.0;
            alpha_private = 0.0;
            #pragma omp for //firstprivate(alpha_private)
            for ( int i = 0; i < N; i ++) {
                //#pragma omp critical
                //alpha_parallel += a[i] * b[i];
                alpha_private += a[i] * b[i];
            }
            #pragma omp critical
            alpha_parallel += alpha_private;
        }
        time_critical = wall_time() - time_start_critical;



        if ( (fabs(alpha_parallel - alpha) / fabs(alpha_parallel)) > EPSILON) {
            cout << "parallel reduction: " << alpha_parallel << " serial :" << alpha << "\n";
            cerr << "Alpha not yet implemented correctly!\n";
            exit(1);
        }


        cout << "Parallel dot product = " << alpha_parallel
             << " time using reduction method = " << time_red
             << " sec, time using critical method " << time_critical
             << " sec" << endl;

        // De-allocate memory
        delete [] a;
        delete [] b;
    }
    return 0;
}
