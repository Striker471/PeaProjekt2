#include "SimulatedAnnealing.h"
#include <iostream>
#include <windows.h>
#include <cmath>
#include <cstdlib>
#include <algorithm> 

using namespace std;


double SimulatedAnnealing::getProbability(int cost, int newCost, double temperature) { //Liczenie prawdopodobieństwa
    return exp(double(((double(cost) - double(newCost)) / temperature)));
}

//Definicja s�siedztwa
void SimulatedAnnealing::changeNeighbors(vector<int>& path) { //Zmiana dwóch losowych miast ze sobą w drodze
    int city1 = rand() % (size_of_matrix - 1);
    int city2 = rand() % (size_of_matrix - 1);

    while (city1 == city2) //Sprawdzamy, czy nie s� r�wne
        city2 = rand() % (size_of_matrix - 1);

    if (typeneighbour == 1)
        std::swap(path[city1], path[city2]);
    else {
        if (city1 < city2)
            reverse(path.begin() + city1, path.begin() + city2);
        else
            reverse(path.begin() + city2, path.begin() + city1);
    }
}

vector<int> SimulatedAnnealing::generateInitPath() {
    initX = rand() % (size_of_matrix - 1); //Losujemy początkowy wierzchołek

    vector<bool> visited(size_of_matrix); //Lista odwiedzonych wierzchołków
    for (int i = 0; i < size_of_matrix; i++)
        visited[i] = false;
    visited[initX] = true;

    vector<int> path;
    path.push_back(initX);
    int minNode = initX;

    //Szukamy po kolei najkrótszej ścieżki i wrzucamy do początkowej drogi
    for (int i = 0; i < size_of_matrix - 1; i++) {
        int minCost = INT_MAX;
        for (int j = 0; j < size_of_matrix; j++) {
            if (!visited[j] && matrix[path[path.size() - 1]][j] < minCost) {
                minCost = matrix[path[path.size() - 1]][j];
                minNode = j;
            }
        }
        path.push_back(minNode);
        visited[minNode] = true;
    }

    //Usuwamy initX z path
    path.erase(path.begin());
    return path;
}

int SimulatedAnnealing::getPathCost(vector <int> path) { //Liczenie kosztu dla danej ścieżki
    int cost = 0;

    cost += matrix[initX][path[0]];
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];
    cost += matrix[path[path.size() - 1]][initX];

    return cost;
}

double SimulatedAnnealing::updateTemperature(double oldTemperature, double alpha) {
    return oldTemperature * alpha;
}

void SimulatedAnnealing::simulateAnnealing(int timeToStop, double alpha, int typeneighborhood) {
    start = Time::read_QPC();
    typeneighbour = typeneighborhood;
    vector<int> path = generateInitPath(); //Znajdujemy początkową drogę
    int cost = getPathCost(path); //I początkowy koszt
    double temperature = setInitTemperature(cost, alpha); //Temperatura początkowa
    int eraLength = size_of_matrix; //Ilość epok
    while (endTime < timeToStop) { //Sprawdzamy warunek stopu
        vector<int> localBest = path;
        int localBestCost = cost;
        vector<int> newPath;
        
        for (int i = 0; i < eraLength; i++) { //Epoki
            newPath = localBest;
            changeNeighbors(newPath);
            int newCost = getPathCost(newPath);

            if (newCost < localBestCost) {
                localBest = newPath;
                localBestCost = newCost;
            }
            else  {
                double probability = getProbability(localBestCost, newCost, temperature);
                double randomNumber = (double)(rand() % 999) / 1000.0;

                if (randomNumber < probability) {
                    localBest = newPath;
                    localBestCost = newCost;
                }
               
            }
        }
        if (localBestCost < cost) {
            path = localBest;
            cost = localBestCost;
        }

        temperature = updateTemperature(temperature, alpha);
        endTime = ((Time::read_QPC() - start) / frequency);
    }
    displayPath(path); //Wyświetlanie wyniku
    displayResult(cost, endTime, temperature);
}


void SimulatedAnnealing::displayResult(int cost, int time, double temperature) {
    cout << "Koszt: " << cost << endl;
}

void SimulatedAnnealing::displayPath(std::vector<int> path) { //Wyświetlanie końcowego wyniku
    cout << "\n\nOdnaleziona droga: " << endl;
    cout << initX << " -> ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " -> ";
    }
    cout << initX << endl;
}

double SimulatedAnnealing::setInitTemperature(int cost, double alpha) {
    return cost * alpha; //Temperatura pocz�tkowa
}
