#include <stdlib.h>
#include <stdio.h>
#include "../MyLib/myLib.h"

size_t file_to_grid(char* filename, char* g[])
//transform the file content into a valid grid of characters to work with
{
	FILE *file_ptr;
	file_ptr = fopen(filename, "r");
	char str[256];
	size_t i = 0;
	// Reading stinrg using fgets
	while (fgets(str, sizeof(str), file_ptr) != NULL)
	{
		g[i]=mystrtolower(str);
		i++;
	}
	fclose(file_ptr);
	return i;
}
