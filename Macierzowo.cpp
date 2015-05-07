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
	if (pierwszeWczytywanie == false)//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf(); //to czyœcimy
	v = iloscWierzcholkow;
	unsigned int **tempGraf = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		for (int j = 0; j < v; j++)
			tempGraf[i][j] = 0; //inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
	}
	pierwszeWczytywanie = false;
	graf = tempGraf;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(int v, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (int i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (int j = 0; j < v; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek¹tnej (maj¹ tam byæ same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	int licznik = 0, minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" - czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie spójnoœci)
		//³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		licznik++;
	}
	while (licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			zmodyfikowane[wiersz][kolumna] = zmodyfikowane[kolumna][wiersz] = graf[wiersz][kolumna] = graf[kolumna][wiersz] = rand() % 9 + 1;
			licznik++;
		}
	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(int v, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (int i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (int j = 0; j < v; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek¹tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej

	int licznik = 0, maxE = v * (v - 1); //max mo¿liwa iloœæ krawêdzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		//³¹czê wierzcho³ki (1->2->3->4->...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		zmodyfikowane[i][i + 1] = graf[i][i + 1] = rand() % 9 + 1; 
		licznik++;
	}
	while(licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			zmodyfikowane[wiersz][kolumna] = graf[wiersz][kolumna] = rand() % 9 + 1;
			licznik++;
		}
	}
	return true;
}

void Macierzowo::wyswietl(){
	for (int i = 0; i < v; i++){
		printf("\n");
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
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wiersz, &kolumna, &tempWaga);
			if (wiersz >= v || kolumna >= v)
				return false;
			graf[wiersz][kolumna] = tempWaga; //wierzcho³ki "wiersz" i "kolumna" reprezentuj¹ jedn¹ krawêdŸ, wpisuje siê tam jej wagê
			if (!dlaProblemuNajkrotszejSciezki) //jeœli rozpatrujemy problem MST
				graf[kolumna][wiersz] = tempWaga; //to krawêdzie grafu s¹ nieskierowane (macierz symetryczna)
		}
		fclose(plik);
		return true;
	}
	else
		return false;
}
