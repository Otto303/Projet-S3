#include <stddef.h>

double xavier();

#ifndef NETWORK_H
#define NETWORK_H

typedef struct {
	size_t num_layers;
	size_t *sizes;
	double **biases;
	double ***weights;
} Network;
#endif

Network* init_network(size_t *sizes, int num_layers);
void free_network(Network *net);
