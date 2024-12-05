#include <stdio.h>
#include <stdlib.h>
#include "read_dataset.h"
#include "../Network/data.h"

#define IMAGE_SIZE 784  // 28x28 pixels

int generate_training_data(size_t* training_size, Data** training_data)
{
	FILE *file = fopen(".cache/NeuronNetwork/Dataset/emnist-letters-train-images-idx3-ubyte", "rb");
	read_int(file);
	size_t num_images = read_int(file);
	fclose(file);

	// Allocate memory for images and labels
	unsigned char **images = malloc(num_images * sizeof(unsigned char *));
	for (size_t i = 0; i < num_images; i++)
        	images[i] = malloc(IMAGE_SIZE * sizeof(unsigned char));
	unsigned char *labels = malloc(num_images * sizeof(unsigned char));

	// Load the images and labels
	load_images(".cache/NeuronNetwork/Dataset/emnist-letters-train-images-idx3-ubyte", images, num_images);
	load_labels(".cache/NeuronNetwork/Dataset/emnist-letters-train-labels-idx1-ubyte", labels, num_images);

	// Initialize training_data
	*training_size = num_images;
	*training_data = calloc(num_images, sizeof(Data));
	for (size_t i = 0; i < num_images; i++)
	{
		(*training_data)[i].x = calloc(IMAGE_SIZE, sizeof(double));
		for (size_t j = 0; j < IMAGE_SIZE; j++)
		{
			if (images[i][j] > 128) (*training_data)[i].x[j] = 1;
			else (*training_data)[i].x[j] = 0;
		}
		(*training_data)[i].y = calloc(26, sizeof(double));
		(*training_data)[i].y[labels[i] - 1] = 1;
	}

	 // Free allocated memory
	for (size_t i = 0; i < num_images; i++)
		free(images[i]);
	free(images);
	free(labels);

	return 0;
}

