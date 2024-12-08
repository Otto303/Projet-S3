#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "network.h"

//Save the given network in the given file
unsigned char save_network(Network *net, const char *filename)
{
	printf("Saving network...\n");
	
	//Load file
	FILE *file = fopen(filename, "w");
	if(file == NULL)
	{
		printf("Unable to save Network: ");
		printf("file \"%s\" not found\n",filename);
		return 0;
	}

	//Save number of layer and size for each
	fprintf(file, "%zu\n", net->num_layers);
	for(size_t i = 0; i < net->num_layers; i++)
		fprintf(file, "%zu ", net->sizes[i]);
	fprintf(file, "\n");

	//Save biases
	for(size_t i = 0; i < net->num_layers - 1; i++)
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
			fprintf(file, "%lf\n", net->biases[i][j]);

	//Save weights
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			for(size_t k = 0; k < net->sizes[i]; k++)
				fprintf(file, "%lf ", net->weights[i][j][k]);
			fprintf(file, "\n");
		}
	}

	fclose(file);

	printf("Network saved\n");
	return 1;
}

//Load and return the network contained in the given file
Network* load_network(const char *filename)
{
	//Load file
	FILE *file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("Unable to load Network: ");
		printf("file \"%s\" not found\n",filename);
		return NULL;
	}

	int fscan_res; // Result of fscan	
	
	//Load number of layer
	size_t num_layers;
	fscan_res = fscanf(file, "%zu\n", &num_layers);
	if (fscan_res != 1)
	{
		printf("Unable to load Network: Cannot read num_layer\n");
		return NULL;
	}
	size_t sizes[num_layers];

	//Load size for each layer
	for(size_t i = 0; i < num_layers; i++)
	{
		fscan_res = fscanf(file, "%zu ", &sizes[i]);
		if (fscan_res != 1)
		{
			printf("Unable to load Network:");
			printf("Cannot read layer_size\n");
			return NULL;
		}
	}
	fscan_res = fscanf(file, "\n");
	
	if (num_layers < 2) num_layers = 2; // Prevents warnings
	
	//load Network
	Network *net = malloc(sizeof(Network));
	net->num_layers = num_layers;

	net->sizes = malloc(num_layers * sizeof(size_t));
	for(size_t i = 0; i < num_layers; i++)
		net->sizes[i] = sizes[i];

	//Load biases
	net->biases = malloc((num_layers - 1) * sizeof(double *));
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		net->biases[i] = malloc(sizes[i + 1] * sizeof(double));
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			fscan_res = fscanf(file, "%lf\n", &net->biases[i][j]);
			if (fscan_res != 1)
			{
				printf("Unable to load Network: ");
				printf("Cannot read biases\n");
				return NULL;
			}
		}
	}

	//Load weights
	net->weights = malloc((num_layers - 1) * sizeof(double **));
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		net->weights[i] = malloc(sizes[i + 1] * sizeof(double *));
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			net->weights[i][j] = malloc(sizes[i] * sizeof(double));
			for(size_t k = 0; k < net->sizes[i]; k++)
			{
                		fscan_res = fscanf(file, "%lf ",
                			&net->weights[i][j][k]);
                		if (fscan_res != 1)
				{
					printf("Unable to load Network: ");
					printf("Cannot read weights\n");
					return NULL;
				}
                	}
			fscan_res = fscanf(file, "\n");
                }
	}

	fclose(file);
	return net;
}
