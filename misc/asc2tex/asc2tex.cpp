// asc2tex.cpp : Defines the entry point for the console application.
//

#include <stdafx.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

void _tmain()
{
	long verteces, faces, i;
	double ftmp, U, V;
	char str[512];

	do {
		cin>>str;
	} while ( strcmp(str, "Vertices:")!=0 );
	cin>>verteces;
	cout<<verteces<<"\n";
	do {
		cin>>str;
	} while ( strcmp(str, "Faces:")!=0 );
	cin>>faces;
	cin>>str;
	if ( strcmpi(str,"Mapped")!=0  )
		return;
	for ( i=0;i<verteces;i++ )
	{
		do {
			cin>>str;
		} while ( strncmp(str, "U:",2) );
		if ( str[3]==' ' )
			cin >> U;
		else
			U = atof(str+2);
		do {
			cin>>str;
		} while ( strncmp(str, "V:",2) );
		if ( str[3]==' ' )
			cin >> V;
		else
			V = atof(str+2);
		cout << U << " ";
		cout << V << "\n";
	}
}