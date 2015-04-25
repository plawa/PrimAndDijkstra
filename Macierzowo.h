#pragma once
#include "stdafx.h"

class Macierzowo {
public:
	Macierzowo();
	Macierzowo(int iloscWierzcholkow, int iloscKrawedzi);
	~Macierzowo();
	bool utworzGraf(int iloscWierzcholkow, int iloscKrawedzi);
	bool algorytmPrima();
private:
	bool usunGraf();
	bool **graf; //macierz incydencji grafu
	int *waga;
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
};
