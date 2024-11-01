#include <stdlib.h>
#include <stdio.h>
#include <math.h> //Remeber '-lm' in gcc
#include "network.h"
#include "sigmoid.h"

void matrix_vector_dot(double **matrix, double *vector,
			double *result, size_t rows, size_t cols)
{
	for(size_t i = 0; i < rows; i++)
	{
		result[i] = 0.0;
		for (size_t j = 0; j < cols; j++)
			result[i] += matrix[i][j] * vector[j];
	}
}

void add_vect(double *A, double *B, size_t size)
{
    for(size_t i = 0; i < size; i++)
        A[i] += B[i];
}

double *feedforward(Network *net, double *input)
{
	double *activation = (double *)malloc(net->sizes[0] * sizeof(double));

	for(size_t i = 0; i < net->sizes[0]; i++)
		activation[i] = input[i];

	for(size_t layer = 1; layer < net->num_layers; layer++)
	{
		double *z = malloc(net->sizes[layer] * sizeof(double));
		double *next_activation = 
			malloc(net->sizes[layer] * sizeof(double));

		matrix_vector_dot(net->weights[layer - 1], activation, z,
			net->sizes[layer], net->sizes[layer - 1]);

		for(size_t j = 0; j < net->sizes[layer]; j++)
		{
			z[j] += net->biases[layer - 1][j];
			next_activation[j] = sigmoid(z[j]);
		}

		free(z);
		free(activation);
		activation = next_activation;
	}

	return activation;
}
