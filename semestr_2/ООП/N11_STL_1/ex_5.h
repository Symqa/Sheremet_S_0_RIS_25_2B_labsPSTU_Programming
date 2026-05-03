#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include "Pair.h"
using namespace std;

template <class T>
class QueueList {
    queue<T> q;
public:
    QueueList() {}
    QueueList(int n) {
        for (int i = 0; i < n; ++i) {
            T a;
            cin >> a;
            q.push(a);
        }
    }
    QueueList(const QueueList<T>& other) : q(other.q) {}

    void Print() {
        queue<T> tmp = q;
        while (!tmp.empty()) {
            cout << tmp.front() << " ";
            tmp.pop();
        }
        cout << endl;
    }

    T Min() const {
        queue<T> tmp = q;
        T m = tmp.front();
        tmp.pop();
        while (!tmp.empty()) {
            if (tmp.front() < m) m = tmp.front();
            tmp.pop();
        }
        return m;
    }

    void AddMinAtPos(int pos) {
        T m = Min();
        vector<T> v;
        while (!q.empty()) {
            v.push_back(q.front());
            q.pop();
        }
        if (pos < 0 || pos > (int)v.size()) throw 1;
        v.insert(v.begin() + pos, m);
        for (size_t i = 0; i < v.size(); ++i)
            q.push(v[i]);
    }

    T Average() const {
        queue<T> tmp = q;
        T sum = T();
        int cnt = 0;
        while (!tmp.empty()) {
            sum = sum + tmp.front();
            tmp.pop();
            ++cnt;
        }
        return sum / cnt;
    }

    void RemoveLessThanAverage() {
        T avg = Average();
        vector<T> v;
        while (!q.empty()) {
            T val = q.front();
            q.pop();
            if (!(val < avg)) v.push_back(val);
        }
        for (size_t i = 0; i < v.size(); ++i)
            q.push(v[i]);
    }

    T Max() const {
        queue<T> tmp = q;
        T m = tmp.front();
        tmp.pop();
        while (!tmp.empty()) {
            if (tmp.front() > m) m = tmp.front();
            tmp.pop();
        }
        return m;
    }

    void DivideByMax() {
        T m = Max();
        vector<T> v;
        while (!q.empty()) {
            v.push_back(q.front() / m);
            q.pop();
        }
        for (size_t i = 0; i < v.size(); ++i)
            q.push(v[i]);
    }
};

void task5_main() {
    try {
        cout << "\nTask5: QueueList<Pair>\nN? ";
        int n; cin >> n;
        QueueList<Pair> ql(n);
        ql.Print();

        Pair minEl = ql.Min();
        cout << "Min element: " << minEl << "\nPos? ";
        int pos; cin >> pos;
        ql.AddMinAtPos(pos);
        cout << "After adding min: ";
        ql.Print();

        ql.RemoveLessThanAverage();
        cout << "After removing < average: ";
        ql.Print();

        ql.DivideByMax();
        cout << "After dividing by max: ";
        ql.Print();
    } catch (int) {
        cout << "Error!\n";
    }
}