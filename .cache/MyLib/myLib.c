#include <stdlib.h>
#include <stdio.h>

size_t mystrlen(char *s)
//give size of a string
{
	size_t i = 0;
	while( *(s+i) != 0 )
		i++;
	return i;
}

char* mystrcpy(char* s)
//return a copy of a string
//WARNING! remeber to free the new string after used!
{
	char *s2;
	s2 = malloc(1);
	size_t i = 0;
	while (*(s+i) != '\0')
	{
		s2 = realloc(s2,i+1);
		*(s2+i) = *(s+i);
		i++;
	}
	*(s2+i) = '\0';
	return s2;
}

void mystrtolower(char* s)
//lower every capital letter in place
{
	for(char *p = s; *p != 0; p++)
		if('A'<=*p && *p<='Z')
			*p+=32;
}
