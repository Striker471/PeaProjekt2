#pragma once
#include <vector>
#include "Time.h"

class SimulatedAnnealing
{
	long long int frequency, start;
	long long int endTime = 0; //Warunek stopu
	Time timee;
	std::vector<std::vector<int>> matrix; //macierz odleglosci miast
	int size_of_matrix;
	int initX;
	int typeneighbour;
public:
	SimulatedAnnealing(std::vector<std::vector<int>> Matrix) : matrix(Matrix), size_of_matrix(Matrix.size()) {
		srand(time(NULL));

		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}
	double getProbability(int cost, int newCost, double temperature);
	void changeNeighbors(std::vector<int> &path);
	std::vector<int> generateInitPath();
	int getPathCost(std::vector <int> path);
	double updateTemperature(double oldTemperature, double alpha);
	void simulateAnnealing(int timeToStop, double alpha, int typeneighborhood);
	void displayResult(int cost, int time, double temperature);
	void displayPath(std::vector<int> path);
	double setInitTemperature(int cost, double alpha);


};

