#include <stddef.h>
#include "data.h"
#include "network.h"

void shuffle(Data *data, int n);
void SGD(Network *net, Data *training_data, int n, int epochs, int mini_batch_size, double eta);
void SGD_evaluate(Network *net, Data *training_data, int n, int epochs, int mini_batch_size, double eta, Data *test_data, int n_test);
