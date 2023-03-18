#pragma once
#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "Dialog_uzytkownik.h"
#include <string>
#include <iostream>

class Macierz
{
	std::vector<std::vector<int>> matrix; //macierz odleglosci miast
	int size_of_matrix;
	const int INF = INT_MAX;
	

public:
	
	void initialization();
	int distance(std::vector<int>& path);
	void random_matrix(int size);
	std::vector<std::vector<int>> get_matrix();
};



