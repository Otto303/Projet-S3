#include <stddef.h>
#include "network.h"

void matrix_dot(double **A, double *B, double *result, int rows, int cols);
void transpose(double *vector, double **result, int size);
void cost_derivative(double *output_activations, double y, double *result, int size);
void backprop(Network *net, double *x, double *y, double **nabla_b[], double **nabla_w[]);
