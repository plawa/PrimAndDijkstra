#include "stdafx.h"
#include "Listowo.h"

//Struktura reprezentuj�ca kraw�d�, b�dzie u�ywana w liscie.
//Jej pocz�tkowy wierzcho�ek reprezentuje index tablicy pod kt�rym sie znajduje.
//----------------------------------------------------------------------------
struct krawedz {
	krawedz(uint poczatek, uint koniec, uint wag){
		v1 = poczatek, v2 = koniec, waga = wag;
	}
	uint v1, v2, waga;
};
//Struktura stworzona na potrzeby implementacji kolejki priorytetowej.
//Odpowiada za rosn�ce sortowanie kraw�dzi w kolejce po wagach.
//---------------------------------------------------------------------------
struct porownajWagi {
	bool operator() (const krawedz &krawedz1, const krawedz &krawedz2){
		if (krawedz1.waga > krawedz2.waga) return true;
		else return false;
	}
};

struct wierzcholek {
	wierzcholek(uint nrWierzcholka, uint odleglosc, uint poprzednik){
		v = nrWierzcholka, d = odleglosc, p = poprzednik;
	}
	uint v, d, p;
};
struct porownajOdleglosci {
	bool operator() (const wierzcholek &v1, const wierzcholek &v2){
		if (v1.d > v2.d) return true;
		else return false;
	}
};

Listowo::Listowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u�ywania funkcji rand()
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
	uint koniec2, koniec1 = koniec2 = v0;			//ko�ce drzewa - pocz�tkowo oba r�wne s� wierzcho�kowi pocz�tkowemu
	for (uint licznik = 0; licznik < v - 1; licznik++){
		TkolejkaKrawedzi kolejka;
		for (uint i = 0; i < v; i++){
			for (list<krawedz>::iterator iter = graf[i].begin(); iter != graf[i].end(); iter++)
				if (iter->v1 == koniec1 || iter->v1 == koniec2)
					kolejka.push(*iter);
		}
		bool dodanoKrawedz = false;
		while (!dodanoKrawedz && !kolejka.empty()){ //wykonuj dop�ki kraw�d� nie zostanie dodana i kolejka nie zostanie wyczerpana
			krawedz tempKraw = kolejka.top();
			kolejka.pop();
			if (odwiedzone[tempKraw.v2] == false){
				tempDrzewoRozp[tempKraw.v1].push_back(tempKraw);
				sumaWag += tempKraw.waga;
				koniec2 = tempKraw.v2;
				odwiedzone[koniec2] = true;
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
}

bool Listowo::algorytmDijkstry(){
	if (pierwszeWczytywanie)
		return false;
	//******* DANE *********
	tabOdleglosci = new uint[v];				//tablica najkr�tszych odleg�o�ci ka�dego wierzcho�ka od �r�d�a (v0)
	tabPoprzednikow = new uint[v];				//tablica poprzednik�w dla ka�dego z wierzch. na jego najkr�tszej �cie�ce
	bool *maPoliczonaOdleglosc = new bool[v];	//tablica kt�ra m�wi czy dany wierzcho�ek ma ju� policzon� najkr�t. �cie�k� od v0

	//inicjalizacja danych
	for (uint i = 0; i < v; i++){
		maPoliczonaOdleglosc[i] = false;		//na pocz�tku �aden wierzch nie ma pol. odleg�o�ci
		tabPoprzednikow[i] = 0;					//brak danych o poprzednikach na starcie
		tabOdleglosci[i] = NIESKONCZONOSC;		//odleg�o�ci na pocz�tku s� r�wne nieskonczono��
	}
	tabOdleglosci[v0] = 0;						//bo koszt doj�cia od �r�d�a do �r�d�a = 0
	//-----------------------------------------
	// ************ P�TLA G�OWNA *************
	//-----------------------------------------
	for (uint i = 0; i < v; i++){
		uint idxMinimum = zwrocIdxMinimum(tabOdleglosci, maPoliczonaOdleglosc); //zwraca index wierzcho�ka o minimalnej odleglosci
		maPoliczonaOdleglosc[idxMinimum] = true;								//przenosi do zbioru wierzch o policzonej odleg�o�ci
		for (uint i = 0; i < graf[idxMinimum].size(); i++){						//iteracja po ka�dym z mo�liwyuch s�siad�w
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
	uint minimum = v-1;
	for (uint i = 0; i < v; i++)
		if (!limiter[i])		//poniewa� szukamy w zbiorze wierzcho�k�w dla kt�rych odleg�o�� nie zosta�a jeszcze obliczona
			if (tabOdleglosci[i] < tabOdleglosci[minimum])
				minimum = i;
	return minimum;
}

void Listowo::wyswietlDijkstry(){
	printf("index:  ");
	for (uint i = 0; i < v; i++)
		printf("%d ", i);
	printf("\nodl(i): ");
	for (uint i = 0; i < v; i++)
		printf("%d ", tabOdleglosci[i]);
	printf("\npop(i): ");
	for (uint i = 0; i < v; i++)
		printf("%d ", tabPoprzednikow[i]);
	printf("\n\nWierzcholek poczatkowy: %d", v0);
	delete[] tabOdleglosci;
	delete[] tabPoprzednikow;
}

bool Listowo::utworzGraf(uint iloscWierzcholkow){
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

bool Listowo::kopiujZMacierzyNieskierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	for (uint i = 0; i < v - 1; i++){ //i: iteracja po wierszu (wierzcho�ku)
		for (uint j = i + 1; j < v; j++){ //j: iteracja po kolumnie (s�siedzie)
			if (uint waga = macierz->graf[i][j]){ //je�li kraw�d� istnieje
				graf[i].push_back(*(new krawedz(i, j, waga))); //to dodaj j� do reprezentacji listowej
				graf[j].push_back(*(new krawedz(j, i, waga)));
			}
		}
	}
	return true;
}

bool Listowo::kopiujZMacierzySkierowany(Macierzowo *macierz){
	utworzGraf(macierz->v);
	v0 = macierz -> v0; //przekopiowanie wierzcho�ka pocz�tkowego
	for (uint i = 0; i < v; i++){ //i: iteracja po wierszu (wierzcho�ku)
		for (uint j = 0; j < v; j++){ //j: iteracja po kolumnie (s�siedzie)
			if (uint waga = macierz->graf[i][j]){ //je�li kraw�d� istnieje
				graf[i].push_back(*(new krawedz(i, j, waga))); //to dodaj j� do reprezentacji listowej
				graf[j].push_back(*(new krawedz(j, i, waga)));
			}
		}
	}
	return true;
}

bool Listowo::wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	uint wierzcholek, sasiad, waga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� dodatkowo nr wierzcho�ka pocz�tkowego
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

/***** FUNKCJE WYCOFANE *****

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
*/
