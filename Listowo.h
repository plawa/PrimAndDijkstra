#pragma once
class Listowo {
public:
	Listowo();
	~Listowo();
	bool wczytajZPliku(char nazwaPliku[], bool dlaProblemuNajkrotszejSciezki = false);
private:
	bool pierwszeWczytywanie;
	FILE *plik; //fdsagdsggasd
};
