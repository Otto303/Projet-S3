#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

// Fonction pour convertir une image en noir et blanc avec un seuil
void grayscale(const char *input_image, const char *output_image, int threshold) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Erreur lors de l'initialisation de SDL : %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Surface *image = SDL_LoadBMP(input_image);
    if (!image) {
        fprintf(stderr, "Erreur lors du chargement de l'image : %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // Parcourir les pixels de l'image
    int width = image->w;
    int height = image->h;
    Uint32 *pixels = (Uint32 *)image->pixels;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Uint32 pixel = pixels[y * width + x];
            Uint8 r, g, b;

            // Extraire les canaux de couleur
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            // Calculer l'intensité moyenne (grayscale)
            Uint8 grayscale_value = (Uint8)((r + g + b) / 3);

            // Appliquer le seuil pour noir et blanc
            Uint8 binary_value = (grayscale_value > threshold) ? 255 : 0;

            // Créer le nouveau pixel en niveaux de gris
            Uint32 new_pixel = SDL_MapRGB(image->format, binary_value, binary_value, binary_value);
            pixels[y * width + x] = new_pixel;
        }
    }

    // Sauvegarder l'image résultante
    if (SDL_SaveBMP(image, output_image) != 0) {
        fprintf(stderr, "Erreur lors de la sauvegarde de l'image : %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        SDL_Quit();
        exit(1);
    }

    SDL_FreeSurface(image);
    SDL_Quit();
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage : %s <input_image.bmp> <output_image.bmp> <threshold>\n", argv[0]);
        return 1;
    }

    const char *input_image = argv[1];
    const char *output_image = argv[2];
    int threshold = atoi(argv[3]);

    if (threshold < 0 || threshold > 255) {
        fprintf(stderr, "Erreur : le seuil doit être compris entre 0 et 255.\n");
        return 1;
    }

    grayscale(input_image, output_image, threshold);

    printf("L'image a été convertie en noir et blanc avec un seuil de %d.\n", threshold);

    return 0;
}