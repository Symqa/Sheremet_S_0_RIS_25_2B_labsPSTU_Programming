#pragma once
#include "Object.h"

class Tree {
public:
    Tree();
    virtual ~Tree();
    Tree(int n);
    void Add();
    void Del();
    void Show();
    int operator()();
    virtual void HandleEvent(TEvent& event);
protected:
    Object** beg;
    int size;
    int cur;
};