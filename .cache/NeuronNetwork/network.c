#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "../MyLib/myLib.h"
#include "neuron.h"

//All of this is placeholder, do not mind
int main(int argc, char *argv[])
{
	if(argc != 2)
		errx(0,"Test Error: Not correct argument number");
	struct neuron n =
	{
		argv[1],
	};
	printf("%s\n",n.placeholder);
	return 1;
}
