/* 
	norm()
	x = vector to be normalized

	Output:
	x --> normalized vector
*/

double norm(double *x){
	size = sizeof(x);
	int i, length;

	length = 0;
	for (i = 0; i < size; i++){
		length += x[i] * x[i];
	}
	length = sqrt(length);

	for (i = 0; i < size; i++){
		x[i] = x[i]/length;
	}

	return x;
}


