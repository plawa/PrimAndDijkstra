#pragma once
#include "stdafx.h"

class Macierzowo {
public:
	Macierzowo();
	Macierzowo(int iloscWierzcholkow, int iloscKrawedzi);
	~Macierzowo();
	bool utworzGraf(int iloscWierzcholkow, int iloscKrawedzi);
	bool algorytmPrima();
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
private:
	bool usunGraf();
	bool **graf; //macierz s¹siedztwa grafu
	int *waga;
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	FILE *plik;
};
