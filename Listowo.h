#pragma once
#include "Macierzowo.h"

using namespace std;

class Macierzowo; //deklaracja dla kompilatora ze wzglêdu na potrzebê u¿ycia instancji tej klasy

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
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj¹cymi krawêdziom
	FILE *plik; //uchwyt I/O
};
