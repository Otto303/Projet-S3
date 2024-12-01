#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "Network/network.h"
#include "Network/feedforward.h"
#include "Network/evaluate.h"
#include "Network/save.h"

//takes file of network, and the inputs to resolve
int main(int argc, char *argv[])
{

	if (argc < 4)
		errx(1,"Not enough arguments\n");

	//Initialize network
	Network* net = load_network(argv[1]);
	if(net == NULL)
		return EXIT_FAILURE;

	//Initialize both arguments
	double data[] = { (double)argv[2][0] - 48, (double)argv[3][0] - 48};

	//Calculate result
	double *output = feedforward(net, data);
	size_t res = argmax(output,net->sizes[net->num_layers-1]);
	
	//Displays final results
	printf("Input: (%.0f, %.0f)\n", data[0], data[1]);
	printf("Output: %ld\n", res);
	
	free(output);
	free_network(net);	

	return EXIT_SUCCESS;
}
