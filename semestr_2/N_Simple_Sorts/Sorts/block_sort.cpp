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

void insertionSort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

void bucketSort(int *arr, int n) {
    if (n <= 1) return;

    int maxVal = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    int numBuckets = n;
    int *bucketCounts = new int[numBuckets]();
    int **buckets = new int*[numBuckets];

    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * numBuckets) / (maxVal + 1);
        bucketCounts[idx]++;
    }

    for (int i = 0; i < numBuckets; i++) {
        if (bucketCounts[i] > 0) {
            buckets[i] = new int[bucketCounts[i]];
        } else {
            buckets[i] = nullptr;
        }
    }

    int *bucketPos = new int[numBuckets]();
    for (int i = 0; i < n; i++) {
        int idx = (arr[i] * numBuckets) / (maxVal + 1);
        buckets[idx][bucketPos[idx]++] = arr[i];
    }

    cout << "\n===== Распределение по корзинам =====" << endl;
    for (int i = 0; i < numBuckets; i++) {
        cout << "Корзина " << i << " (" << bucketCounts[i] << " элементов): ";
        if (bucketCounts[i] > 0) {
            for (int j = 0; j < bucketCounts[i]; j++) {
                cout << buckets[i][j] << " ";
            }
        }
        cout << endl;
    }

    cout << "\n===== Сортировка внутри корзин (вставками) =====" << endl;
    for (int i = 0; i < numBuckets; i++) {
        if (bucketCounts[i] > 1) {
            cout << "Сортируем корзину " << i << " до: ";
            for (int j = 0; j < bucketCounts[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            insertionSort(buckets[i], bucketCounts[i]);
            cout << "\n                после: ";
            for (int j = 0; j < bucketCounts[i]; j++) {
                cout << buckets[i][j] << " ";
            }
            cout << endl;
        } else if (bucketCounts[i] == 1) {
            cout << "Корзина " << i << " (один элемент, не сортируем): " << buckets[i][0] << endl;
        } else {
            cout << "Корзина " << i << " пуста" << endl;
        }
    }

    int index = 0;
    for (int i = 0; i < numBuckets; i++) {
        for (int j = 0; j < bucketCounts[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }

    cout << "\n===== После сборки =====" << endl;
    cout << "Массив: ";
    printArr(arr, n);

    for (int i = 0; i < numBuckets; i++) {
        if (buckets[i] != nullptr) delete[] buckets[i];
    }
    delete[] buckets;
    delete[] bucketCounts;
    delete[] bucketPos;
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    srand(time(0));

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Исходный массив: ";
    printArr(arr, n);

    bucketSort(arr, n);

    cout << "\nИтоговый отсортированный массив: ";
    printArr(arr, n);

    delete[] arr;
    return 0;
}