#pragma once
#include "Pair.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

// Создание файла и запись N объектов
int make_file(const char* f_name) {
    fstream stream(f_name, ios::out | ios::trunc);
    if (!stream) return -1;
    int n;
    Pair p;
    cout << "N? "; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> p;
        stream << p;
    }
    stream.close();
    return n;
}

// Чтение и вывод всех записей
int print_file(const char* f_name) {
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Pair p;
    int i = 0;
    while (stream >> p) {
        cout << p << "\n";
        ++i;
    }
    stream.close();
    return i;
}

// Удаление записей, попадающих в интервал [k1, k2]
int del_interval(const char* f_name, const Pair& k1, const Pair& k2) {
    fstream temp("temp", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Pair p;
    int deleted = 0;
    while (stream >> p) {
        if (stream.eof()) break;
        if (!(p >= k1 && p <= k2)) {
            temp << p;
        } else {
            ++deleted;
        }
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return deleted;
}

// Увеличение в два раза записей, равных val
int double_value(const char* f_name, const Pair& val) {
    fstream temp("temp", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    Pair p;
    int changed = 0;
    while (stream >> p) {
        if (stream.eof()) break;
        if (p == val) {
            p *= 2;   // удвоение обоих полей
            ++changed;
        }
        temp << p;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return changed;
}

// Добавление записей в начало файла
int add_begin(const char* f_name, const vector<Pair>& new_records) {
    fstream temp("temp", ios::out);
    fstream stream(f_name, ios::in);
    if (!stream) return -1;
    // сначала новые записи
    for (const auto& rec : new_records) {
        temp << rec;
    }
    // затем старые
    Pair p;
    while (stream >> p) {
        if (stream.eof()) break;
        temp << p;
    }
    stream.close();
    temp.close();
    remove(f_name);
    rename("temp", f_name);
    return new_records.size();
}