#include <stdafx.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std;

void main()
{
	long verteces, faces, i;
	long itmp, A,B,C;
	double ftmp, X, Y, Z, U, V;
	char str[512];

	do {
		cin>>str;
	} while ( strcmp(str, "Vertices:")!=0 );
	cin>>verteces;
	cout<<verteces;
	do {
		cin>>str;
	} while ( strcmp(str, "Faces:")!=0 );
	cin>>faces;
	cout << " " << faces;
	cout << " " << faces*3 << "\n";
	for ( i=0;i<verteces;i++ )
	{
		do {
			cin>>str;
		} while ( strncmp(str, "X:",2) );
		if ( str[3]==' ' )
			cin >> X;
		else
			X = atof(str+2);
		do {
			cin>>str;
		} while ( strncmp(str, "Y:",2) );
		if ( str[3]==' ' )
			cin >> Y;
		else
			Y = atof(str+2);
		do {
			cin>>str;
		} while ( strncmp(str, "Z:",1) );
		if ( str[3]==' ' )
			cin >> Z;
		else
			Z = atof(str+2);
		cout << X << " ";
		cout << Z << " ";
		cout << Y << "\n";
	}

	do {
		cin>>str;
	} while ( strcmp(str, "list:") );
	for ( i=0;i<faces;i++ )
	{
		cout << "3 ";
		do {
			cin>>str;
		} while ( strcmp(str, "Face") );
		cin >> str;
		cin >> str;
		A = atol(str+2)+1;
		cin >> str;
		B =  atol(str+2)+1;
		cin >> str;
		C =  atol(str+2)+1;

		cout << A << " " << C << " " << B << "\n";
	}
}