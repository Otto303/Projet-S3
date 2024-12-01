#include <SDL2/SDL.h> //gcc -o bmp_to_array bmp_to_array.c -lSDL2
#include <stdio.h>
#include <stdlib.h>

double* loadImageAsArray(const char* filename, size_t* width, size_t* height)
{
	//Initialize SDL
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr,"Error initializing SDL: %s\n", SDL_GetError());
		return NULL;
	}

	//Load BMP file
	SDL_Surface* imageSurface = SDL_LoadBMP(filename);
	if(!imageSurface)
	{
		fprintf(stderr,"Error loading BMP file: %s\n", SDL_GetError());
		SDL_Quit();
		return NULL;
	}

	//Get image dimensions
	*width = imageSurface->w;
	*height = imageSurface->h;
	size_t totalPixels = (*width) * (*height);

	//Allocate memory for the array of doubles
	double* array = malloc(totalPixels * sizeof(double));
	if(!array)
	{
		fprintf(stderr, "Error allocating memory.\n");
		SDL_FreeSurface(imageSurface);
		SDL_Quit();
		return NULL;
	}

	//Convert pixel data to double and store in the array
	Uint32* pixels = imageSurface->pixels;
	for(size_t i = 0; i < totalPixels; i++)
	{
		Uint8 r, g, b;
		//have to use 3 values to initialize,
		//but only use 1 as we suppose greyscale is already done
		SDL_GetRGB(pixels[i], imageSurface->format, &r, &g, &b);

		//Normalize grayscale between 0 and 1
		//double grayscale=(0.299 * r + 0.587 * g + 0.114 * b) / 255.0;
		array[i] = r / 255.0;
	}

	SDL_FreeSurface(imageSurface);
	SDL_Quit();

	return array;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: %s <bmp_file>\n", argv[0]);
		return 1;
	}

	size_t width;
	size_t height;
	double* pixelArray = loadImageAsArray(argv[1], &width, &height);

	if(!pixelArray)
	{
		fprintf(stderr, "Failed to load image.\n");
		return 1;
	}

	//Display the pixel array as grayscale values (for testing)
	printf("Image dimensions: %ldx%ld\n", width, height);
	for(size_t i = 0; i < width * height; i++)
	{
		printf("%0.0f ", pixelArray[i]);
		if ((i+1) % width == 0) printf("\n"); //Newline after each row
	}

	free(pixelArray);

	return 0;
}

