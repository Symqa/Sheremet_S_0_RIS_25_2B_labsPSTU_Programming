#include <iostream>
#include <clocale>
#include <stdlib.h>
#include <chrono>

using namespace std;

void fillArr(int* arr, int &size) {
	for (int i = 0; i < size; i++) {
		arr[i] = rand()%100-50;
	}
	cout << "Исходный массив: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}

void printRing(int *arr, int &size, int &K) {
	if (size == 0) {
		cout << "Массив пуст." << endl;
		return;
	}
	cout << "Кольцо (вид слева) K = " << K << ": ";
	for (int i = K; i <= size - 1; ++i) {
		cout << arr[i] << ' ';
	}
	for (int i = 0; i < K; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
	cout << "Кольцо (вид справа) K = " << K << ": ";
	for (int i = K; i >= 0; --i) {
		cout << arr[i] << ' ';
	}
	for (int i = size - 1; i > K; i--) {
		cout << arr[i] << ' ';
	}
	cout << endl << endl;
}

void deleteFirstAndLast(int* arr, int& size) {
	int temp = arr[0];
	for (int i = 1; i < size; i++) {
		arr[i-1] = arr[i];
	}
	arr[size-1] = temp;
	size-=2;
	cout << "Массив после удаления первого и последнего: ";
	for (int i = 0; i < size; i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;
}


int main() {
	auto start = std::chrono::high_resolution_clock::now();
	setlocale(LC_ALL, "ru");
	const int N = 256;
	int size, K;

	do {
		cout << "Введите размер кольца (не больше 256): ";
		cin >> size;
	} while(size <= 0 || size >= N);

	do {
		cout << "Введите индекс K, с которого печатается кольцо от 0 до " << size - 1 << ": ";
		cin >> K;
	} while (K < 0 || K >= size);
	cout << endl;

	int arr[N];
	fillArr(arr, size);
	printRing(arr, size, K);
	deleteFirstAndLast(arr, size);
	printRing(arr, size, K);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Время выполнения: " << diff.count() << " секунд" << std::endl;
	cin >> K;

	return 0;
}