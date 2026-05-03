#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>

using namespace std;

void printArr(int *arr, int size) {
    cout << endl << endl;
    for (int i = 0; i < size; i++) {
        cout << arr[i] << ' ';
    }
}

void insertionSortByStep(int *arr, int size) {
    int stepNum = 1;
    for (int step = size/2; step > 0; step/=2) {
        cout << "\n===== Шаг " << stepNum << ": шаг = " << step << " =====" << endl;
        cout << "Массив до шага:";
        printArr(arr, size);
        cout << endl;

        for (int i = step; i < size; i++) {
            int temp = arr[i];
            int j;
            cout << "  Берём arr[" << i << "] = " << temp << endl;
            for (j = i; j >= step && arr[j - step] > temp; j -= step) {
                cout << "    Сравниваем с arr[" << j - step << "] = " << arr[j - step] << " -> сдвигаем вправо" << endl;
                arr[j] = arr[j - step];
                cout << "    Промежуточный массив:";
                printArr(arr, size);
                cout << endl;
            }
            if (j != i) {
                arr[j] = temp;
                cout << "    Вставляем " << temp << " на позицию " << j << endl;
                cout << "    После вставки:";
                printArr(arr, size);
                cout << endl;
            } else {
                cout << "    Сдвиг не требуется" << endl;
            }
        }
        stepNum++;
        cout << "Массив после шага:";
        printArr(arr, size);
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    srand(time(0));
    int n;
    cout << "Введите размер массива: ";
    do {
        cin >> n;
    } while (n < 2);

    int *arr = new int[n];
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    cout << "Начальный массив:";
    printArr(arr, n);
    cout << endl;

    insertionSortByStep(arr, n);

    cout << "\n\nКонечный отсортированный массив:";
    printArr(arr, n);
    cout << endl;

    delete[] arr;
    return 0;
}