#pragma once
#include "Macierzowo.h"
using namespace std;

#define NIESKONCZONOSC 4294967295 //max zakres dla unsigned int

class Macierzowo; //deklaracja dla kompilatora ze wzgl�du na potrzeb� u�ycia instancji tej klasy

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //kolejka priorytetowa, sortuj�ca kraw�dzie rosn�co po wagach
typedef unsigned int uint;

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
	bool algorytmPrima();
	bool algorytmDijkstry();
	bool kopiujZMacierzyNieskierowany(Macierzowo *macierz);
	bool kopiujZMacierzySkierowany(Macierzowo *macierz);
	void wyswietlDijkstry();
	void wyswietlPrima();
	void czyscDijkstry();
	void czyscPrima();
private:
	bool utworzGraf(uint iloscWierzcholkow);
	bool utworzGraf();
	void usunGraf();
	void wyswietl(list<krawedz> *graf);
	uint zwrocIdxMinimum(uint *tabOdleglosci, bool *limiter);
	bool pierwszeWczytywanie;
	uint *tabPoprzednikow; //dla Dijkstry
	uint *tabOdleglosci; //dla Dijkstry
	uint v; //ilo�� wierzcho�k�w
	uint e; //ilo�� kraw�dzi
	uint v0; //nr wierzcho�ka pocz�tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj�cymi kraw�dziom
	list<krawedz> *MST; //tablica list z kraw�dzami minimalnego drzewa rozpinaj�cego (dla alg Prima)
	uint sumaWagMST;
	FILE *plik; //uchwyt I/O
};
