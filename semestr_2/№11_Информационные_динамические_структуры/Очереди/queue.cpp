#include <iostream>
#include <clocale>
#include <string>
using namespace std;


struct Node {
	string str;
	Node* next_node = nullptr;
};


struct Queue {
	Node* head_node = nullptr;
	Node* tail_node = nullptr;
	int size = 0;
};


// Добавление элемента в конец
void append_to_back(Queue& queue, string element) {
	Node* new_node = new Node;
	new_node->str = element;
	new_node->next_node = nullptr;

	if (queue.head_node == nullptr) { // пустой список
		queue.head_node = new_node;
		queue.tail_node = new_node;
	}
	else {
		queue.tail_node->next_node = new_node;
		queue.tail_node = new_node;
	}
	queue.size++;
}


// Добавление элемента в начало
void append_to_start(Queue& queue, string element) {
	Node* new_node = new Node;
	new_node->str = element;

	if (queue.head_node == nullptr) {
		queue.head_node = new_node;
		queue.tail_node = new_node;
	}
	else {
		new_node->next_node = queue.head_node;
		queue.head_node = new_node;
	}
	queue.size++;
}


// Удаление элемемента с конца
void delete_element_from_back(Queue& queue) {

	if (queue.head_node == nullptr) { return; } // пустой список
	if (queue.head_node == queue.tail_node) { // один элемент
		delete queue.head_node;
		queue.head_node = nullptr;
		queue.tail_node = nullptr;
		queue.size--;
		return;
	}

	Node* cur_node = queue.head_node;
	while (cur_node->next_node != queue.tail_node) { // после цикла cur_node будет перед tail
		cur_node = cur_node->next_node;
	}
	delete queue.tail_node;
	queue.tail_node = cur_node;
	cur_node->next_node = nullptr;
	queue.size--;

}


// Удаление элемента с начала
void delete_element_from_start(Queue& queue) {
	if (queue.head_node == nullptr) { return; } // пустой список
	if (queue.head_node == queue.tail_node) { // один элемент
		delete queue.head_node;
		queue.head_node = nullptr;
		queue.tail_node = nullptr;
		queue.size--;
		return;
	}

	Node* cur = queue.head_node->next_node;
	delete queue.head_node;
	queue.head_node = cur;
	queue.size--;

}


// Удаление элемента по ключу
void delete_element_by_key(Queue& queue, const string& key) {
	// Пустой список
	if (queue.head_node == nullptr) {
		return;
	}

	// Удаление первого элемента (включая случай одного элемента)
	if (queue.head_node->str == key) {
		Node* new_head = queue.head_node->next_node;
		delete queue.head_node;
		queue.head_node = new_head;
		// если список был из одного элемента, tail_node обновляется
		if (queue.head_node == nullptr) {
			queue.tail_node = nullptr;
		}
		queue.size--;
		return;
	}

	// Поиск элемента в середине или в конце
	Node* cur = queue.head_node->next_node;
	Node* prev = queue.head_node;
	while (cur != nullptr) {
		if (cur->str == key) {
			prev->next_node = cur->next_node;
			// если удаляем последний элемент, обновляем tail_node
			if (cur == queue.tail_node) {
				queue.tail_node = prev;
			}
			delete cur;
			queue.size--;
			return;
		}
		prev = cur;
		cur = cur->next_node;
	}
}


void delete_element_by_number(Queue& queue, int number) {
	if (queue.head_node == nullptr || number < 1) { // пустой список и number < 1
		return;
	}

	if (number == 1) { // проверка на случай первого элемента или одного в списке
		Node* cur = queue.head_node->next_node;
		delete queue.head_node;
		queue.head_node = cur;
		if (queue.head_node == nullptr) {
			queue.tail_node = nullptr;
		}
		queue.size--;
		return;
	}

	Node* cur = queue.head_node->next_node;
	Node* prev = queue.head_node;
	int cur_num = 2;
	while (cur != nullptr) {
		if (cur_num == number) {
			prev->next_node = cur->next_node;
			if (cur == queue.tail_node) {
				queue.tail_node = prev;
			}
			delete cur;
			queue.size--;
			return;
		}
		prev = cur;
		cur = cur->next_node;
		cur_num++;
	}
}


void add_element_by_key(Queue& queue, string key, string value) {
	if (queue.head_node == nullptr) { return; } // пустой список

	if (queue.head_node == queue.tail_node) { // один элемент в списке
		if (queue.head_node->str == key) {
			Node* cur = new Node;
			cur->str = value;
			queue.head_node->next_node = cur;
			queue.tail_node = cur;
			cur->next_node = nullptr;
			queue.size++;
			return;
		}
	}

	// более одного элемента и последний
	Node* cur_node = queue.head_node;
	while (cur_node != nullptr) {
		if (cur_node->str == key) {
			Node* new_node = new Node;
			new_node->str = value;
			if (cur_node == queue.tail_node) {
				new_node->next_node = nullptr;
				queue.tail_node = new_node;
				cur_node->next_node = new_node;
			}
			else {
				new_node->next_node = cur_node->next_node;
				cur_node->next_node = new_node;
			}
			queue.size++;
			return;
		}
		cur_node = cur_node->next_node;
	}

}


void add_element_by_number(Queue& queue, int number, string value) {
	if (queue.head_node == nullptr) {
		Node* new_node = new Node;
		new_node->str = value;
		queue.head_node = new_node;
		queue.tail_node = new_node;
		queue.size++;
		return;
	}

	Node* cur_node = queue.head_node;
	int cur_num = 1;
	while (cur_node != nullptr) {
		if (cur_num == number) {

			Node* new_node = new Node;
			new_node->str = value;

			if (cur_node == queue.tail_node) {
				new_node->next_node = nullptr;
				queue.tail_node = new_node;
				cur_node->next_node = new_node;
			}
			else {
				new_node->next_node = cur_node->next_node;
				cur_node->next_node = new_node;
			}
			queue.size++;
			return;
		}
		cur_num++;
		cur_node = cur_node->next_node;
	}
}

void print_queue(Queue& queue) {
	if (queue.head_node == nullptr) {
		cout << "Очередь пуста" << endl;
		return;
	}
	cout << endl << "Текущее состояние очереди: " << endl;
	Node* cur = queue.head_node;
	while (cur != nullptr) {
		if (cur->next_node == nullptr) {
			cout << cur->str << endl;
		}
		else {
			cout << cur->str << "<-";
		}
		cur = cur->next_node;
	}
}


void fill_queue(Queue& queue, int count) {
	for (int i = 0; i < count; i++) {
		string s;
		cout << "Введите " << i + 1 << " элемент: ";
		cin >> s;
		append_to_back(queue, s);
	}
}

int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	Queue queue;
	fill_queue(queue, 3);
	print_queue(queue);

	int k;
	cout << "1. Удалить K элементов с конца, введите K: ";
	cin >> k;
	for (int i = 1; i <= k; i++) {
		delete_element_from_back(queue);
	}
	print_queue(queue);

	string key, value;
	cout << endl << "2. Добавить элемент после после элемента с заданным ключом, введите ключ и значение (через пробел): ";
	cin >> key >> value;
	add_element_by_key(queue, key, value);
	print_queue(queue);

	return 0;
}