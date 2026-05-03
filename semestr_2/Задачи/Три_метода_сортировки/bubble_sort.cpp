#include <iostream>
#include <algorithm>
using namespace std;

// Сортировка пузырьком
void bubbleSort(int* arr, int);

int main() {
    // Исходные данные
    int N = 4;
    int data[N] = {64, 25, 11, 90};

    cout << "Исходный маcсив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl << endl;

    bubbleSort(data, N);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                cout << arr[j] << "  <=>  " << arr[j + 1] << endl << "Массив после смены: ";
                swap(arr[j], arr[j + 1]);
                for (int i = 0; i < n; i++) {
                    cout << arr[i] << " ";
                }
                cout << endl << endl;
                swapped = true;
            }
        }
        // Если обменов не было, массив уже отсортирован
        if (!swapped) break;
    }
}