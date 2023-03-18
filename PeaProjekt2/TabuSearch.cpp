#include "TabuSearch.h"
#include <algorithm> 
using std::vector;
using std::cout;
using std::endl;

//Definicja s¹siedztwa
std::vector<int>  TabuSearch::changeNeighbors(std::vector<int> path, std::vector<std::vector<int>> &tabu, int &critical) { //Zmiana dwóch losowych miast ze sob¹ w drodze
    do {
        city1 = rand() % (size_of_matrix - 1);
        city2 = rand() % (size_of_matrix - 1);  
        if (tabu[city1][city2] != 0)
            critical++;

    } while (city1 == city2 || tabu[city1][city2] != 0); //Sprawdzamy, czy nie s¹ równe i czy wystepuje tabu
    if (typeneighbour == 1)
        std::swap(path[city1], path[city2]);
    else {
        if (city1 < city2)
            reverse(path.begin() + city1, path.begin() + city2);
        else
            reverse(path.begin() + city2, path.begin() + city1);
    }
    return path;
}

vector<int> TabuSearch::generateInitPath() {
    initX = rand() % (size_of_matrix - 1); //Losujemy pocz¹tkowy wierzcho³ek

    vector<bool> visited(size_of_matrix); //Lista odwiedzonych wierzcho³ków
    for (int i = 0; i < size_of_matrix; i++)
        visited[i] = false;
    visited[initX] = true;

    vector<int> path;
    path.push_back(initX);
    int minNode = initX;

    //Szukamy po kolei najkrótszej œcie¿ki i wrzucamy do pocz¹tkowej drogi
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

int TabuSearch::getPathCost(vector <int> path) { //Liczenie kosztu dla danej œcie¿ki
    int cost = 0;

    cost += matrix[initX][path[0]];
    for (int i = 0; i < path.size() - 1; i++)
        cost += matrix[path[i]][path[i + 1]];
    cost += matrix[path[path.size() - 1]][initX];

    return cost;
}


void TabuSearch::tabuSearch_run(int TimeToStop, int type) {
    vector<vector<int>> tabu(size_of_matrix - 1, vector<int>(size_of_matrix - 1, 0));
    typeneighbour = type;

    start = Time::read_QPC();

    vector<int> optimal_path = generateInitPath(); //Znajdujemy pocz¹tkow¹ drogê
    final_path = optimal_path;
    final_cost = getPathCost(optimal_path); //I pocz¹tkowy koszt
    int optimal_cost = final_cost;
    const int critical = size_of_matrix * 5; // jesli bez poprawy przez wiele iteracji
    int x = 0;
    while (endTime < TimeToStop) {

        for (int i = 0; i < size_of_matrix - 1; i++)
            for (int j = 0; j < size_of_matrix - 1; j++)
                if (tabu[i][j] > 0)
                    tabu[i][j]--;

        vector<int> neighbourpath(size_of_matrix - 1);
        vector<int> temp_best_path = optimal_path;
        int temp_best_cost = optimal_cost;
        int temp_cost;
        int critical_counter = 0;
        do {
            neighbourpath = changeNeighbors(temp_best_path, tabu, critical_counter);
            temp_cost = getPathCost(neighbourpath);
            if (temp_cost < temp_best_cost) {
                temp_best_cost = temp_cost;
                temp_best_path = neighbourpath;
                tabu[city1][city2] = 10;
                break;
            }
                critical_counter++;
        } while (critical_counter < critical);

        if (optimal_cost > temp_best_cost) {
            
            optimal_cost = temp_best_cost;
            optimal_path = temp_best_path;
            x = 0;
            if (final_cost > optimal_cost) {
                final_cost = optimal_cost;
                final_path = optimal_path;
            }
        }
        else
            x++;
        if (x == 100) {
            optimal_path = generateInitPath();
            optimal_cost = getPathCost(optimal_path);
 
            x = 0;

        }
     endTime = ((Time::read_QPC() - start) / frequency);
    }
    displayPath();
    displayResult();
}

void TabuSearch::displayPath() { //Wyœwietlanie koñcowego wyniku
    cout << "\n\nOdnaleziona droga: " << endl;
    cout << initX << " -> ";
    for (int i = 0; i < final_path.size(); i++) {
        cout << final_path[i] << " -> ";
    }
    cout << initX << endl;
}

void TabuSearch::displayResult() {
    cout << "Koszt: " << final_cost << endl;
}