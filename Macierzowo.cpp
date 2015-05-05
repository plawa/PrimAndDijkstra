#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>

Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}
Macierzowo::~Macierzowo(){
	usunGraf();
}

bool Macierzowo::algorytmPrima(){

	return true;
}

bool Macierzowo::utworzGraf(int iloscWierzcholkow){
	if (!pierwszeWczytywanie)//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf(); //to czyœcimy
	v = iloscWierzcholkow;
	unsigned int **tempGraf = new unsigned int*[v], **tempWaga = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		tempWaga[i] = new unsigned int[v];
		for (int j = 0; j < v; j++){
			tempGraf[i][j] = 0; //inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
			tempWaga[i][j] = 0; //pocz¹tkowo wagi s¹ zerowe
		}
	}
	graf = tempGraf;
	waga = tempWaga;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(int v, int gestosc){
	int licznik = 0, maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	if (gestosc < 1 || gestosc > 100) //procenty musz¹ siê zgadzaæ
		return false;
	utworzGraf(v);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (int i = 0; i < v-1 && licznik < e; i++) {
		for (int j = i+1; j < v && licznik < e; j++) {
			unsigned int dodawana = rand() % 6; //losuj liczbê (krawêdŸ wraz z wag¹)
			if (dodawana){ //jeœli dodawana liczba reprezentuje krawedz
				graf[i][j] = graf[j][i] = 1;//bo macierz symetryczna
				waga[i][j] = waga[j][i] = dodawana;
				licznik++;
			}
		}

	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(int v, int gestosc){
	int licznik = 0, maxE = (v - 1)^v; //max iloœæ krawêdzi dla grafu skierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	if (gestosc < 1 || gestosc > 100) //procenty musz¹ siê zgadzaæ
		return false;
	utworzGraf(v);
	for (int i = 0; i < v && licznik < e; i++) {
		for (int j = 0; j < v && licznik < e; j ++) {
			if (i == j) //zakaz tworzenia pêtli
				continue;
			unsigned int dodawana = rand() % 6; //losuj liczbê (krawêdŸ wraz z wag¹)
			if (dodawana){ //jeœli dodana liczba reprezentuje krawedz
				licznik++;
				graf[i][j] = 1;
				waga[i][j] = dodawana;
			}
		}
	}
	return true;
}

void Macierzowo::wyswietl(bool wagi){
	unsigned int **wsk;
	if (wagi)
		wsk = waga;
	else
		wsk = graf;
	printf("  "); //kosmetyka
	for (int i = 0; i < v; i++)
		printf("%d ", i);
	for (int i = 0; i < v; i++) {
		printf("\n%d ", i);
		for (int j = 0; j < v; j++)
			printf("%d ", wsk[i][j]);
	}
}

void Macierzowo::usunGraf(){
	for (int i = 0; i < v; i++)
		delete[] graf[i];
	delete[] graf;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wiersz, kolumna, tempWaga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &tempWaga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = 1; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
			waga[wiersz][kolumna] = tempWaga;
			if (!dlaProblemuNajkrotszejSciezki){ //jeœli rozpatrujemy problem MST
				graf[kolumna][wiersz] = 1; //to krawêdzie grafu s¹ nieskierowane (macierz symetryczna)
				waga[kolumna][wiersz] = tempWaga;
			}
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
