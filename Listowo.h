#pragma once
#include "Macierzowo.h"
using namespace std;

#define NIESKONCZONOSC 4294967295 //max zakres dla unsigned int

class Macierzowo; //deklaracja dla kompilatora ze wzglêdu na potrzebê u¿ycia instancji tej klasy

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //kolejka priorytetowa, sortuj¹ca krawêdzie rosn¹co po wagach
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
	uint v; //iloœæ wierzcho³ków
	uint e; //iloœæ krawêdzi
	uint v0; //nr wierzcho³ka pocz¹tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj¹cymi krawêdziom
	list<krawedz> *MST; //tablica list z krawêdzami minimalnego drzewa rozpinaj¹cego (dla alg Prima)
	uint sumaWagMST;
	FILE *plik; //uchwyt I/O
};
