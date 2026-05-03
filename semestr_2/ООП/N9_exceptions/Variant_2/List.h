#pragma once
#include <iostream>
using namespace std;

const int MAX_SIZE = 30;

class List {
    struct Node {
        int data;
        Node* next;
        Node(int d = 0, Node* n = nullptr) : data(d), next(n) {}
    };
    Node* head;
    int sz;
    mutable int current;
    Node* getNode(int i) const;
public:
    List();
    List(int n, int* arr = nullptr);
    List(const List&);
    ~List();
    List& operator=(const List&);

    int& operator[](int i);
    int  operator()() const;
    List operator*(int factor) const;
    int& operator-(int n);

    friend ostream& operator<<(ostream& out, const List& l);
    friend istream& operator>>(istream& in, List& l);
};