#pragma once
#include <vector>
#include "Time.h"
class TabuSearch
{
	
	long long int frequency, start;
	long long int endTime = 0; //Warunek stopu
	Time timee;
	std::vector<std::vector<int>> matrix; //macierz odleglosci miast
	int size_of_matrix;
	int initX; // aktualny wierzcholek poczatkowy
	std::vector<int> final_path;
	int final_cost = INT_MAX;
	int city1,city2;
	int typeneighbour;

public:
	TabuSearch(std::vector<std::vector<int>> Matrix) : matrix(Matrix), size_of_matrix(Matrix.size()) {
		srand(time(NULL));

		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}
	
	std::vector<int> changeNeighbors(std::vector<int> path, std::vector<std::vector<int>>& tabu, int& critical);
	std::vector<int> generateInitPath();
	int getPathCost(std::vector <int> path);
	void tabuSearch_run(int TimeToStop, int type);
	void displayPath();
	void displayResult();
};

