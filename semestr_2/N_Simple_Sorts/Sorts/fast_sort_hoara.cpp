#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArray(int *arr, int size, int low = -1, int high = -1, int markIdx = -1) {
    cout << "[";
    for (int i = 0; i < size; i++) {
        if (i == low) cout << "[";
        cout << arr[i];
        if (i == markIdx) cout << "*";
        if (i == high) cout << "]";
        if (i < size - 1) cout << " ";
    }
    cout << "]\n";
}

int hoarePartition(int *arr, int low, int high) {
    int pivot = arr[low + (high - low) / 2];
    int i = low - 1;
    int j = high + 1;

    cout << "  Разбиение [" << low << ".." << high << "], опорный = " << pivot << endl;

    while (true) {
        do {
            i++;
        } while (arr[i] < pivot);

        do {
            j--;
        } while (arr[j] > pivot);

        if (i >= j) {
            cout << "  Завершение, граница j = " << j << "\n  Результат: ";
            for (int k = low; k <= high; k++) {
                if (k == low) cout << "[";
                cout << arr[k];
                if (k == j) cout << "*";
                if (k == high) cout << "]";
                if (k < high) cout << " ";
            }
            cout << "  (левая часть [.." << j << "], правая [" << j+1 << "..])\n\n";
            return j;
        }

        swap(arr[i], arr[j]);

        cout << "    Обмен arr[" << i << "]=" << arr[i] << " и arr[" << j << "]=" << arr[j] << " -> ";
        for (int k = low; k <= high; k++) {
            if (k == low) cout << "[";
            cout << arr[k];
            if (k == high) cout << "]";
            if (k < high) cout << " ";
        }
        cout << endl;
    }
}

void hoareSort(int *arr, int low, int high) {
    if (low < high) {
        cout << "Сортируем подмассив [" << low << ".." << high << "]: ";
        for (int i = low; i <= high; i++) cout << arr[i] << " ";
        cout << endl;

        int p = hoarePartition(arr, low, high);

        hoareSort(arr, low, p);
        hoareSort(arr, p + 1, high);
    }
}

void hoareSort(int *arr, int size) {
    hoareSort(arr, 0, size - 1);
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
    cout << "\nНачинаем быструю сортировку (Хоара)...\n\n";

    hoareSort(arr, n);

    cout << "Отсортированный массив: ";
    printArray(arr, n);

    delete[] arr;
    return 0;
}