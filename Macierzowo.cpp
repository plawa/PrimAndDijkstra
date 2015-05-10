#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>

#define NIESKONCZONOSC 4294967295

//Struktura reprezentuj�ca kraw�d�, b�dzie u�ywana w liscie.
//Jej pocz�tkowy wierzcho�ek reprezentuje index tablicy pod kt�rym sie znajduje.
//----------------------------------------------------------------------------
struct krawedz {
	krawedz(uint poczatek, uint koniec, uint wag) {	v1 = poczatek, v2 = koniec, waga = wag;	}
	uint v1, v2, waga;
};

//Struktura stworzona na potrzeby implementacji kolejki priorytetowej dla alg Prima.
//Odpowiada za rosn�ce sortowanie kraw�dzi w kolejce po wagach.
//---------------------------------------------------------------------------
struct porownajWagi {
	bool operator() (const krawedz &krawedz1, const krawedz &krawedz2){
		if (krawedz1.waga > krawedz2.waga) return true;
		else return false;
	}
};

struct wierzch {
	wierzch(uint poprzednik, uint nrWierzcholka, uint odlegloscOdZrodla){
		poprz = poprzednik, v = nrWierzcholka, odleglosc = odlegloscOdZrodla;
	}
	uint poprz, v, odleglosc;
};

//Struktura stworzona na potrzeby implementacji kolejki priorytetowej dla alg Dijkstry.
//Odpowiada za rosn�ce sortowanie wierzcho�k�w w kolejce po odleg�o�ciach od �r�d�a.
//---------------------------------------------------------------------------
struct porownajOdleglosci{
	bool operator() (const wierzch &wierzch1, const wierzch &wierzch2){
		if (wierzch1.odleglosc > wierzch2.odleglosc) return true;
		else return false;
	}
};

//Konstruktor, kt�ry resetuje generator liczb pseudolowych i zapewnia, �e pierwsze
//wczytanie grafu przebiegnie bez pr�by usuwania poprzedniej (nieistniej�cej) instancji.
//---------------------------------------------------------------------------
Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u�ywania funkcji rand()
}

//Destruktor, wywo�uje funkcj� "usunGraf()"
//--------------------------------------------------------------------------
Macierzowo::~Macierzowo(){
	usunGraf();
}

//Znajduje najkr�tsze drzewo rozpinaj�ce w grafie reprez. przez macierz.
// TYLKO DLA PROBLEMU NR 1
//--------------------------------------------------------------------------
uint Macierzowo::algorytmPrima(){
	uint sumaWag = 0;
	bool *odwiedzone = new bool[v];
	uint **tempDrzewoRozp = new uint*[v];
	//inicjalizacja macierzy MST i tablicy odwiedzin (bool) zerami
	for (uint i = 0; i < v; i++){
		odwiedzone[i] = false;
		tempDrzewoRozp[i] = new uint[v];
		for (uint j = 0; j < v; j++)
			tempDrzewoRozp[i][j] = 0;
	}
	odwiedzone[v0] = true;							//wierzcho�ek pocz�tkowy oznaczam jako odwiedzony
	uint koniec2, koniec1 = koniec2 = v0;			//ko�ce drzewa - pocz�tkowo oba r�wne s� wierzcho�kowi pocz�tkowemu
	// ----- P�TLA G�OWNA ------
	for (uint licznik = 0; licznik < v - 1; licznik++){ //kraw�dzi b�dzie o 1 mniej ni� jest wierzcho�k�w
		//budowanie kolejki wierzcho�k�w osi�galnych przez MST
		TkolejkaKrawedzi kolejka;
		for (uint i = 0; i < v; i++){				//i = koniec 1, bo macierz grafu nieskierowanego jest symetryczna
			if (uint waga = graf[koniec1][i])		//sprawdzam kraw�dzie wychodz�ce z koniec1 i przy okazji przypisuj� do zmiennej "waga"
				kolejka.push(*(new krawedz(koniec1, i, waga)));
			if (koniec2 != koniec1)					//je�li graf ma dwa r�ne ko�ce
				if (uint waga = graf[koniec2][i])	//sprawdzam kraw�dzie wychodz�ce z koniec2
					kolejka.push(*(new krawedz(koniec2, i, waga)));
		}
		bool dodanoKrawedz = false;
		while (!dodanoKrawedz && !kolejka.empty()){ //wykonuj dop�ki kraw�d� nie zostanie dodana i kolejka nie zostanie wyczerpana
			krawedz tempKraw = kolejka.top();
			kolejka.pop();
			if (odwiedzone[tempKraw.v2] == false){	//je�li wierzcholek jeszcze nie by� odwiedzony
				//to dodaj kraw�d� do MST
				sumaWag += tempDrzewoRozp[tempKraw.v2][tempKraw.v1] = tempDrzewoRozp[tempKraw.v1][tempKraw.v2] = tempKraw.waga; 
				koniec2 = tempKraw.v2;
				odwiedzone[koniec2] = true;
				dodanoKrawedz = true;
			}
		}
	}
	wyswietl(drzewoRozpinajace = tempDrzewoRozp); //przypisz i wyswietl
	return sumaWag;
}


