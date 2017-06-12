#include <iostream.h>
#include <string.h>
#include <stdlib.h>

void main()
{
	long verteces, faces, i;
	long itmp;
	float ftmp;
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
		} while ( strcmp(str, "X:") );
		cin >> ftmp;
		cout << ftmp << " ";
		do {
			cin>>str;
		} while ( strcmp(str, "Y:") );
		cin >> ftmp;
		cout << ftmp << " ";
		do {
			cin>>str;
		} while ( strcmp(str, "Z:") );
		cin >> ftmp;
		cout << ftmp << "\n";
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
		cout << atol(str+2)+1 << " ";
		cin >> str;
		cout << atol(str+2)+1 << " ";
		cin >> str;
		cout << atol(str+2)+1 << "\n";
	}
}