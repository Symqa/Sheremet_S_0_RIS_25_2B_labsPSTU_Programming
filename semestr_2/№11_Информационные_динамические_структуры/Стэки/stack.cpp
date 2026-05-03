#include <iostream>
#include <clocale>
#include <string>
using namespace std;


struct Node {
	string str;
	Node* next_node = nullptr;

	Node(string s): str(s) {}
};


struct Stack {
	Node *head = nullptr;
	int size = 0;

	void fill_stack(int count) {
		for (int i = 1; i <= count; i++) {
			string str;
			cout << "Введите " << i << " элемент: ";
			cin >> str;
			add_item_to_start(str);
		}
	}
	// Добавить заместо head
	void add_item_to_start(string str) { 
		Node *new_item = new Node(str);
		
		if (size == 0) { // стэк пуст
			head = new_item;
		}
		else {
			new_item->next_node = head;
			head = new_item;
		}
		
		size++;
	}

	// Добавить в самый низ кучи
	void add_item_to_back(string str) {
		Node* new_item = new Node(str);

		if (size == 0) {
			head = new_item;
		}
		else {
			Node *cur = head;
			while (cur->next_node != nullptr) cur = cur->next_node; // cur = последний элемент кучи
			cur->next_node = new_item;
		}

		size++;
	}

	// Удалить из самого низа кучи
	void delete_item_from_back() {
		if (size == 0) {
			return; // куча пуста
		} else if (size == 1) { // 1 элемент
			delete head;
			head = nullptr;
		}
		else { // от 2 и более
			Node *cur = head->next_node;
			Node *prev = head;
			while (cur->next_node != nullptr) {
				prev = cur;
				cur = cur->next_node;
			}
			prev->next_node = nullptr;
			delete cur;
		}

		size--;
	}

	// Удалить элемент из самого верха кучи
	void delete_item_from_start() {
		if (size == 0) {
			return;
		}
		Node *cur = head->next_node;
		delete head;
		head = nullptr;
		if (cur != nullptr) {
			head = cur;
		}

		size--;
	}

	// Удаление элемента по ключу
	void delete_item_by_key(string key) {
		if (size == 0) {
			return;
		}
		
		Node *cur = head;
		Node *prev;
		while (cur->next_node != nullptr) {
			if (cur->str == key) {
				if (cur == head) {
					head = cur->next_node;
					delete cur;
					size--;
					return;
				}
				prev->next_node = cur->next_node;
				delete cur;
				size--;
				return;
			}
			prev = cur;
			cur = cur->next_node;
		}
	}
	
	// Удаление элемента по номеру
	void delete_item_by_number(int number) {
		if (size == 0 || number < 0) {
			return;
		}

		if (number == 1) {
			Node *cur = head->next_node;
			delete head;
			head = cur;
			size--;
			return;
		}
	
		int cur_num = 2;
		Node *cur = head->next_node;
		Node *prev = head;
		while (cur->next_node != nullptr) {
				
			if (cur_num == number) {
				prev->next_node = cur->next_node;
				delete cur;
				size--;
				return;
			}
			prev = cur;
			cur = cur->next_node;
			cur_num++;
		}
	}

	// Добавить элемент после ключа
	void add_item_by_key(string str, string key) {
		if (size == 0) {
			return;
		}

		Node *cur = head;
		
		while (cur != nullptr) {
			
			if (cur->str == key) {
				Node* new_item = new Node(str);
				new_item->next_node = cur->next_node;
				cur->next_node = new_item;
				size++;
				return;
			}
			cur = cur->next_node; 
			
		}
		
		
	
	}

	// Добавить элемент после номера
	void add_item_by_number(string str, int number) {
		if (size == 0 || number == 1) {
			Node *new_item = new Node(str);
			head = new_item;
			size++;
			return;
		}

		int cur_num = 2;
		Node *cur = head;
		while (cur != nullptr) {
			if (cur_num == number) {
				Node* new_item = new Node(str);
				new_item->next_node = cur->next_node;
				cur->next_node = new_item;
				size++;
				return;
			}

			cur_num++;
			cur = cur->next_node;
		}
	}

	void show() {
		if (size == 0) {
			cout << "Стек пуст." << endl;
			return;
		}

		cout << endl << "Текущий размер стэка: " << size << endl;
		Node* cur = head;
		for (int i = 0; i < size; i++) {
			cout << cur->str << "->";
			cur = cur->next_node;
		}
		cout << "Конец стэка" << endl;
		
		
	}

};



int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	int size, k;
	Stack stack;
	string key, value;

	// Заполнение
	cout << "Введите размер стэка: ";

	do {
		cin >> size;
	} while (size < 0);

	
	stack.fill_stack(size);
	stack.show();

	// Задание 1 
	cout << "1. Удалить K элементов с конца, введите K: ";
	do {
		cin >> k;
	} while (k < 0);
	
	for (int i = 0; i < k; i++) {
		stack.delete_item_from_back();
	}
	stack.show();
	
	// Задание 2
	cout << endl << "2. Добавить элемент после после элемента с заданным ключом, введите ключ и значение (через пробел): ";
	cin >> key >> value;
	stack.add_item_by_key(value, key);

	stack.show();
	



	return 0;
}