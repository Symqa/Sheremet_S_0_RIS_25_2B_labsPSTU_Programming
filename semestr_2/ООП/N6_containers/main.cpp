#include <iostream>
#include "List.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    std::cout << "===== Тестирование класса List (Список) =====" << std::endl;

    // 1. Конструктор с параметрами – 5 элементов, заполненных нулями
    List a(5);
    std::cout << "a: " << a << std::endl;

    // 2. Ввод значений
    std::cout << "Введите 5 элементов списка a: ";
    std::cin >> a;
    std::cout << "a после ввода: " << a << std::endl;

    // 3. Доступ по индексу
    a[2] = 100;
    std::cout << "a после a[2] = 100: " << a << std::endl;

    // 4. Конструктор с начальным значением
    List b(10, 1);
    std::cout << "b (10 элементов, равных 1): " << b << std::endl;

    // 5. Оператор присваивания
    b = a;
    std::cout << "b после b = a: " << b << std::endl;

    // 6. Умножение всех элементов на число
    List c = a * 3;
    std::cout << "c = a * 3: " << c << std::endl;

    // 7. Определение размера списка
    std::cout << "\nРазмер a: " << a() << std::endl;
    std::cout << "Размер c: " << c() << std::endl;

    // 8. Работа с итератором
    std::cout << "\n===== Работа с итератором =====" << std::endl;
    Iterator it = a.first();
    std::cout << "Первый элемент: " << *it << std::endl;

    ++it;
    std::cout << "После ++it (второй элемент): " << *it << std::endl;

    it = it + 2;   // переход вправо на 2
    std::cout << "После it + 2 (четвёртый элемент): " << *it << std::endl;

    it = it - 1;   // переход влево на 1 (операция - n)
    std::cout << "После it - 1 (третий элемент): " << *it << std::endl;

    // Демонстрация перехода влево на n от конца
    Iterator it2 = a.last() - 2;  // на 2 элемента левее последнего
    std::cout << "Элемент на 2 левее последнего: " << *it2 << std::endl;

    // Обход всего списка с помощью итератора
    std::cout << "Все элементы через итератор: ";
    for (Iterator iter = a.first(); iter != a.last(); ++iter) {
        std::cout << *iter << " ";
    }
    std::cout << std::endl;

    return 0;
}