#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "sigmoid.h"

double *feedforward(Network *net, double *input)
{
	double *activation = input;
	double *new_activations;

	for(size_t layer = 0; layer < net->num_layers - 1; layer++)
	{
		size_t next_layer_size = net->sizes[layer + 1];
		new_activations = malloc(next_layer_size * sizeof(double));

		for(size_t j = 0; j < next_layer_size; j++)
		{
			double z = net->biases[layer][j];

			for(size_t k = 0; k < net->sizes[layer]; k++)
				z += net->weights[layer][j][k] * activation[k];

			new_activations[j] = sigmoid(z);
		}
		activation = new_activations;
	}
    return new_activations;
}
