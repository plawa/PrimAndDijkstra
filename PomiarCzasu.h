#pragma once
#include "stdafx.h"

class PomiarCzasu
{
public:
	PomiarCzasu();
	~PomiarCzasu();
	void startTimer();
	double getTimer();
	double getCzestotliwoscCPU();
private:
	__int64 czasStartu;
	double czestotliwoscCPU;
};