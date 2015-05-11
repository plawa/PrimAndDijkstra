#pragma once
#include "Macierzowo.h"

#define NIESKONCZONOSC 4294967295

using namespace std;

class Macierzowo; //deklaracja dla kompilatora ze względu na potrzebę użycia instancji tej klasy

struct krawedz;
struct wierzcholek;
struct porownajWagi;
struct porownajOdleglosci;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //deklaracja typu kolejki dla algorytmu Prima
typedef priority_queue<wierzcholek, vector<wierzcholek>, porownajOdleglosci> TkolejkaWierzch;
typedef unsigned int uint;

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
	uint algorytmPrima();
	bool algorytmDijkstry();
	bool kopiujZMacierzyNieskierowany(Macierzowo *macierz);
	bool kopiujZMacierzySkierowany(Macierzowo *macierz);
private:
	bool utworzGraf(uint iloscWierzcholkow);
	bool utworzGraf();
	void usunGraf();
	void wyswietl(list<krawedz> *graf);
	bool pierwszeWczytywanie;
	uint v; //ilość wierzchołków
	uint e; //ilość krawędzi
	uint v0; //nr wierzchołka początkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadającymi krawędziom
	list<krawedz> *MST; //tablica list z krawędzami minimalnego drzewa rozpinającego (dla alg Prima)
	FILE *plik; //uchwyt I/O
};
