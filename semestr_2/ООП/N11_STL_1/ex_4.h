#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include "Pair.h"
using namespace std;

typedef queue<Pair> Que;
typedef vector<Pair> VecP;

Que make_queue(int n) {
    Que q;
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        q.push(p);
    }
    return q;
}

VecP queue_to_vector(Que q) {
    VecP v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }
    return v;
}

Que vector_to_queue(const VecP& v) {
    Que q;
    for (size_t i = 0; i < v.size(); ++i)
        q.push(v[i]);
    return q;
}

void print_queue(Que q) {
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

Pair find_min_queue(Que q) {
    VecP v = queue_to_vector(q);
    Pair m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] < m) m = v[i];
    return m;
}

Que add_min_at_pos_queue(Que q, int pos) {
    Pair m = find_min_queue(q);
    VecP v = queue_to_vector(q);
    if (pos < 0 || pos > (int)v.size()) throw 1;
    v.insert(v.begin() + pos, m);
    return vector_to_queue(v);
}

Pair average_queue(Que q) {
    VecP v = queue_to_vector(q);
    Pair sum(0,0);
    for (size_t i = 0; i < v.size(); ++i)
        sum = sum + v[i];
    return sum / (int)v.size();
}

Que remove_less_than_average_queue(Que q) {
    Pair avg = average_queue(q);
    VecP v = queue_to_vector(q);
    VecP temp;
    for (size_t i = 0; i < v.size(); ++i)
        if (!(v[i] < avg)) temp.push_back(v[i]);
    return vector_to_queue(temp);
}

Pair find_max_queue(Que q) {
    VecP v = queue_to_vector(q);
    Pair m = v[0];
    for (size_t i = 1; i < v.size(); ++i)
        if (v[i] > m) m = v[i];
    return m;
}

Que divide_by_max_queue(Que q) {
    Pair m = find_max_queue(q);
    VecP v = queue_to_vector(q);
    for (size_t i = 0; i < v.size(); ++i)
        v[i] = v[i] / m;
    return vector_to_queue(v);
}

void task4_main() {
    try {
        cout << "\nTask4: queue<Pair>\nN? ";
        int n; cin >> n;
        Que q = make_queue(n);
        cout << "Initial queue: ";
        print_queue(q);

        Pair minEl = find_min_queue(q);
        cout << "Min element: " << minEl << "\nPos? ";
        int pos; cin >> pos;
        q = add_min_at_pos_queue(q, pos);
        cout << "After adding min at pos " << pos << ": ";
        print_queue(q);

        q = remove_less_than_average_queue(q);
        cout << "After removing < average: ";
        print_queue(q);

        q = divide_by_max_queue(q);
        cout << "After dividing by max: ";
        print_queue(q);
    } catch (int) {
        cout << "Error!\n";
    }
}