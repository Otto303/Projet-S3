#include <stddef.h>
#include "data.h"
#include "network.h"

size_t argmax(double *array, int length);
int evaluate(Network *net, Data *test_data, int test_data_size);
