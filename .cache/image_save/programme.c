#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

// Fonction pour nettoyer le dossier de sortie
void clear_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *entry;
        char filepath[512];

        while ((entry = readdir(dir)) != NULL) {
            // Ignorer "." et ".."
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
            remove(filepath);
        }
        closedir(dir);
    }
}

// Fonction de binarisation
int **binarize_image(SDL_Surface *image, int threshold) {
    Uint32 pixel;
    Uint8 r, g, b;
    int width = image->w;
    int height = image->h;

    // Allouer la matrice
    int **matrix = (int **)malloc(height * sizeof(int *));
    if (!matrix) {
        fprintf(stderr, "Erreur : Impossible d'allouer la mémoire pour la matrice.\n");
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        matrix[i] = (int *)malloc(width * sizeof(int));
        if (!matrix[i]) {
            fprintf(stderr, "Erreur : Impossible d'allouer la mémoire pour la matrice.\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            return NULL;
        }
    }

    // Remplir la matrice avec les valeurs binaires
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // Lire le pixel
            pixel = ((Uint32 *)image->pixels)[y * image->w + x];
            SDL_GetRGB(pixel, image->format, &r, &g, &b);

            // Calculer l'intensité en niveaux de gris
            Uint8 grayscale = (r + g + b) / 3;

            // Appliquer le seuil
            matrix[y][x] = (grayscale < threshold) ? 0 : 1;
        }
    }

    return matrix;
}

// Libérer la mémoire de la matrice
void free_matrix(int **matrix, int height) {
    for (int i = 0; i < height; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
//si on

// Trouve les lettres et les enregistre dans des fichiers

void extract_letters(SDL_Surface *image, int **matrix, const char *output_dir) {
    int width = image->w;
    int height = image->h;
    bool **visited = (bool **)malloc(height * sizeof(bool *));
    for (int i = 0; i < height; i++) {
        visited[i] = (bool *)calloc(width, sizeof(bool));
    }

    // Structure pour stocker les régions détectées
    typedef struct {
        int min_x, min_y, max_x, max_y;
        int width, height;
    } Region;

    Region *regions = (Region *)malloc(1000 * sizeof(Region)); // Jusqu'à 1000 régions
    int region_count = 0;

    // Fonction interne pour explorer une région
    void explore_region(int x, int y, int *min_x, int *min_y, int *max_x, int *max_y) {
        if (x < 0 || x >= width || y < 0 || y >= height || visited[y][x] || matrix[y][x] == 1) {
            return;
        }

        visited[y][x] = true;

        if (x < *min_x) *min_x = x;
        if (x > *max_x) *max_x = x;
        if (y < *min_y) *min_y = y;
        if (y > *max_y) *max_y = y;

        explore_region(x + 1, y, min_x, min_y, max_x, max_y);
        explore_region(x - 1, y, min_x, min_y, max_x, max_y);
        explore_region(x, y + 1, min_x, min_y, max_x, max_y);
        explore_region(x, y - 1, min_x, min_y, max_x, max_y);
    }

    // Détection des régions
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (matrix[y][x] == 0 && !visited[y][x]) {
                int min_x = x, max_x = x, min_y = y, max_y = y;

                explore_region(x, y, &min_x, &min_y, &max_x, &max_y);

                int region_width = max_x - min_x + 1;
                int region_height = max_y - min_y + 1;

                // Stocker la région détectée si elle respecte les critères
                if (region_count < 1000 && region_width > 2 && region_height > 6 &&
                    region_width < 40 && region_height < 40) {

                    regions[region_count].min_x = min_x;
                    regions[region_count].min_y = min_y;
                    regions[region_count].max_x = max_x;
                    regions[region_count].max_y = max_y;
                    regions[region_count].width = region_width;
                    regions[region_count].height = region_height;
                    region_count++;
                }
            }
        }
    }

    // Traiter les régions validées
    Uint32 blue_color = SDL_MapRGB(image->format, 0, 0, 255);
    for (int i = 0; i < region_count; i++) {
        int min_x = regions[i].min_x;
        int min_y = regions[i].min_y;
        int max_x = regions[i].max_x;
        int max_y = regions[i].max_y;

        // Colorier l'image originale
        for (int x = min_x; x <= max_x; x++) {
            if (min_y >= 0 && min_y < height) ((Uint32 *)image->pixels)[min_y * width + x] = blue_color;
            if (max_y >= 0 && max_y < height) ((Uint32 *)image->pixels)[max_y * width + x] = blue_color;
        }
        for (int y = min_y; y <= max_y; y++) {
            if (min_x >= 0 && min_x < width) ((Uint32 *)image->pixels)[y * width + min_x] = blue_color;
            if (max_x >= 0 && max_x < width) ((Uint32 *)image->pixels)[y * width + max_x] = blue_color;
        }

        // Sauvegarder l'image découpée
        int letter_width = max_x - min_x + 1;
        int letter_height = max_y - min_y + 1;

        SDL_Surface *letter_image = SDL_CreateRGBSurface(0, letter_width, letter_height, 32,
            0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

        if (!letter_image) {
            fprintf(stderr, "Erreur : Impossible de créer la surface pour une lettre.\n");
            continue;
        }

        for (int j = 0; j < letter_height; j++) {
            for (int i = 0; i < letter_width; i++) {
                int src_x = min_x + i;
                int src_y = min_y + j;
                Uint32 pixel = ((Uint32 *)image->pixels)[src_y * width + src_x];
                ((Uint32 *)letter_image->pixels)[j * letter_width + i] = pixel;
            }
        }

        // Sauvegarder l'image
        char filename[256];
        snprintf(filename, sizeof(filename), "%s/letter_%d_%d.bmp", output_dir, min_x, min_y);
        SDL_SaveBMP(letter_image, filename);
        SDL_FreeSurface(letter_image);
    }

    // Libérer la mémoire
    for (int i = 0; i < height; i++) {
        free(visited[i]);
    }
    free(visited);
    free(regions);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <image.bmp> <threshold>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int threshold = atoi(argv[2]);
    const char *output_dir = "lettres";

    // Créer ou vider le répertoire
    struct stat st = {0};
    if (stat(output_dir, &st) == -1) {
        mkdir(output_dir, 0700);
    } else {
        clear_directory(output_dir);
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *image = SDL_LoadBMP(filename);
    if (!image) {
        printf("Erreur de chargement de l'image : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    int **matrix = binarize_image(image, threshold);
    if (!matrix) {
        SDL_FreeSurface(image);
        SDL_Quit();
        return 1;
    }

    extract_letters(image, matrix, output_dir);

    SDL_SaveBMP(image, "imbw.bmp");

    free_matrix(matrix, image->h);
    SDL_FreeSurface(image);
    SDL_Quit();

    return 0;
}