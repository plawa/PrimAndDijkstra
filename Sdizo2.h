#pragma once
#include "stdafx.h"
#include "Macierzowo.h"
#include "Listowo.h"

class Sdizo2 {
public:
	void menu();
private:
	void wyswietlGraf();
	void wczytajGraf();
	void wczytajGrafPNS(); //dla problemu najkr�tszej �cie�ki
	Macierzowo macierzowo;
	Listowo listowo;
};