#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "Network/network.h"
#include "Network/feedforward.h"
#include "Network/evaluate.h"
#include "Network/save.h"
#include "bmp_to_array.h"

//takes file of network, and the inputs to resolve
char predict(char *nw,char *file_name)
{
	// Initialize array
	size_t width;
	size_t height;
	double* pixelArray = loadImageAsArray(file_name, &width, &height);
	if (pixelArray == NULL)
		return EXIT_FAILURE;
	
	//Initialize network
	Network* net = load_network(nw);
	if (net == NULL)
		return EXIT_FAILURE;

	//if (net->sizes[0] != width*height)
	//	errx(1,"Image not on valid size\n");

	//Calculate result
	double *output = feedforward(net, pixelArray);
	size_t res = argmax(output,net->sizes[net->num_layers-1]);
	
	//Displays final results
	printf("Output: %c\n", (char)res + 'A');
	
	free(output);
	free(pixelArray);
	free_network(net);

	return (char)res + 'A';
}
