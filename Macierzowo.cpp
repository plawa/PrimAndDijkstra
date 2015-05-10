#include "stdafx.h"
#include "Macierzowo.h"
#include <math.h>

#define NIESKONCZONOSC 4294967295

//Struktura reprezentuj¹ca krawêdŸ, bêdzie u¿ywana w liscie.
//Jej pocz¹tkowy wierzcho³ek reprezentuje index tablicy pod którym sie znajduje.
//----------------------------------------------------------------------------
struct krawedz {
	krawedz(uint poczatek, uint koniec, uint wag) {	v1 = poczatek, v2 = koniec, waga = wag;	}
	uint v1, v2, waga;
};

//Struktura stworzona na potrzeby implementacji kolejki priorytetowej dla alg Prima.
//Odpowiada za rosn¹ce sortowanie krawêdzi w kolejce po wagach.
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
//Odpowiada za rosn¹ce sortowanie wierzcho³ków w kolejce po odleg³oœciach od Ÿród³a.
//---------------------------------------------------------------------------
struct porownajOdleglosci{
	bool operator() (const wierzch &wierzch1, const wierzch &wierzch2){
		if (wierzch1.odleglosc > wierzch2.odleglosc) return true;
		else return false;
	}
};

//Konstruktor, który resetuje generator liczb pseudolowych i zapewnia, ¿e pierwsze
//wczytanie grafu przebiegnie bez próby usuwania poprzedniej (nieistniej¹cej) instancji.
//---------------------------------------------------------------------------
Macierzowo::Macierzowo(){
	pierwszeWczytywanie = true;
	srand((size_t)time(NULL)); //na potrzeby u¿ywania funkcji rand()
}

//Destruktor, wywo³uje funkcjê "usunGraf()"
//--------------------------------------------------------------------------
Macierzowo::~Macierzowo(){
	usunGraf();
}

