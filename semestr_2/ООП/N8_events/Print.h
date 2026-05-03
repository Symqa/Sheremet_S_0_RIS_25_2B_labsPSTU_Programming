#pragma once
#include "Object.h"
#include <string>
using namespace std;

class Print : public Object {
public:
    Print();
    virtual ~Print();
    void Show();
    void Input();
    Print(string, string);
    Print(const Print&);
    string GetName() { return name; }
    string GetAuthor() { return author; }
    void SetName(string);
    void SetAuthor(string);
    Print& operator=(const Print&);
    void HandleEvent(const TEvent& e);
protected:
    string name;
    string author;
};