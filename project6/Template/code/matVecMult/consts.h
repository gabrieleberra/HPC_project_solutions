#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <time.h>



/*
typedef struct
{
	int nRow;
	int nCol;
	MPI_Comm comm;
} Partition;
*/
/*
typedef struct
{
	int start;
	int end;
} Domain;
*/

/*
Partition createPartition(int size){

	Partition p;

	// Create dimension of cartesian with one column and p rows
	int gridSize[2] = {size, 1};
	MPI_Dims_create(size, 2, gridSize);
	p.nRow = gridSize[0];
	p.nCol = gridSize[1];

	// Create non periodic cartesian
	int periods[2] = {0,0};
	MPI_Cart_create(MPI_COMM_WORLD, 2, gridSize, periods, 0, &p.comm);

	return p;
}
*/

/*
Domain createDomain(int my_rank, int size, int n){
	
	Domain d;

	d.start = my_rank*n*(n/size);
	d.end = n*(n/size) + (d.start-1);

	return d;
}
*/

/*  
	generateMatrix()
	n = number of columns (and rows) of the matrix
	numProc = number of processors
	start = starting point for generating rundom number
	end = final point for generating rundom number

	Output:
	A --> (n,n) matrix A
*/
double *generateMatrix(int n, int size) 
	{   
	double *A;
	double randNum;
	int i;

	A = (double*)calloc(n * (n/size), sizeof(double));
	srand(time(NULL));
	
	for (i=0; i< n*(n/size); i++){
		randNum = rand();
		A[i] = randNum;
	}

	return A;
}


/* 
	norm()
	x = vector to be normalized

	Output:
	x --> normalized vector
*/
double *norm(double *x, int n)
{
	int i;
	double length;

	length = 0;
	for (i = 0; i < n; i++){
		length += x[i] * x[i];
	}
	
	//printf("%f\n",length );
	length = sqrt(length);

	for (i = 0; i < n; i++){
		x[i] = x[i]/length;
	}

	//for (int i = 0; i < n; i++){
	//	printf("%f\n",x[i] );
	//}

	return x;
}


double *matVec(double *x, double *A, int size, int n, int my_rank)
{
	int i,j, ierr;
	double  sum, res[n/size];

	ierr = MPI_Bcast(x, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	if (ierr != MPI_SUCCESS){
		printf("Error in MPI_Bcast\n");
		MPI_Abort(MPI_COMM_WORLD, 3);
	}

	for (i = 0; i<(n/size); i++){
		sum = 0;
		for (j = (i*n); j<n*(i+1); j++){
			sum += A[j] * x[j-(i*n)];
		}
		res[i] = sum;
	}
	
	if(my_rank==0){
		ierr = MPI_Gather(&res, (n/size), MPI_DOUBLE, x, (n/size), MPI_DOUBLE, 0, MPI_COMM_WORLD);

		if (ierr != MPI_SUCCESS){
			printf("Error in MPI_Gather\n");
			MPI_Abort(MPI_COMM_WORLD, 4);
		}	
	}else{
		MPI_Gather(&res, (n/size), MPI_DOUBLE, NULL, 0, MPI_DOUBLE, 0, MPI_COMM_WORLD);
	}

	return x;
}


/* generate a random floating point number from min to max */
double randFromTo(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}



/*
	generateVector()
	n = number of components of the vector

	Output: 
	x --> a vector 
*/
double *generateVector(int n)
{
	double *x;
	int i; 
	double randNum;
	x = (double*)calloc(n, sizeof(double));

	srand(time(NULL));

	for (i = 0; i < n; i++){
		randNum = rand();
		x[i] = randNum;
	}
	return x;
}



double *powerMethod(double *x, double *A, int size, int n, int my_rank)
{
	x = norm(x, n);

	x = matVec(x, A, size, n, my_rank);

	return x;
}








