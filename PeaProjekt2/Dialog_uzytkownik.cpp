#include "Dialog_uzytkownik.h"


void Dialog_uzytkownik::dialog()
{
	Macierz macierz;
	cout << "Autor Jakub Budzilo\nWitam w TSP\n\n";
	macierz.initialization();
	int x;
	int time = kryterium_stopu();
	int typeneighbourhood = sasiedztwo_wybor();
	for (;;)
	{
		cout << "0.Wybierz macierz" << endl;
		cout << "1.Zamien kryterium_stopu" << endl;
		cout << "2.Zamiana sasiedztwa" << endl;
		cout << "3.Uruchom Wyzarzanie" << endl;
		cout << "4.Uruchom TabuSearch" << endl;
		cout << "5.Opusc program" << endl;

		x = duza_liczba(0, 5);

		switch (x)
		{
		case 0:
		{
			macierz.initialization();
		}
		break;
		case 1:
		{
			time = kryterium_stopu();
		}
		break;
		case 2:
		{
			typeneighbourhood = sasiedztwo_wybor();
		}
		break;
		case 3:
		{
			SimulatedAnnealing* simulatedAnnealing = new SimulatedAnnealing(macierz.get_matrix());

			simulatedAnnealing->simulateAnnealing(time, 0.95, typeneighbourhood);

			delete simulatedAnnealing;
		}
		break;
		case 4:
		{
			TabuSearch* tabusearch = new TabuSearch(macierz.get_matrix());

			tabusearch->tabuSearch_run(time, typeneighbourhood);

			delete tabusearch;
		}
		break;
		case 5:
		{
			exit(0);
		}
		break;
	}
	}
}

int Dialog_uzytkownik::duza_liczba(int min, int max)
{
	cout << "Podaj wartosc:";
	string text;
	cin >> text;
	while (!czy_liczba_nieujemna(text))
	{
	et1:
		cout << "Niepoprawny znak";
		cin.clear();
		cin.ignore(50, '\n');
		cout << endl << "Podaj wartosc:";
		cin >> text;

	}
	int x = stoi(text);
	if (x > max || x < min)
		goto et1;
	cout << "\n";
	return x;
}
int Dialog_uzytkownik::duza_liczba()
{
	cout << "Podaj wartosc:";
	string text;
	cin >> text;
	while (!czy_liczba(text))
	{

		cout << "Niepoprawny znak";
		cin.clear();
		cin.ignore(50, '\n');
		cout << endl << "Podaj wartosc:";
		cin >> text;

	}
	int x = stoi(text);
	cout << "\n";
	return x;
}
bool Dialog_uzytkownik::czy_liczba_nieujemna(string text)
{
	for (int i = 0; i < text.length(); i++) if (text[i] > '9' || text[i] < '0') return false;

	return true;
}

bool Dialog_uzytkownik::czy_liczba(string text)
{

	for (int i = 0; i < text.length(); i++) if (text[i] > '9' || text[i] < '0')
		if (!((text[0] == '-') && i == 0))
			return false;

	return true;
}

int Dialog_uzytkownik::kryterium_stopu() {
	int time;
	cout << "Podaj czas wykonywania algorytmu w sekundach:\n";
	do {
		time = duza_liczba(1,INT_MAX);
	}
	while (time <= 0);
	return time;
}
int Dialog_uzytkownik::sasiedztwo_wybor() {
	int sasiedztwo;
	cout << "Podaj sasiedztwo:\n'1' = SWAP\n'2' = Reverse\n";
	sasiedztwo = duza_liczba(1, 2);
	return sasiedztwo;
}