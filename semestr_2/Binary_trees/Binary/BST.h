#pragma once

#include <string>
#include <vector>
#include <cstring>


// =====================================================================
//  Узел бинарного дерева поиска
//  Информационное поле: char* (строка)
//  Ключ сравнения: лексикографическое сравнение строк (strcmp)
// =====================================================================
struct Node {
    char* data;    // информационное поле
    Node* left;    // левый потомок
    Node* right;   // правый потомок
    Node* parent;  // родитель

    explicit Node(const char* str)
        : left(nullptr), right(nullptr), parent(nullptr)
    {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
    }

    ~Node() {
        delete[] data;
    }
};

// =====================================================================
//  Класс бинарного дерева поиска
// =====================================================================
class BST {
public:
    BST() : root_(nullptr) {}
    ~BST() { destroyTree(root_); }

    // ---------- Редактирование дерева ----------
    void insert(const char* str);
    bool remove(const char* str);
    Node* search(const char* key) const;

    // ---------- Обходы дерева ----------
    void preOrder(Node* node) const;    // Прямой
    void inOrder(Node* node) const;     // Симметричный
    void postOrder(Node* node) const;   // Обратный

    // ---------- Балансировка (Day-Stout-Warren / сортировка+ребилд) ----------
    void balance();

    // ---------- Вертикальная и горизонтальная печать ----------
    void printHorizontal() const;       // Горизонтальная (повернуто 90°)
    void printVertical() const;         // Вертикальная (поуровнево)

    // ---------- Вариантное задание ----------
    // Подсчитать узлы, значение которых начинается с заданного символа
    int countStartingWith(char c) const;

    Node* getRoot() const { return root_; }

    // ---------- Вспомогательные ----------
    void clear() { destroyTree(root_); root_ = nullptr; }

private:
    Node* root_;

    // Удалить всё дерево рекурсивно
    void destroyTree(Node* node);

    // Вспомогательная: найти минимальный узел в поддереве
    Node* findMin(Node* node) const;

    // Вспомогательная: вставка одного узла
    void insertNode(const char* str);

    // Вспомогательные для балансировки
    void collectSorted(Node* node, std::vector<std::string>& out) const;
    Node* buildBalanced(const std::vector<std::string>& keys, int lo, int hi, Node* parent);

    // Вспомогательная для горизонтальной печати
    void printHorizontalRec(Node* node, int level) const;

    // Вспомогательная для подсчёта
    int countStartingWithRec(Node* node, char c) const;
};



