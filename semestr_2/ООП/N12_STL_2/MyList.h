#ifndef MYLIST_H
#define MYLIST_H

#include <iostream>
#include <map>
using namespace std;

template <class T>
class MyList {
    multimap<int, T> data;
public:
    MyList() {}
    MyList(int n) {
        T val;
        for (int i = 0; i < n; ++i) {
            cout << "Element " << i << ": ";
            cin >> val;
            data.insert(make_pair(i, val));
        }
    }
    ~MyList() {}

    void Print() const {
        for (auto it = data.begin(); it != data.end(); ++it)
            cout << "Key: " << it->first << " Value: " << it->second << endl;
    }

    void Add(int key, const T& value) {
        data.insert(make_pair(key, value));
    }

    T Average() const {
        if (data.empty()) return T();
        T sum = data.begin()->second;
        auto it = data.begin();
        for (++it; it != data.end(); ++it)
            sum = sum + it->second;
        return sum / (int)data.size();
    }

    T Min() const {
        if (data.empty()) throw runtime_error("Empty container");
        auto it = data.begin();
        T minVal = it->second;
        for (; it != data.end(); ++it)
            if (it->second < minVal) minVal = it->second;
        return minVal;
    }

    T Max() const {
        if (data.empty()) throw runtime_error("Empty container");
        auto it = data.begin();
        T maxVal = it->second;
        for (; it != data.end(); ++it)
            if (it->second > maxVal) maxVal = it->second;
        return maxVal;
    }

    void AddMinAtPos(int key) {
        T m = Min();
        data.insert(make_pair(key, m));
        cout << "Added min " << m << " at key " << key << endl;
    }

    void RemoveLessThanAverage() {
        T avg = Average();
        for (auto it = data.begin(); it != data.end(); ) {
            if (it->second < avg)
                it = data.erase(it);
            else
                ++it;
        }
    }

    void DivideByMax() {
        if (data.empty()) return;
        T maxVal = Max();
        for (auto it = data.begin(); it != data.end(); ++it)
            it->second = it->second / maxVal;
    }
};

#endif