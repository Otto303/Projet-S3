#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "minibatch.h"
#include "evaluate.h"

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
		int epochs, int mini_batch_size, double eta)
{
	for (int j = 0; j < epochs; j++)
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

		printf("Epoch %d complete\n", j);
	}
}

void SGD_evaluate(Network *net, Data *training_data, int n,
		int epochs, int mini_batch_size, double eta,
				Data *test_data, int n_test)
{
	for (int j = 0; j < epochs; j++)
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
		printf("Epoch %d: %d / %d\n", j, correct, n_test);
	}
}
