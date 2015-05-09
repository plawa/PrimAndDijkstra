#pragma once
#include "Macierzowo.h"

using namespace std;

class Macierzowo; //deklaracja dla kompilatora ze wzgl�du na potrzeb� u�ycia instancji tej klasy

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //deklaracja typu kolejki dla algorytmu Prima

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
	bool algorytmPrima(); //////
	bool algorytmDijkstry(); ///////
	bool kopiujZMacierzyNieskierowany(Macierzowo *macierz);
	bool kopiujZMacierzySkierowany(Macierzowo *macierz);
private:
	bool utworzGraf(int iloscWierzcholkow);
	bool utworzGraf();
	void usunGraf();
	bool pierwszeWczytywanie;
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj�cymi kraw�dziom
	FILE *plik; //uchwyt I/O
};
