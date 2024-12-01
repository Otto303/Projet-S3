#include <stddef.h>
#include "network.h"

unsigned char save_network(Network *net, const char *filename);
Network* load_network(const char *filename);
