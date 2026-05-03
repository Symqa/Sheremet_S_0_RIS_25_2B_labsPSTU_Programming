#include "List.h"
#include <iostream>
using namespace std;

int main() {
    try {
        List a;
        cout << "List a: " << a;
        cout << "Size: " << a() << endl;

        int mas[] = { 10, 20, 30 };
        List b(3, mas);
        cout << "List b: " << b;
        cout << "b[1] = " << b[1] << endl;
        cout << "Size: " << b() << endl;

        List c = b * 2;
        cout << "b * 2 : " << c;

        b[1];
        cout << "b - 0 : " << (b - 0) << endl;

        List d;
        cin >> d;
        cout << "You entered: " << d;

        // cout << d[100] << endl;   // throw 3
        // List e(40);               // throw 1
        // List f; f - 1;            // throw 4
    }
    catch (int code) {
        cout << "Error code: " << code << endl;
    }
    return 0;
}