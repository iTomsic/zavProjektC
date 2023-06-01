#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//11 zastita parametara kod svih funkcija (funkcije su sigurne)

//1 odabir konkretnih primitivnih tipova podataka za rad s cjelobrojnim i realnim konstantama
//5 primjena kljucne rijeci static za globalne i lokalne varijable
static int brojKomponenti = 0, i, j, br = 0; 

//8 izbornik/podizbornici
int menu()
{
	int izbor = 0;
	
	//9 Generalno upotreba pokazivaca tamo gdje su potrebni
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
		
		//15 Sigurno brisanje memorije koja je dinamicki zauzeta...
		if (polje != NULL) {
			free(polje);		
			polje = NULL;
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

//21 pretrazivanje – pokusati koristiti ugrađenu bsearch() funkciju
int menuSearch()
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;
	polje = (KOMPONENTA*)ucitavanjeKomponente();	

	printf("\nPretrazivanje po:\n\n");
	printf("\t 1. ID-u\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 2. Imenu tvrtke/marke\n");
	printf("----------------------------------------------------------------------------------\n");
	printf("\t 3. Imenu komponente\n");
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

//20 sortiranje – pokusati koristiti ugrađenu qsort() funkciju
int menuSort()
{
	int izbor = 0;
	KOMPONENTA* polje = NULL;					
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

//16 datoteke, koristiti tekstualnu ili binarnu, provjera pokazivaca i zatvaranje datoteke
void kreiranjeDat()
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "wb");
	
	//19 upravljati s pogreskama, errno, perror(), strerror(), feof(), ferror() – neku od njih ako ne sve
	if (fp == NULL) {
		perror("Kreiranje"); 				
	}
	
	//17 koristiti funkcije fseek(), ftell(), rewind(), ovisno o potrebi – neku od njih ako ne sve
	fwrite(&brojKomponenti, sizeof(int), 1, fp);		

	fclose(fp);
}


void dodavanjeKomponente()
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "rb+");
	if (fp == NULL)
		perror("Dodavanje");				

	fread(&brojKomponenti, sizeof(int), 1, fp);
	printf("Trenutni broj komponenti: %d\n", brojKomponenti);

	KOMPONENTA komponenta;
	komponenta.id = brojKomponenti;
	br++;

	getchar();
	printf("Unesite ime tvrtke/marke: ");
	scanf("%24[^\n]", komponenta.marka);
	getchar();
	printf("Unesite ime komponente: ");
	scanf("%9[^\n]", komponenta.imeKomponente);
	getchar();
	printf("Unesite cijenu komponente: ");
	scanf("%d", &komponenta.cijena);
	getchar();

	fseek(fp, sizeof(KOMPONENTA) * brojKomponenti, SEEK_CUR);	
	fwrite(&komponenta, sizeof(KOMPONENTA), 1, fp);
	rewind(fp);							
	brojKomponenti++;
	fwrite(&brojKomponenti, sizeof(int), 1, fp);			

	fclose(fp);
}


void* ucitavanjeKomponente()
{
	FILE* fp = fopen("komponente.bin", "rb");
	if (fp == NULL) {
		printf("Niste unijeli niti jednu komponentu.\n");
		return NULL;
	}

	fread(&brojKomponenti, sizeof(int), 1, fp);
	
	//13 koristiti dinamicko zauzimanje memorije za bilo koji tip podatka...
	//14 koristiti funkcije malloc(), calloc(), realloc(), free() – neku od njih, ako ne i sve
	KOMPONENTA* polje = NULL;
	polje = (KOMPONENTA*)calloc(brojKomponenti, sizeof(KOMPONENTA));	
	if (polje == NULL) {
		perror("Zauzimanje memorije");			
		return NULL;
	}

	fread(polje, sizeof(KOMPONENTA), brojKomponenti, fp);

	fclose(fp);

	return polje;
}

