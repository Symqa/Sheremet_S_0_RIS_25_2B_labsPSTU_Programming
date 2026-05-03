#pragma once
#include "Object.h"
#include <iostream>
using namespace std;

class Vector {
public:
    Vector(void);           // конструктор без параметров
    Vector(int);            // конструктор с размером
    ~Vector(void);          // деструктор
    void Add(Object*);      // добавление элемента
    friend ostream& operator<<(ostream& out, const Vector& v);
private:
    Object** beg;           // указатель на массив указателей
    int size;               // размер массива
    int cur;                // текущая позиция
};