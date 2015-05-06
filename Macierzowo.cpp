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
	unsigned int **tempGraf = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		for (int j = 0; j < v; j++)
			tempGraf[i][j] = 0; //inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy �adna kraw�d�
	}
	graf = tempGraf;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(int v, int gestosc){
	int licznik = 0, minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent kraw�dzi, aby graf by� sp�jny
	int maxE = v*(v - 1) / 2; //max ilo�� kraw�dzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi do dodania wyliczona na podstawie g�sto�ci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni�ej nast�puje po "tr�jk�cie" - cz�ci tablicy, kt�ra b�dzie symetrycznie odbijana wzgl�dem przek�tnej
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; //��cz� wierzcho�ki (1->2->3->4 ...), tworz�c najpierw graf sp�jny z wagami 1 do 9
		licznik++;
	}
	for (int i = 0; i < v - 2 && licznik < e; i++) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
		for (int j = i + 2; j < v && licznik < e; j++){
			graf[i][j] = graf[j][i] = rand() % 9 + 1;
			licznik++;
		}
	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(int v, int gestosc){
	int licznik = 0;
	int maxE = v * (v - 1); //max ilo�� kraw�dzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi wyliczona na podstawie g�sto�ci
	if (gestosc < minProcent || gestosc > 100) //procenty musz� si� zgadza�
		return false;
	utworzGraf(v);
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		graf[i][i + 1] = rand() % 9 + 1; //��cz� wierzcho�ki (1->2->3->4 ...), tworz�c najpierw graf sp�jny z wagami 1 do 9
		licznik++;
	}
	for (int i = 0; i < v - 2 && licznik < e; i++) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
		for (int j = i + 2; j < v && licznik < e; j++){
			graf[i][j] = rand() % 9 + 1; //DO ZROBIENIA, KOREKTA GENEROWANIA BEZ SYMETRII
			licznik++;
		}
	}
	return true;
}

void Macierzowo::wyswietl(){
	printf("  "); //kosmetyka
	for (int i = 0; i < v; i++)
		printf("%d ", i);
	for (int i = 0; i < v; i++) {
		printf("\n%d ", i);
		for (int j = 0; j < v; j++)
			printf("%d ", graf[i][j]);
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
			graf[wiersz][kolumna] = tempWaga; //wierzcho�ki "wiersz" i "kolumna" reprezentuj� jedn� kraw�d�, wpisuje si� tam jej wag�
			if (!dlaProblemuNajkrotszejSciezki) //je�li rozpatrujemy problem MST
				graf[kolumna][wiersz] = tempWaga; //to kraw�dzie grafu s� nieskierowane (macierz symetryczna)
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
