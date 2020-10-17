// #include <omp.h>
#include <iostream>
#include "walltime.h"
#include <stdlib.h>
#include <unistd.h>
#include <omp.h>
#include <iomanip>

#define NUM_ITERATIONS 100

// Example benchmarks
// 0.03s ~0.8MB
// #define NMAX 100
// #define NMAX 100000
// 0.3s ~8MB
//#define NMAX 1000000
// 3.s ~80MB
//#define NMAX 10000000
// 30s ~800MB
// #define NMAX 100000000

// compile with g++ -O3 -fopenmp dotProduct.cpp -o dot

//#define TN 8

// TODO:
// 1. scalar product in parallel
//   i. Using reduction pragma
//   ii. Using critical pragma

using namespace std;

int main(int argc, char** argv) {

	/**
	 * Define input variables
	 */
	if (argc != 4) {
		cout << "usage: " << argv[0] << " THREAD_COUNT(INT) VECTOR_SIZE(INT) DETAIL_OUPUT(BOOL)" << endl;
		exit(1);
	}

	int TN  = int( strtol(argv[1], NULL, 0) );
	int NMAX  = int( strtol(argv[2], NULL, 0) );
	int DETAILOUT  = int( strtol(argv[3], NULL, 0) );

	/**
	 * Set active threads
	 */
	//omp_set_num_threads(TN);

	int myId, numTdreads;
	double time_serial, time_start = 0.0;
	long double dotProduct;
	long double *a, *b;

	cout << fixed;
	cout << setprecision(3);

	// Allocate memory for the vectors as 1-D arrays
	a = new long double[NMAX];
	b = new long double[NMAX];

	// Initialize the vectors with some values
	for (int i = 0; i < NMAX; i++) {
		a[i] = i / 1.0;
		b[i] = i / 10.0;
	}

	long double alpha = 0.0;

	// serial execution
	// Note that we do extra iterations to reduce relative timing overhead
	time_start = wall_time();
	for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
		for (int i = 0; i < NMAX; i ++) {
			alpha += a[i] * b[i];
		}
	}
	time_serial = wall_time() - time_start;


	long double alpha_critical = 0.0;
	long double alpha_red = 0.0;
	double time_red = 0.0;
	double time_critical = 0.0;

	/**
	 * Parallelization with reduction clause
	 */

	time_start = wall_time();
	#pragma omp barrier
	#pragma omp parallel for reduction(+:alpha_red)
	for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
		for (int i = 0; i < NMAX; i ++) {
			alpha_red += a[i] * b[i];
		}
	}
	time_red = wall_time() - time_start;


	/**
	 * Parallelization with critical clause
	 */
	time_start = wall_time();
	long double alpha_parallel_local = 0.0;

	#pragma omp barrier
	#pragma omp parallel firstprivate(alpha_parallel_local)
	{
		#pragma omp for
		for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
			for (int i = 0; i < NMAX; i ++) {
				alpha_parallel_local += a[i] * b[i];
			}
		}

		#pragma omp critical
		alpha_critical += alpha_parallel_local;
	}
	time_critical = wall_time() - time_start;



	/**
	 * Relative Error detections
	 */

	const long double e = 10e-13;

	long double errRed = (alpha - alpha_red);
	long double errCrit = (alpha - alpha_critical);

	long double relErrRed  =  errRed > 0 ? errRed / alpha  : -1 * errRed / alpha ;
	long double relErrCrit = errCrit > 0 ? errCrit / alpha : -1 * errCrit / alpha;

	int errPass = (relErrRed < e && relErrCrit < e) ? 1 : 0;

	if (!errPass) throw invalid_argument("Error Dont Prodct Not Working !");


	if (DETAILOUT) {
		cout << endl;
		cout << "-------- Vector Size:" << NMAX << " --------" << endl;
		cout << "Critial dot product         = " << alpha_critical << endl;
		cout << "Critial error               = " << errCrit << endl;
		cout << "Reduc dot product           = " << alpha_red << endl;
		cout << "Reduc error                 = " << errRed << endl;
		cout << "Serial dot product          = " << alpha << endl;

		cout << endl;
		cout << "Error Pass:                 = " << errPass << endl;
		cout << "RelError Red                = " << relErrRed << endl;
		cout << "RelError Crit               = " << relErrCrit << endl;

		cout << endl;
		cout << "Time Reduc                  = " << time_red << endl;
		cout << "Time Critial                = " << time_critical << endl;
		cout << "Time Serial                 = " << time_serial << endl;
		cout << endl;
		cout << "Time Reduc X-up             = " << time_serial / time_red << endl;
		cout << "Time Critial X-up           = " << time_serial / time_critical << endl;
	} else {
		cout << NMAX << "," << time_serial << "," << time_critical << "," << time_red << endl;
	}

	// De-allocate memory
	delete [] a;
	delete [] b;

	return 0;
}
