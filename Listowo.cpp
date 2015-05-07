#include "stdafx.h"
#include "Listowo.h"


Listowo::Listowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}
Listowo::~Listowo(){
	usunGraf();
}

bool Listowo::utworzGraf(int iloscWierzcholkow){
	if (pierwszeWczytywanie == false)
		usunGraf();
	v = iloscWierzcholkow;
	list<krawedz> *tempGraf = new list<krawedz>[v]; //stworzenie tablicy pustych list dla odpowiadajacych wierzcho³ków grafu
	pierwszeWczytywanie = false;
	graf = tempGraf;
	return true;
}

bool Listowo::utworzGraf(){
	return utworzGraf(v);
}

bool Listowo::generujLosowoNieskierowany(int v, int gestosc){
	int licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie spójnoœci)
		//³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9
		graf[i].push_back(*(new krawedz(i + 1, rand() % 9 + 1)));
		licznik++;
	}
	while (licznik < e){
		bool istniejeTakaKrawedz = false;
		unsigned int wierzcholek = rand() % v;
		unsigned int sasiad = rand() % v;
		if (wierzcholek == sasiad) //zakaz tworzenia pêtli
			continue;
		unsigned int waga = rand() % 9 + 1;
		for (list<krawedz>::iterator iter = graf[wierzcholek].begin(); iter != graf[wierzcholek].end(); iter++)
			if (iter->sasiad == sasiad)
				istniejeTakaKrawedz = true;
		if (istniejeTakaKrawedz == false){
			graf[wierzcholek].push_back(*(new krawedz(sasiad, waga)));
			licznik++;
		}
	}
	return true;
}

bool Listowo::generujLosowoSkierowany(int v, int gestosc){
	return false;
}

bool Listowo::kopiujZMacierzyNieskierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	for (int i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho³ku)
		for (int j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s¹siedzie)
			if (int waga = macierz->graf[i][j]) //jeœli krawêdŸ istnieje
				graf[i].push_back(*(new krawedz(j, waga))); //to dodaj j¹ do reprezentacji listowej
		}
	}
	return true;
}

bool Listowo::kopiujZMacierzySkierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	for (int i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho³ku)
		for (int j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s¹siedzie)
			if (int waga = macierz->graf[i][j]) //jeœli krawêdŸ istnieje
				graf[i].push_back(*(new krawedz(j, waga))); //to dodaj j¹ do reprezentacji listowej
		}
	}
	return true;
}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wierzcholek, sasiad, waga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (int i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wierzcholek, &sasiad, &waga);
			if (wierzcholek >= v || sasiad >= v)
				return false;
			graf[wierzcholek].push_back(*(new krawedz(sasiad, waga)));
		}
		fclose(plik);
		return true;
	} 
	else
		return false;
}

void Listowo::wyswietl(){
	for (int i = 0; i < v; i++){
		printf("\n%d: ", i);
		for (list<krawedz>::iterator iter = graf[i].begin(); iter != graf[i].end(); iter++)
			printf("(%d, %d), ", iter->sasiad, iter->waga);
	}
}

void Listowo::usunGraf(){
	delete[] graf;
}
