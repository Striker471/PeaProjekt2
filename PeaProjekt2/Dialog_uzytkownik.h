#pragma once
#include <iostream>
#include <string>
#include "Macierz.h"
#include "SimulatedAnnealing.h"
#include "TabuSearch.h"
using namespace std;
class Dialog_uzytkownik
{
public:
	void dialog();
	static int duza_liczba();
	static int duza_liczba(int min, int max);
	static bool czy_liczba_nieujemna(string text);
	static bool czy_liczba(string text);
	static int kryterium_stopu();
	static int sasiedztwo_wybor();
};