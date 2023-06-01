#ifndef HEADER_H
#define HEADER_H


//3 primjena typedef sa strukturama i unijama, po potrebi s enum tipovima podataka tamo gdje treba (u ovom slucaju KOMPONENTA)
//2 odabir konkretnih složenih tipova podataka za rad sa specifičnim objektima (u ovom slucaju KOMPONENTA)
typedef struct komp {
	int id;
	int cijena;
	char marka[50];
	char imeKomponente[50];
}KOMPONENTA;

int menu();
void kreiranjeDat();
int menuSearch();
int menuSort();
void dodavanjeKomponente();
void* ucitavanjeKomponente();
void ispis(KOMPONENTA*);
void* searchID(KOMPONENTA*);
void* searchMarka(KOMPONENTA*);
void* searchImeKomponente(KOMPONENTA*);
void* searchCijena(KOMPONENTA*);
void subZaSortSil(KOMPONENTA*, KOMPONENTA*);
void subZaSortUzl(KOMPONENTA*, KOMPONENTA*);
void selectionSortCijenaUzl(KOMPONENTA*);
void selectionSortCijenaSil(KOMPONENTA*);
void brisanjeKomponente(KOMPONENTA*);
void izlaz(KOMPONENTA*);

#endif //HEADER_H

