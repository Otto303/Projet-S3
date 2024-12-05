#include <stdio.h>
#include <stdlib.h>

#define IMAGE_SIZE 784  // 28x28 pixels

// Function to read 4-byte integer from binary file
int read_int(FILE *file)
{
	unsigned char bytes[4];
	int fread_res = fread(bytes, sizeof(unsigned char), 4, file);
	if (fread_res != 4)
	{
		printf("Error reading dataset from file\n");
		return 0;
	}
	return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

// Load images from binary file
void load_images(const char *filename, unsigned char **images, int num_images)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}	
	read_int(file); // Skip magic number
	read_int(file); // Skip number of images
	read_int(file); // Skip number of rows
	read_int(file); // Skip number of columns

	int fread_res; // result of fread
	for (int i = 0; i < num_images; i++)
	{
		fread_res = fread(images[i], sizeof(unsigned char), IMAGE_SIZE, file);
		if (fread_res != IMAGE_SIZE)
		{
			printf("Error reading dataset from file\n");
			return;
		}
	}
	fclose(file);
}

// Load labels from binary file
void load_labels(const char *filename, unsigned char *labels, int num_labels)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		perror("Unable to open file");
		exit(EXIT_FAILURE);
	}
	read_int(file); // Skip magic number
	read_int(file); // Skip number of labels

	int fread_res; // result of fread
	fread_res = fread(labels, sizeof(unsigned char), num_labels, file);
	if (fread_res != num_labels)
	{
		printf("Error reading dataset from file\n");
		return;
	}
	fclose(file);
}
/*
int main()
{
	FILE *file = fopen("emnist-letters-train-images-idx3-ubyte", "rb");
	read_int(file);
	int num_images = read_int(file);
	fclose(file);

	// Allocate memory for images and labels
	unsigned char **images = malloc(num_images * sizeof(unsigned char *));
	for (int i = 0; i < num_images; i++)
        	images[i] = malloc(IMAGE_SIZE * sizeof(unsigned char));
	unsigned char *labels = malloc(num_images * sizeof(unsigned char));

	// Load the images and labels
	load_images("emnist-letters-train-images-idx3-ubyte", images, num_images);
	load_labels("emnist-letters-train-labels-idx1-ubyte", labels, num_images);

	// Example: Print first image and label
	printf("First label: %c\n", labels[0] + 'A' - 1);  // Convert to ASCII letter
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j < 28; j++)
			printf("%c", images[0][i * 28 + j] > 128 ? '#' : '.');
		printf("\n");
	}

	// Free allocated memory
	for (int i = 0; i < num_images; i++)
		free(images[i]);
	free(images);
	free(labels);

	return 0;
}
*/
