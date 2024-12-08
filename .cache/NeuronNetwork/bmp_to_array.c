#include <SDL2/SDL.h>
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
		if (r > 128) array[i] = 1;
		else array[i] = 0;
	}

	SDL_FreeSurface(imageSurface);
	SDL_Quit();

	return array;
}
