#include <iostream>
#include <algorithm>
using namespace std;

// Сортировка выбором
void selectionSort(int* arr, int N);

int main() {
    int N = 4;
    int data[N] = {99, 0, 194, 3};

    cout << "Исходный маcсив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl << endl;

    selectionSort(data, N);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}


void selectionSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            cout << arr[i] << " <=> " << arr[min_idx] << endl;
            swap(arr[i], arr[min_idx]);
            cout << "Массив после перестановки: ";
            for (int i = 0; i < n; i++) {
                    cout << arr[i] << " ";
                }
            cout << endl << endl;
        }
    }
}