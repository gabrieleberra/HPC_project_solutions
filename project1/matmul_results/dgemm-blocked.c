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
  int blockSize, irregSize, irregFlag, s, s_i, s_j, s_k, N;

  blockSize = 19; // chosen block size (best 19)
  s = blockSize;
  s_i = blockSize;
  s_j = blockSize;
  s_k = blockSize;


  if (n % blockSize == 0) {
    N = n / blockSize;
    irregSize = blockSize;
    irregFlag = 0;
  } else {
    irregFlag = 1;
    irregSize = n % blockSize; // irregular size of the last block
    N = (n - irregSize) / blockSize + 1; // adding one more block in each dimension
  }

  //printf("%d\n", irregSize);
  for (int ib = 0; ib < N; ib++) {
    //printf("%d", ib);
    for (int jb = 0; jb < N; jb++) {

      if (irregFlag) {
        if (jb < N - 1 && ib < N - 1) {
          s_i = blockSize;
          s_j = blockSize;
        } else if (jb == N - 1 && ib < N - 1) {
          s_i = blockSize;
          s_j = irregSize;
        } else if (ib == N - 1 && jb < N - 1) {
          s_i = irregSize;
          s_j = blockSize;
        } else {
          s_i = irregSize;
          s_j = irregSize;
        }
      }

      for (int kb = 0; kb < N; kb++) {
        if (kb == N - 1) {
          s_k = irregSize;
        } else {
          s_k = blockSize;
        }
        /* For each row i of A */
        for (int i = 0; i < s_i; i++)
          /* For each column j of B */
          for (int j = 0; j < s_j; j++) {
            /* Compute C(i,j) in column-major format */
            double cij = C[i + (j * n) + (ib * s) + jb * (s * n)];
            for (int k = 0; k < s_k; k++) {
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




































