#include <stddef.h>

//Functions that test if the character at given coordonates
//is the start of the word in x direction

//horizontal tests
unsigned char is_horizontal_right(char* grid[], size_t x, size_t y,
				char word[], size_t word_size);

unsigned char is_horizontal_left(char* grid[], size_t x, size_t y,
				char word[], size_t word_size);

//vertical tests
unsigned char is_vertical_bottom(char* grid[], size_t lines_number,
				size_t x, size_t y,
				char word[], size_t word_size);

unsigned char is_vertical_upper(char* grid[], size_t x, size_t y,
				char word[], size_t word_size);

//diagonal tests
unsigned char is_diagonal_bottom_right(char* grid[], size_t lines_number,
				size_t x, size_t y,
				char word[], size_t word_size);

unsigned char is_diagonal_bottom_left(char* grid[], size_t lines_number,
				size_t x, size_t y,
				char word[], size_t word_size);

unsigned char is_diagonal_upper_right(char* grid[], size_t x, size_t y,
				char word[], size_t word_size);

unsigned char is_diagonal_upper_left(char* grid[], size_t x, size_t y,
				char word[], size_t word_size);
