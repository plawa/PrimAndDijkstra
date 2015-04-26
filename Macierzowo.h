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
	unsigned int **graf; //nr wiersza/nr kolumny - macierz s¹siedztwa grafu
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	FILE *plik;
};
