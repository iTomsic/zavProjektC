#ifndef HEADER_H
#define HEADER_H


//3
typedef struct komp {
	int cijena;
	char marka[50];
	char imeKomponente[50];
	int id;
}KOMPONENTA;

int menu();
void kreiranjeDat();
int menuSearch();
int menuSort();
void dodavanjeKomponente();
void* ucitavanjeKomponente();
void ispis(KOMPONENTA*);
void* searchMarka(KOMPONENTA*);
void* searchImeProizvoda(KOMPONENTA*);
void* searchCijena(KOMPONENTA*);
void subZaSortSil(KOMPONENTA*, KOMPONENTA*);
void subZaSortUzl(KOMPONENTA*, KOMPONENTA*);
void selectionSortCijenaUzl(KOMPONENTA*);
void selectionSortCijenaSil(KOMPONENTA*);
void brisanjeKomponente(KOMPONENTA*);
void izlaz(KOMPONENTA*);

#endif //HEADER_H


