#include <iostream>
#include <clocale>
#include <stdlib.h>
using namespace std;


void printArr(int **arr, int rows, int cols) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}
}

int getMax(int** arr, int rows, int cols) {
	int max = arr[0][0];
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
			}
		}
	}
	return max;
}

int main() {
	setlocale(LC_ALL, "Russian");

	// Размеры
	int rows, cols;
	cout << "Введите размеры массива (сначала строки, потом столбцы, через пробел): ";
	cin >> rows >> cols;

	// Создание основного массива
	int **matrix = new int*[rows];
	for (int i = 0; i < rows; i++) {
		matrix[i] = new int[cols];
	}
	
	// Заполнение случайными числами
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = rand()%10;
		}
	}
	cout << endl << "Исходный массив: " << endl;
	printArr(matrix, rows, cols);

	// Нахождение максимума
	const int MAX = getMax(matrix, rows, cols);
	cout << endl << "Максимальный элемент: " << MAX << endl;

	// Создание новых bool массивов под индексы i и j
	bool *indexesI = new bool[rows]();
	bool *indexesJ = new bool[cols]();

	// Заполнение новых bool массивов под индексы i и j, используя максимум
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == MAX) {
				indexesI[i] = true;
				indexesJ[j] = true;
			}
		}
	}

	// Нахождение новых размеров массива
	int newRows = 0, newCols = 0;
	for (int i = 0; i < rows; i++) if (!indexesI[i]) newRows++;
	for (int j = 0; j < cols; j++) if (!indexesJ[j]) newCols++;

	// Создание нового массива
	int **new_matrix = new int*[rows];
	for (int i = 0; i < newRows; i++) {
		new_matrix[i] = new int[cols];
	}
	
	// Заполнение массива, исходя из значений из bool массивов
	int newI = 0;
	for (int i = 0; i < rows; i++) {
		if (indexesI[i]) continue;
		int newJ = 0;

		for (int j = 0; j < cols; j++) {
			if (indexesJ[j]) continue;
			new_matrix[newI][newJ] = matrix[i][j];
			newJ++;
		}
		newI++;
		
	}

	// Освобождение памяти и вывод нового массива
	cout << endl; 
	for (int i = 0; i < rows; i++) {
		delete[] matrix[i];
		matrix[i] = nullptr;
	}
	delete[] matrix;
	matrix = nullptr;

	cout << endl << "Новый массив: " << endl;
	printArr(new_matrix, newRows, newCols);
	delete[] indexesI;
	delete[] indexesJ;
	indexesI = nullptr;
	indexesJ = nullptr;
	return 0;
}