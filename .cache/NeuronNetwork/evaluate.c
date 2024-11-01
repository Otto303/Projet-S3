#include <stdlib.h>
#include <stdio.h>
#include "data.h"
#include "network.h"
#include "feedforward.h"

//Find index of neuron with max activation
size_t argmax(double *array, size_t length)
{
	size_t max_index = 0;
	double max_value = array[0];
	for(size_t i = 1; i < length; i++)
	{
		if(array[i] > max_value)
		{
			max_value = array[i];
			max_index = i;
		}
	}
	return max_index;
}

int evaluate(Network *net, Data *test_data, size_t test_data_size)
{
	int correct_results = 0;
	for(size_t i = 0; i < test_data_size; i++)
	{
		double *output = feedforward(net, test_data[i].x);
		size_t predicted = argmax(output,
			net->sizes[net->num_layers - 1]);
		if(predicted == argmax(test_data[i].y,2))
			correct_results++;
		free(output);
	}
	return correct_results;
}
