#include <stdio.h>
#include <stdlib.h>

#define SEUIL_PIXEL 250

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned char *data;
} Image;

// Function to read an unsigned integer in little-endian format
unsigned int read_uint32_le(FILE *file) {
    unsigned char bytes[4];
    fread(bytes, sizeof(unsigned char), 4, file);
    return (unsigned int)(bytes[0]) | (unsigned int)(bytes[1] << 8) |
           (unsigned int)(bytes[2] << 16) | (unsigned int)(bytes[3] << 24);
}

// Function to read a BMP image and convert it to a custom RGB format
Image* lire_image_bmp(const char *filename) {
    FILE *bmp_file = fopen(filename, "rb");
    if (!bmp_file) {
        printf("Erreur : impossible d'ouvrir le fichier BMP.\n");
        return NULL;
    }

    fseek(bmp_file, 18, SEEK_SET);
    unsigned int width = read_uint32_le(bmp_file);
    unsigned int height = read_uint32_le(bmp_file);

    printf("Largeur : %u, Hauteur : %u\n", width, height);

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char *data = (unsigned char*)malloc(row_padded * height);
    if (!data) {
        printf("Erreur : impossible d'allouer de la mémoire.\n");
        fclose(bmp_file);
        return NULL;
    }

    fseek(bmp_file, 54, SEEK_SET);
    fread(data, sizeof(unsigned char), row_padded * height, bmp_file);
    fclose(bmp_file);

    Image *image = (Image*)malloc(sizeof(Image));
    image->width = width;
    image->height = height;
    image->data = data;

    return image;
}

// Function to detect letter dimensions
void detecter_dimensions_lettre(Image *image, int x, int y, int *lettre_width, int *lettre_height) {
    int row_padded = (image->width * 3 + 3) & (~3);
    int max_x = x, max_y = y;

    for (int i = y; i < image->height; i++) {
        for (int j = x; j < image->width; j++) {
            int pixel_index = i * row_padded + j * 3;
            if (pixel_index >= row_padded * image->height) continue;

            unsigned char blue = image->data[pixel_index];
            unsigned char green = image->data[pixel_index + 1];
            unsigned char red = image->data[pixel_index + 2];

            if (red < SEUIL_PIXEL || green < SEUIL_PIXEL || blue < SEUIL_PIXEL) {
                if (j > max_x) max_x = j;
                if (i > max_y) max_y = i;
            }
        }
    }

    *lettre_width = max_x - x + 1;
    *lettre_height = max_y - y + 1;

    printf("Dimensions de la lettre détectées : largeur = %d, hauteur = %d\n", *lettre_width, *lettre_height);
}

// Function to save the letter as an image
void decouper_lettre(Image *image, int x, int y, const char *output_filename) {
    int lettre_width, lettre_height;
    detecter_dimensions_lettre(image, x, y, &lettre_width, &lettre_height);

    if (x + lettre_width > image->width) lettre_width = image->width - x;
    if (y + lettre_height > image->height) lettre_height = image->height - y;

    int row_padded = (image->width * 3 + 3) & (~3);
    unsigned char *data = (unsigned char*)malloc(lettre_width * lettre_height * 3);

    for (int i = 0; i < lettre_height; i++) {
        for (int j = 0; j < lettre_width; j++) {
            for (int k = 0; k < 3; k++) {
                data[(i * lettre_width + j) * 3 + k] = image->data[((y + i) * row_padded + (x + j) * 3 + k)];
            }
        }
    }

    FILE *file = fopen(output_filename, "wb");
    if (!file) {
        printf("Erreur : impossible de créer le fichier.\n");
        free(data);
        return;
    }

    int output_row_padded = (lettre_width * 3 + 3) & (~3);
    unsigned char header[54] = {
        0x42, 0x4D, 0, 0, 0, 0, 0, 0, 0, 0,
        54, 0, 0, 0, 40, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 24, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int filesize = 54 + output_row_padded * lettre_height;
    header[2] = (unsigned char)(filesize);
    header[3] = (unsigned char)(filesize >> 8);
    header[4] = (unsigned char)(filesize >> 16);
    header[5] = (unsigned char)(filesize >> 24);

    header[18] = (unsigned char)(lettre_width);
    header[19] = (unsigned char)(lettre_width >> 8);
    header[20] = (unsigned char)(lettre_width >> 16);
    header[21] = (unsigned char)(lettre_width >> 24);

    header[22] = (unsigned char)(lettre_height);
    header[23] = (unsigned char)(lettre_height >> 8);
    header[24] = (unsigned char)(lettre_height >> 16);
    header[25] = (unsigned char)(lettre_height >> 24);

    fwrite(header, sizeof(unsigned char), 54, file);
    fwrite(data, sizeof(unsigned char), output_row_padded * lettre_height, file);
    fclose(file);
    free(data);
    printf("Lettre sauvegardée : %s\n", output_filename);
}

int main() {
    const char *input_filename = "source_image.bmp";
    const char *output_filename = "lettre1.bmp";

    Image *image = lire_image_bmp(input_filename);
    if (!image) {
        return 1;
    }

    printf("Début du découpage de la lettre...\n");
    decouper_lettre(image, 10, 5, output_filename);

    free(image->data);
    free(image);
    return 0;
}

