#include <stdlib.h>
#include <stdio.h>
#include "../MyLib/myLib.h"
#include "directions.h"

unsigned char is_word(char* grid[], size_t lines_number, size_t x, size_t y, char word[], size_t word_size)
//return an integer >= 1 (depending of the word direction) if given word start at coordonnates(x,y), else return 0.
{
	//test for any possible direction (all 8 characters around this one) if the word_size following characters form the word
	if (is_horizontal_right(grid,x,y,word,word_size))
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x+(word_size-1),y); //print start and end coordonates
		return 1;
	}
	else if (is_horizontal_left(grid,x,y,word,word_size))
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x-(word_size-1),y); //print start and end coordonates
		return 2;
	}
	else if (is_vertical_bottom(grid,lines_number,x,y,word,word_size))
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x,y+(word_size-1)); //print start and end coordonates
		return 3;
	}
	else if (is_vertical_upper(grid,x,y,word,word_size))
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x,y-(word_size-1)); //print start and end coordonates
		return 4;
	}
	else if (is_diagonal_upper_right(grid,x,y,word,word_size))
	{
		//Print is handled by function itself
		return 5;
	}
	else if (is_diagonal_upper_left(grid,x,y,word,word_size))
	{
		//Print is handled by function itself
		return 6;
	}
	else if (is_diagonal_bottom_right(grid,lines_number,x,y,word,word_size))
	{
		//Print is handled by function itself
		return 7;
	}
	else if (is_diagonal_bottom_left(grid,lines_number,x,y,word,word_size))
	{
		//Print is handled by function itself
		return 8;
	}
	else return 0; //if the word doesn't start here return 0
}
