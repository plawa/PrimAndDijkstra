#include "stdafx.h"
#include "Listowo.h"

Listowo::Listowo(){
	pierwszeWczytywanie = true;
}
Listowo::~Listowo(){}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wiersz, kolumna, waga; //
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê nr wierzcho³ka pocz¹tkowego
		if (pierwszeWczytywanie)
			utworzGraf(v, e);
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &waga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = waga; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
