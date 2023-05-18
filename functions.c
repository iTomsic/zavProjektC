#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//19 u funckijama koristi se perror

static int brojProizvoda = 0, i, j, br = 0; //5

//8
int menu() 
{
	int izbor = 0;
	static KOMPONENTA* polje = NULL; 

	printf("----------------------------------------------------------------------------------\n");
	printf("Izaberite opciju:\n\n");
	printf("1.	Dodaj proizvod\n");
	printf("2.	Uredi postojeci proizvod\n");
	printf("3.	Ispis proizvoda\n");
	printf("4.	Trazenje\n");
	printf("5.	Sortiraj proizvode po cijeni\n");
	printf("6.	Brisanje proizvoda\n");
	printf("7.	Izlaz iz programa\n");
	printf("----------------------------------------------------------------------------------\n");

	scanf("%d", &izbor);
	system("cls");


	switch (izbor) {
	case 1:
		ucitavanjeKomponente();
		if (brojProizvoda == 0) {
			kreiranjeDat();
		}
		dodavanjeKomponente();
		printf("Odabrano 1. Dodaj proizvod\n");
		break;
	case 2:
		
		printf("Odabrano 2. Uredi postojeci proizvod \n");
		break;
	case 3:
		
		printf("Odabrano 3. Ispis proizvoda \n");
		break;
	case 4:
		
		printf("Odabrano 4. Trazenje \n");
		break;
	case 5:
		
		printf("Odabrano 5. Sortiraj proizvode po cijeni \n");
		break;
	case 6:
	
		printf("Odabrano 6. Brisanje proizvoda \n");
		break;
	case 7:
		izlaz(polje);
		return 999;
		break;
	default:
		printf("\nOdabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}

	return izbor;
}

//16
void kreiranjeDat() 
{
	FILE* fp = NULL;						
	fp = fopen("komponente.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje"); 
	}

	fwrite(&brojProizvoda, sizeof(int), 1, fp);

	fclose(fp);
}

//16,17
void dodavanjeKomponente()
{
	FILE* fp = NULL;						
	fp = fopen("komponente.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");

	fread(&brojProizvoda, sizeof(int), 1, fp);
	printf("Trenutni broj proizvoda: %d\n", brojProizvoda);

	KOMPONENTA proizvod;
	proizvod.id = brojProizvoda;
	br++;

	getchar();
	printf("Unesite ime tvrtke: ");
	scanf("%24[^\n]", proizvod.marka);

	getchar();
	printf("Unesite ime proizvoda: ");
	scanf("%9[^\n]", proizvod.imeKomponente);

	getchar();
	printf("Unesite cijenu proizvoda: ");
	scanf("%d", &proizvod.cijena);

	getchar();

	fseek(fp, sizeof(KOMPONENTA) * brojProizvoda, SEEK_CUR);
	fwrite(&proizvod, sizeof(KOMPONENTA), 1, fp);
	rewind(fp);
	brojProizvoda++;
	fwrite(&brojProizvoda, sizeof(int), 1, fp);

	fclose(fp);
}

//13,14,16
void* ucitavanjeKomponente() 
{
	FILE* fp = fopen("komponente.bin", "rb");						
	if (fp == NULL) {
		printf("Niste unijeli niti jedan proizvod.\n");
		return NULL;
	}

	fread(&brojProizvoda, sizeof(int), 1, fp);
	KOMPONENTA* polje = NULL;																
	polje = (KOMPONENTA*)calloc(brojProizvoda, sizeof(KOMPONENTA));
	if (polje == NULL) {
		perror("Zauzimanje memorije");
		return NULL;
	}

	fread(polje, sizeof(KOMPONENTA), brojProizvoda, fp);

	fclose(fp);

	return polje;
}


void izlaz(KOMPONENTA* polje) 
{
	printf("\nZelite li pri izlasku programa izbrisati datoteku ili zadrzati?\n");
	printf("Ako zelite izbrisati datoteku napisite 'OBRISI', ako zelite zadrzati upisite bilo sto\n\n");

	char uvjet[7] = { '\0' }; //12
	scanf("%6s", uvjet);
	if (!strcmp("OBRISI", uvjet)) {
		remove("komponente.bin") == 0 ? printf("Izbrisali ste datoteku komponente.bin.\n") : printf("Datoteka neuspjesno izbrisani ili ona ne postoji.\n");
		printf("\nIzlaz iz programa.\n");
		free(polje);
	}
	else 
	{
		free(polje);
		printf("\nZadrzali ste datoteku.\nIzlaz iz programa\n");
	}
		
}
