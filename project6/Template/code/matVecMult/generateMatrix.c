
#include "stdlib.h"
#include "randFromTo.c"
#include <stdio.h>
/*  
	generateMatrix()
	n = number of columns (and rows) of the matrix
	numProc = number of processors
	start = starting point for generating rundom number
	end = final point for generating rundom number

	Output:
	A --> (n,n) matrix A
*/

double* generateMatrix(int n, double start, double end){
	double *A;
	double randNum;
	int i;


	A = (double*)calloc(n * n, sizeof(double));

	for (i=0; i< n*n; i++){
		randNum = randFromTo(start, end);
		A[i] = randNum;
	}
	return A;
}
