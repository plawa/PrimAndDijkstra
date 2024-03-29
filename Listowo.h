#pragma once
#include "Macierzowo.h"
using namespace std;

#define NIESKONCZONOSC 4294967295 //max zakres dla unsigned int

class Macierzowo; //deklaracja dla kompilatora ze względu na potrzebę użycia instancji tej klasy

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //kolejka priorytetowa, sortująca krawędzie rosnąco po wagach
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
	uint v; //ilość wierzchołków
	uint e; //ilość krawędzi
	uint v0; //nr wierzchołka początkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadającymi krawędziom
	list<krawedz> *MST; //tablica list z krawędzami minimalnego drzewa rozpinającego (dla alg Prima)
	uint sumaWagMST;
	FILE *plik; //uchwyt I/O
};
