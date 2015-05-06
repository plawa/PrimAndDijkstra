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
	unsigned int **tempGraf = new unsigned int*[v];
	for (int i = 0; i < v; i++) {
		tempGraf[i] = new unsigned int[v];
		for (int j = 0; j < v; j++)
			tempGraf[i][j] = 0; //inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
	}
	graf = tempGraf;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(int v, int gestosc){
	int licznik = 0, minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" - czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; //³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9
		licznik++;
	}
	for (int i = 0; i < v - 2 && licznik < e; i++) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
		for (int j = i + 2; j < v && licznik < e; j++){
			graf[i][j] = graf[j][i] = rand() % 9 + 1;
			licznik++;
		}
	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(int v, int gestosc){
	int licznik = 0;
	int maxE = v * (v - 1); //max iloœæ krawêdzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100) //procenty musz¹ siê zgadzaæ
		return false;
	utworzGraf(v);
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		graf[i][i + 1] = rand() % 9 + 1; //³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9
		licznik++;
	}
	for (int i = 0; i < v - 2 && licznik < e; i++) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
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
