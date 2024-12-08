#include <stdlib.h>
#include <stdio.h>
#include "network.h"
#include "ReLu.h"

double *feedforward(Network *net, double *input)
{
	double *activation = malloc(net->sizes[0] * sizeof(double));
	for (size_t i = 0; i < net->sizes[0]; i++) activation[i] = input[i];

	for(size_t layer = 0; layer < net->num_layers - 1; layer++)
	{
		double *new_activation =
			calloc(net->sizes[layer+1],sizeof(double));
		for(size_t j = 0; j < net->sizes[layer+1]; j++)
		{
			double z = net->biases[layer][j];

			for(size_t k = 0; k < net->sizes[layer]; k++)
				z += net->weights[layer][j][k] * activation[k];

			new_activation[j] = ReLu(z);
		}

		free(activation);
		activation = calloc(net->sizes[layer+1], sizeof(double));
		for(size_t j = 0; j < net->sizes[layer+1]; j++)
			activation[j] = new_activation[j];
		free(new_activation);
		new_activation = NULL;
	}
	return activation;
}
