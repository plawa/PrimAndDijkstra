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
	**graf = new bool*[v];
	waga = new int[v];
	for (int i = 0; i < v; i++) {
		*graf[i] = new bool[v];
		waga[i] = rand()%100;
	}
	return true;
}

bool Macierzowo::usunGraf(){

}