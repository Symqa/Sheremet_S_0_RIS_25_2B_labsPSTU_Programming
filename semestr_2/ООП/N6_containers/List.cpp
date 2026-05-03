#include "List.h"
#include <cassert>
#include <iostream>

// Конструктор с параметрами
List::List(int s, int k) : size(s) {
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = k;
        beg = Iterator(data);
        end = Iterator(data + size);
    } else {
        data = nullptr;
        beg = Iterator(nullptr);
        end = Iterator(nullptr);
    }
}

// Конструктор копирования
List::List(const List& a) : size(a.size) {
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = a.data[i];
        beg = Iterator(data);
        end = Iterator(data + size);
    } else {
        data = nullptr;
        beg = Iterator(nullptr);
        end = Iterator(nullptr);
    }
}

// Деструктор
List::~List() {
    delete[] data;
    data = nullptr;
}

// Оператор присваивания
List& List::operator=(const List& a) {
    if (this == &a)
        return *this;
    delete[] data;
    size = a.size;
    if (size > 0) {
        data = new int[size];
        for (int i = 0; i < size; ++i)
            data[i] = a.data[i];
        beg = Iterator(data);
        end = Iterator(data + size);
    } else {
        data = nullptr;
        beg = Iterator(nullptr);
        end = Iterator(nullptr);
    }
    return *this;
}

// Доступ по индексу
int& List::operator[](int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Ошибка: индекс " << index
                  << " вне диапазона [0, " << size - 1 << "]" << std::endl;
        assert(0 && "Выход за границы массива");
    }
    return data[index];
}

// Умножение всех элементов на число
List List::operator*(int k) const {
    List result(size);
    for (int i = 0; i < size; ++i)
        result.data[i] = data[i] * k;
    return result;
}

// Получение размера списка
int List::operator()() const {
    return size;
}

// Вывод списка в поток
std::ostream& operator<<(std::ostream& out, const List& a) {
    for (int i = 0; i < a.size; ++i)
        out << a.data[i] << " ";
    return out;
}

// Ввод списка из потока
std::istream& operator>>(std::istream& in, List& a) {
    for (int i = 0; i < a.size; ++i)
        in >> a.data[i];
    return in;
}