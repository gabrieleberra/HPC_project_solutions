/*
    Please include compiler name below (you may also include any other modules you would like to be loaded)

COMPILER= gnu

    Please include All compiler flags and libraries as you want them run. You can simply copy this over from the Makefile's first few lines

CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm

*/
#include <stdio.h>

const char* dgemm_desc = "Naive, three-loop dgemm.";

/* This routine performs a dgemm operation
 * C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values. */


void square_dgemm (int n, double* A, double* B, double* C) {
  // TODO: Implement optimization of the block size

  // TODO: Review the code by taking into account the indexing

  // defining the number of blocks
  int s = 50;
  int N = n / s;

  for (int ib = 0; ib < N; ib++) {
    //printf("%d", ib);
    for (int jb = 0; jb < N; jb++) {
      for (int kb = 0; kb < N; kb++) {
        /* For each row i of A */
        for (int i = 0; i < s; i++)
          /* For each column j of B */
          for (int j = 0; j < s; j++) {
            /* Compute C(i,j) in column-major format */
            double cij = C[i + (j * n) + (ib * s) + jb * (s * n)];
            for (int k = 0; k < s; k++) {
              cij += A[i + (k * n) + (ib * s) + kb * (s * n)] * B[k + (j * n) + (kb * s) + jb * (s * n)];

              //if (jb == 1) {
              //printf("i = %d, j = %d, k = %d\n\n", i, j, k);
              //printf("A(%d) = %f\n", i + (k * n) + (ib * s) + kb * (s * n), A[i + (k * n) + (ib * s) + kb * (s * n)]);
              //printf("B(%d) = %f\n", k + (j * n) + (kb * s) + jb * (s * n), B[k + (j * n) + (kb * s) + jb * (s * n)]);
              //printf("C(%d) = %f\n\n", i + (j * n) + (ib * s) + jb * (s * n), cij);
              //}
            }
            C[i + (j * n) + (ib * s) + jb * (s * n)] = cij;
            //printf("----------------------------\n");
          }
      }
    }
  }
}



































