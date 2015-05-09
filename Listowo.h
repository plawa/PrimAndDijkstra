#pragma once
#include "Macierzowo.h"

using namespace std;

class Macierzowo; //deklaracja dla kompilatora ze wzglêdu na potrzebê u¿ycia instancji tej klasy

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //deklaracja typu kolejki dla algorytmu Prima
typedef unsigned int uint;

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
	uint algorytmPrima();
	bool algorytmDijkstry(); ///////
	bool kopiujZMacierzyNieskierowany(Macierzowo *macierz);
	bool kopiujZMacierzySkierowany(Macierzowo *macierz);
private:
	bool utworzGraf(uint iloscWierzcholkow);
	bool utworzGraf();
	void usunGraf();
	void wyswietl(list<krawedz> *graf);
	bool pierwszeWczytywanie;
	uint v; //iloœæ wierzcho³ków
	uint e; //iloœæ krawêdzi
	uint v0; //nr wierzcho³ka pocz¹tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj¹cymi krawêdziom
	list<krawedz> *MST; //tablica list z krawêdzami minimalnego drzewa rozpinaj¹cego (dla alg Prima)
	FILE *plik; //uchwyt I/O
};
