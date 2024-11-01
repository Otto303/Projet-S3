#include <stdio.h>
#include <stdlib.h>
#include "network.h"

void save_network(Network *net, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Unable to save: file \"net.txt\" not found");
        return;
    }

    //Save number of layer and size for each
    fprintf(file, "%ld\n", net->num_layers);
    for (size_t i = 0; i < net->num_layers; i++)
	fprintf(file, "%ld ", net->sizes[i]);
    fprintf(file, "\n");

    //Save biases
    for (size_t i = 0; i < net->num_layers - 1; i++)
    {
        for (size_t j = 0; j < net->sizes[i + 1]; j++)
            fprintf(file, "%f\n", net->biases[i][j]);
    }

    //Save weights
    for (size_t i = 0; i < net->num_layers - 1; i++)
    {
        for (size_t j = 0; j < net->sizes[i + 1]; j++)
        {
            for (size_t k = 0; k < net->sizes[i]; k++)
                fprintf(file, "%f ", net->weights[i][j][k]);
            fprintf(file, "\n");
        }
    }

    fclose(file);
}

void load_network(Network *net, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Unable to load: file \"net.txt\" not found");
        return;
    }

    //Load number of layer and size for each
    fscanf(file, "%ld", &net->num_layers);
    net->sizes = malloc(net->num_layers * sizeof(int));
    for (size_t i = 0; i < net->num_layers; i++)
        fscanf(file, "%ld", &net->sizes[i]);

    //Allocation pour les biais et les poids en fonction de la taille du réseau
    net->biases = malloc((net->num_layers - 1) * sizeof(double **));
    net->weights = malloc((net->num_layers - 1) * sizeof(double **));

    // Chargement des biais
    for (size_t i = 0; i < net->num_layers - 1; i++)
    {
        net->biases[i] = malloc(net->sizes[i + 1] * sizeof(double *));
        for (size_t j = 0; j < net->sizes[i + 1]; j++)
        {
            fscanf(file, "%lf", &net->biases[i][j]);
        }
    }

    // Chargement des poids
    for (size_t i = 0; i < net->num_layers - 1; i++)
    {
        net->weights[i] = malloc(net->sizes[i + 1] * sizeof(double *));
        for (size_t j = 0; j < net->sizes[i + 1]; j++)
        {
            net->weights[i][j] = malloc(net->sizes[i] * sizeof(double));
            for (size_t k = 0; k < net->sizes[i]; k++)
            {
                fscanf(file, "%lf", &net->weights[i][j][k]);
            }
        }
    }

    fclose(file);
}
