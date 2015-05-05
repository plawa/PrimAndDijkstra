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
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	list<int> graf; //lista 
	FILE *plik; //uchwyt I/O
};
