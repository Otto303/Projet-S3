// Activation function

double ReLu(double z)
{
	if (z < 0) return 0;
	else return z;
}

double ReLu_prime(double z)
{
	if (z < 0) return 0;
	else return 1;
}
