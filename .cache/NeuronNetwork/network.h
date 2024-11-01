#include <stddef.h>

double randn();

#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	size_t num_layers;
	size_t *sizes;
	double **biases;
	double ***weights;
} Network;
#endif

Network* init_network(int *sizes, int num_layers);
void free_network(Network *net);
