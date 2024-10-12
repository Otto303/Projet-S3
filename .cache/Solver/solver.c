#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "../MyLib/myLib.h"
#include "find_word.h"
#include "file_to_grid.h"

int main(int argc, char *argv[])
{
	if (argc < 3) //test if not too few arguments
		errx(0,"input not on fomat: \"./solver filename word\"\n");
	
	char* g[256];
	size_t lines_number = file_to_grid(argv[1], g);
	//create grid from the file
	
	char* word = mystrcpy(argv[2]);
	mystrtolower(word);
	
	int val = find_word(g, word, lines_number); //search for the word
	
	free(word);
	free_grid(g, lines_number); //free every line of grid
	
	return val;
}

/*
return value depends on:
	- 0 if word not found (or if there is an error)
	- 1 if word written hroizontal right
	- 2 if word written hroizontal left
	- 3 if word written vertical bottom
	- 4 if word written vertical upper
	- 5 if word written diagonal upper-right
	- 6 if word written diagonal upper-left
	- 7 if word written diagonal bottom-right
	- 8 if word written diagonal bottom-left

See the following shema:
	(6)	(4)	(5)
	(2) FirstLetter (1)
	(8)	(3)	(7)

All those values (except the error one) are managed inside is_word.c
*/
