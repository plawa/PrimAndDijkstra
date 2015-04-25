#include "stdafx.h"

#define ZAPYTAJ_O_PROBLEM "Ktory problem chcesz rozwiazac?\n"\
		"1. Wyznaczanie minimalnego drzewa rozpinajacego (MST)\n"\
		"2. Wyznaczanie najkrotszej sciezki w grafie\n"\
		"0. Wyjscie\n"\
		"\nPodaj wybor: "
#define ZAPYTAJ_O_OPERACJE "\n1. Wczytaj z pliku\n"\
		"2. Wygeneruj graf losowo\n"\
		"3. Wyswietl listowo i macierzowo na ekranie\n"\
		

class SDIZO2 {
public:

private:

};

void main() {
	SDIZO2 uchwyt;
	unsigned char problem, operacja;
	do { printf(ZAPYTAJ_O_PROBLEM); scanf_s("%d", &problem); } while (problem >= 3);
	while (true){
		switch (problem){
		case 1:
			printf(ZAPYTAJ_O_OPERACJE "4. Algorytm Prima\n5. Algorytm Kruskala\n\nPodaj wybor: "); scanf_s("%d", &operacja);

			break;
		case 2:
			printf(ZAPYTAJ_O_OPERACJE "4. Algorytm Dijkstry\n5. Algorytm Forda-Bellmana\n\nPodaj wybor: "); scanf_s("%d", &operacja);

			break;
		case 0:
			return; //wyjscie z programu
		default: 
			printf("Podano niewlasciwy wybor. Ponow probe.\n");
		}
		fflush(stdin); //wyczyœæ bufor klawiatury aby w razie wprowadzenia b³êdnego znaku pêtla nie by³a przetwarzana w nieskoñczonoœæ
	}
}

