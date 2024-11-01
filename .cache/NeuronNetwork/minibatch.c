#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "network.h"
#include "backprop.h"

//Initialize an array of zeros
double* zeros(size_t size)
{
	double *array = malloc(size * sizeof(double));
	for(size_t i = 0; i < size; i++)
		array[i] = 0.0;
	return array;
}

//Initialize a matrix of zeros
double** matrix_zeros(size_t rows, size_t cols)
{
	double **matrix = malloc(rows * sizeof(double*));
	for(size_t i = 0; i < rows; i++)
		matrix[i] = zeros(cols);
	return matrix;
}

void update_mini_batch(Network *net, Data *mini_batch,
			size_t mini_batch_size, double eta)
{
	double **nabla_b[net->num_layers - 1];
	double **nabla_w[net->num_layers - 1];

	//Initialize nabla_b & nabla_w with zeros
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		nabla_b[i] = matrix_zeros(net->sizes[i + 1], 1);
		nabla_w[i] = matrix_zeros(net->sizes[i + 1], net->sizes[i]);
	}

	//Calculate gradients for each (x, y) in mini_batch
	for(size_t i = 0; i < mini_batch_size; i++)
	{
		double **delta_nabla_b[net->num_layers - 1];
		double **delta_nabla_w[net->num_layers - 1];

		//Call backprop to calculate delta_nabla_b & delta_nabla_w
		backprop(net, mini_batch[i].x, mini_batch[i].y,
				delta_nabla_b, delta_nabla_w);

		//Update nabla_b & nabla_w
		for(size_t j = 0; j < net->num_layers - 1; j++)
		{
			for(size_t k = 0; k < net->sizes[j + 1]; k++)
			{
				nabla_b[j][k][0] += delta_nabla_b[j][k][0];
				for(size_t l = 0; l < net->sizes[j]; l++)
					nabla_w[j][k][l] +=
						delta_nabla_w[j][k][l];
            		}
        	}

		//Free memory of delta_nabla_b & delta_nabla_w
		for(size_t j = 0; j < net->num_layers - 1; j++)
		{
			for(size_t k = 0; k < net->sizes[j + 1]; k++)
			{
				free(delta_nabla_b[j][k]);
				free(delta_nabla_w[j][k]);
			}
			free(delta_nabla_b[j]);
			free(delta_nabla_w[j]);
		}
	}

	//Update weights & biases
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			net->biases[i][j] -= (eta / mini_batch_size)
						* nabla_b[i][j][0];
			for(size_t k = 0; k < net->sizes[i]; k++)
				net->weights[i][j][k] -=
					(eta / mini_batch_size)
						* nabla_w[i][j][k];
		}
	}

	//Free memory of nabla_b & nabla_w
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			free(nabla_b[i][j]);
			free(nabla_w[i][j]);
		}
		free(nabla_b[i]);
		free(nabla_w[i]);
	}
}
