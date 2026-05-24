#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstring>
#include "BST.h"


void BST::destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

Node* BST::findMin(Node* node) const {
    while (node && node->left)
        node = node->left;
    return node;
}

// ---------- Вставка ----------
void BST::insert(const char* str) {
    insertNode(str);
}

void BST::insertNode(const char* str) {
    Node* newNode = new Node(str);
    if (!root_) {
        root_ = newNode;
        return;
    }
    Node* cur = root_;
    while (true) {
        int cmp = strcmp(str, cur->data);
        if (cmp < 0) {
            if (!cur->left) {
                cur->left = newNode;
                newNode->parent = cur;
                return;
            }
            cur = cur->left;
        } else {
            // >= идут в правое поддерево (дубликаты допустимы)
            if (!cur->right) {
                cur->right = newNode;
                newNode->parent = cur;
                return;
            }
            cur = cur->right;
        }
    }
}

// ---------- Удаление ----------
bool BST::remove(const char* str) {
    Node* e = search(str);
    if (!e) return false;   // элемент не найден

    Node* p = e->parent;

    // Случай 1: нет потомков
    if (!e->left && !e->right) {
        if (!p) { root_ = nullptr; }
        else if (p->left == e) p->left = nullptr;
        else                   p->right = nullptr;
        delete e;
    }
    // Случай 2: один потомок
    else if (!e->left || !e->right) {
        Node* child = e->left ? e->left : e->right;
        child->parent = p;
        if (!p) { root_ = child; }
        else if (p->left == e) p->left = child;
        else                   p->right = child;
        e->left = e->right = nullptr;
        delete e;
    }
    // Случай 3: два потомка — заменяем данными минимального из правого поддерева
    else {
        Node* successor = findMin(e->right);
        // Копируем данные
        char* tmp = new char[strlen(successor->data) + 1];
        strcpy(tmp, successor->data);
        // Удаляем successor (у него не более одного потомка — правого)
        remove(successor->data);
        // Записываем скопированные данные в e
        delete[] e->data;
        e->data = tmp;
    }
    return true;
}

// ---------- Поиск ----------
Node* BST::search(const char* key) const {
    Node* cur = root_;
    while (cur) {
        int cmp = strcmp(key, cur->data);
        if (cmp == 0) return cur;
        cur = (cmp < 0) ? cur->left : cur->right;
    }
    return nullptr;
}

// ---------- Прямой обход (корень → лево → право) ----------
void BST::preOrder(Node* node) const {
    if (!node) return;
    std::cout << node->data << " ";
    preOrder(node->left);
    preOrder(node->right);
}

// ---------- Симметричный обход (лево → корень → право) ----------
void BST::inOrder(Node* node) const {
    if (!node) return;
    inOrder(node->left);
    std::cout << node->data << " ";
    inOrder(node->right);
}

// ---------- Обратный обход (лево → право → корень) ----------
void BST::postOrder(Node* node) const {
    if (!node) return;
    postOrder(node->left);
    postOrder(node->right);
    std::cout << node->data << " ";
}

// ---------- Балансировка (собрать отсортированный массив → перестроить) ----------
void BST::collectSorted(Node* node, std::vector<std::string>& out) const {
    if (!node) return;
    collectSorted(node->left, out);
    out.emplace_back(node->data);
    collectSorted(node->right, out);
}

Node* BST::buildBalanced(const std::vector<std::string>& keys, int lo, int hi, Node* parent) {
    if (lo > hi) return nullptr;
    int mid = lo + (hi - lo) / 2;
    Node* node = new Node(keys[mid].c_str());
    node->parent = parent;
    node->left  = buildBalanced(keys, lo, mid - 1, node);
    node->right = buildBalanced(keys, mid + 1, hi, node);
    return node;
}

void BST::balance() {
    std::vector<std::string> sorted;
    collectSorted(root_, sorted);
    destroyTree(root_);
    root_ = buildBalanced(sorted, 0, (int)sorted.size() - 1, nullptr);
}

// ---------- Горизонтальная печать (повёрнуто на 90°, лево — вверху) ----------
void BST::printHorizontalRec(Node* node, int level) const {
    if (!node) return;
    printHorizontalRec(node->right, level + 1);
    for (int i = 0; i < level; ++i) std::cout << "    ";
    std::cout << node->data << "\n";
    printHorizontalRec(node->left, level + 1);
}

void BST::printHorizontal() const {
    std::cout << "\n--- Горизонтальная печать (повернуто 90°) ---\n";
    printHorizontalRec(root_, 0);
    std::cout << "----------------------------------------------\n";
}

// ---------- Вертикальная печать (поуровнево, BFS) ----------
void BST::printVertical() const {
    std::cout << "\n--- Вертикальная печать (по уровням) ---\n";
    if (!root_) { std::cout << "(дерево пустое)\n"; return; }

    std::queue<Node*> q;
    q.push(root_);
    int level = 1;
    while (!q.empty()) {
        int sz = (int)q.size();
        std::cout << "Уровень " << level++ << ": ";
        for (int i = 0; i < sz; ++i) {
            Node* cur = q.front(); q.pop();
            std::cout << cur->data << " ";
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        std::cout << "\n";
    }
    std::cout << "-----------------------------------------\n";
}

// ---------- Вариантное задание ----------
int BST::countStartingWithRec(Node* node, char c) const {
    if (!node) return 0;
    int cnt = 0;
    if (node->data[0] == c) cnt = 1;
    return cnt
         + countStartingWithRec(node->left, c)
         + countStartingWithRec(node->right, c);
}

int BST::countStartingWith(char c) const {
    return countStartingWithRec(root_, c);
}