#include <iostream>
#include <map>
#include "Pair.h"
using namespace std;

typedef multimap<int, Pair> MMapPair;
typedef MMapPair::iterator It;
typedef MMapPair::const_iterator CIt;

MMapPair make_multimap(int n) {
    MMapPair m;
    Pair p;
    for (int i = 0; i < n; ++i) {
        cout << "Pair (first second) for key " << i << ": ";
        cin >> p;
        m.insert(make_pair(i, p));
    }
    return m;
}

void print_multimap(const MMapPair& m) {
    for (CIt it = m.begin(); it != m.end(); ++it)
        cout << "Key: " << it->first << " Value: " << it->second << endl;
}

Pair average(const MMapPair& m) {
    if (m.empty()) return Pair();
    Pair sum;
    for (CIt it = m.begin(); it != m.end(); ++it)
        sum = sum + it->second;
    return sum / (int)m.size();
}

CIt find_min(const MMapPair& m) {
    if (m.empty()) return m.end();
    CIt minIt = m.begin();
    for (CIt it = m.begin(); it != m.end(); ++it)
        if (it->second < minIt->second) minIt = it;
    return minIt;
}

CIt find_max(const MMapPair& m) {
    if (m.empty()) return m.end();
    CIt maxIt = m.begin();
    for (CIt it = m.begin(); it != m.end(); ++it)
        if (it->second > maxIt->second) maxIt = it;
    return maxIt;
}

void add_min_at_key(MMapPair& m, int key) {
    CIt minIt = find_min(m);
    if (minIt != m.end()) {
        Pair minVal = minIt->second;
        m.insert(make_pair(key, minVal));
        cout << "Added min " << minVal << " at key " << key << endl;
    }
}

void remove_less_than_average(MMapPair& m) {
    Pair avg = average(m);
    for (It it = m.begin(); it != m.end(); ) {
        if (it->second < avg)
            it = m.erase(it);
        else
            ++it;
    }
}

void divide_by_max(MMapPair& m) {
    if (m.empty()) return;
    CIt maxIt = find_max(m);
    Pair maxVal = maxIt->second;
    if (maxVal.get_first() == 0 || maxVal.get_second() == 0)
        cout << "Warning: max contains zero, division may be invalid." << endl;
    for (It it = m.begin(); it != m.end(); ++it)
        it->second = it->second / maxVal;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    MMapPair m = make_multimap(n);
    cout << "\nInitial multimap:\n";
    print_multimap(m);

    int pos;
    cout << "Enter key to insert min element: ";
    cin >> pos;
    add_min_at_key(m, pos);
    cout << "\nAfter adding min at key " << pos << ":\n";
    print_multimap(m);

    remove_less_than_average(m);
    cout << "\nAfter removing elements less than average:\n";
    print_multimap(m);

    divide_by_max(m);
    cout << "\nAfter dividing by max:\n";
    print_multimap(m);

    return 0;
}