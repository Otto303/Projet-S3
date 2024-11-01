#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Remeber '-lm' in gcc

//return random following Gaussian distributions
//with mean 0 and standard deviation 1
double randn()
{
	double u = ((double) rand() / RAND_MAX); //Random between 0 and 1
	double v = ((double) rand() / RAND_MAX);
	double z = sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
	return z;
}

typedef struct {
	size_t num_layers;

	//number of neurons in respective layer
	size_t *sizes;

	//each element is list of biases between this layer & the next
	double **biases;

	//each element is matrix size(layer) lines & size(next_layer) columns
	double ***weights;
} Network;

Network* init_network(int *sizes, size_t num_layers)
{
	Network *net = (Network*)malloc(sizeof(Network));
	net->num_layers = num_layers;

	net->sizes = malloc(num_layers * sizeof(size_t));
	for(size_t i = 0; i < num_layers; i++)
		net->sizes[i] = sizes[i];

	//Initialize biases
	net->biases = malloc((num_layers - 1) * sizeof(double*));
	for(size_t i = 0; i < num_layers - 1; i++)
	{
		int y = sizes[i + 1];
		net->biases[i] = malloc(y * sizeof(double));
		for(int j = 0; j < y; j++)
			net->biases[i][j] = randn();
	}

	//Initialize weights
	net->weights = malloc((num_layers - 1) * sizeof(double**));
	for(size_t i = 0; i < num_layers - 1; i++)
	{
		size_t x = sizes[i];
		size_t y = sizes[i + 1];
		net->weights[i] = malloc(y * sizeof(double*));
		for(size_t j = 0; j < y; j++)
		{
			net->weights[i][j] = malloc(x * sizeof(double));
			for(size_t k = 0; k < x; k++)
				net->weights[i][j][k] = randn();
		}
	}

	return net;
}

void free_network(Network *net)
{
	for(size_t i = 0; i < net->num_layers - 1; i++)
		free(net->biases[i]);

	free(net->biases);

	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		for (size_t j = 0; j < net->sizes[i + 1]; j++)
			free(net->weights[i][j]);
		free(net->weights[i]);
	}

	free(net->weights);
	free(net->sizes);
	free(net);
}
