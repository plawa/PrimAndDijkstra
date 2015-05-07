#include "stdafx.h"
#include "Listowo.h"


Listowo::Listowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u�ywania funkcji rand()
}
Listowo::~Listowo(){
	usunGraf();
}

bool Listowo::utworzGraf(int iloscWierzcholkow){
	if (pierwszeWczytywanie == false)
		usunGraf();
	v = iloscWierzcholkow;
	list<krawedz> *tempGraf = new list<krawedz>[v]; //stworzenie tablicy pustych list dla odpowiadajacych wierzcho�k�w grafu
	pierwszeWczytywanie = false;
	graf = tempGraf;
	return true;
}

bool Listowo::utworzGraf(){
	return utworzGraf(v);
}

bool Listowo::generujLosowoNieskierowany(int v, int gestosc){
	int licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent kraw�dzi, aby graf by� sp�jny
	int maxE = v*(v - 1) / 2; //max ilo�� kraw�dzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi do dodania wyliczona na podstawie g�sto�ci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (int i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie sp�jno�ci)
		//��cz� wierzcho�ki (1->2->3->4 ...), tworz�c najpierw graf sp�jny z wagami 1 do 9
		graf[i].push_back(*(new krawedz(i + 1, rand() % 9 + 1)));
		licznik++;
	}
	while (licznik < e){
		bool istniejeTakaKrawedz = false;
		unsigned int wierzcholek = rand() % v;
		unsigned int sasiad = rand() % v;
		if (wierzcholek == sasiad) //zakaz tworzenia p�tli
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
	for (int i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho�ku)
		for (int j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s�siedzie)
			if (int waga = macierz->graf[i][j]) //je�li kraw�d� istnieje
				graf[i].push_back(*(new krawedz(j, waga))); //to dodaj j� do reprezentacji listowej
		}
	}
	return true;
}

bool Listowo::kopiujZMacierzySkierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	for (int i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho�ku)
		for (int j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s�siedzie)
			if (int waga = macierz->graf[i][j]) //je�li kraw�d� istnieje
				graf[i].push_back(*(new krawedz(j, waga))); //to dodaj j� do reprezentacji listowej
		}
	}
	return true;
}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	int wierzcholek, sasiad, waga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� dodatkowo nr wierzcho�ka pocz�tkowego
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
