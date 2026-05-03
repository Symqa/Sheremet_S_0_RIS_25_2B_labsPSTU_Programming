#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person();
    virtual ~Person();
    Person(string, int);
    Person(const Person&);
    string GetName() const { return name; }
    int GetAge() const { return age; }
    void SetName(string);
    void SetAge(int);
    Person& operator=(const Person&);
    friend istream& operator>>(istream& in, Person& p);
    friend ostream& operator<<(ostream& out, const Person& p);
};