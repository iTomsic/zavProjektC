#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//9 generalna upotreba pokazivaca gdje su potrebni (implementirano u funk)
//10 generalna upotreba struktura i funckija (implementirano u funk)
//19 u funckijama koristi se perror (implementirano u funk)


static int brojKomponenti = 0, i, j, br = 0; //5

//8
int menu()
{
	int izbor = 0;
	static KOMPONENTA* polje = NULL;

	printf("\nIzaberite opciju:\n\n");
	printf("  1.	Dodavanje komponente\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("  2.	Ispis komponente\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("  3.	Trazenje po kategoriji\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("  4.	Sortiranje komponenti po cijeni\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("  5.	Brisanje komponenti\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("  6.	Izlaz iz programa\n");
	printf("----------------------------------------------------------------------------------\n");

	scanf("%d", &izbor);
	system("cls");


	switch (izbor) {
	case 1:

		ucitavanjeKomponente();
		if (brojKomponenti == 0) {
			kreiranjeDat();
		}
		dodavanjeKomponente();
		break;

	case 2:

		if (polje != NULL) {
			free(polje);		//15
			polje = NULL;		//15
		}
		polje = (KOMPONENTA*)ucitavanjeKomponente();
		ispis(polje);
		break;

	case 3:

		while (izbor != 997) {
			izbor = menuSearch();
		}
		break;

	case 4:

		while (izbor != 998)
			izbor = menuSort();
		break;

	case 5:

		if (polje == NULL)
			printf("\nNema komponenti u skladistu.\n");
		else
			brisanjeKomponente(polje);
		break;

	case 6:

		izlaz(polje);
		return 999;
		break;

	default:

		printf("\nOdabrali ste pogresan broj!\nMolim pokusajte ponovno.\n");

	}

	return izbor;
}

//8,21
int menuSearch()
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;
	polje = (KOMPONENTA*)ucitavanjeKomponente();	//13

	printf("\nPretrazivanje po:\n\n");
	printf("\t 1. ID-u\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 2. Imenu tvrtke\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 3. Imenu proizvoda\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 4. Cijeni\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 5. Povratak\n");
	printf("----------------------------------------------------------------------------------\n");

	scanf("%d", &izbor);
	system("cls");

	switch (izbor) {
	case 1:
		
		searchID(polje);
		break;

	case 2:
		
		searchMarka(polje);
		break;

	case 3:
		
		searchImeKomponente(polje);
		break;

	case 4:
		
		searchCijena(polje);
		break;

	case 5:
		
		return 997;

	default: printf("Odabrali ste pogresan broj!\nMolim pokusajte ponovno.\n");

	}
	return izbor;
}

//8,20
int menuSort()
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;						//13
	polje = (KOMPONENTA*)ucitavanjeKomponente();

	printf("\nSortiranje po:\n\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 1. Cijeni uzlazno\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 2. Cijeni silazno\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 3. Povratak\n");
	printf("----------------------------------------------------------------------------------\n");

	scanf("%d", &izbor);
	system("cls");

	switch (izbor) {
	case 1:

		selectionSortCijenaUzl(polje);
		break;

	case 2:

		selectionSortCijenaSil(polje);
		break;

	case 3:

		return 998;

	default: printf("Odabrali ste pogresan broj!\nMolim pokusajte ponovno.\n");

	}
	return izbor;
}

//16
void kreiranjeDat()
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "wb");
	if (fp == NULL) {
		perror("Kreiranje"); 				//19
	}

	fwrite(&brojKomponenti, sizeof(int), 1, fp);		//17

	fclose(fp);
}

//16,17
void dodavanjeKomponente()
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");				//19

	fread(&brojKomponenti, sizeof(int), 1, fp);
	printf("Trenutni broj proizvoda: %d\n", brojKomponenti);

	KOMPONENTA komponenta;
	komponenta.id = brojKomponenti;
	br++;

	getchar();
	printf("Unesite ime tvrtke: ");
	scanf("%24[^\n]", komponenta.marka);
	getchar();
	printf("Unesite ime proizvoda: ");
	scanf("%9[^\n]", komponenta.imeKomponente);
	getchar();
	printf("Unesite cijenu proizvoda: ");
	scanf("%d", &komponenta.cijena);
	getchar();

	fseek(fp, sizeof(KOMPONENTA) * brojKomponenti, SEEK_CUR);	//17
	fwrite(&komponenta, sizeof(KOMPONENTA), 1, fp);
	rewind(fp);							//17
	brojKomponenti++;
	fwrite(&brojKomponenti, sizeof(int), 1, fp);			//17

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

	fread(&brojKomponenti, sizeof(int), 1, fp);
	KOMPONENTA* polje = NULL;
	polje = (KOMPONENTA*)calloc(brojKomponenti, sizeof(KOMPONENTA));	//13
	if (polje == NULL) {
		perror("Zauzimanje memorije");			//19
		return NULL;
	}

	fread(polje, sizeof(KOMPONENTA), brojKomponenti, fp);

	fclose(fp);

	return polje;
}

