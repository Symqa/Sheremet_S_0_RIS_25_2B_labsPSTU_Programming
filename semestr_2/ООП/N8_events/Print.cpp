#include "Print.h"
#include <iostream>
using namespace std;

Print::Print() : name(""), author("") {}
Print::~Print() {}
Print::Print(string n, string a) : name(n), author(a) {}
Print::Print(const Print& p) : name(p.name), author(p.author) {}

void Print::SetName(string n) { name = n; }
void Print::SetAuthor(string a) { author = a; }

Print& Print::operator=(const Print& p) {
    if (&p == this) return *this;
    name = p.name;
    author = p.author;
    return *this;
}

void Print::Show() {
    cout << "\nName: " << name;
    cout << "\nAuthor: " << author;
}

void Print::Input() {
    cout << "\nName: "; cin >> name;
    cout << "Author: "; cin >> author;
}

void Print::HandleEvent(const TEvent& e) {
    if (e.what == evMessage) {
        if (e.command == cmGet) {
            cout << "Name = " << name << endl;
        }
    }
}