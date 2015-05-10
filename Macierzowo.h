#pragma once
#include "stdafx.h"
#include "Listowo.h"
using namespace std;

struct krawedz;
struct porownajWagi;
struct wierzch;
struct porownajOdleglosci;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //deklaracja typu kolejki dla algorytmu Prima
typedef priority_queue<wierzch, vector<wierzch>, porownajOdleglosci> TkolejkaWierzch; //dla Dijkstry
typedef unsigned int uint;

class Macierzowo {
	friend class Listowo;
public:
	Macierzowo();
	~Macierzowo();
	uint algorytmPrima();
	bool algorytmDijkstry(); //////
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl(); //wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //g�sto�� w %
	bool generujLosowoSkierowany(uint v, int gestosc); //g�sto�� w %
	uint getV0();
private:
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf(); //czy�ci pami�� z nieu�ywanego ju� grafu
	void wyswietl(uint **macierz);
	uint zwrocIdxMinimum(uint *tablica, bool *limiter);
	bool wszystkieTrue(bool *tablica);
	bool pierwszeWczytywanie;
	uint **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	uint **drzewoRozpinajace;
	uint v; //ilo�� wierzcho�k�w
	uint e; //ilo�� kraw�dzi
	uint v0; //nr wierzcho�ka pocz�tkowego
	FILE *plik; //uchwyt I/O
};
