#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;

//1.	Создание списка.
//2.	Добавление элемента в список(в соответствии со своим вариантом).
//3.	Удаление элемента из списка(в соответствии со своим вариантом).
//4.	Печать списка.
//5.	Запись списка в файл.
//6.	Уничтожение списка.
//7.	Восстановление списка из файла.

// 15.	Записи в линейном списке содержат ключевое поле типа * char(строка символов).
// Сформировать двунаправленный список.
// Удалить К элементов из конца списка.
// Добавить элемент после элемента с заданным ключом.

struct Node {
	char* data = nullptr;
	Node *prev_node = nullptr;
	Node *next_node = nullptr;
};


struct List {
	Node *head_node = nullptr;
	Node *tail_node = nullptr;
};

void pushBackToList(List& list, char *data) {
	Node *new_node = new Node;
	new_node->data = data;
	
	if (list.head_node == nullptr) {

		list.head_node = new_node;
		list.tail_node = new_node;

	}
	else { // "первый" "второй" "новый"
		list.tail_node->next_node = new_node; // второй элемент ссылается на новый
		new_node->prev_node = list.tail_node; // новый ссылается на второй
		list.tail_node = new_node; // последний - новый
	}
}


void loadListFromFile(const char* filename, List& list) {
	// Открытие файла
	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		cout << "Невозможно открыть файл для восстановления";
		exit(1);
	}
	
	// Переменная для получения длины data
	int len = 0;
	while (fread(&len, sizeof(int), 1, f) == 1) {
		// Получение данных одного элемента из файла
		char *data = new char[len+1];
		fread(data, sizeof(char), len, f);
		data[len] = '\0';
		
		// Пуш в конец листа
		pushBackToList(list, data);
	}
	fclose(f);
	cout << "Список успешно загружен." << endl;
}


void deleteList(List& list) {
	Node* cur = list.head_node;
	while (cur) {
		Node* to_delete = cur;
		cur = cur->next_node;
		delete[] to_delete->data;
		delete to_delete;
	}
	list.head_node = nullptr;
	list.tail_node = nullptr;
}


void saveListToFile(const char* filename, List& list) {
	if (list.head_node == nullptr) {
		cout << "Лист пуст";
		return;
	}
	FILE *f = fopen(filename, "wb");
	if (f == NULL) {
		cout << "Невозможно открыть файл для сохранения";
		exit(1);
	}
	Node* cur = list.head_node;
	while (cur) {
		int i = 0;
		while (cur->data[i] != '\0') {
			i++;
		}
		int len = i;

		fwrite(&len, sizeof(int), 1, f);
		fwrite(cur->data, sizeof(char), len, f);

		if (ferror(f)) {
			cout << "Невозможно записать данные в файл";
			exit(2);
		}
		cur = cur->next_node;
	}
	fclose(f);
	cout << "Файл успешно сохранён.";
}


void printList(List& list) {
	Node* cur = list.head_node;
	if (cur == nullptr) {
		cout << "Список пуст" << endl;
		return;
	}
	cout << "Список: " << endl;
	int i = 1;
	while (cur) {
		cout << i << "-ый элемент: " << "[ " << string(cur->data) << " ]" << endl;
		cur = cur->next_node;
		i++;
	}

}

void deleteElementsByCount(List& list, const int count) {
	if (count > 0) {
		Node* cur_node = list.tail_node;
		for (int i = 0; i < count; i++) {
			if (cur_node == list.head_node) {
				delete[] cur_node->data;
				delete cur_node;
				list.head_node = nullptr;
				list.tail_node = nullptr;
				cout << "Лист полностью очищен." << endl;
				return;
			}
			cur_node = cur_node->prev_node;
			delete[] cur_node->next_node->data;
			delete cur_node->next_node;
		}
		list.tail_node = cur_node;
		cur_node->next_node = nullptr;
	}
	else {
		cout << "Указанное количество должно быть больше 0." << endl;
	}
}


void insertElementByKey(List &list, char *key, char *data) {
	Node *cur_node = list.head_node;
	while (string(cur_node->data) != string(key)) {
		cur_node = cur_node->next_node;
	}
	if (cur_node == nullptr) {
		cout << "Заданный ключ не найден в списке" << endl;
		return;
	}
	else {
		Node *new_node = new(Node);
		new_node->data = data;
		new_node->prev_node = cur_node;
		
		if (cur_node == list.tail_node) {
			new_node->prev_node = list.tail_node;
			list.tail_node->next_node = new_node;
			list.tail_node = new_node;
		}
		else { // {"перед", "новый", "после"}
			new_node->prev_node = cur_node; // Ссылка на элемент "перед"
			cur_node = cur_node->next_node; // Перескок на элемент "после"

			new_node->next_node = cur_node; // Ссылка на элемент "после"
			cur_node->prev_node = new_node; // Ссылка элемента "после" на новый элемент

			new_node->prev_node->next_node = new_node; // Ссылка элемента "перед" на новый элемент
		}
	}
}



void addItem(List& list, char* data) {
	Node* new_node = new(Node);
	new_node->data = data;
	
	if (list.head_node == nullptr) {
		list.head_node = new_node;
		list.tail_node = new_node;
		return;
	}
	
	new_node->prev_node = list.tail_node;
	list.tail_node->next_node = new_node;
	list.tail_node = new_node;
	
}

char* getDataFromUser() {
	const int BUFFER_SIZE = 100;
	char* data = nullptr;

	// Создание нового буфера
	char buffer[BUFFER_SIZE]{};

	// Получение ввода пользователя
	cin >> buffer;

	// Получение количества элементов в ключе
	int i = 0;
	while (buffer[i] != '\0') {
		i++;
	}

	// Выделение памяти под ключ и \0 (конец строки)
	data = new char[i + 1];
	i = 0;
	while (buffer[i] != '\0') {
		data[i] = buffer[i];
		i++;
	}
	// Дошли до buffer[i] == '\0', поэтому можно смело добавить в data
	data[i] = buffer[i];
	return data;
}

void fillList(List &list, int size) {
	char* data;

	for (int k = 0; k < size; k++) {
		cout << "Ключ " << k + 1 << " элемента: ";
		data = getDataFromUser();
		addItem(list, data);
	}
}


int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	List list;
	int size, count_to_delete;
	char *key = nullptr, *data = nullptr;

	cout << "Введите размер листа: ";
	cin >> size;
	cout << endl << "1. Заполнение листа : " << endl;
	fillList(list, size);
	printList(list);

	cout << endl <<"2. Добавление элемента: " << endl;
	cout << "a) Ключ нового элемента: ";
	data = getDataFromUser();
	cout << "b) Ключ элемента, после которого добавится новый: ";
	key = getDataFromUser();
	cout << endl;
	insertElementByKey(list, key, data);
	printList(list);

	cout << endl << "3. Введите количество элементов, которое будет удалено из списка: ";
	cin >> count_to_delete;
	deleteElementsByCount(list, count_to_delete);
	printList(list);
	
	cout << endl << "4. Запись в файл: " << endl;
	saveListToFile("file.dat", list);

	cout << endl << endl << "5. Удаление списка: " << endl;
	deleteList(list);
	printList(list);

	cout << endl << "6. Загрузка листа из файла: " << endl;
	loadListFromFile("file.dat", list);
	printList(list);
	return 0;
}