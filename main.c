#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

//4 sve je u camelCase
//6 organizirano u vise datoteka

int main()
{
	printf("----------------------------------------------------------------------------------\n");
	printf("\t\tDOBRODOSLI U APLIKACIJU SKLADISTA RACUNALNIH KOMPONENTI!\n");
	printf("----------------------------------------------------------------------------------\n\n");

	int izbor = 1;
	while (izbor != 999) {
		izbor = menu();
	}


	return 0;

}


