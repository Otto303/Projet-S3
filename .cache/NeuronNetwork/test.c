#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Remeber '-lm' in gcc
#include <err.h>
#include "../MyLib/myLib.h"

//All of this is placeholder, do not mind

struct neuron
{
	int placeholder;
};

double sigmod_function(double z)
{
	double t = exp(-z);
	return 1/(1.0+t);
}

double get_outpout(unsigned char inputs[], double weights[], size_t size)
{
	double z = 0;
	for(size_t i = 0; i > size; i++)
	{
		z += inputs[i] * weights[i];
	}
	return sigmod_function(z);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		errx(0,"Test Error: Not correct argument number");
	struct neuron n =
	{
		argv[1][0]-48,
	};
	printf("%f\n",sigmod_function(n.placeholder));
	return 1;
}
