#include <iostream>
#include <clocale>
#include <string>
using namespace std;


struct Node {
	string str;
	Node* next_node = nullptr;
};


struct List {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
};


// Добавление элемента в конец
void append_to_back(List &list, string element) {
	Node* new_node = new Node;
	new_node->str = element;
	new_node->next_node = nullptr;

	if (list.head_node == nullptr) { // пустой список
		list.head_node = new_node;
		list.tail_node = new_node;
	}
	else {
		list.tail_node->next_node = new_node;
		list.tail_node = new_node;
	}
}


// Добавление элемента в начало
void append_to_start(List &list, string element) {
	Node* new_node = new Node;
	new_node->str = element;

	if (list.head_node == nullptr) {
		list.head_node = new_node;
		list.tail_node = new_node;
	}
	else {
		new_node->next_node = list.head_node;
		list.head_node = new_node;
	}
}


// Удаление элемемента с конца
void delete_element_from_back(List &list) {

	if (list.head_node == nullptr) { return; } // пустой список
	if (list.head_node == list.tail_node) { // один элемент
		delete list.head_node;
		list.head_node = nullptr;
		list.tail_node = nullptr;
		return;
	}

	Node *cur_node = list.head_node;
	while (cur_node->next_node != list.tail_node) { // после цикла cur_node будет перед tail
		cur_node = cur_node->next_node;	
	}
	delete list.tail_node;
	list.tail_node = cur_node;
	cur_node->next_node = nullptr;

}


// Удаление элемента с начала
void delete_element_from_start(List& list) {
	if (list.head_node == nullptr) { return; } // пустой список
	if (list.head_node == list.tail_node) { // один элемент
		delete list.head_node;
		list.head_node = nullptr;
		list.tail_node = nullptr;
		return;
	}
	
	Node *cur = list.head_node->next_node;
	delete list.head_node;
	list.head_node = cur; 

}


// Удаление элемента по ключу
void delete_element_by_key(List& list, const string& key) {
	// Пустой список
	if (list.head_node == nullptr) {
		return;
	}

	// Удаление первого элемента (включая случай одного элемента)
	if (list.head_node->str == key) {
		Node* new_head = list.head_node->next_node;
		delete list.head_node;
		list.head_node = new_head;
		// если список был из одного элемента, tail_node обновляется
		if (list.head_node == nullptr) {
			list.tail_node = nullptr;
		}
		return;
	}

	// Поиск элемента в середине или в конце
	Node* cur = list.head_node->next_node;
	Node* prev = list.head_node;
	while (cur != nullptr) {
		if (cur->str == key) {
			prev->next_node = cur->next_node;
			// если удаляем последний элемент, обновляем tail_node
			if (cur == list.tail_node) {
				list.tail_node = prev;
			}
			delete cur;
			return;
		}
		prev = cur;
		cur = cur->next_node;
	}
}


void delete_element_by_number(List &list, int number) {
	if (list.head_node == nullptr || number < 1) { // пустой список и number < 1
		return;
	}

	if (number == 1) { // проверка на случай первого элемента или одного в списке
		Node* cur = list.head_node->next_node;
		delete list.head_node;
		list.head_node = cur;
		if (list.head_node == nullptr) {
			list.tail_node = nullptr;
		}
		return;
	}

	Node *cur = list.head_node->next_node;
	Node *prev = list.head_node;
	int cur_num = 2;
	while (cur != nullptr) {
		if (cur_num == number) {
			prev->next_node = cur->next_node;
			if (cur == list.tail_node) {
				list.tail_node = prev;
			}
			delete cur;
			return;
		}
		prev = cur;
		cur = cur->next_node;
		cur_num++;
	}
}


void add_element_by_key(List& list, string key, string value) {
	if (list.head_node == nullptr) { return; } // пустой список

	if (list.head_node == list.tail_node) { // один элемент в списке
		if (list.head_node->str == key) {
			Node* cur = new Node;
			cur->str = value;
			list.head_node->next_node = cur;
			list.tail_node = cur;
			cur->next_node = nullptr;
			return;
		}
	}

	// более одного элемента и последний
	Node *cur_node = list.head_node;
	while (cur_node != nullptr) {
		if (cur_node->str == key) {
			Node *new_node = new Node;
			new_node->str = value;
			if (cur_node == list.tail_node) {
				new_node->next_node = nullptr;
				list.tail_node = new_node;
				cur_node->next_node = new_node;
			}
			else {
				new_node->next_node = cur_node->next_node;
				cur_node->next_node = new_node;
			}
			return;
		}
		cur_node = cur_node->next_node;
	}
	
}


void add_element_by_number(List& list, int number, string value) {
	if (list.head_node == nullptr) { 
		Node* new_node = new Node;
		new_node->str = value;
		list.head_node = new_node;
		list.tail_node = new_node;
		return;
	}
	
	Node *cur_node = list.head_node;
	int cur_num = 1;
	while (cur_node != nullptr) {
		if (cur_num == number) {

			Node *new_node = new Node;
			new_node->str = value;
			
			if (cur_node == list.tail_node) {
				new_node->next_node = nullptr;
				list.tail_node = new_node;
				cur_node->next_node = new_node;
			}
			else {
				new_node->next_node = cur_node->next_node;
				cur_node->next_node = new_node;
			}
			return;	
		}
		cur_num++;
		cur_node = cur_node->next_node;
	}
}

void print_list(List& list) {
	if (list.head_node == nullptr) {
		cout << "Список пуст" << endl;
		return;
	}
	cout << endl << "Текущее состояние листа: " << endl;
	Node *cur = list.head_node;
	int num = 1;
	while (cur != nullptr) {
		cout << "Элемент " << num << ": " << cur->str << endl;
		num++;
		cur = cur->next_node;
	}
}


void fill_list(List& list, int count) {
	for (int i = 0; i < count; i++) {
		string s;
		cout << "Введите " << i+1 << " элемент: ";
		cin >> s;
		append_to_back(list, s);
	}
}

int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	List list;
	fill_list(list, 3);
	print_list(list);

	int k;
	cout << "1. Удалить K элементов с конца, введите K: ";
	cin >> k;
	for (int i = 1; i <= k; i++) {
		delete_element_from_back(list);
	}
	print_list(list);
	
	string key, value;
	cout << endl << "2. Добавить элемент после после элемента с заданным ключом, введите ключ и значение (через пробел): ";
	cin >> key >> value;
	add_element_by_key(list, key, value);
	print_list(list);

	return 0;
}