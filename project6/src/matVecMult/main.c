#include "consts.h"
#include "hpc-power.h"
#include "hpc-power.c"

#include <mpi.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// run with mpirun -np 4 ./mian n k

int main(int argc, char* argv[])
{
	// Initialize MPI 
	MPI_Init(&argc, &argv);
	int my_rank, size, n, k;

	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	// Check if the number of proessors used is correct 
	if (my_rank == 0){
		int flag = 1;
		if (size == 1 || size == 4 || size == 8 || size == 16 || size == 32 || size == 64){
			flag = 0;
		}
		if(flag){
			printf("Error: number of processors must be equal to {1,4,8,16,32,64}! \n");
			MPI_Abort(MPI_COMM_WORLD, 1);
		}
	}

	// Check if the number of processor is a perfect divisor of n 
	n = atoi(argv[1]);
	if (n % size != 0){
		printf("Error: the number of processors must be a perfect divisor of n! \n");
		MPI_Abort(MPI_COMM_WORLD, 2);	
	}

	//Partition p = createPartition(size);
	Domain d = createDomain(my_rank, size, n);

	//if(my_rank == 0){
	//	printf("rankID: %i \t Start: %i \t End: %i \n", my_rank, d.start, d.end);
	//}

	double *A = generateMatrix(n, size, d, my_rank);
	
	//if (my_rank == 2){
	//	for (int i =0; i < 16; i++){
	//		printf("%f \n",A[i]);
	//	}
	//	printf("\n");
	//}
	
	//if(my_rank==0){
	double *x = generateVector(n, my_rank);
	//}

	//if (my_rank == 0){
	//	for (int i = 0; i<n; i++){
	//		printf("%f \n",x[i] );
	//	}
	//}

	k = atoi(argv[2]);

	//if(my_rank==0){
	double initTime = hpc_timer();
	//}
	
	for (int i = 0; i< k; i++){
		x = powerMethod(x, A, size, n, my_rank);
	}


	if(my_rank==0){
		double finalTime = hpc_timer();
		double time = finalTime - initTime;
		printf("%f\n",time);
	}


	//if (my_rank == 0){
	//	int res = hpc_verify(x,  n, time);
	//	printf("%i\n", res);
	//}
		

	//if (my_rank==0){
	//	for (int i =0 ; i<8;i++){
	//		printf("%f \n",x[i] );
	//	}
	//}
	
	free(A);
	free(x);
	MPI_Finalize();
	return 0;
}





