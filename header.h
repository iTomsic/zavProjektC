#ifndef HEADER_H
#define HEADER_H


//3
typedef struct komp {
	int cijena;
	char marka[25];
	char imeKomponente[15];
	int id;
}KOMPONENTA;

int menu();
void kreiranjeDat();
void dodavanjeKomponente();
void* ucitavanjeKomponente();
void izlaz(KOMPONENTA*);

#endif //HEADER_H


