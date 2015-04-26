#include "stdafx.h"
#include "Listowo.h"

Listowo::Listowo(){
	pierwszeWczytywanie = true;
}
Listowo::~Listowo(){}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wiersz, kolumna, waga; //
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� nr wierzcho�ka pocz�tkowego
		if (pierwszeWczytywanie)
			utworzGraf(v, e);
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &waga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = waga; //wierzcho�ki "wiersz" i "kolumna" reprezentuj� jedn� kraw�d�, wpisuje si� tam jej wag�
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
