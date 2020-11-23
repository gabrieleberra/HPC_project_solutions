#include <stdio.h>
#include <stdlib.h>

/* generate a random floating point number from min to max */
double randFromTo(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}
