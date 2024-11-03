#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include "interface.h"

#define MAX_PATH_LENGTH 256


/*
void noirEtBlanc(SDL_Surface *surface) {
    if (surface == NULL) {
        fprintf(stderr, "Invalid surface: %s\n", SDL_GetError());
        return;
    }

    if (SDL_LockSurface(surface) < 0) {
        fprintf(stderr, "Unable to lock surface: %s\n", SDL_GetError());
        return;
    }

    SDL_PixelFormat *format = surface->format;
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int width = surface->w;
    int height = surface->h;

    if (width <= 0 || height <= 0) {
        fprintf(stderr, "Invalid surface dimensions: %d x %d\n", width, height);
        SDL_UnlockSurface(surface);
        return;
    }

    if (pixels == NULL) {
        fprintf(stderr, "Surface has no pixel data\n");
        SDL_UnlockSurface(surface);
        return;
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            
            Uint32 pixel = pixels[y * width + x];
            Uint8 r, g, b;

            
            SDL_GetRGB(pixel, format, &r, &g, &b);

            
            Uint8 gray = (Uint8)((r + g + b) / 3);

            float contrastFactor = 1.5f; 
	    r = (Uint8)((gray + (r - gray) * contrastFactor) > 255 ? 255
			: (gray + (r - gray) * contrastFactor));
        g = (Uint8)((gray + (g - gray) * contrastFactor) > 255 ? 255
			: (gray + (g - gray) * contrastFactor));
        b = (Uint8)((gray + (b - gray) * contrastFactor) > 255 ? 255
			: (gray + (b - gray) * contrastFactor));

            pixels[y * width + x] = SDL_MapRGB(format, r, g, b);
        }
    }

    SDL_UnlockSurface(surface);
}

*/

void open_window() {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture = NULL;
    SDL_Texture *textTexture = NULL;
    SDL_Texture *titleTexture = NULL;

    char imagePath[MAX_PATH_LENGTH] = "";
    int pathLength = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized: %s\n", SDL_GetError());
        return;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("Image is not on format JPG or PNG: %s\n", IMG_GetError());
        SDL_Quit();
        return;
    }

    if (TTF_Init() == -1) {
        printf("TTF could not be initialized: %s\n", TTF_GetError());
        SDL_Quit();
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");

    window = SDL_CreateWindow("OCR by OCR PRO MAX", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Window could not be created: %s\n", SDL_GetError());
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Render could not be created: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    TTF_Font *font =
		TTF_OpenFont(".cache/Interface/Roboto/Roboto-Regular.ttf", 24);
    if (!font) {
        printf("Font could not be loaded: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        SDL_Quit();
        return;
    }

    TTF_Font *titleFont =
		TTF_OpenFont(".cache/Interface/Roboto/Roboto-Regular.ttf", 48);
    if (!titleFont) {
        printf("Title font could not be loaded: %s\n",
				TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        IMG_Quit();
        return;
    }

    SDL_Event e;
    int running = 1;
    int enterPressed = 0;
    int imageLoaded = 0;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
            else if (e.type == SDL_TEXTINPUT && !enterPressed) {
                if (pathLength < MAX_PATH_LENGTH - 1) {
                    strcat(imagePath, e.text.text);
                    pathLength += strlen(e.text.text);
                }
            }
            else if (e.type == SDL_KEYDOWN && !enterPressed) {
                if (e.key.keysym.sym == SDLK_BACKSPACE && pathLength > 0) {
                    imagePath[--pathLength] = '\0';
                }
                else if (e.key.keysym.sym == SDLK_RETURN) {
                    SDL_Surface *imageSurface = IMG_Load(imagePath);
                    if (!imageSurface) {
                        printf("Image could not be loaded: %s\n",
								IMG_GetError());
                    }
                    else {
			 //noirEtBlanc(imageSurface);

                        if (texture) {
                            SDL_DestroyTexture(texture);
                        }

                        texture = SDL_CreateTextureFromSurface(renderer,
								imageSurface);
                        if (!texture) {
                            printf("Texture could not be created : %s\n",
									SDL_GetError());
                        }
                        SDL_FreeSurface(imageSurface);
                        enterPressed = 1;
			imageLoaded = 1;
                    }
                }
            }
        }

        int windowWidth, windowHeight;
        SDL_GetWindowSize(window, &windowWidth, &windowHeight);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
	if (!imageLoaded) {
		SDL_Color titleColor = { 0, 0, 0, 255 };
                SDL_Surface *titleSurface = TTF_RenderText_Solid(titleFont,
						"Welcome to OCR by OCR PRO MAX", titleColor);
                if (titleSurface) {
                titleTexture = SDL_CreateTextureFromSurface(renderer,
						titleSurface);
                SDL_FreeSurface(titleSurface);
                	if (titleTexture) {
				SDL_Rect titleRect;
                		titleRect.x = (windowWidth - titleSurface->w) / 2;
                		titleRect.y = 10;
                		titleRect.w = titleSurface->w;
                		titleRect.h = titleSurface->h;
                		SDL_RenderCopy(renderer, titleTexture,
								NULL, &titleRect);
			}
		}
        }

        if (texture) {
            int maxWidth = windowWidth / 2;
            int maxHeight = windowHeight / 2;
            int imgWidth, imgHeight;
            SDL_QueryTexture(texture, NULL, NULL, &imgWidth, &imgHeight);
            float Scale = (float)imgWidth / (float)imgHeight;

            if (imgWidth > maxWidth) {
                imgWidth = maxWidth;
                imgHeight = (int)(maxWidth / Scale);
            }
            if (imgHeight > maxHeight) {
                imgHeight = maxHeight;
                imgWidth = (int)(maxHeight * Scale);
            }

            SDL_Rect dstRect;
            dstRect.w = imgWidth;
            dstRect.h = imgHeight;
            dstRect.x = (windowWidth - imgWidth) / 2;
            dstRect.y = (windowHeight - imgHeight) / 2;

            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
        }

        if (!imageLoaded && pathLength > 0) {
            SDL_Color textColor = { 0, 0, 0, 255 };
            SDL_Surface *textSurface = TTF_RenderText_Solid(font,
					imagePath, textColor);
            if (textSurface) {
                textTexture =
					SDL_CreateTextureFromSurface(renderer, textSurface);
                SDL_FreeSurface(textSurface);

                if (textTexture) {
                    int textWidth, textHeight;
                    SDL_QueryTexture(textTexture, NULL, NULL,
							&textWidth, &textHeight);
                    SDL_Rect textRect = {10, windowHeight - textHeight - 10,
						textWidth, textHeight };
                    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
                }
            }
        }

        SDL_RenderPresent(renderer);
    }

    if (textTexture) {
        SDL_DestroyTexture(textTexture);
    }
    if (titleTexture) {
        SDL_DestroyTexture(titleTexture);
    }
    if (texture) {
        SDL_DestroyTexture(texture);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void interface() {
    open_window();
}

