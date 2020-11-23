//#include "consts.h"
//#include <mpi.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>



int main(void){
	srand(time(0));
	for(int i = 0 ; i<4; i++){
		printf("%d\n",rand() );
	}
	return 0;
}



/*
int main(){
	double *A = generateMatrix(6);

	for (int i = 0; i < 6; i++) {
    	printf("\n");
    	for (int j = 0; j < 6; j++) {
       		printf("%f \t", A[6 * i + j]);
    	}
	}
	printf("\n\n");

	double *x = generateVector(6);

	for (int i = 0; i < 6; i++) {
    	printf("%f \t", x[i]);
	}
	printf("\n");


	int size = 6;
	if (size != 1 || size != 4 || size != 8 || size != 16 || size != 32 || size != 64){
		printf("Error: number of processors must be equal to {1,4,8,16,32,64}! \n");
	}


}
*/




