#include <stddef.h>
#include "network.h"

void matrix_vector_dot(double **matrix, double *vector, double *result, size_t rows, size_t cols);
double* feedforward(Network *net, double *a);
