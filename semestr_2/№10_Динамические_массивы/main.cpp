#include <iostream>
#include <stdlib.h>
#include <clocale>
#include <ctime>
using namespace std;
// При поиске максимального элемента возвращать индексы, которые идут под снос
void fillArr(int** arr, int columns, int rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			arr[i][j] = rand()%10;
		}
	}
}

void printArr(int** arr, int columns, int rows) {
	cout << endl << "Массив:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}
	cout << endl;
}

int getMax(int **arr, int columns, int rows) {
	int max = arr[0][0];
	int count = 1;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (arr[i][j] > max) {
				max = arr[i][j];
				count = 1;
			}
			else if (arr[i][j] == max) {
				count++;
			}
		}
	}
	cout << endl << "Количество максимальных элементов: " << count << endl;
	return max;
}

void deleteArr(int **&arr, int& columns, int& rows) {
	for (int i = 0; i < rows; i++) {
		delete[] arr[i];
		arr[i] = nullptr;
	}
	delete[] arr;
	arr = nullptr;
}

int** deleteRowAndColumn(int **arr, int& columns, int& rows, int& max_i, int& max_j) {

	int **new_arr = new int*[rows-1];
	for (int index = 0; index < rows-1; index++) {
		new_arr[index] = new int[columns-1];
	}
	int shift_i = 0, shift_j = 0;
	for (int i = 0; i < rows; i++) {
		shift_j = 0;
		for (int j = 0; j < columns; j++) {
			if (i == max_i) {
				shift_i++;
				break;
			}
			else if (j == max_j) {
				shift_j++;
				continue;
			}
			else {
				new_arr[i-shift_i][j-shift_j] = arr[i][j];
			}
		}
	}
	deleteArr(arr, columns, rows);
	columns-=1;
	rows-=1;
	return new_arr;
	
}

int main() {
	int rows, columns, max;
	setlocale(LC_ALL, "ru");
	srand(time(nullptr));

	cout << "Введите количество строк матрицы: ";
	cin >> rows;
	cout << endl;

	int **arr = new int*[rows];
	cout << "Введите размер каждой строки: ";
	cin >> columns;
	cout << endl;

	for (int i = 0; i < rows; i++) {
		arr[i] = new int[columns];
	}
	fillArr(arr, columns, rows);
	printArr(arr, columns, rows);
	max = getMax(arr, columns, rows);
	cout << "Максимальный элемент: " << max << endl;
	
	bool find_max;
	while (getMax(arr, columns, rows) == max) {
		find_max = false;
		for (int i = 0; i < rows; i++) {
			if (find_max) break;
			for (int j = 0; j < columns; j++) {
				if (arr[i][j] == max) {
					arr = deleteRowAndColumn(arr, columns, rows, i, j);
					find_max = true;
					break;
				}
			}
		}
	}
	printArr(arr, columns, rows);
	

	cin >> rows;
	return 0;
}