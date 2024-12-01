#include <stddef.h>
#include "data.h"
#include "network.h"

double* zeros(int size);
double** matrix_zeros(int rows, int cols);
void update_mini_batch(Network *net, Data *mini_batch, int mini_batch_size, double eta);
