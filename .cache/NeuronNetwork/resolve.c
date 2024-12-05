#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "Network/network.h"
#include "Network/feedforward.h"
#include "Network/evaluate.h"
#include "Network/save.h"
#include "bmp_to_array.h"

//takes file of network, and the inputs to resolve
int main(int argc, char *argv[])
{

	if (argc != 3)
		errx(1,"Not correct argument number\n");

	// Initialize array
	size_t width;
	size_t height;
	double* pixelArray = loadImageAsArray(argv[2], &width, &height);
	if (pixelArray == NULL)
		return EXIT_FAILURE;
	
	//Initialize network
	Network* net = load_network(argv[1]);
	if(net == NULL)
		return EXIT_FAILURE;

	//Calculate result
	double *output = feedforward(net, pixelArray);
	size_t res = argmax(output,net->sizes[net->num_layers-1]);
	
	//Displays final results
	printf("Output: %c\n", (char)res + 'A');
	
	free(output);
	free_network(net);

	return EXIT_SUCCESS;
}
