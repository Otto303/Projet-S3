#include <stdlib.h>
#include <stdio.h>
#include "../MyLib/myLib.h"

size_t file_to_grid(char* filename, char* g[])
//transform the file content into a valid grid of characters to work with
//return number of lines
{
	FILE *file_ptr;
	file_ptr = fopen(filename, "r");
	char str[256];
	size_t i = 0;
	// Reading string using fgets
	while (fgets(str, sizeof(str), file_ptr) != NULL)
	{
		g[i]=mystrcpy(str);
		mystrtolower(g[i]);
		i++;
	}
	fclose(file_ptr);
	return i;
}

void free_grid(char* g[], size_t line_number)
//Due to the use of malloc in mystrcpy, we use this function to free
{
	for(size_t i = 0; i<line_number; i++)
	{
		free(g[i]);
	}
}
