#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef vector<float> Vec;

Vec make_vector(int n) {
    Vec v;
    for (int i = 0; i < n; ++i) {
        float a = (rand() % 100 - 50) / 10.0f;
        v.push_back(a);
    }
    return v;
}

void print_vector(const Vec& v) {
    for (size_t i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;
}

float find_min(const Vec& v) {
    float m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] < m) m = v[i];
    return m;
}

float average(const Vec& v) {
    float sum = 0;
    for (size_t i = 0; i < v.size(); ++i)
        sum += v[i];
    return sum / v.size();
}

void add_at_pos(Vec& v, float el, int pos) {
    if (pos < 0 || pos > (int)v.size()) throw 1;
    v.insert(v.begin() + pos, el);
}

void remove_less_than_average(Vec& v) {
    float avg = average(v);
    Vec temp;
    for (size_t i = 0; i < v.size(); ++i)
        if (!(v[i] < avg)) temp.push_back(v[i]);
    v = temp;
}

void divide_by_max(Vec& v) {
    float m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] > m) m = v[i];
    for (size_t i = 0; i < v.size(); ++i)
        v[i] /= m;
}

void task1_main() {
    srand((unsigned)time(0));
    try {
        int n;
        cout << "Task1: vector<float>\nN? "; cin >> n;
        Vec v = make_vector(n);
        print_vector(v);

        // Задание 3: найти минимальный и добавить на заданную позицию
        float minEl = find_min(v);
        cout << "Min element: " << minEl << "\nPos? ";
        int pos;
        cin >> pos;
        add_at_pos(v, minEl, pos);
        cout << "After adding min at pos " << pos << ":\n";
        print_vector(v);

        // Задание 4: удалить элементы меньше среднего
        remove_less_than_average(v);
        cout << "After removing elements < average:\n";
        print_vector(v);

        // Задание 5: каждый элемент разделить на максимальный
        divide_by_max(v);
        cout << "After dividing by max:\n";
        print_vector(v);
    } catch (int) {
        cout << "Error!\n";
    }
}