//10 generalna upotreba struktura i funckija (u ovom slucaju ispis iz strukture)
void ispis(KOMPONENTA* polje)
{
	for (i = 0; i < brojKomponenti; i++) {
		printf("\nID: %d  Ime tvrtke/marke :%s  Ime komponente:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
}

void* searchID(KOMPONENTA* polje)
{
	int trazenaID, br = 0;

	printf("Unesite broj ID-a kojeg trazite:\n");
	scanf("%d", &trazenaID);

	for (i = 0; i < brojKomponenti; i++) {
		if (trazenaID == (polje + i)->id) {

			printf("\nID: %d  Ime tvrtke/marke : % s  Ime komponente : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazen ID nije pronadjen.\n");
	return NULL;
}


void* searchMarka(KOMPONENTA* polje)
{
	char trazenaMarka[50];
	int br = 0;

	printf("Upisite ime tvrtke/marku trazene komponente:\n");
	getchar();
	scanf("%49[^\n]", trazenaMarka);

	for (i = 0; i < brojKomponenti; i++) {
		if (!strcmp(trazenaMarka, (polje + i)->marka)) {

			printf("\nID: %d  Ime tvrtke/marke : % s  Ime komponente : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nMarka nije pronadjena.\n");
	return NULL;
}


void* searchImeKomponente(KOMPONENTA* polje) {
	char trazenaKomponenta[50];
	int br = 0;

	printf("Upisite ime komponente kojeg trazite:\n");
	getchar();
	scanf("%49[^\n]", trazenaKomponenta);

	for (i = 0; i < brojKomponenti; i++) {
		if (!strcmp(trazenaKomponenta, (polje + i)->imeKomponente)) {

			printf("\nID: %d  Ime tvrtke/marke : % s  Ime komponente : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena komponenta nije pronadjen.\n");
	return NULL;
}


void* searchCijena(KOMPONENTA* polje) {
	int trazenaCijena, br = 0;

	printf("Unesite broj cijene koju trazite:\n");
	scanf("%d", &trazenaCijena);

	for (i = 0; i < brojKomponenti; i++) {
		if (trazenaCijena == (polje + i)->cijena) {

			printf("\nID: %d  Ime tvrtke/marke : % s  Ime komponenta : % s  Cijena : % d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);

			br++;
		}
	}
	if (br == 0)
		printf("\nTrazena cijena nije pronadjena.\n");
	return NULL;
}


void subZaSortSil(KOMPONENTA* veci, KOMPONENTA* manji)
{
	KOMPONENTA temp = { 0 };
	temp = *veci;
	*veci = *manji;
	*manji = temp;
}


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
		printf("\nID: %d Ime tvrtke/marke :%s  Ime komponenta:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
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
		printf("\nID: %d Ime tvrtke/marke :%s  Ime komponenta:%s  Cijena: %d\n", (polje + i)->id, (polje + i)->marka, (polje + i)->imeKomponente, (polje + i)->cijena);
	}
	printf("\n");
}


void brisanjeKomponente(KOMPONENTA* polje)
{
	FILE* fp = NULL;
	fp = fopen("komponente.bin", "wb");
	if (fp == NULL) {
		perror("Brisanje");
	}

	rewind(fp);									
	fseek(fp, sizeof(int), SEEK_CUR);			

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

	//12 koristiti staticki zauzeta polja
	char uvjet[7] = { '\0' }; 
	scanf("%6s", uvjet);
	
	//18. Koristiti funkcije remove(), rename(), po potrebi implementirati funkciju za kopiranje datoteka.
	if (!strcmp("OBRISI", uvjet)) {
	
		remove("komponente.bin") == 0 ? printf("\nDatoteka komponente.bin uspjesno izbrisana.\n") : printf("\nDatoteka neuspjesno izbrisana ili ne postoji.\n");	
		printf("\n\nIzlaz iz programa.\n");
		free(polje);
		
	}
	else
	{
		free(polje);
		printf("\nZadrzali ste datoteku.\n\nIzlaz iz programa.\n");
	}

}
