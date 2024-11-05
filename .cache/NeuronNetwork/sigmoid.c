#include <math.h>

double sigmoid(double z)
{
	return 1.0/(1.0+exp(-z));
}

double sigmoid_prime(double z)
{
	double s = sigmoid(z);
	return s*(1-s);
}
