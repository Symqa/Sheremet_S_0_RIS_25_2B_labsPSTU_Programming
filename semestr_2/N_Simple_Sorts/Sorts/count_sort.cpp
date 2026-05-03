#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArr(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void setMinMax(int *arr, int size, int &min, int &max) {
    min = arr[0];
    max = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
}

void countSort(int *arr, int size) {
    int min, max;
    setMinMax(arr, size, min, max);
    int range = max - min + 1;
    int *temp_arr = new int[range]();

    for (int i = 0; i < size; i++) {
        temp_arr[arr[i] - min]++;
    }

    cout << "\nМассив частот: ";
    for (int i = 0; i < range; i++) {
        cout << temp_arr[i] << " ";
    }
    cout << endl;

    int cur_index = 0;
    for (int i = 0; i < range; i++) {
        if (temp_arr[i] == 0) continue;
        for (int j = 0; j < temp_arr[i]; j++) {
            arr[cur_index++] = i + min;
            cout << "Шаг " << cur_index << ": ";
            printArr(arr, size);
        }
    }

    delete[] temp_arr;
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    srand(time(0));
    
    int size;
    cout << "Введите размер массива: ";
    do {
        cin >> size;
    } while (size < 2);

    int *arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 20;
    }

    cout << "Исходный массив: ";
    printArr(arr, size);

    countSort(arr, size);

    cout << "Отсортированный массив: ";
    printArr(arr, size);

    delete[] arr;
    return 0;
}