#include "stdafx.h"
#include "Listowo.h"

//Struktura reprezentuj¹ca krawêdŸ, bêdzie u¿ywana w liscie.
//Jej pocz¹tkowy wierzcho³ek reprezentuje index tablicy pod którym sie znajduje.
//----------------------------------------------------------------------------
struct krawedz {
	krawedz(uint poczatek, uint koniec, uint wag){
		v1 = poczatek, v2 = koniec, waga = wag;
	}
	uint v1, v2, waga;
};
//Struktura stworzona na potrzeby implementacji kolejki priorytetowej.
//Odpowiada za rosn¹ce sortowanie krawêdzi w kolejce po wagach.
//---------------------------------------------------------------------------
struct porownajWagi {
	bool operator() (const krawedz &krawedz1, const krawedz &krawedz2){
		if (krawedz1.waga > krawedz2.waga) return true;
		else return false;
	}
};


Listowo::Listowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}
Listowo::~Listowo(){
	usunGraf();
}

bool Listowo::algorytmPrima(){
	if (pierwszeWczytywanie)
		return false;
	uint sumaWag = 0;
	bool *odwiedzone = new bool[v];
	list<krawedz> *tempDrzewoRozp = new list<krawedz>[v];
	for (uint i = 0; i < v; i++)
		odwiedzone[i] = false;
	odwiedzone[v0] = true;
	for (uint licznik = 0; licznik < v - 1; licznik++){
		TkolejkaKrawedzi kolejka;
		for (uint i = 0; i < v; i++){
			if (odwiedzone[i])
				for (list<krawedz>::iterator iter = graf[i].begin(); iter != graf[i].end(); iter++)
					kolejka.push(*iter);
		}
		bool dodanoKrawedz = false;
		while (!dodanoKrawedz && !kolejka.empty()){ //wykonuj dopóki krawêdŸ nie zostanie dodana i kolejka nie zostanie wyczerpana
			krawedz tempKraw = kolejka.top();
			kolejka.pop();
			if (odwiedzone[tempKraw.v2] == false){
				tempDrzewoRozp[tempKraw.v1].push_back(tempKraw);
				sumaWag += tempKraw.waga;
				odwiedzone[tempKraw.v2] = true;
				dodanoKrawedz = true;
			}
		}
	}
	MST = tempDrzewoRozp;
	sumaWagMST = sumaWag;
	return true;
}

void Listowo::wyswietlPrima(){
	wyswietl(MST);
	printf("\n\nWierzcholek poczatkowy: %d\nSuma wag: %d\n", v0, sumaWagMST);
	czyscPrima();
}

bool Listowo::algorytmDijkstry(){
	if (pierwszeWczytywanie)
		return false;
	//******* DANE *********
	tabOdleglosci = new uint[v];				//tablica najkrótszych odleg³oœci ka¿dego wierzcho³ka od Ÿród³a (v0)
	tabPoprzednikow = new uint[v];				//tablica poprzedników dla ka¿dego z wierzch. na jego najkrótszej œcie¿ce
	bool *maPoliczonaOdleglosc = new bool[v];	//tablica która mówi czy dany wierzcho³ek ma ju¿ policzon¹ najkrót. œcie¿kê od v0

	//inicjalizacja danych
	for (uint i = 0; i < v; i++){
		maPoliczonaOdleglosc[i] = false;		//na pocz¹tku ¿aden wierzch nie ma pol. odleg³oœci
		tabPoprzednikow[i] = 0;					//brak danych o poprzednikach na starcie
		tabOdleglosci[i] = NIESKONCZONOSC;		//odleg³oœci na pocz¹tku s¹ równe nieskonczonoœæ
	}
	tabOdleglosci[v0] = 0;						//bo koszt dojœcia od Ÿród³a do Ÿród³a = 0
	//-----------------------------------------
	// ************ PÊTLA G£OWNA *************
	//-----------------------------------------
	for (uint i = 0; i < v; i++){
		uint idxMinimum = zwrocIdxMinimum(tabOdleglosci, maPoliczonaOdleglosc); //zwraca index wierzcho³ka o minimalnej odleglosci
		maPoliczonaOdleglosc[idxMinimum] = true;								//przenosi do zbioru wierzch o policzonej odleg³oœci
		for (uint i = 0; i < graf[idxMinimum].size(); i++){						//iteracja po ka¿dym z mo¿liwyuch s¹siadów
			for (list<krawedz>::iterator iter = graf[idxMinimum].begin(); iter != graf[idxMinimum].end(); iter++){
				if (tabOdleglosci[iter->v2] > tabOdleglosci[idxMinimum] + iter->waga){
					tabOdleglosci[iter->v2] = tabOdleglosci[idxMinimum] + iter->waga;
					tabPoprzednikow[iter->v2] = idxMinimum;
				}
			}
		}
	}
	delete[] maPoliczonaOdleglosc;
	return true;
}

