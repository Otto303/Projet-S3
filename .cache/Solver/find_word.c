#include <stdlib.h>
#include <stdio.h>
#include "../MyLib/myLib.h"
#include "is_word.h"

unsigned char find_word(char* grid[], char word[], size_t lines_number)
{
//test for each letter if the word start here, print start & end coordonates
	
	size_t word_size = mystrlen(word);
	unsigned char b = 0; //condition & return value
	size_t y = 0;
	
	while(b==0 && y<lines_number)
	//for each line, as long as we didn't find the word
	{
		size_t x = 0;
		while(b==0 && grid[y][x]!=0) //for each character in the line
		{
			//test not necessary but useful for optimisation
			if (grid[y][x] == word[0])
			{
				b = is_word(grid, lines_number, x, y,
						word,word_size);
				//test if the word start here in any direction
				// + handle the print
				//if it does then b becomes != 0
			}
			x++;
		}
		y++;
	}
	
	if(b == 0)
		printf("Not found\n");
	
	return b;
	//return 0 if word not found
	//else return an integer (as a char) >= 1 & <= 8 corresponding to
	//the direction of the word from the start coordonates
	//see is_word.c for further information (summary in solver.c)
}
