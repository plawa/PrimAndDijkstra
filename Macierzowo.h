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
	bool **graf; //macierz s�siedztwa grafu
	int *waga;
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	FILE *plik;
};
