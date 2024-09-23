#include <stdlib.h>
#include <stdio.h>

size_t mystrlen(char *s)
//give len of a string
{
	size_t i = 0;
	while( *(s+i) != 0 )
		i++;
	return i;
}

char* mystrcpy(char* s)
//returna a copy of a string
{
	char *s2;
	s2 = (char*)malloc(20);
	char *p1 = s;
	char *p2 = s2;
	while (*p1 != '\0')
	{
		*p2 = *p1;
		p1++;
		p2++;
	}
	*p2 = '\0';
	return s2;
}

char* mystrtolower(char* s)
//return a copy of a string with every capital letters lowered
{
	char *s2 = mystrcpy(s);
	for(char *p = s2; *p != 0; p++)
		if(65<=*p && *p<=90)
			*p+=32;
	return s2;
}
