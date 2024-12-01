#include <stddef.h>
#include <stdio.h>

int read_int(FILE *file);

void load_images(const char *filename, unsigned char **images, int num_images);

void load_labels(const char *filename, unsigned char *labels, int num_labels);
