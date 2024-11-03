#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "data.h"
#include "network.h"
#include "SGD.h"
#include "feedforward.h"
#include "evaluate.h"


int main(int argc, char *argv[])
{
	if (argc < 2)
		errx(1,"Not enough arguments\n");

	//Initialize network
	int sizes[] = {2, 2, 2};
	Network* net = init_network(sizes, 3);

	//Datas for NOT(A AND B) OR (A AND B) with expected results
	Data training_data[4];
	for(size_t i = 0; i < 4; i++)
	{
        	training_data[i].x = malloc(2 * sizeof(double));
        	training_data[i].y = malloc(2 * sizeof(double));
        }

	// NOT(0 XOR 0) = 1
	training_data[0].x[0] = 0;
	training_data[0].x[1] = 0;
	training_data[0].y[0] = 0;
	training_data[0].y[1] = 1;

	// NOT(0 XOR 1) = 0
	training_data[1].x[0] = 0;
	training_data[1].x[1] = 1;
	training_data[1].y[0] = 1;
	training_data[1].y[1] = 0;

	// NOT(1 XOR 0) = 0
	training_data[2].x[0] = 1;
	training_data[2].x[1] = 0;
	training_data[2].y[0] = 1;
	training_data[2].y[1] = 0;

	// NOT(1 XOR 1) = 1
	training_data[3].x[0] = 1;
	training_data[3].x[1] = 1;
	training_data[3].y[0] = 0;
	training_data[3].y[1] = 1;
	
	//Parameters for training
	int epochs = 1000000000;
	int mini_batch_size = 4;
	double eta = 0.9;

	//Training with stochastic gradient descent
	if(argv[1][0] == '0')
		SGD(net,training_data,4,epochs,mini_batch_size,eta);
	else
		SGD_evaluate(net, training_data, 4, epochs,
			mini_batch_size, eta, training_data, 4);

	// Evaluation of network with training data
	int correct_results = evaluate(net, training_data, 4);
	printf("Correct results: %d out of 4\n", correct_results);
	
	//Displays final results
	for(size_t i = 0; i < 4; i++)
	{
		double *output = feedforward(net, training_data[i].x);
		printf("Input: (%.0f, %.0f), ",
			training_data[i].x[0], training_data[i].x[1]);

		printf("Expected output: %ld,",
			argmax(training_data[i].y,2));

		printf("Network output: %ld\n",
			argmax(output,net->sizes[net->num_layers-1]));
		free(output);
	}

	for(size_t i = 0; i < 4; i++)
		free(training_data[i].x);
	
	return 0;
}
