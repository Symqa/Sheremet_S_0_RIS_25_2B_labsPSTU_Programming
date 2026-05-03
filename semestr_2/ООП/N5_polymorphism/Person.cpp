#include "Person.h"

Person::Person(void) {
    name = "";
    age = 0;
}

Person::~Person(void) {}

void Person::Show() {
    cout << "Name: " << name << ", Age: " << age << endl;
}

Person::Person(string n, int a) {
    name = n;
    age = a;
}

Person::Person(const Person& p) {
    name = p.name;
    age = p.age;
}

void Person::SetName(string n) {
    name = n;
}

void Person::SetAge(int a) {
    age = a;
}

Person& Person::operator=(const Person& p) {
    if (this == &p) return *this;
    name = p.name;
    age = p.age;
    return *this;
}

istream& operator>>(istream& in, Person& p) {
    cout << "Enter name: ";
    in >> p.name;
    cout << "Enter age: ";
    in >> p.age;
    return in;
}

ostream& operator<<(ostream& out, const Person& p) {
    out << "Name: " << p.name << ", Age: " << p.age;
    return out;
}