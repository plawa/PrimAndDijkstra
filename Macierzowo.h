#pragma once
#include "stdafx.h"
#include "Listowo.h"

class Macierzowo {
	friend class Listowo;
public:
	Macierzowo();
	~Macierzowo();
	bool algorytmPrima(); //////
	bool algorytmDijkstry(); //////
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl(); //wyœwietla graf w postaci macierzy s¹siedztwa na ekranie
	bool generujLosowoNieskierowany(int v, int gestosc); //gêstoœæ w %
	bool generujLosowoSkierowany(int v, int gestosc); //gêstoœæ w %
private:
	bool utworzGraf(int iloscWierzcholkow); //tworzy pusty graf (same wierzcho³ki, bez krawêdzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj¹c obecnej iloœci wierzcho³ków
	void usunGraf(); //czyœci pamiêæ z nieu¿ywanego ju¿ grafu
	bool pierwszeWczytywanie;
	unsigned int **graf; //nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	FILE *plik; //uchwyt I/O
};
