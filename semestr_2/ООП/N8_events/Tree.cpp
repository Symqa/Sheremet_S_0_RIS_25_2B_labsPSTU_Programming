#include "Tree.h"
#include <iostream>
#include "Print.h"
#include "Book.h"
using namespace std;

Tree::Tree() : beg(0), size(0), cur(0) {}
Tree::~Tree() {
    for (int i = 0; i < cur; ++i)
        delete beg[i];
    delete[] beg;
}
Tree::Tree(int n) {
    size = n;
    beg = new Object*[size];
    cur = 0;
}

void Tree::Add() {
    Object* p = 0;
    cout << "1. Print" << endl;
    cout << "2. Book" << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        Print* a = new Print;
        a->Input();
        p = a;
    } else if (choice == 2) {
        Book* b = new Book;
        b->Input();
        p = b;
    } else return;
    if (cur < size) {
        beg[cur] = p;
        ++cur;
    }
}

void Tree::Show() {
    if (cur == 0)
        cout << "Empty" << endl;
    Object** p = beg;
    for (int i = 0; i < cur; ++i) {
        (*p)->Show();
        ++p;
    }
}

int Tree::operator()() {
    return cur;
}

void Tree::Del() {
    if (cur > 0)
        --cur;
}

void Tree::HandleEvent(TEvent& event) {
    if (event.what == evMessage) {
        if (event.command == cmGet) {
            int index = event.a;
            if (index >= 0 && index < cur) {
                beg[index]->HandleEvent(event);
            }
            event.what = evNothing;
        }
    }
}