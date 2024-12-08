#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "predict.h"

//takes file of network, and the inputs to resolve
int main(int argc, char *argv[])
{

	if (argc != 3)
		errx(1,"Not correct argument number\n");

	return predict(argv[1],argv[2]);
}
