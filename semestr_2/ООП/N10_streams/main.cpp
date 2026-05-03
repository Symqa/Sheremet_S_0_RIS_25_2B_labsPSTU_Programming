#include "Pair.h"
#include "file_work.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Pair p1, p2;
    int k, c;
    char file_name[30];

    do {
        cout << "\n1. Make file";
        cout << "\n2. Print file";
        cout << "\n3. Delete records from interval [k1, k2]";
        cout << "\n4. Double records with given value";
        cout << "\n5. Add K records to beginning of file";
        cout << "\n0. Exit\n";
        cin >> c;

        switch (c) {
        case 1:
            cout << "file name? "; cin >> file_name;
            k = make_file(file_name);
            if (k < 0) cout << "Can't make file\n";
            break;
        case 2:
            cout << "file name? "; cin >> file_name;
            k = print_file(file_name);
            if (k == 0) cout << "Empty file\n";
            if (k < 0) cout << "Can't read file\n";
            break;
        case 3:
            cout << "file name? "; cin >> file_name;
            cout << "Enter k1:\n"; cin >> p1;
            cout << "Enter k2:\n"; cin >> p2;
            if (p2 < p1) swap(p1, p2);   // обеспечим k1 <= k2
            k = del_interval(file_name, p1, p2);
            if (k < 0) cout << "Can't read file\n";
            else cout << "Deleted " << k << " records\n";
            break;
        case 4:
            cout << "file name? "; cin >> file_name;
            cout << "Enter value to double:\n"; cin >> p1;
            k = double_value(file_name, p1);
            if (k < 0) cout << "Can't read file\n";
            else if (k == 0) cout << "No such records\n";
            else cout << "Changed " << k << " records\n";
            break;
        case 5: {
            cout << "file name? "; cin >> file_name;
            int K;
            cout << "K? "; cin >> K;
            vector<Pair> new_pairs;
            for (int i = 0; i < K; ++i) {
                cout << "Enter pair " << i + 1 << ":\n";
                Pair pp;
                cin >> pp;
                new_pairs.push_back(pp);
            }
            k = add_begin(file_name, new_pairs);
            if (k < 0) cout << "Can't read file\n";
            else cout << "Added " << k << " records\n";
            break;
        }
        case 0: break;
        default: cout << "Wrong choice\n";
        }
    } while (c != 0);

    return 0;
}