#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
class List
{
public:
    // конструктор с параметрами: size элементов, инициализированных k
    List(int s, T k);
    // конструктор копирования
    List(const List<T>& a);
    // деструктор
    ~List();
    // оператор присваивания
    List<T>& operator=(const List<T>& a);

    // доступ по индексу (не const)
    T& operator[](int index);
    // доступ по индексу (const)
    const T& operator[](int index) const;

    // определение размера списка
    int operator()() const;

    // умножение всех элементов на скаляр (константу)
    List<T> operator*(const T& scalar) const;

    // дружественные функции ввода-вывода
    template <class U>
    friend ostream& operator<<(ostream& out, const List<U>& a);
    template <class U>
    friend istream& operator>>(istream& in, List<U>& a);

private:
    int size;
    T* data;
};

// Реализация методов шаблона

template <class T>
List<T>::List(int s, T k) : size(s)
{
    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = k;
}

template <class T>
List<T>::List(const List<T>& a) : size(a.size)
{
    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = a.data[i];
}

template <class T>
List<T>::~List()
{
    delete[] data;
}

template <class T>
List<T>& List<T>::operator=(const List<T>& a)
{
    if (this == &a) return *this;
    if (data != nullptr) delete[] data;
    size = a.size;
    data = new T[size];
    for (int i = 0; i < size; i++)
        data[i] = a.data[i];
    return *this;
}

template <class T>
T& List<T>::operator[](int index)
{
    if (index >= 0 && index < size)
        return data[index];
    else
    {
        cerr << "\nError! Index out of range";
        exit(1);
    }
}

template <class T>
const T& List<T>::operator[](int index) const
{
    if (index >= 0 && index < size)
        return data[index];
    else
    {
        cerr << "\nError! Index out of range";
        exit(1);
    }
}

template <class T>
int List<T>::operator()() const
{
    return size;
}

template <class T>
List<T> List<T>::operator*(const T& scalar) const
{
    List<T> result(size, scalar); // временный объект
    for (int i = 0; i < size; i++)
        result.data[i] = data[i] * scalar;
    return result;
}

template <class T>
ostream& operator<<(ostream& out, const List<T>& a)
{
    for (int i = 0; i < a.size; i++)
        out << a.data[i] << " ";
    return out;
}

template <class T>
istream& operator>>(istream& in, List<T>& a)
{
    for (int i = 0; i < a.size; i++)
        in >> a.data[i];
    return in;
}

#endif // LIST_H