void ispis(KOMPONENTA* polje)
{
	for (i = 0; i < brojKomponenti; i++) {
		printf("\nID: %d  Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
}

void* searchID(KOMPONENTA* polje)
{
	int trazenaID, br = 0;

	printf("Unesite broj ID-a kojeg trazite:\n");
	scanf("%d", &trazenaID);

	for (i = 0; i < brojKomponenti; i++) {
		if (trazenaID == (polje + i)->id) {

			printf("\nID: %d  Ime tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazen ID nije pronadjen.\n");
	return NULL;
}

//21
void* searchMarka(KOMPONENTA* polje)
{
	char trazenaMarka[50];
	int br = 0;

	printf("Upisite ime tvrtke/marku trazenog proizvoda:\n");
	getchar();
	scanf("%49[^\n]", trazenaMarka);

	for (i = 0; i < brojKomponenti; i++) {
		if (!strcmp(trazenaMarka, (polje + i)->marka)) {

			printf("\nID: %d  Ime tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nMarka nije pronadjena.\n");
	return NULL;
}

//21
void* searchImeKomponente(KOMPONENTA* polje) {
	char trazenProizvod[50];
	int br = 0;

	printf("Upisite ime proizvoda kojeg trazite:\n");
	getchar();
	scanf("%49[^\n]", trazenProizvod);

	for (i = 0; i < brojKomponenti; i++) {
		if (!strcmp(trazenProizvod, (polje + i)->imeKomponente)) {

			printf("\nID: %d  Ime tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazen proizvod nije pronadjen.\n");
	return NULL;
}

//21
void* searchCijena(KOMPONENTA* polje) {
	int trazenaCijena, br = 0;

	printf("Unesite broj cijene koju trazite:\n");
	scanf("%d", &trazenaCijena);

	for (i = 0; i < brojKomponenti; i++) {
		if (trazenaCijena == (polje + i)->cijena) {

			printf("\nID: %d  Ime tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);

			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena cijena nije pronadjena.\n");
	return NULL;
}

//20
void subZaSortSil(KOMPONENTA* veci, KOMPONENTA* manji)
{
	KOMPONENTA temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}

//20
void subZaSortUzl(KOMPONENTA* manji, KOMPONENTA* veci)
{
	KOMPONENTA temp = { 0 };
	temp = *manji;
	*manji = *veci;
	*veci = temp;
}

void selectionSortCijenaUzl(KOMPONENTA* polje) {
	for (int j = 0; j < brojKomponenti; j++) {
		for (int i = 0; i < brojKomponenti - 1; i++) {
			if (polje[i].cijena > polje[i + 1].cijena) {
				subZaSortUzl((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojKomponenti; i++) {
		printf("\nID: %d Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
	printf("\n");
}

void selectionSortCijenaSil(KOMPONENTA* polje) {
	for (int j = 0; j < brojKomponenti; j++) {
		for (int i = 0; i < brojKomponenti - 1; i++) {
			if (polje[i].cijena < polje[i + 1].cijena) {
				subZaSortSil((polje + i), (polje + i + 1));
			}
		}
	}
	for (i = 0; i < brojKomponenti; i++) {
		printf("\nID: %d Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
	printf("\n");
}

//16
void brisanjeKomponente(KOMPONENTA* polje)
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje");
	}

	rewind(fp);										//17
	fseek(fp, sizeof(int), SEEK_CUR);				//17

	int idZaBrisanje, br = 0;

	printf("Unesite ID komponente koje zelite obrisati:");
	scanf("%d", &idZaBrisanje);

	for (i = 0; i < brojKomponenti; i++) {
		if (idZaBrisanje != (polje + i)->id) {
			fwrite((polje + i), sizeof(KOMPONENTA), 1, fp);
			br++;
		}
	}

	rewind(fp);
	fwrite(&br, sizeof(int), 1, fp);
	fclose(fp);

}

void izlaz(KOMPONENTA* polje)
{
	printf("Zelite li pri izlasku izbrisati datoteku ili je zadrzati?\n");
	printf("Ukoliko zelite izbrisati datoteku napisite 'OBRISI'\n\n");

	char uvjet[7] = { '\0' }; //12
	scanf("%6s", uvjet);
	if (!strcmp("OBRISI", uvjet)) {
		remove("komponente.bin") == 0 ? printf("\nDatoteka komponente.bin uspjesno izbrisana.\n") : printf("\nDatoteka neuspjesno izbrisana ili ne postoji.\n");	//18
		printf("\n\nIzlaz iz programa.\n");
		free(polje);
	}
	else
	{
		free(polje);
		printf("\nZadrzali ste datoteku.\n\nIzlaz iz programa.\n");
	}

}