//Znajduje najkr�tsze drogi z wierzcho�ka v0 do wszystkich innych.
//TYLKO DLA PROBLEMU NR 2
//---------------------------------------------------------------
bool Macierzowo::algorytmDijkstry(){
	//******* DANE *********
	v0;											//wierzcho�ek startowy
	uint *odleglosc = new uint[v];				//tablica najkr�tszych odleg�o�ci ka�dego wierzcho�ka od �r�d�a (v0)
	uint *poprzednik = new uint[v];			//tablica poprzednik�w dla ka�dego z wierzch. na jego najkr�tszej �cie�ce
	bool *maPoliczonaOdleglosc = new bool[v];	//tablica kt�ra m�wi czy dany wierzcho�ek ma ju� policzon� najkr�t. �cie�k� od v0

	//inicjalizacja danych
	for (uint i = 0; i < v; i++){
		maPoliczonaOdleglosc[i] = false;		//na pocz�tku �aden wierzch nie ma pol. odleg�o�ci
		poprzednik[i] = 0;						//brak danych o poprzednikach na starcie
		odleglosc[i] = NIESKONCZONOSC;			//odleg�o�ci na pocz�tku s� r�wne nieskonczono��
	}
	odleglosc[v0] = 0;							//bo koszt doj�cia od �r�d�a do �r�d�a = 0
	//-----------------------------------------
	while (!wszystkieTrue(maPoliczonaOdleglosc)){
		uint idxMinimum = zwrocIdxMinimum(odleglosc, maPoliczonaOdleglosc); //zwraca index wierzcho�ka o minimalnej odleglosci
		maPoliczonaOdleglosc[idxMinimum] = true;							//przenosi do zbioru wierzch o policzonej odleg�o�ci
		for (uint i = 0; i < v; i++)										//iteracja po ka�dym z mo�liwyuch s�siad�w
			if (uint waga = graf[idxMinimum][i])							//je�li pod danym indexem istnieje kraw�d�:
				if (odleglosc[i] > odleglosc[idxMinimum] + waga){
					odleglosc[i] = odleglosc[idxMinimum] + waga;			//to zmodyfikuj odpowiednio
					poprzednik[i] = idxMinimum;
				}
	}

	return true;
}

uint Macierzowo::zwrocIdxMinimum(uint *tablica, bool *limiter){
	uint minimum;
	for (uint i = 0; i < v; i++)
		if (!limiter[i]){
			minimum = i;
			break;
		}
	for (uint i = 0; i < v; i++)
		if( ! limiter[i])		//szukamy w zbiorze Q
			if (tablica[i] < minimum)
				minimum = i;
	return minimum;
}

bool Macierzowo::wszystkieTrue(bool *tablica){
	for (uint i = 0; i < v; i++)
		if (tablica[i] == false) return false;
	return true;
}

