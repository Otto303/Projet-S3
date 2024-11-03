#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int is_dark_pixel(Uint8 r, Uint8 g, Uint8 b) {
    int threshold = 200;
    return (r < threshold) && (g < threshold) && (b < threshold);
}

// Detect bounds of a single letter from a specific point, limiting bounds
SDL_Rect detect_limits_letter(SDL_Surface *surface, int x, int y) {
    SDL_Rect letter = {x, y, 0, 0};
    int left = x, right = x, top = y, bottom = y;

    while (right < surface->w) {
        Uint32 pixel = ((Uint32*)surface->pixels)[y * surface->w + right];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (!is_dark_pixel(r, g, b)) break;
        right++;
    }

    while (bottom < surface->h) {
        Uint32 pixel = ((Uint32*)surface->pixels)[bottom * surface->w + x];
        Uint8 r, g, b;
        SDL_GetRGB(pixel, surface->format, &r, &g, &b);
        if (!is_dark_pixel(r, g, b)) break;
        bottom++;
    }

    letter.x = left;
    letter.y = top;
    letter.w = right - left;
    letter.h = bottom - top;

    return letter;
}

int save_letter(SDL_Surface *surface, SDL_Rect letter,
                       const char* filename) {
    SDL_Surface *letter_surface = SDL_CreateRGBSurface(
        0, letter.w, letter.h, 24,
        0x00FF0000, 0x0000FF00, 0x000000FF, 0
    );
    if (!letter_surface) {
        printf("Error: could not create letter surface (%s)\n",
               SDL_GetError());
        return 1;
    }

    SDL_Rect src_rect = {letter.x, letter.y, letter.w, letter.h};
    SDL_BlitSurface(surface, &src_rect, letter_surface, NULL);

    if (SDL_SaveBMP(letter_surface, filename) != 0) {
        printf("Error: could not save image (%s)\n",
               SDL_GetError());
        SDL_FreeSurface(letter_surface);
        return 1;
    }

    SDL_FreeSurface(letter_surface);
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Usage: %s <image_file> <coord_x> <coord_y>\n",
               argv[0]);
        return 1;
    }

    const char* image_file = argv[1];
    int coord_x = atoi(argv[2]);
    int coord_y = atoi(argv[3]);

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: could not initialize SDL (%s)\n",
               SDL_GetError());
        return 1;
    }

    SDL_Surface *image = SDL_LoadBMP(image_file);
    if (!image) {
        printf("Error: could not load image (%s)\n",
               SDL_GetError());
        SDL_Quit();
        return 1;
    }

    if (coord_x < 0 || coord_x >= image->w ||
        coord_y < 0 || coord_y >= image->h) {
        printf("Error: coordinates out of image bounds.\n");
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    Uint32 pixel = ((Uint32*)image->pixels)[coord_y * image->w + coord_x];
    Uint8 r, g, b;
    SDL_GetRGB(pixel, image->format, &r, &g, &b);

    if (!is_dark_pixel(r, g, b)) {
        printf("No dark letter found at specified coordinates.\n");
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    SDL_Rect letter = detect_limits_letter(image, coord_x, coord_y);

    const char* output_filename = "extracted_letter.bmp";
    if (save_letter(image, letter, output_filename) == 0) {
        printf("Letter successfully saved as '%s'\n",
               output_filename);
    } else {
        printf("Error saving the letter.\n");
    }

    SDL_FreeSurface(image);
    SDL_Quit();

    return 0;
}
