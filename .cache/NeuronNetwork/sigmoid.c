#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Remeber '-lm' in gcc

double sigmoid(double z)
{
	return 1/(1.0+exp(-z));
}

double sigmoid_prime(double z)
{
	double s = sigmoid(z);
	return s*(1-s);
}
