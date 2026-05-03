#pragma once
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Pair.h"
using namespace std;

typedef vector<Pair> VecP;

VecP make_vector_pair(int n) {
    VecP v;
    for (int i = 0; i < n; ++i) {
        int f = rand() % 20 - 10;
        int s = rand() % 20 - 10;
        v.push_back(Pair(f, s));
    }
    return v;
}

void print_vector_pair(const VecP& v) {
    for (size_t i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;
}

Pair find_min_pair(const VecP& v) {
    Pair m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] < m) m = v[i];
    return m;
}

Pair average_pair(const VecP& v) {
    Pair sum(0,0);
    for (size_t i = 0; i < v.size(); ++i)
        sum = sum + v[i];
    return sum / (int)v.size();
}

void add_at_pos_pair(VecP& v, const Pair& el, int pos) {
    if (pos < 0 || pos > (int)v.size()) throw 1;
    v.insert(v.begin() + pos, el);
}

void remove_less_than_average_pair(VecP& v) {
    Pair avg = average_pair(v);
    VecP temp;
    for (size_t i = 0; i < v.size(); ++i)
        if (!(v[i] < avg)) temp.push_back(v[i]);
    v = temp;
}

void divide_by_max_pair(VecP& v) {
    Pair m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] > m) m = v[i];
    // Если максимальный элемент равен (0,0), деление может быть опасным.
    // В рамках учебной задачи предполагаем, что это не так.
    for (size_t i = 0; i < v.size(); ++i)
        v[i] = v[i] / m;
}

void task2_main() {
    srand((unsigned)time(0));
    try {
        int n;
        cout << "\nTask2: vector<Pair>\nN? "; cin >> n;
        VecP v = make_vector_pair(n);
        print_vector_pair(v);

        Pair minEl = find_min_pair(v);
        cout << "Min element: " << minEl << "\nPos? ";
        int pos;
        cin >> pos;
        add_at_pos_pair(v, minEl, pos);
        cout << "After adding min at pos " << pos << ":\n";
        print_vector_pair(v);

        remove_less_than_average_pair(v);
        cout << "After removing elements < average:\n";
        print_vector_pair(v);

        divide_by_max_pair(v);
        cout << "After dividing by max:\n";
        print_vector_pair(v);
    } catch (int) {
        cout << "Error!\n";
    }
}