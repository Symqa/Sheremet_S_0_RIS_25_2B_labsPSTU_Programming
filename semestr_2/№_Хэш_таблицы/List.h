#pragma once
#include "Random.h"
#include <string>

struct Node {
    Human human;
    Node* next_node = nullptr;
};

struct List {
    Node* head_node = nullptr;

    // Возвращает последнего человека (или пустого, если список пуст)
    Human last() {
        if (head_node == nullptr) {
            Human h = Human();
            h.full_name = "Пустая ячейка";
            return h;
        };
        Node* cur = head_node;
        while (cur->next_node != nullptr)
            cur = cur->next_node;
        return cur->human;
    }

    void add(const Human& person, int& collision_count) {
        Node* new_node = new Node{person, nullptr};

        if (head_node == nullptr) {
            head_node = new_node;
            return;
        }

        Node* cur = head_node;
        while (cur->next_node != nullptr) {
            cur = cur->next_node;
            collision_count++;   // учитываем дополнительный проход по цепочке
        }
        cur->next_node = new_node;
    }

    void clearList() {
        Node* cur = head_node;
        while (cur != nullptr) {
            Node* next = cur->next_node;
            delete cur;
            cur = next;
        }
        head_node = nullptr;
    }

    void deleteByPersonName(const std::string& person_name) {
        if (head_node == nullptr) return;

        if (head_node->human.full_name == person_name) {
            Node* to_delete = head_node;
            head_node = head_node->next_node;
            delete to_delete;
            return;
        }

        Node* prev = head_node;
        Node* cur = head_node->next_node;
        while (cur != nullptr && cur->human.full_name != person_name) {
            prev = cur;
            cur = cur->next_node;
        }
        if (cur != nullptr) {
            prev->next_node = cur->next_node;
            delete cur;
        }
    }

    void show() const {
        Node* cur = head_node;
        while (cur != nullptr) {
            cur->human.show();
            cur = cur->next_node;
        }
    }

    Human get(const std::string& full_name, int& collision_count) {
        Node* cur = head_node;
        while (cur != nullptr) {
            collision_count++;
            if (cur->human.full_name == full_name)
                return cur->human;
            cur = cur->next_node;
        }
        Human h = Human();
        h.full_name = "Пустая ячейка";
        return h;   // не найдено
    }
};