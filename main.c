#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>

//4 imenovanje identifikatora (varijabli, konstanti, polja, funkcija, pokazivača…) – upotreba camelCase, PascalCase i snake_case konzistento kroz cijeli projekt (u ovom slucaju CamelCase)
//6 organizacija izvornog kôda (nalazi se u vise datoteka, formatiranje je konzistentno...)

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