//Znajduje najkrótsze drzewo rozpinaj¹ce w grafie reprez. przez macierz.
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
	odwiedzone[v0] = true;							//wierzcho³ek pocz¹tkowy oznaczam jako odwiedzony
	uint koniec2, koniec1 = koniec2 = v0;			//koñce drzewa - pocz¹tkowo oba równe s¹ wierzcho³kowi pocz¹tkowemu
	// ----- PÊTLA G£OWNA ------
	for (uint licznik = 0; licznik < v - 1; licznik++){ //krawêdzi bêdzie o 1 mniej ni¿ jest wierzcho³ków
		//budowanie kolejki wierzcho³ków osi¹galnych przez MST
		TkolejkaKrawedzi kolejka;
		for (uint i = 0; i < v; i++){				//i = koniec 1, bo macierz grafu nieskierowanego jest symetryczna
			if (uint waga = graf[koniec1][i])		//sprawdzam krawêdzie wychodz¹ce z koniec1 i przy okazji przypisujê do zmiennej "waga"
				kolejka.push(*(new krawedz(koniec1, i, waga)));
			if (koniec2 != koniec1)					//jeœli graf ma dwa ró¿ne koñce
				if (uint waga = graf[koniec2][i])	//sprawdzam krawêdzie wychodz¹ce z koniec2
					kolejka.push(*(new krawedz(koniec2, i, waga)));
		}
		bool dodanoKrawedz = false;
		while (!dodanoKrawedz && !kolejka.empty()){ //wykonuj dopóki krawêdŸ nie zostanie dodana i kolejka nie zostanie wyczerpana
			krawedz tempKraw = kolejka.top();
			kolejka.pop();
			if (odwiedzone[tempKraw.v2] == false){	//jeœli wierzcholek jeszcze nie by³ odwiedzony
				//to dodaj krawêdŸ do MST
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


//Znajduje najkrótsze drogi z wierzcho³ka v0 do wszystkich innych.
//TYLKO DLA PROBLEMU NR 2
//---------------------------------------------------------------
bool Macierzowo::algorytmDijkstry(){
	//******* DANE *********
	v0;											//wierzcho³ek startowy
	uint *odleglosc = new uint[v];				//tablica najkrótszych odleg³oœci ka¿dego wierzcho³ka od Ÿród³a (v0)
	uint *poprzednik = new uint[v];			//tablica poprzedników dla ka¿dego z wierzch. na jego najkrótszej œcie¿ce
	bool *maPoliczonaOdleglosc = new bool[v];	//tablica która mówi czy dany wierzcho³ek ma ju¿ policzon¹ najkrót. œcie¿kê od v0

	//inicjalizacja danych
	for (uint i = 0; i < v; i++){
		maPoliczonaOdleglosc[i] = false;		//na pocz¹tku ¿aden wierzch nie ma pol. odleg³oœci
		poprzednik[i] = 0;						//brak danych o poprzednikach na starcie
		odleglosc[i] = NIESKONCZONOSC;			//odleg³oœci na pocz¹tku s¹ równe nieskonczonoœæ
	}
	odleglosc[v0] = 0;							//bo koszt dojœcia od Ÿród³a do Ÿród³a = 0
	//-----------------------------------------
	while (!wszystkieTrue(maPoliczonaOdleglosc)){
		uint idxMinimum = zwrocIdxMinimum(odleglosc, maPoliczonaOdleglosc); //zwraca index wierzcho³ka o minimalnej odleglosci
		maPoliczonaOdleglosc[idxMinimum] = true;							//przenosi do zbioru wierzch o policzonej odleg³oœci
		for (uint i = 0; i < v; i++)										//iteracja po ka¿dym z mo¿liwyuch s¹siadów
			if (uint waga = graf[idxMinimum][i])							//jeœli pod danym indexem istnieje krawêdŸ:
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
	if (pierwszeWczytywanie == false)	//jeœli graf tworzony jest niepierwszy raz w obecnym obiekcie
		usunGraf();						//to czyœcimy
	v = iloscWierzcholkow;
	uint **tempGraf = new uint*[v];
	for (uint i = 0; i < v; i++) {
		tempGraf[i] = new uint[v];
		for (uint j = 0; j < v; j++)
			tempGraf[i][j] = 0;			//inicjalizacja zerami, które oznaczaj¹ ¿e danych dwóch wierzcho³ków nie ³¹czy ¿adna krawêdŸ
	}
	graf = tempGraf;
	pierwszeWczytywanie = false;
	return true;
}

bool Macierzowo::utworzGraf(){
	return utworzGraf(v);
}

bool Macierzowo::generujLosowoNieskierowany(uint v, int gestosc){
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false;
		zmodyfikowane[i][i] = true; //blokada przek¹tnej (maj¹ tam byæ same zera)
	}//koniec inicjalizacji macierzy boolowskiej
	
	uint licznik = 0;
	int minProcent = static_cast<int>(ceil(static_cast<float>(200 / v))); //min procent krawêdzi, aby graf by³ spójny
	int maxE = v*(v - 1) / 2; //max iloœæ krawêdzi dla grafu nieskierowanego
	e = (int)floor((float)(maxE * gestosc / 100)); //iloœæ krawêdzi do dodania wyliczona na podstawie gêstoœci
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	//iteracja poni¿ej nastêpuje po "trójk¹cie" - czêœci tablicy, która bêdzie symetrycznie odbijana wzglêdem przek¹tnej
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu (zapewnienie spójnoœci)
		//³¹czê wierzcho³ki (1->2->3->4 ...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = graf[i + 1][i] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = zmodyfikowane[i + 1][i] = true;
		licznik++;
	}
	while (licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
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
	//inicjalizacja macierzy, która przechowywaæ bêdzie informacje czy dana komórka zosta³a ju¿ wczeœniej edytowana przez generator
	bool **zmodyfikowane = new bool*[v];
	for (uint i = 0; i < v; i++){
		zmodyfikowane[i] = new bool[v];
		for (uint j = 0; j < v; j++)
			zmodyfikowane[i][j] = false; 
		zmodyfikowane[i][i] = true; //blokada, bo po przek¹tnej tylko zera
	}//koniec inicjalizacji macierzy boolowskiej
	//------------------------------------
	uint licznik = 0, maxE = v * (v - 1); //max mo¿liwa iloœæ krawêdzi dla grafu skierowanego
	int minProcent = static_cast<int>(ceil(static_cast<float>(100/v)));
	e = static_cast<int>( floor( static_cast<float>(maxE*gestosc/100) ) ); //iloœæ krawêdzi wyliczona na podstawie gêstoœci
	v0 = rand() % v; //losowanie wierzcho³ka pocz¹tkowego dla PNS
	if (gestosc < minProcent || gestosc > 100)
		return false;
	utworzGraf(v);
	for (uint i = 0; i < v - 1; i++){ //najpierw inicjalizacja grafu
		//³¹czê wierzcho³ki (1->2->3->4->...), tworz¹c najpierw graf spójny z wagami 1 do 9 i "odznaczam" w zmodyfikowanych
		graf[i][i + 1] = rand() % 9 + 1; 
		zmodyfikowane[i][i + 1] = true;
		licznik++;
	}
	while(licznik < e) { //nastêpnie uzupe³nianie losowymi wartoœciami do uzyskania po¿¹danej iloœci krawêdzi
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
	if (plik = fopen(nazwaPliku, "r")){ //uchwyt s³u¿¹cy jedynie do odczytu, sprawdzenie czy otwarcie pliku siê powiod³o
		fscanf_s(plik, "%d %d", &e, &v); //wczytujê liczbê krawêdzi i liczbê wierzcho³ków
		if (dlaProblemuNajkrotszejSciezki)
			fscanf_s(plik, "%d", &v0); //wczytujê dodatkowo nr wierzcho³ka pocz¹tkowego
		utworzGraf();
		for (uint i = 0; i < e; i++){
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

uint Macierzowo::getV0(){
	return v0;
}