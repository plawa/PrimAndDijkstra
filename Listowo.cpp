#include "stdafx.h"
#include "Listowo.h"
#include <list>
using namespace std;

Listowo::Listowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}
Listowo::~Listowo(){
	usunGraf();
}

bool Listowo::utworzGraf(int iloscWierzcholkow){
	if (pierwszeWczytywanie == false)
		usunGraf();
	v = iloscWierzcholkow;
	list<krawedz> *tempGraf = new list<krawedz>[v]; //stworzenie tablicy pustych list dla odpowiadajacych wierzcho³ków grafu
	pierwszeWczytywanie = false;
	graf = tempGraf;
	return true;
}

bool Listowo::utworzGraf(){
	return utworzGraf(v);
}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wierzcholek, sasiad, waga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wierzcholek, &sasiad, &waga);
			if (wierzcholek >= v || sasiad >= v)
				return false;
			graf[wierzcholek].push_back(*(new krawedz(sasiad, waga)));
		}
		fclose(plik);
		return true;
	} else
		return false;
}

void Listowo::wyswietl(){

}

void Listowo::usunGraf(){
	delete[] graf;
}
