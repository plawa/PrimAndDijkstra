#include "stdafx.h"
#include "Macierzowo.h"


Macierzowo::Macierzowo(){
	Macierzowo(10, 20);
}
Macierzowo::Macierzowo(int iloscWierzcholkow, int iloscKrawedzi){
	utworzGraf(iloscWierzcholkow, iloscKrawedzi);
	srand(time(NULL));
	
}
Macierzowo::~Macierzowo(){
	
}

bool Macierzowo::algorytmPrima(){

	return true;
}

bool Macierzowo::utworzGraf(int iloscWierzcholkow, int iloscKrawedzi){
	v = iloscWierzcholkow;
	e = iloscKrawedzi;
	bool **tempGraf = new bool*[v];
	waga = new int[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new bool[v];
		waga[i] = rand()%100;
	}
	
	return true;
}

bool Macierzowo::usunGraf(){
	return true;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê nr wierzcho³ka pocz¹tkowego
		for (int i = 0; i < e; i++){
			;
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}