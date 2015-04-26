#include "stdafx.h"
#include "Macierzowo.h"


Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((unsigned int)time(NULL)); //na potrzeby u�ywania funkcji rand()
}
Macierzowo::~Macierzowo(){
	usunGraf();
}

bool Macierzowo::algorytmPrima(){
	return true;
}

bool Macierzowo::utworzGraf(int iloscWierzcholkow, int iloscKrawedzi){
	if (!pierwszeWczytywanie){//je�li graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf(); //to czy�cimy
		pierwszeWczytywanie = false;
	}
	v = iloscWierzcholkow;
	e = iloscKrawedzi;
	unsigned int **tempGraf = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		for (int j = 0; j < v; j++)
			tempGraf[i][j] = 0; //inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy kraw�d�
	}
	graf = tempGraf;
	return true;
}

void Macierzowo::usunGraf(){
	for (int i = 0; i < v; i++)
		delete[] graf[i];
	delete[] graf;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wiersz, kolumna, waga; //
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� nr wierzcho�ka pocz�tkowego
		utworzGraf(v, e);
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &waga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = waga; //wierzcho�ki "wiersz" i "kolumna" reprezentuj� jedn� kraw�d�, wpisuje si� tam jej wag�
		}
		fclose(plik);
		return true;
	} else
		return false;
}

void Macierzowo::wyswietl(){
	printf("  "); //kosmetyka
	for (int i = 0; i < v; i++)
		printf("%d ", i);
	for (int i = 0; i < v; i++) {
		printf("\n%d ", i);
		for (int j = 0; j < v; j++)
			printf("%d ", graf[i][j]>0 ? 1:0); //uproszczony if, kt�ry wy�wietla 1 lub 0, w zale�no�ci od warto�ci wyra�enia
	}
}
