#include "PomiarCzasu.h"
#include "stdafx.h"

PomiarCzasu::PomiarCzasu()
{
	czasStartu = 0;
	czestotliwoscCPU = 0.0;
}

PomiarCzasu::~PomiarCzasu()
{
}

void PomiarCzasu::startTimer()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("Wyst¹pi³ b³¹d licznika!");
	czestotliwoscCPU = double(li.QuadPart);
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&li);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	czasStartu = li.QuadPart;
}
double PomiarCzasu::getTimer()
{
	LARGE_INTEGER li;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&li);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);
	return 1000*( (double)(li.QuadPart - czasStartu) / czestotliwoscCPU ); //pomno¿one przez 1000, bo milisekundy
}
double PomiarCzasu::getCzestotliwoscCPU(){
	return czestotliwoscCPU;
}