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
    return (unsigned int)(bytes[0]) |
           (unsigned int)(bytes[1] << 8) |
           (unsigned int)(bytes[2] << 16) |
           (unsigned int)(bytes[3] << 24);
}

// Function to read a BMP image and convert it to a custom RGB format
Image* read_image_bmp(const char *filename) {
    FILE *bmp_file = fopen(filename, "rb");
    if (!bmp_file) {
        printf("Error : unable to load BMP file.\n");
        return NULL;
    }

    fseek(bmp_file, 18, SEEK_SET);
    unsigned int width = read_uint32_le(bmp_file);
    unsigned int height = read_uint32_le(bmp_file);
    printf("Width : %u, Height : %u\n", width, height);

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char *data = (unsigned char*)malloc(row_padded * height);
    if (!data) {
        printf("Erreur : unable to allow memory.\n");
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
void detect_dimensions_letter(
    Image *image, int x, int y, int *lettre_width, int *lettre_height
) {
    int row_padded = (image->width * 3 + 3) & (~3);
    int max_x = x, max_y = y;

    for (int i = y; i < (int)image->height; i++) {
        for (int j = x; j < (int)image->width; j++) {
            int pixel_index = i * row_padded + j * 3;
            if (pixel_index >= (int)(row_padded * image->height))
                    continue;
            unsigned char blue = image->data[pixel_index];
            unsigned char green = image->data[pixel_index + 1];
            unsigned char red = image->data[pixel_index + 2];

            if (red < SEUIL_PIXEL || green < SEUIL_PIXEL || blue < SEUIL_PIXEL)
            {
                if (j > max_x) max_x = j;
                if (i > max_y) max_y = i;
            }
        }
    }

    *lettre_width = max_x - x + 1;
    *lettre_height = max_y - y + 1;

    printf("Dimensions of detected letter : width = %d, height = %d\n",
           *lettre_width, *lettre_height);
}

// Function to save the letter as an image
void cut_letter(
    Image *image, int x, int y, const char *output_filename
) {
    int letter_width, letter_height;
    detect_dimensions_letter(image, x, y, &letter_width, &letter_height);

    if (x + letter_width > (int)image->width)
        letter_width = image->width - x;
    if (y + letter_height > (int)image->height)
        letter_height = image->height - y;

    int row_padded = (image->width * 3 + 3) & (~3);
    unsigned char *data = (unsigned char*)
            malloc(letter_width * letter_height * 3);

    for (int i = 0; i < letter_height; i++) {
        for (int j = 0; j < letter_width; j++) {
            for (int k = 0; k < 3; k++) {
                data[(i * letter_width + j) * 3 + k] =
                    image->data[((y + i) * row_padded + (x + j) * 3 + k)];
            }
        }
    }

    FILE *file = fopen(output_filename, "wb");
    if (!file) {
        printf("Error : File could not be created\n");
        free(data);
        return;
    }

    int output_row_padded = (letter_width * 3 + 3) & (~3);
    unsigned char header[54] = {
        0x42, 0x4D, 0, 0, 0, 0, 0, 0, 0, 0,
        54, 0, 0, 0, 40, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 24, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0
    };

    int filesize = 54 + output_row_padded * letter_height;
    header[2] = (unsigned char)(filesize);
    header[3] = (unsigned char)(filesize >> 8);
    header[4] = (unsigned char)(filesize >> 16);
    header[5] = (unsigned char)(filesize >> 24);

    header[18] = (unsigned char)(letter_width);
    header[19] = (unsigned char)(letter_width >> 8);
    header[20] = (unsigned char)(letter_width >> 16);
    header[21] = (unsigned char)(letter_width >> 24);

    header[22] = (unsigned char)(letter_height);
    header[23] = (unsigned char)(letter_height >> 8);
    header[24] = (unsigned char)(letter_height >> 16);
    header[25] = (unsigned char)(letter_height >> 24);

    fwrite(header, sizeof(unsigned char), 54, file);
    fwrite(data, sizeof(unsigned char),
            output_row_padded * letter_height, file);
    fclose(file);
    free(data);
    printf("Letter saved : %s\n", output_filename);
}

int main() {
    const char *input_filename =
           ".cache/image_save/source_image.bmp";
    const char *output_filename = "lettre1.bmp";

    Image *image = read_image_bmp(input_filename);
    if (!image) {
        return 1;
    }

    printf("Stating cutting letter...\n");
    cut_letter(image, 10, 5, output_filename);

    free(image->data);
    free(image);
    return 0;
}
