#include <iostream>
#include <clocale>
#include <cstdlib>
using namespace std;


void printArray(int *arr, int size, int left = -1, int right = -1, int mid = -1) {
    cout << '[';
    for (int i = 0; i < size; ++i) {
        if (i == left) cout << '[';
        cout << arr[i];
        if (i == mid) cout << '|';
        if (i == right) cout << "]";
        if (i < size - 1) cout << " ";
    }
    cout << "]\n";
}

void merge(int *arr, int mid, int left, int right, int size) {
    int n1 = mid - left + 1; // размер слева
    int n2 = right - mid; // размер справа

    int *L = new int[n1];
    int *R = new int[n2];

    // Копирование данных
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    // слияние
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }
    // остатки данных
    while (i < n1) {
        arr[k++] = L[i++];
    } 
    while (j < n2) {
        arr[k++] = R[j++];
    }

    cout << "Слияние [" << left << ".." << mid << "] и [" << mid + 1 << "..." << right << "] -> ";
    printArray(arr, size, left, right, mid);

    delete[] L;
    delete[] R;
}


void mergeSort(int *arr, int left, int right, int size) {
    if (left >= right) return; // один элемент
    
    int mid = left + (right-left) / 2;
    mergeSort(arr, left, mid, size);
    mergeSort(arr, mid+1, right, size);
    merge(arr, mid, left, right, size);
}


void mergeSort(int *arr, int size) {
    return mergeSort(arr, 0, size-1, size);
} 



int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    int n;
    cout << "Введите размер массива: ";
    do {
        cin >> n;
    } while (n < 1);

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 100;
    }


    cout << "Исходный массив: ";
    printArray(arr, n);

    cout << "Начинаем сортировку слиянием...\n\n";
    mergeSort(arr, n);

    cout << "Отсортированный массив: ";
    printArray(arr, n);

    delete[] arr;

    return 0;
}