uint Listowo::zwrocIdxMinimum(uint *tabOdleglosci, bool *limiter){
	uint minimum = v;
	for (uint i = 0; i < v; i++)
		if (!limiter[i])		//poniewa¿ szukamy w zbiorze wierzcho³ków dla których odleg³oœæ nie zosta³a jeszcze obliczona
			if (tabOdleglosci[i] < tabOdleglosci[minimum])
				minimum = i;
	return minimum;
}

void Listowo::wyswietlDijkstry(){
	printf("wierzch.:  ");
	for (uint i = 0; i < v; i++)
		printf("%d ", i);
	printf("\nodleglosc: ");
	for (uint i = 0; i < v; i++)
		printf("%d ", tabOdleglosci[i]);
	czyscDijkstry();
}

bool Listowo::utworzGraf(uint iloscWierzcholkow){
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

bool Listowo::kopiujZMacierzyNieskierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	for (uint i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho³ku)
		for (uint j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s¹siedzie)
			if (uint waga = macierz->graf[i][j]){ //jeœli krawêdŸ istnieje
				graf[i].push_back(*(new krawedz(i, j, waga))); //to dodaj j¹ do reprezentacji listowej
				graf[j].push_back(*(new krawedz(j, i, waga)));
			}
		}
	}
	return true;
}

bool Listowo::kopiujZMacierzySkierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	v0 = macierz -> v0; //przekopiowanie wierzcho³ka pocz¹tkowego
	for (uint i = 0; i < v; i++){ //i: iteracja po wierszu (wierzcho³ku)
		for (uint j = 0; j < v; j++){ //j: iteracja po kolumnie (s¹siedzie)
			if (uint waga = macierz->graf[i][j]){ //jeœli krawêdŸ istnieje
				graf[i].push_back(*(new krawedz(i, j, waga))); //to dodaj j¹ do reprezentacji listowej
				graf[j].push_back(*(new krawedz(j, i, waga)));
			}
		}
	}
	return true;
}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	uint wierzcholek, sasiad, waga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (uint i = 0; i < e; i++){
			fscanf_s(plik, "%d %d %d", &wierzcholek, &sasiad, &waga);
			if (wierzcholek >= v || sasiad >= v)
				return false;
			graf[wierzcholek].push_back(*(new krawedz(wierzcholek, sasiad, waga)));
			if (!dlaProblemuNajkrotszejSciezki)
				graf[sasiad].push_back(*(new krawedz(sasiad, wierzcholek, waga)));
		}
		fclose(plik);
		return true;
	} 
	else
		return false;
}

void Listowo::wyswietl(list<krawedz> *grafListowo){
	for (uint i = 0; i < v; i++){
		printf("\n%d: ", i);
		for (list<krawedz>::iterator iter = grafListowo[i].begin(); iter != grafListowo[i].end(); iter++)
			printf("(%d, %d), ", iter->v2, iter->waga);
	}
}

void Listowo::wyswietl(){
	wyswietl(graf);
}

void Listowo::usunGraf(){
	delete[] graf;
}

void Listowo::czyscDijkstry(){
	delete[] tabOdleglosci;
	delete[] tabPoprzednikow;
}

void Listowo::czyscPrima(){
	delete[] MST;
}