#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <SDL2/SDL.h>

// Takes as parameters the image to rotate and the angle
int main(int argc, char* argv[])
{
	if (argc != 3)
		errx(1,"Not correct arguments number");

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window* window = SDL_CreateWindow("Rotate Image",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* surface = SDL_LoadBMP(argv[1]);
	if (!surface)
	{
		printf("Failed to load image: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	// Convert surface to texture
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	// Create a target texture for rendering the rotated image
	SDL_Texture* target = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 800, 600);
	SDL_SetRenderTarget(renderer, target);

	// Clear the target texture
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// Define parameters
	double angle = strtod(argv[2],NULL); // Rotation angle
	SDL_Rect destRect = { 200, 150, 400, 300 };
	SDL_Point center = { destRect.w / 2, destRect.h / 2 };

	// Render rotated texture onto the target
	SDL_RenderCopyEx(renderer, texture, NULL, &destRect, angle,
		&center, SDL_FLIP_NONE);
	SDL_RenderPresent(renderer);

	// Save the target texture to a file
	SDL_Surface* saveSurface = SDL_CreateRGBSurfaceWithFormat(0, 800, 600,
		32, SDL_PIXELFORMAT_RGBA8888);
	if (saveSurface)
	{
		SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_RGBA8888,
			saveSurface->pixels, saveSurface->pitch);
		SDL_SaveBMP(saveSurface, "rotated_image.bmp");
		SDL_FreeSurface(saveSurface);
	}
	else printf("Failed to create save surface: %s\n", SDL_GetError());

	// Cleanup
	SDL_DestroyTexture(target);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
