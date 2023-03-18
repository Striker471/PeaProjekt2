#include "Macierz.h"



void Macierz::initialization() {
	std::fstream file;

	
	bool is_file_good = 0;
	do{
		string name;
		std::cout << "Podaj nazwe pliku(pamietaj o rozszerzeniu)\n";
		std::cin >> name;
		file.open(name, std::ios::in);

		if (file.good()){
			file >> size_of_matrix;
			matrix.resize(size_of_matrix);		// ustawienie rozmiaru vectora, zeby odpowiadal macierzy dwuwymiarowej
			for (int i = 0; i < size_of_matrix; i++)
				matrix[i].resize(size_of_matrix);
			for (int i = 0; i < size_of_matrix; i++)  // wypelnienie macierzy wartosciami z pliku
				for (int j = 0; j < size_of_matrix; j++) {
					
					file >> matrix[i][j];
					if (file.eof()) {
						std::cout << "Niepoprawna ilosc danych w pliku\n";
						goto et1;
					}	
				}	
			is_file_good = 1;
		}
		else {
			std::cout << "File error Podaj ponownie\n";
		}
		et1:
		file.close();
	}while (!is_file_good);
}

int Macierz::distance(std::vector<int>& path) {
	int temp_dist = 0;
	int j = 0;
	for (int i = 0; i < size_of_matrix - 1; i++)	// obliczanie drogi
	{
		temp_dist += matrix[j][path[i]];
		j = path[i];
	}
	temp_dist += matrix[j][0];
	return temp_dist;
}

void Macierz::random_matrix(int size) {
	srand(time(NULL));
	size_of_matrix = size;
	matrix.resize(size_of_matrix);		// ustawienie rozmiaru vectora, zeby odpowiadal macierzy dwuwymiarowej
	for (int i = 0; i < size_of_matrix; i++)
		matrix[i].resize(size_of_matrix);
	for (int i = 0; i < size_of_matrix; i++)  // wypelnienie macierzy wartosciami z pliku
		for (int j = 0; j < size_of_matrix; j++)
			matrix[i][j] = rand() % 1000 + 1;
	for (int i = 0; i < size_of_matrix; i++)
		matrix[i][i] = INF;

	/*for (int i = 0; i < size_of_matrix; i++) {
		for (int j = 0; j < size_of_matrix; j++)
			std::cout << matrix[i][j] << " ";
		std::cout << std::endl;
	}*/
}

std::vector<std::vector<int>> Macierz::get_matrix() {
	return matrix;
}
