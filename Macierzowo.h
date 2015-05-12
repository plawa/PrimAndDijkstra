#pragma once
#include "stdafx.h"
#include "Listowo.h"
using namespace std;
#define NIESKONCZONOSC 4294967295 //max zakres dla unsigned int

struct krawedz;
struct porownajWagi;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //kolejka priorytetowa, sortuj�ca kraw�dzie rosn�co po wagach
typedef unsigned int uint;

class Macierzowo {
	friend class Listowo;
public:
	Macierzowo();
	~Macierzowo();
	bool algorytmPrima();
	bool algorytmDijkstry();
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl(); //wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //g�sto�� w %
	bool generujLosowoSkierowany(uint v, int gestosc); //g�sto�� w %
	uint getV0();
	void wyswietlPrima();
	void wyswietlDijkstry();
	void wyswietlDrogi();
	void czyscDijkstry();
	void czyscPrima();
private:
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf(); //czy�ci pami�� z nieu�ywanego ju� grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	uint zwrocIdxMinimum(uint *tablica, bool *limiter);
	bool pierwszeWczytywanie;
	bool istniejeMST;
	uint **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	uint **drzewoRozpinajace;
	uint sumaWagMST;
	uint *tabPoprzednikow; //dla Dijkstry
	uint *tabOdleglosci; //dla Dijkstry
	uint v; //ilo�� wierzcho�k�w
	uint e; //ilo�� kraw�dzi
	uint v0; //nr wierzcho�ka pocz�tkowego
	FILE *plik; //uchwyt I/O
};
