#include "ATM.h"
#include <iostream>
#include <clocale>
using namespace std;


int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    // 1. Демонстрация конструктора без параметров
    cout << "=== 1. Конструктор без параметров (случайные поля) ===" << endl;
    ATM atm1;
    atm1.show();

    // 2. Демонстрация конструктора с параметрами
    cout << "\n=== 2. Конструктор с параметрами ===" << endl;
    ATM atm2(1001, 150000.0, 50000.0);
    atm2.show();

    // 3. Демонстрация конструктора копирования (инициализация другим объектом)
    cout << "\n=== 3. Конструктор копирования (atm3 = atm2) ===" << endl;
    ATM atm3 = atm2;
    atm3.show();

    // Изменяем данные atm3 через модификаторы (сеттеры)
    atm3.setId(2002);
    atm3.setBalance(75000);     // ожидается int, дробная часть отбросится
    atm3.setMaxWithdraw(30000);
    cout << "После изменения данных atm3:" << endl;
    atm3.show();

    // 4. Конструктор копирования при передаче объекта в функцию по значению
    cout << "\n=== 4. Передача объекта в функцию (print_atm) ===" << endl;
    print_atm(atm3);

    // 5. Конструктор копирования при возврате объекта из функции
    cout << "\n=== 5. Возврат объекта из функции (make_atm) ===" << endl;
    atm1 = make_atm();
    cout << "Полученный объект atm1:" << endl;
    atm1.show();

    // Проверка работы withdraw и deposit
    cout << "\n=== Дополнительно: операции с банкоматом atm2 ===" << endl;
    atm2.withdraw(10000);
    cout << endl;
    atm2.deposit(25000);
    cout << endl;
    atm2.show();

    cout << "\n=== Завершение main, объекты будут удалены ===" << endl;
    return 0;
}