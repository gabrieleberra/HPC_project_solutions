/*
	generateVector()
	n = number of components of the vector

	Output: 
	x --> a vector 
*/

double* generateVector(int n){
	double *x;
	int i, randNum;

	x = (double*)calloc(n, sizeof(double));

	for (i = 0; i < n; i++){
		randNum = randFromTo(start, end);
		x[i] = randNum;
	}
	return x;
}