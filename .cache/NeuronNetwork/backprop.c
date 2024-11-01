#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "network.h"
#include "sigmoid.h"

//Calculate cost
double *cost_derivative(double *output_activations, double *y, size_t size)
{
	double *derivative = malloc(size * sizeof(double));
	for(size_t i = 0; i < size; i++)
	{
		derivative[i] = output_activations[i] - y[i];
	}
	return derivative;
}

void backprop(Network *net, double *x, double *y,
		double **nabla_b[], double ***nabla_w)
{
	//Initialize gradients
	size_t last_layer = net->num_layers - 1;

	for(size_t i = 0; i < last_layer; i++)
	{
		nabla_b[i] = malloc(net->sizes[i + 1] * sizeof(double*));
		nabla_w[i] = malloc(net->sizes[i + 1] * sizeof(double*));
		for (size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			nabla_b[i][j] = malloc(1 * sizeof(double));
			nabla_w[i][j] = malloc(net->sizes[i] * sizeof(double));
		}
	}

	//Feedforward
	double **activations = malloc(net->num_layers * sizeof(double *));
	double **zs = malloc((net->num_layers - 1) * sizeof(double *));

	//Initialize activation with input x
	activations[0] = malloc(net->sizes[0] * sizeof(double));
	for(size_t i = 0; i < net->sizes[0]; i++)
		activations[0][i] = x[i];

	for(size_t layer = 1; layer < net->num_layers; layer++)
	{
		zs[layer - 1] = malloc(net->sizes[layer] * sizeof(double));
		activations[layer] = malloc(net->sizes[layer]*sizeof(double));

        // Calcul of z = W * a + b
        // Initialize z
		for(size_t j = 0; j < net->sizes[layer]; j++)
		{
			zs[layer - 1][j] = 0.0;
			for(size_t k = 0; k < net->sizes[layer - 1]; k++)
				zs[layer - 1][j] +=
					net->weights[layer - 1][j][k]
					* activations[layer - 1][k];
            		zs[layer - 1][j] += net->biases[layer - 1][j];
			activations[layer][j] = sigmoid(zs[layer - 1][j]);
		}
	}

	//backward pass
	double *delta = malloc(net->sizes[net->num_layers - 1]*sizeof(double));
	double *output_activations = activations[net->num_layers - 1];

	// Calculate delta for output layer
	double *cost_deriv = cost_derivative(output_activations, y,
					net->sizes[net->num_layers - 1]);
	for(size_t j = 0; j < net->sizes[net->num_layers - 1]; j++)
        	delta[j] = cost_deriv[j]
        		* sigmoid_prime(zs[net->num_layers - 2][j]);
	free(cost_deriv);
    
	//Stock nabla_b & nabla_w for last layer
	for(size_t j = 0; j < net->sizes[net->num_layers - 1]; j++)
	{
		nabla_b[net->num_layers - 2][j][0] = delta[j];
		for(size_t k = 0; k < net->sizes[net->num_layers - 2]; k++)
			nabla_w[net->num_layers - 2][j][k] =
				delta[j] * activations[net->num_layers - 2][k];
	}

	//For the precedent layers
	for(size_t layer = 2; layer < net->num_layers; layer++)
	{
		for (size_t j = 0; j < net->sizes[net->num_layers-layer]; j++)
		{
			double sp = sigmoid_prime(
				zs[net->num_layers - layer - 1][j]);
			delta[j] = 0.0;
			for(size_t k = 0;
				k < net->sizes[net->num_layers - layer + 1];
				k++) delta[j] +=
                		net->weights[net->num_layers - layer][k][j]
                			* delta[k];
			delta[j] *= sp;

			nabla_b[net->num_layers - layer - 1][j][0] = delta[j];
			for(size_t k = 0;
				k < net->sizes[net->num_layers - layer];
				k++)
				nabla_w[net->num_layers - layer - 1][j][k] =
				delta[j] *
				activations[net->num_layers - layer - 1][k];
		}
	}

	for(size_t i = 1; i < net->num_layers; i++)
	{
		free(zs[i - 1]);
		free(activations[i]);
	}
	free(zs);
	free(activations[0]); // Libérer l'activation d'entrée
	free(activations);
	free(delta);
}
