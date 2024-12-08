#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "Network/data.h"
#include "Network/network.h"
#include "Network/SGD.h"
#include "Network/feedforward.h"
#include "Network/evaluate.h"
#include "Network/save.h"
#include "Dataset/read_dataset.h"
#include "Dataset/generate_training_data.h"

//takes as arguments weither you want to evalute(0 or 1),
//the file to load from and save on
int main(int argc, char *argv[])
{
	if (argc > 2)
		errx(1,"Too many arguments\n");

	//Initialize network
	Network* net = NULL;
	if (argc == 2)
		net = load_network(argv[1]);

	if (net == NULL) //if file doesn't exists, create new network
	{
		printf("Creating network from scratch...\n");
		size_t sizes[] = {784, 256, 128, 26};
		net = init_network(sizes, 4);
		printf("Network created\n");
	}
	
	
	size_t training_size;
	Data* training_data;
	generate_training_data(&training_size,&training_data);

	//Parameters for training
	int mini_batch_size = training_size/100;
	double eta = 0.8;

	//Training with stochastic gradient descent
	SGD(net, training_data, training_size, mini_batch_size, eta,
					training_data, training_size);

	// Evaluation of network with training data
	int correct_results = evaluate(net, training_data, training_size);
	printf("Correct results: %d/%ld (%ld%%)\n",
	correct_results, training_size, correct_results * 100 / training_size);
	
	if (argc == 2)
		save_network(net,argv[1]);
	
	for(size_t i = 0; i < 4; i++)
	{
		free(training_data[i].x);
		free(training_data[i].y);
	}
	free(training_data);
	free_network(net);	

	return EXIT_SUCCESS;
}
