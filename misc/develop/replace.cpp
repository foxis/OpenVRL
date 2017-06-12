#include <stdio.h>
#include <string.h>

void main()
{
	char str[512];
	unsigned int i, c=0;
	unsigned long ln=0;

	do {
		str[0] = 0;
		gets(str);
		for ( i=0;i<strlen(str);i++ )
			if ( str[i]==',' )
				str[i] = '.';
		if ( strlen(str)==0 ) 
		{
			c++;
			fprintf(stderr, "c: %u      \r", c);
		}
		else 
		{
			ln++;
			fprintf(stderr, "ln: %lu      \r", ln);
			puts(str);
		}
	} while ( c<100 );
}
