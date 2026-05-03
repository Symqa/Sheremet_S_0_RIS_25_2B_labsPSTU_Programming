#ifndef LIST_H
#define LIST_H

#include <iostream>

class List; // Предварительное объявление

class Iterator {
    friend class List; // дружественный класс List
public:
    Iterator() : elem(nullptr) {}
    Iterator(int* p) : elem(p) {}
    Iterator(const Iterator& it) : elem(it.elem) {}

    // Операции сравнения
    bool operator==(const Iterator& it) const { return elem == it.elem; }
    bool operator!=(const Iterator& it) const { return elem != it.elem; }

    // Разыменование
    int& operator*() const { return *elem; }

    // Префиксный инкремент/декремент
    Iterator& operator++() { ++elem; return *this; }
    Iterator& operator--() { --elem; return *this; }

    // Постфиксный инкремент/декремент
    Iterator operator++(int) { Iterator tmp(*this); ++elem; return tmp; }
    Iterator operator--(int) { Iterator tmp(*this); --elem; return tmp; }

    // Переход вправо на n элементов
    Iterator operator+(int n) const { return Iterator(elem + n); }
    // Переход влево на n элементов (операция - n)
    Iterator operator-(int n) const { return Iterator(elem - n); }

    // Составное присваивание сдвига
    Iterator& operator+=(int n) { elem += n; return *this; }
    Iterator& operator-=(int n) { elem -= n; return *this; }

private:
    int* elem; // указатель на текущий элемент типа int
};

class List {
public:
    // Конструктор с параметрами (размер, начальное значение)
    List(int s = 0, int k = 0);
    // Конструктор копирования
    List(const List& a);
    // Деструктор
    ~List();
    // Оператор присваивания
    List& operator=(const List& a);

    // Операция доступа по индексу
    int& operator[](int index);
    // Операция умножения всех элементов на число
    List operator*(int k) const;
    // Операция определения размера списка
    int operator()() const;

    // Перегруженные операции ввода-вывода
    friend std::ostream& operator<<(std::ostream& out, const List& a);
    friend std::istream& operator>>(std::istream& in, List& a);

    // Методы для получения итераторов
    Iterator first() const { return beg; }
    Iterator last() const { return end; }

private:
    int size;     // размер списка
    int* data;    // указатель на динамический массив значений
    Iterator beg; // итератор на первый элемент
    Iterator end; // итератор на элемент за последним
};

#endif // LIST_H