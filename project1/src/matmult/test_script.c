// test script
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sizeTest 5


void mat_trans (double* pSource, double* pTrans, int m, int n) {
	int i, j;

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			pTrans[i + j * m] = pSource[i * n + j];
		}
	}
}


void square_dgemm (int n, double* A, double* B, double* C) {
	// TODO: Implement optimization of the block size

	// TODO: Review the code by taking into account the indexing

	// defining the number of blocks
	int blockSize, irregSize, irregFlag, s, s_i, s_j, s_k, N;

	blockSize = 2; // chosen block size
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

int main() {
	int totSize = sizeTest * sizeTest;

	double AA[sizeTest * sizeTest] = {
		1, 2, 1, 2, 3,
		2, 3, 1, 4, 1,
		3, 2, 1, 0, 2,
		4, 2, 2, 1, 1,
		1, 3, 2, 2, 1
	};

	double BB[sizeTest * sizeTest] = {
		1, 3, 4, 2, 1,
		1, 1, 3, 2, 0,
		1, 3, 4, 1, 1,
		1, 2, 2, 1, 0,
		1, 1, 2, 2, 1
	};


	double* A = (double*) calloc (totSize, sizeof(double));
	double* B = (double*) calloc (totSize, sizeof(double));
	double* C = (double*) calloc (totSize, sizeof(double));

	memcpy(A, AA, totSize * sizeof(double));
	memcpy(B, BB, totSize * sizeof(double));

	square_dgemm(sizeTest, A, B, C);

	printf("\n");
	for (int i = 0; i < sizeTest; i++) {
		printf("\n");
		for (int j = 0; j < sizeTest; j++) {
			printf("%f \t", C[sizeTest * i + j]);
		}
	}
	printf("\n");
	printf("\n");


	free(A);
	free(B);

	return 0;
}