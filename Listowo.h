#pragma once
#include <list>
using namespace std;

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
private:
	bool utworzGraf(int iloscWierzcholkow);
	bool pierwszeWczytywanie;
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	list<int> graf; //lista 
	FILE *plik; //uchwyt I/O
};
