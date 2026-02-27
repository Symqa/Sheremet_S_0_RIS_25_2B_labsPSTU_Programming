#include <iostream>
#include <clocale>
#include <stdlib.h>
#include <chrono>
using namespace std;

void printArr(int arr[][10], const int& rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 10; j++) {
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}
}

void fillArr(int arr[][10], const int& rows) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < 10; j++) {
			arr[i][j] = rand()%10;
		}
	}
}

void changeArr(int arr[][10], const int& rows) {
	int k = 1;
	int j = 0;
	while (k < 10) {
		for (int i = rows-1; i > rows - 1 - k; i--) {
			arr[i][j] = 0;
		}
		k++;
		j++;
	}
}

void sumColumns(int arr[][10], const int& rows) {
	int max = 0;
	for (int j = 0; j < rows - 1; j++) {
		int i = 0;
		int sum = 0;
		while (i < 10) {
			sum+= arr[i][j];
			i++;
		}
		cout << sum << ' ';
		if (sum > max) {
			max = sum;
		}
	}
	cout << endl;
	cout << "Максимальная сумма: " << max;
}

int main() {
	auto start = std::chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "ru");
	int a;
	const int size = 10;
	int arr[size][size];
	
	fillArr(arr, size);
	cout << "Массив после заполнения:" << endl;
	printArr(arr, size);
	changeArr(arr, size);
	cout << endl << endl;
	cout << "Массив после обработки (визуализация):" << endl;
	printArr(arr, size);
	cout << endl;
	sumColumns(arr, size);
	cout << endl;
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Время выполнения: " << diff.count() << " секунд" << std::endl;
	
	cin >> a;
	return 0;
}