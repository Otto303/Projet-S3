#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "minibatch.h"
#include "evaluate.h"
#include "save.h"

void shuffle(Data *data, int n)
{
	srand(time(NULL));
	for(int i = n - 1; i > 0; i--)
	{
		int j = rand() % (i + 1);
		Data temp = data[i];
		data[i] = data[j];
		data[j] = temp;
	}
}

void SGD(Network *net, Data *training_data, int n,
		int mini_batch_size, double eta, Data *test_data, int n_test)
{	
	printf("Training network...\n");
	for (int j = 1; 1; j++)
	{
		shuffle(training_data, n);

		// Create mini-batches
		for(int k = 0; k < n; k += mini_batch_size)
		{
			int batch_end = k + mini_batch_size;
			if (batch_end > n)
				batch_end = n;
			update_mini_batch(net, &training_data[k],
					batch_end - k, eta);
		}
		
		printf("Epoch %d complete\n",j);
		if (j % 1000 == 0)
		{
			int correct = evaluate(net, test_data, n_test);
			printf("results: %d/%d\n", correct, n_test);
			if (j % 2000 == 0)
				save_network(net,"nw_2");
			else save_network(net,"nw_1");
		}
	}
}

void SGD_evaluate(Network *net, Data *training_data, int n,
		int mini_batch_size, double eta, Data *test_data, int n_test)
{
	for (int j = 1; 1; j++)
	{
		shuffle(training_data, n);

		// Create mini-batches
		for(int k = 0; k < n; k += mini_batch_size)
		{
			int batch_end = k + mini_batch_size;
			if (batch_end > n)
				batch_end = n;
			update_mini_batch(net, &training_data[k],
						batch_end - k, eta);
		}

		//Evaluate network after each epoch
		int correct = evaluate(net, test_data, n_test);
		printf("Epoch %d: %d/%d\n", j, correct, n_test);
		if (j % 10000 == 0)
		{
			printf("Epoch %d complete\n", j);
			if (j % 20000 == 0) save_network(net,"nw_2");
			else save_network(net,"nw_1");
		}
	}
}
