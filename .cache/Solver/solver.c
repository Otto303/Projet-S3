#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include "../MyLib/myLib.h"
#include "file_to_grid.h"
#include "find_word.h"

int main(int argc, char *argv[])
{
	if (argc < 3) //test if correct argument number
		errx(0,"input not on fomat: \"./solver filename word\"\n");
	char* g[256];
	size_t lines_number = file_to_grid(argv[1], g);
	//create grid from the file
	char* word = mystrtolower(argv[2]);
	return find_word(g, word, lines_number);
}

/*
return value depends on:
	- 0 if word not found OR if there is an error
	- 1 if word written vertical right
	- 2 if word written vertical left
	- 3 if word written hroizontal bottom
	- 4 if word written hroizontal upper
	- 5 if word written diagonal upper-right
	- 6 if word written diagonal upper-left
	- 7 if word written diagonal bottom-right
	- 8 if word written diagonal bottom-left
All those values are managed by the 'is_word()' function (see 'is_word.c')
*/
