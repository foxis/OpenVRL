
#include <stdio.h>

#define _TOSTR(a) #a
#define BLAH(a) "BA: '" #a "' was told at line " _TOSTR(__LINE__) "\n"


void main()
{
	printf(BLAH( printf(blah()); ));
}