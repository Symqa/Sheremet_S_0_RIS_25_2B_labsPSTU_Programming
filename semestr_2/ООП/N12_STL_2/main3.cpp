#include <iostream>
#include "Pair.h"
#include "MyList.h"
using namespace std;

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    MyList<Pair> list(n);
    cout << "\nInitial list:\n";
    list.Print();

    int pos;
    cout << "Enter key to insert min element: ";
    cin >> pos;
    list.AddMinAtPos(pos);
    cout << "\nAfter adding min:\n";
    list.Print();

    list.RemoveLessThanAverage();
    cout << "\nAfter removing less than average:\n";
    list.Print();

    list.DivideByMax();
    cout << "\nAfter dividing by max:\n";
    list.Print();

    return 0;
}