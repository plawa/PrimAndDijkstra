#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>

Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u�ywania funkcji rand()
}
Macierzowo::~Macierzowo(){
	usunGraf();
}

bool Macierzowo::algorytmPrima(){

	return true;
}

bool Macierzowo::utworzGraf(int iloscWierzcholkow){
	if (!pierwszeWczytywanie)//je�li graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf(); //to czy�cimy
	v = iloscWierzcholkow;
	unsigned int **tempGraf = new unsigned int*[v], **tempWaga = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		tempWaga[i] = new unsigned int[v];
		for (int j = 0; j < v; j++){
			tempGraf[i][j] = 0; //inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy �adna kraw�d�
			tempWaga[i][j] = 0; //pocz�tkowo wagi s� zerowe
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
	int licznik = 0, maxE = v*(v - 1) / 2; //max ilo�� kraw�dzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi wyliczona na podstawie g�sto�ci
	if (gestosc < 1 || gestosc > 100) //procenty musz� si� zgadza�
		return false;
	utworzGraf(v);
	//iteracja poni�ej nast�puje po "tr�jk�cie" cz�ci tablicy, kt�ra b�dzie symetrycznie odbijana wzgl�dem przek�tnej
	for (int i = 0; i < v-1 && licznik < e; i++) {
		for (int j = i+1; j < v && licznik < e; j++) {
			unsigned int dodawana = rand() % 6; //losuj liczb� (kraw�d� wraz z wag�)
			if (dodawana){ //je�li dodawana liczba reprezentuje krawedz
				graf[i][j] = graf[j][i] = 1;//bo macierz symetryczna
				waga[i][j] = waga[j][i] = dodawana;
				licznik++;
			}
		}

	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(int v, int gestosc){
	int licznik = 0, maxE = (v - 1)^v; //max ilo�� kraw�dzi dla grafu skierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi wyliczona na podstawie g�sto�ci
	if (gestosc < 1 || gestosc > 100) //procenty musz� si� zgadza�
		return false;
	utworzGraf(v);
	for (int i = 0; i < v && licznik < e; i++) {
		for (int j = 0; j < v && licznik < e; j ++) {
			if (i == j) //zakaz tworzenia p�tli
				continue;
			unsigned int dodawana = rand() % 6; //losuj liczb� (kraw�d� wraz z wag�)
			if (dodawana){ //je�li dodana liczba reprezentuje krawedz
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
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� dodatkowo nr wierzcho�ka pocz�tkowego
		utworzGraf();
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &tempWaga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = 1; //wierzcho�ki "wiersz" i "kolumna" reprezentuj� jedn� kraw�d�, wpisuje si� tam jej wag�
			waga[wiersz][kolumna] = tempWaga;
			if (!dlaProblemuNajkrotszejSciezki){ //je�li rozpatrujemy problem MST
				graf[kolumna][wiersz] = 1; //to kraw�dzie grafu s� nieskierowane (macierz symetryczna)
				waga[kolumna][wiersz] = tempWaga;
			}
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
