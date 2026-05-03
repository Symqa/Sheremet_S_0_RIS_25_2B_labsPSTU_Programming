#include <iostream>
using namespace std;


// Сортировка вставками

void insertionSort(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Сдвигаем элементы, которые больше key, на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
        
        cout << i <<".\t";
        for (int x = 0; x < n; x++) {
            cout << arr[x] << " ";
        }
        cout << endl;
    }
}

int main() {
    // Исходные данные
    int N = 4;
    int data[N] = {64, 25, 11, 90};

    cout << "Исходный маcсив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    insertionSort(data, N);

    cout << "Отсортированный массив: ";
    for (int i = 0; i < N; i++) {
        cout << data[i] << " ";
    }
    cout << endl;

    return 0;
}