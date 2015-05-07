#pragma once
#include <list>
using namespace std;

struct krawedz { //struktura reprezentuj¹ca krawêdŸ, bêdzie u¿ywana w liscie
	krawedz(unsigned int sas, unsigned int wag){
		sasiad = sas, waga = wag;
	}
	unsigned int sasiad, waga;
};

class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
	void wyswietl();
private:
	bool utworzGraf(int iloscWierzcholkow);
	bool utworzGraf();
	void usunGraf();
	bool pierwszeWczytywanie;
	int v; //iloœæ wierzcho³ków
	int e; //iloœæ krawêdzi
	int v0; //nr wierzcho³ka pocz¹tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj¹cymi krawêdziom
	FILE *plik; //uchwyt I/O
};
