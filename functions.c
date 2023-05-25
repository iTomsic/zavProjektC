#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//9 generalna upotreba pokazivaca gdje su potrebni (implementirano u funk)
//10 generalna upotreba struktura i funckija (implementirano u funk)
//19 u funckijama koristi se perror (implementirano u funk)


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
		if (polje != NULL) {
			free(polje);		//15
			polje = NULL;		//15
		}
		polje = (KOMPONENTA*)ucitavanjeKomponente();
		ispis(polje);
		printf("Odabrano 3. Ispis proizvoda \n");
		break;
	case 4:
		while (izbor != 997) {
			 izbor = menuSearch();
		}
		printf("Odabrano 4. Trazenje \n");
		break;
	case 5:
		while (izbor != 998)
			izbor = menuSort();
		printf("Odabrano 5. Sortiraj proizvode po cijeni \n");
		break;
	case 6:
		if (polje == NULL)
			printf("Nema komponenti u skladistu.");
		else
			brisanjeKomponente(polje);
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

//8,21
int menuSearch() 
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;			
	polje = (KOMPONENTA*)ucitavanjeKomponente();	//13
	printf("Pretrazi po:\n");
	printf("\t 1. Imenu tvrtke\n");
	printf("\t 2. Imenu proizvoda\n");
	printf("\t 3. Cijeni\n");
	printf("\t 4. Natrag\n");

	scanf("%d", &izbor);
	system("cls");

	switch (izbor) {
	case 1:
		searchMarka(polje);
		break;
	case 2:
		searchImeProizvoda(polje);
		break;
	case 3:
		searchCijena(polje);
		break;
	case 4:
		return 997;
	default: printf("Odabrali ste pogresan broj!\nMolim probajte ponovno.\n");
	}
	return izbor;
}

//8,20
int menuSort() 
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;						//13
	polje = (KOMPONENTA*)ucitavanjeKomponente();
	printf("Sortiranje po:\n");
	printf("\t 1. Cijeni uzlazno\n");
	printf("\t 2. Cijeni silazno\n");
	printf("\t 3. Natrag\n");

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

	fwrite(&brojProizvoda, sizeof(int), 1, fp);		//17

	fclose(fp);
}

//16,17
void dodavanjeKomponente()
{
	FILE* fp = NULL;						
	fp = fopen("komponente.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");				//19

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

	fseek(fp, sizeof(KOMPONENTA) * brojProizvoda, SEEK_CUR);	//17
	fwrite(&proizvod, sizeof(KOMPONENTA), 1, fp);
	rewind(fp);							//17
	brojProizvoda++;
	fwrite(&brojProizvoda, sizeof(int), 1, fp);			//17

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
	polje = (KOMPONENTA*)calloc(brojProizvoda, sizeof(KOMPONENTA));	//13
	if (polje == NULL) {
		perror("Zauzimanje memorije");			//19
		return NULL;
	}

	fread(polje, sizeof(KOMPONENTA), brojProizvoda, fp);

	fclose(fp);

	return polje;
}

void ispis(KOMPONENTA* polje)
{
	for (i = 0; i < brojProizvoda; i++) {
		/*printf("Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);*/

		printf("\nID: %d  Ime tvrtke:%s  Ime proizvoda:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
}

//21
void* searchMarka(KOMPONENTA* polje) 
{
	char trazenaMarka[50];
	int br = 0;

	printf("Upisite ime tvrtke/marku trazenog proizvoda:\n");
	getchar();
	scanf("%49[^\n]", trazenaMarka);

	for (i = 0; i < brojProizvoda; i++) {
		if (!strcmp(trazenaMarka, (polje + i)->marka)) {
			
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);

			br++;
		}
	}
	if (br == 0)
		printf("\nMarka nije pronadjena.\n");
	return NULL;
}

//21
void* searchImeProizvoda(KOMPONENTA* polje) {
	char trazenProizvod[50];
	int br = 0;

	printf("Upisite ime proizvoda kojeg trazite:\n");
	getchar();
	scanf("%49[^\n]", trazenProizvod);

	for (i = 0; i < brojProizvoda; i++) {
		if (!strcmp(trazenProizvod, (polje + i)->imeKomponente)) {
			
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);

			//ispis(trazenProizvod);

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

	for (i = 0; i < brojProizvoda; i++) {
		if (trazenaCijena == (polje + i)->cijena) {
			
			printf("\nIme tvrtke : % s  Ime proizvoda : % s  Cijena : % d\n", (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);

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

	int br = 0, trazenId;

	printf("Unesite ID komponente koje zelite obrisati:");
	scanf("%d", &trazenId);

	for (i = 0; i < brojProizvoda; i++) {
		if (trazenId != (polje + i)->id) {
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
