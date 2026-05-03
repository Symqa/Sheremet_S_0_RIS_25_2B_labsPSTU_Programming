#include "Pair.h"
#include <iostream>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    // 1. Конструкторы
    Pair a;                        // без параметров (first и second = случайные числа)
    Pair b(10, 3.14);              // с параметрами
    Pair c(b);                     // копирования

    cout << "=== Созданные объекты ===" << endl;
    cout << "a: " << a;
    cout << "b: " << b;
    cout << "c (копия b): " << c;

    // 2. Селекторы и модификаторы
    cout << "\n=== Селекторы/модификаторы ===" << endl;
    cout << "first у b = " << b.getFirst() << ", second у b = " << b.getSecond() << endl;
    b.setFirst(42);
    b.setSecond(9.81);
    cout << "После изменений b: " << b;

    // 3. Присваивание
    a = b;                         
    cout << "\n=== Присваивание (a = b) ===" << endl;
    cout << "a стало: " << a;
    cout << "b осталось: " << b;

    // 4. Операции сравнения
    cout << "\n=== Сравнения ===" << endl;
    cout << "a == b ? " << (a == b ? "true" : "false") << endl;   // true, т.к. только что присвоили
    cout << "a != c ? " << (a != c ? "true" : "false") << endl;   // true, т.к. a=b, а c=3.14

    // 5. Вычитание константы
    cout << "\n=== Вычитание константы ===" << endl;
    Pair d(20, 5.5);
    cout << "Исходная пара d: " << d;

    d - 7;                         // целое число -> вычитается из first
    cout << "d - 7 (целое): " << d;

    d - 2.5;                       // дробное число -> вычитается из second
    cout << "d - 2.5 (дробное): " << d;

    // 6. Ввод с клавиатуры
    Pair e;
    cin >> e;
    cout << "Вы ввели: " << e;

    cout << "\n=== Завершение программы ===" << endl;
    return 0;
}