#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

using namespace std;


void printArray(int *arr, int size, int low = -1, int high = -1, int pivotIdx = -1) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        if (i == low) cout << "[";      
        cout << arr[i];
        if (i == pivotIdx) cout << "*";  
        if (i == high) cout << "]";     
        if (i < size - 1) cout << " ";
    }
    cout << "]\n";
}


int lomutoPartition(int *arr, int low, int high) {
    int pivot = arr[high];
    int i = low;

    cout << "  Разбиение [" << low << ".." << high << "], опорный = " << pivot << endl;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);


    cout << "  Результат: ";
    for (int k = low; k <= high; k++) {
        if (k == low) cout << "[";
        cout << arr[k];
        if (k == i) cout << "*";
        if (k == high) cout << "]";
        if (k < high) cout << " ";
    }
    cout << "  (опорный на позиции " << i << ")\n\n";
    return i;
}


void lomutoSort(int *arr, int low, int high, int totalSize) {
    if (low < high) {
        cout << "Сортируем подмассив с индексами [" << low << ".." << high << "]: ";
        for (int i = low; i <= high; i++) cout << arr[i] << " ";
        cout << endl;

        int pivot = lomutoPartition(arr, low, high);

        lomutoSort(arr, low, pivot - 1, totalSize);
        lomutoSort(arr, pivot + 1, high, totalSize);
    }
}


void lomutoSort(int *arr, int size) {
    lomutoSort(arr, 0, size - 1, size);
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    srand(time(NULL));

    int n;
    cout << "Введите размер массива: ";
    do {
        cin >> n;
    } while (n < 1);

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    cout << "\nИсходный массив: ";
    printArray(arr, n);
    cout << "\nНачинаем быструю сортировку (Ломуто)...\n\n";

    lomutoSort(arr, n);

    cout << "Отсортированный массив: ";
    printArray(arr, n);

    delete[] arr;
    return 0;
}