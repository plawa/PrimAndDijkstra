#include "stdafx.h"
#include "Macierzowo.h"


Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((unsigned int)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}
Macierzowo::~Macierzowo(){
	usunGraf();
}

bool Macierzowo::algorytmPrima(){
	return true;
}

bool Macierzowo::utworzGraf(int iloscWierzcholkow, int iloscKrawedzi){
	if (!pierwszeWczytywanie){//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf(); //to czyœcimy
		pierwszeWczytywanie = false;
	}
	v = iloscWierzcholkow;
	e = iloscKrawedzi;
	unsigned int **tempGraf = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		for (int j = 0; j < v; j++)
			tempGraf[i][j] = 0; //inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy krawêdŸ
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
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê nr wierzcho³ka pocz¹tkowego
		utworzGraf(v, e);
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &waga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = waga; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
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
			printf("%d ", graf[i][j]>0 ? 1:0); //uproszczony if, który wyœwietla 1 lub 0, w zale¿noœci od wartoœci wyra¿enia
	}
}
