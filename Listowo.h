#pragma once
#include <list>
using namespace std;

struct krawedz { //struktura reprezentuj�ca kraw�d�, b�dzie u�ywana w liscie
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
	int v; //ilo�� wierzcho�k�w
	int e; //ilo�� kraw�dzi
	int v0; //nr wierzcho�ka pocz�tkowego
	list<krawedz> *graf; //tablica list ze strukturami odpowiadaj�cymi kraw�dziom
	FILE *plik; //uchwyt I/O
};
