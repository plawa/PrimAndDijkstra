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
	void wyswietl(); //wy�wietla graf w postaci macierzy s�siedztwa na ekranie
	bool generujLosowoNieskierowany(int v, int gestosc); //g�sto�� w %
	bool generujLosowoSkierowany(int v, int gestosc); //g�sto�� w %
private:
	bool utworzGraf(int iloscWierzcholkow); //tworzy pusty graf (same wierzcho�ki, bez kraw�dzi)
	bool utworzGraf(); //tworzy pusty graf nie zmieniaj�c obecnej ilo�ci wierzcho�k�w
	void usunGraf(); //czy�ci pami�� z nieu�ywanego ju� grafu
	bool pierwszeWczytywanie;
	unsigned int **graf; //nr wiersza/nr kolumny - macierz s�siedztwa grafu
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	FILE *plik; //uchwyt I/O
};
