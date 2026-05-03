#include "Number.h"
#include <iostream>
#include <limits>

using namespace std;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printSeparator() {
    cout << "\n----------------------------------------\n";
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    Number num;               // объект, созданный конструктором по умолчанию
    Number num2;
    int choice;
    int f;
    double s, k;

    do {
        cout << "\n===== МЕНЮ ДЕМОНСТРАЦИИ КЛАССА Number =====\n";
        cout << "1. Создать объект конструктором по умолчанию\n";
        cout << "2. Инициализировать существующий объект (Init)\n";
        cout << "3. Ввести объект с клавиатуры (Read)\n";
        cout << "4. Показать объект (Show)\n";
        cout << "5. Получить значение (getValue)\n";
        cout << "6. Умножить значение на число (multiply)\n";
        cout << "7. Создать объект через make_Number\n";
        cout << "8. Продемонстрировать проверку ошибок в Init\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: {
                num = Number();   // присваиваем новый объект
                cout << "Создан объект с полями по умолчанию: ";
                num.Show();
                break;
            }
            case 2: {
                cout << "Введите целую часть (>0): ";
                cin >> f;
                cout << "Введите дробную часть (>=0): ";
                cin >> s;
                clearInputBuffer();
                num.Init(f, s);
                cout << "После Init: ";
                num.Show();
                break;
            }
            case 3: {
                cout << "Заполнение объекта через Read:\n";
                num.Read();
                cout << "Считанный объект: ";
                num.Show();
                break;
            }
            case 4: {
                cout << "Текущий основной объект:\n";
                num.Show();
                break;
            }
            case 5: {
                cout << "Значение объекта (first + second): " 
                     << num.getValue() << endl;
                break;
            }
            case 6: {
                cout << "Введите множитель k: ";
                cin >> k;
                clearInputBuffer();
                cout << "multiply(" << k << ") = " << num.multiply(k) << endl;
                break;
            }
            case 7: {
                cout << "Введите first и second для make_Number: ";
                cin >> f >> s;
                clearInputBuffer();
                num2 = make_Number(f, s);
                cout << "Созданный объект: ";
                num2.Show();
                cout << "Его значение: " << num2.getValue() << endl;
                break;
            }
            case 8: {
                printSeparator();
                cout << "Попытка Init с недопустимыми аргументами:\n";
                cout << "1) first = -2, second = 3.5\n";
                num.Init(-2, 3.5);
                num.Show();

                cout << "2) first = 0, second = -1.2\n";
                num.Init(0, -1.2);
                num.Show();

                cout << "3) first = 5, second = -10.0\n";
                num.Init(5, -10.0);
                num.Show();
                printSeparator();
                break;
            }
            case 0:
                cout << "Демонстрация завершена.\n";
                break;
            default:
                cout << "Неверный пункт меню. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}