bool Macierzowo::utworzGraf(uint iloscWierzcholkow){
	if (pierwszeWczytywanie == false)	//je�li graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();						//to czy�cimy
	v = iloscWierzcholkow;
	uint **tempGraf = new uint*[v];
	for (uint i = 0; i < v; i++) {
		tempGraf[i] = new uint[v];
		for (uint j = 0; j < v; j++)
			tempGraf[i][j] = 0;			//inicjalizacja zerami, kt�re oznaczaj� �e danych dw�ch wierzcho�k�w nie ��czy �adna kraw�d�
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(uint v, int gestosc){
	//inicjalizacja macierzy, kt�ra przechowywa� b�dzie informacje czy dana kom�rka zosta�a ju� wcze�niej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek�tnej (maj� tam by� same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	uint licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent kraw�dzi, aby graf by� sp�jny
	int maxE = v*(v - 1) / 2; //max ilo�� kraw�dzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //ilo�� kraw�dzi do dodania wyliczona na podstawie g�sto�ci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni�ej nast�puje po "tr�jk�cie" - cz�ci tablicy, kt�ra b�dzie symetrycznie odbijana wzgl�dem przek�tnej
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie sp�jno�ci)
		//��cz� wierzcho�ki (1->2->3->4 ...), tworz�c najpierw graf sp�jny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = true;
		licznik++;
	}
	while (licznik < e) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
		int waga = rand() % 9 + 1;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			graf[wiersz][kolumna] = graf[kolumna][wiersz] = waga;
			zmodyfikowane[wiersz][kolumna] = zmodyfikowane[kolumna][wiersz] = true;
			licznik++;
		}
	}
	return true;
}

bool Macierzowo::generujLosowoSkierowany(uint v, int gestosc){
	//inicjalizacja macierzy, kt�ra przechowywa� b�dzie informacje czy dana kom�rka zosta�a ju� wcze�niej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek�tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej
	//------------------------------------
	uint licznik = 0, maxE = v * (v - 1); //max mo�liwa ilo�� kraw�dzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //ilo�� kraw�dzi wyliczona na podstawie g�sto�ci
	v0 = rand() % v; //losowanie wierzcho�ka pocz�tkowego dla PNS
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		//��cz� wierzcho�ki (1->2->3->4->...), tworz�c najpierw graf sp�jny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = true;
		licznik++;
	}
	while(licznik < e) { //nast�pnie uzupe�nianie losowymi warto�ciami do uzyskania po��danej ilo�ci kraw�dzi
		int wiersz = rand() % v;
		int kolumna = rand() % v;
		if (zmodyfikowane[wiersz][kolumna] == false) {
			graf[wiersz][kolumna] = rand() % 9 + 1;
			zmodyfikowane[wiersz][kolumna] = true;
			licznik++;
		}
	}
	return true;
}


void Macierzowo::wyswietl(uint **macierz){
	for (uint i = 0; i < v; i++){
		printf("\n");
		for (uint j = 0; j < v; j++)
			printf("%d ", macierz[i][j]);
	}
	printf("\n");
}

void Macierzowo::wyswietl(){
	wyswietl(graf);
}

void Macierzowo::usunGraf(){
	for (uint i = 0; i < v; i++)
		delete[] graf[i];
	delete[] graf;
}

bool Macierzowo::wczytajZPliku(const char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki){
	uint wiersz, kolumna, tempWaga;
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s�u��cy jedynie do odczytu, sprawdzenie czy otwarcie pliku si� powiod�o
		fscanf_s(plik, "%d %d", &e, &v); //wczytuj� liczb� kraw�dzi i liczb� wierzcho�k�w
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytuj� dodatkowo nr wierzcho�ka pocz�tkowego
		utworzGraf();
		for (uint i = 0; i < e; i++){
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

uint Macierzowo::getV0(){
	return v0;
}