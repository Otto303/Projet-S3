//#include <stdio.h>
//#include <stdlib.h>
#include <math.h>

double sigmoid(double z)
{
	return 1.0/(1.0+exp(-z));
	//return fmax(0,z);
}

double sigmoid_prime(double z)
{
	double s = sigmoid(z);
	return s*(1-s);
	//return fmax(0,z)/z;
}
/*
int main(int argc, char *argv[])
{
	double x = (double)atoi(argv[1]);
	printf("%f\n%f\n",sigmoid(x),sigmoid_prime(x));
	return 0;
}
*/
