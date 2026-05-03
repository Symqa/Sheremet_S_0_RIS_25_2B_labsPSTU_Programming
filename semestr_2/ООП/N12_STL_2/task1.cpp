#include <iostream>
#include <map>
using namespace std;

typedef multimap<int, float> MMap;
typedef MMap::iterator It;
typedef MMap::const_iterator CIt;

MMap make_multimap(int n) {
    MMap m;
    float val;
    for (int i = 0; i < n; ++i) {
        cout << "Element " << i << ": ";
        cin >> val;
        m.insert(make_pair(i, val));
    }
    return m;
}

void print_multimap(const MMap& m) {
    for (CIt it = m.begin(); it != m.end(); ++it)
        cout << "Key: " << it->first << " Value: " << it->second << endl;
}

float average(const MMap& m) {
    if (m.empty()) return 0;
    float sum = 0;
    for (CIt it = m.begin(); it != m.end(); ++it)
        sum += it->second;
    return sum / m.size();
}

CIt find_min(const MMap& m) {
    if (m.empty()) return m.end();
    CIt minIt = m.begin();
    for (CIt it = m.begin(); it != m.end(); ++it)
        if (it->second < minIt->second) minIt = it;
    return minIt;
}

CIt find_max(const MMap& m) {
    if (m.empty()) return m.end();
    CIt maxIt = m.begin();
    for (CIt it = m.begin(); it != m.end(); ++it)
        if (it->second > maxIt->second) maxIt = it;
    return maxIt;
}

void add_min_at_key(MMap& m, int key) {
    CIt minIt = find_min(m);
    if (minIt != m.end()) {
        float minVal = minIt->second;
        m.insert(make_pair(key, minVal));
        cout << "Added min " << minVal << " at key " << key << endl;
    }
}

void remove_less_than_average(MMap& m) {
    float avg = average(m);
    for (It it = m.begin(); it != m.end(); ) {
        if (it->second < avg)
            it = m.erase(it);
        else
            ++it;
    }
}

void divide_by_max(MMap& m) {
    if (m.empty()) return;
    CIt maxIt = find_max(m);
    float maxVal = maxIt->second;
    if (maxVal == 0) {
        cout << "Max is zero, division impossible." << endl;
        return;
    }
    for (It it = m.begin(); it != m.end(); ++it)
        it->second /= maxVal;
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    MMap m = make_multimap(n);
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