#include <stdlib.h>
#include <math.h>

double xavier(double inp, double out) //create random with xavier initialization
{
	double x = sqrt(6.0/(inp + out)); //for the varience
	double nb = (rand() / (double)RAND_MAX) * 2 * x - x; //create random between -x & x
	return nb;
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

Network* init_network(size_t *sizes, size_t num_layers)
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
		{
			net->biases[i][j] = 0;
		}
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
				net->weights[i][j][k] = xavier(sizes[0],sizes[num_layers - 1]);
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
