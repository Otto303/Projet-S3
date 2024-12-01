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
		printf("Unable to save Network: file \"%s\" not found\n",filename);
		return 0;
	}

	//Save number of layer and size for each
	fprintf(file, "%ld\n", net->num_layers);
	for(size_t i = 0; i < net->num_layers; i++)
		fprintf(file, "%ld ", net->sizes[i]);
	fprintf(file, "\n");

	//Save biases
	for(size_t i = 0; i < net->num_layers - 1; i++)
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
			fprintf(file, "%f\n", net->biases[i][j]);

	//Save weights
	for(size_t i = 0; i < net->num_layers - 1; i++)
	{
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
		{
			for(size_t k = 0; k < net->sizes[i]; k++)
				fprintf(file, "%f ", net->weights[i][j][k]);
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
	printf("Loading network...\n");
	
	//Load file
	FILE *file = fopen(filename, "r");
	if(file == NULL)
	{
		printf("Unable to load Network: file \"%s\" not found\n",filename);
		return NULL;
	}

	//Load number of layer
	size_t num_layers = 0;
	fscanf(file, "%zu", &num_layers);
	size_t sizes[num_layers];

	//Load size for each layer
	for(size_t i = 0; i < num_layers; i++)
		fscanf(file, "%zu", &sizes[i]);

	//load Network
	Network* net = init_network(sizes, num_layers);

	//Load biases
	for(size_t i = 0; i < net->num_layers - 1; i++)
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
			fscanf(file, "%lf", &net->biases[i][j]);

	//Load weights
	for(size_t i = 0; i < net->num_layers - 1; i++)
		for(size_t j = 0; j < net->sizes[i + 1]; j++)
			for(size_t k = 0; k < net->sizes[i]; k++)
                		fscanf(file, "%lf", &net->weights[i][j][k]);

	fclose(file);
	printf("Network loaded\n");
	return net;
}
