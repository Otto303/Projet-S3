#include <stdlib.h>
#include <stdio.h>


//Each of these functions tests for its respective direction
//if the character at given coordonates and the word_size following ones
//form the word.

//return 1 if the word start there and 0 if it doesn't

//WARNING: Those functions don't all take the same amount of parameters!
//Be sure to check when using them!


unsigned char is_horizontal_right(char* grid[], size_t x, size_t y,
				char word[], size_t word_size)
//return 1 if word start at coordonnates(x,y), 0 else. Test is horizontal only
{
	size_t i = 0;
	while(grid[y][x+i]!=0 && word[i]!=0 && grid[y][x+i]==word[i])
		i++;
	if(i==word_size)
		return 1;
	else
		return 0;
}


unsigned char is_horizontal_left(char* grid[], size_t x, size_t y,
				char word[], size_t word_size)
//return 1 if word start at coordonnates(x,y), 0 else.
//Test is horizontal backward only
{
	size_t i = 0;
	while(x>=i && word[i]!=0 && grid[y][x-i]==word[i])
		i++;
	if(i==word_size)
		return 1;
	else
		return 0;
}


unsigned char is_vertical_bottom(char* grid[], size_t lines_number, size_t x,
				size_t y, char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is vertical only
{
	size_t i = 0;
	while(y+i<lines_number && word[i]!=0 && grid[y+i][x]==word[i])
		i++;
	if(i==word_size)
		return 1;
	else
		return 0;
}


unsigned char is_vertical_upper(char* grid[], size_t x, size_t y,
				char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is vertical backward only
{
	size_t i = 0;
	while(y>=i && word[i]!=0 && grid[y-i][x]==word[i])
		i++;
	if(i==word_size)
		return 1;
	else
		return 0;
}


unsigned char is_diagonal_bottom_right(char* grid[], size_t lines_number,
					size_t x, size_t y,
					char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is diagonal only towards the bottom right
{
	size_t i = 0;
	while(y+i<lines_number && grid[y+i][x+i]!=0 &&
		word[i]!=0 && grid[y+i][x+i]==word[i])
		i++;
	if(i==word_size)
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x+i-1,y+i-1);
		return 1;
	}
	else
		return 0;
}


unsigned char is_diagonal_bottom_left(char* grid[], size_t lines_number,
					size_t x, size_t y,
					char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is diagonal only towards the bottom left
{
	size_t i = 0;
	while(y+i<lines_number && x>=i && word[i]!=0 &&
		grid[y+i][x-i]==word[i])
		i++;
	if(i==word_size)
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x-i+1,y+i-1);
		return 1;
	}
	else
		return 0;
}


unsigned char is_diagonal_upper_right(char* grid[], size_t x, size_t y,
					char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is diagonal only towards the upper right
{
	size_t i = 0;
	while(y>=i && grid[y-i][x+i]!=0 && word[i]!=0 &&
		grid[y-i][x+i]==word[i])
		i++;
	if(i==word_size)
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x+i-1,y-i+1);
		return 1;
	}
	else
		return 0;
}


unsigned char is_diagonal_upper_left(char* grid[], size_t x, size_t y,
					char word[], size_t word_size)
//return 1 if given word start at coordonnates(x,y), 0 else.
//Test is diagonal only towards the upper left
{
	size_t i = 0;
	while(y>=i && x>=i && word[i]!=0 && grid[y-i][x-i]==word[i])
		i++;
	if(i==word_size)
	{
		printf("(%zu,%zu)(%zu,%zu)\n",x,y,x-i+1,y-i+1);
		return 1;
	}
	else
		return 0;
}
