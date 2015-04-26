#pragma once
#include "stdafx.h"

class Macierzowo {
public:
	Macierzowo();
	~Macierzowo();
	bool utworzGraf(int iloscWierzcholkow, int iloscKrawedzi);
	bool algorytmPrima();
	bool wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
private:
	void usunGraf();
	bool pierwszeWczytywanie;
	unsigned int **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	FILE *plik;
};
