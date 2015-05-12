#pragma once
#include "stdafx.h"
#include "Macierzowo.h"
#include "Listowo.h"

class Sdizo2 {
public:
	void menu();
private:
	void wyswietlGraf();
	void wczytajGraf(bool dlaPNS); //dlaProblemu najkrotszej œcie¿ki
	void generujGraf(bool dlaPNS);
	void algorytmPrima();
	void algorytmDijkstry();
	void eksperyment();
	void testPrima(int iloscWierzch, int gestosc);
	void testDijkstry(int iloscWierzch, int gestosc);
	Macierzowo macierzowo;
	Listowo listowo;
	PomiarCzasu timer;
};
