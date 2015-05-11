#pragma once
#include "stdafx.h"
#include "Listowo.h"

#define NIESKONCZONOSC 4294967295

using namespace std;

struct krawedz;
struct porownajWagi;
struct wierzch;
struct porownajOdleglosci;
typedef priority_queue<krawedz, vector<krawedz>, porownajWagi> TkolejkaKrawedzi; //deklaracja typu kolejki dla algorytmu Prima
typedef unsigned int uint;

class Macierzowo {
	friend class Listowo;
public:
	Macierzowo();
	~Macierzowo();
	bool algorytmPrima();
	bool algorytmDijkstry();
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl(); //wyœwietla graf w postaci macierzy s¹siedztwa na ekranie
	bool generujLosowoNieskierowany(uint v, int gestosc); //gêstoœæ w %
	bool generujLosowoSkierowany(uint v, int gestosc); //gêstoœæ w %
	uint getV0();
	void wyswietlPrima();
	void wyswietlDijkstry();
private:
	bool utworzGraf(uint iloscWierzcholkow); //tworzy pusty graf (same wierzcho³ki, bez krawêdzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj¹c obecnej iloœci wierzcho³ków
	void usunGraf(); //czyœci pamiêæ z nieu¿ywanego ju¿ grafu
	void usun(uint **macierz);
	void usun(bool **macierz);
	void wyswietl(uint **macierz);
	uint zwrocIdxMinimum(uint *tablica, bool *limiter);
	bool pierwszeWczytywanie;
	bool istniejeMST;
	uint **graf; //nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	uint **drzewoRozpinajace;
	uint sumaWagMST;
	uint *tabPoprzednikow; //dla Dijkstry
	uint *tabOdleglosci; //dla Dijkstry
	uint v; //iloœæ wierzcho³ków
	uint e; //iloœæ krawêdzi
	uint v0; //nr wierzcho³ka pocz¹tkowego
	FILE *plik; //uchwyt I/O
};
