#include <iostream>
#include <clocale>
#include ".\Random.h"
#include ".\List.h"
#include <fstream>
using namespace std;



struct HashTable {
    List *arr;
    int size;
    int collision_count = 0;

    int getSumFullName(const string &full_name) {
        int sum = 0;
        for (char a: full_name) {
            sum = sum + static_cast<unsigned char>(a);
        }
        return sum;
    }

    int hashFunction(const string &full_name) {
        return getSumFullName(full_name) % size;
    }
    
    void createBlankTable(int sz) {
        arr = new List[sz];
        size = sz;
        collision_count = 0;
    }

    void clearTable() {
        if (arr) {
            for (int i = 0; i < size; i++) {
                arr[i].clearList();
            }
            delete[] arr;
        }
        collision_count = 0;
        size = 0;
    }

    void add(const Human &person) {
        int index = hashFunction(person.full_name); // получение хэш-кода из ФИО
        arr[index].add(person, collision_count); // добавление элемента в конец списка и подсчёт коллизий
    }

    void pop(const string &full_name) {
        int index = hashFunction(full_name); // находим индекс в хэш таблице по имени

        if (index != -1) { // если нашли
            arr[index].deleteByPersonName(full_name); // делаем пустого human
            return;
        }
        return; // если не нашли - ничего не делаем
    }

    void show() {
        for (int i = 0; i < size; i++) {
            cout << "Индекс ячейки: " << i << endl;
            arr[i].show();
        }
        return;
    }


    void generateHumans() {
        for (int i = 0; i < size; i++) {
            Human person;
            person.createRandom();
            add(person);
        }
    }

    void saveTableToFile(const char* filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Ошибка открытия файла для записи: " << filename << std::endl;
        return;
    }

    // 1. Сохраняем размер таблицы
    out.write(reinterpret_cast<const char*>(&size), sizeof(size));

    // 2. Для каждой корзины
    for (int i = 0; i < size; ++i) {
        // Определяем количество элементов в цепочке
        int count = 0;
        Node* cur = arr[i].head_node;
        while (cur) {
            ++count;
            cur = cur->next_node;
        }

        // Записываем длину списка
        out.write(reinterpret_cast<const char*>(&count), sizeof(count));

        // Записываем элементы списка
        cur = arr[i].head_node;
        while (cur) {
            const Human& h = cur->human;

            int len = h.full_name.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(h.full_name.data(), len);

            len = h.birthday.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(h.birthday.data(), len);

            len = h.address.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(h.address.data(), len);

            cur = cur->next_node;
        }
    }

    std::cout << "Хеш-таблица успешно сохранена в файл " << filename << std::endl;
    }

    void loadFromFile(const char* filename) {
        std::ifstream in(filename, std::ios::binary);
        if (!in) {
            std::cerr << "Ошибка открытия файла для чтения: " << filename << std::endl;
            return;
        }

        clearTable();  // Корректно удаляет старую таблицу со списками

        int newSize = 0;
        in.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
        if (!in) {
            std::cerr << "Ошибка чтения размера таблицы\n";
            return;
        }

        arr = new List[newSize];  // Массив корзин (head_node = nullptr автоматически)
        size = newSize;
        collision_count = 0;      // При загрузке обнуляем счётчик (мы его не сохраняли)

        for (int i = 0; i < size; ++i) {
            int count;
            in.read(reinterpret_cast<char*>(&count), sizeof(count));
            if (!in) break;

            for (int j = 0; j < count; ++j) {
                Human person;
                int len;

            // Чтение full_name
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (!in) break;
            person.full_name.resize(len);
            in.read(&person.full_name[0], len);

            // Чтение birthday
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (!in) break;
            person.birthday.resize(len);
            in.read(&person.birthday[0], len);

            // Чтение address
            in.read(reinterpret_cast<char*>(&len), sizeof(len));
            if (!in) break;
            person.address.resize(len);
            in.read(&person.address[0], len);

            // Вставка элемента в начало списка (быстрее, без прохода по списку)
            Node* newNode = new Node();
            newNode->human = person;
            newNode->next_node = arr[i].head_node;
            arr[i].head_node = newNode;
            // Примечание: мы не вызываем arr[i].add(), чтобы не менять collision_count
            // и не проходить по списку для вставки в конец. Порядок элементов не важен.
        }
    }

    std::cout << "Хеш-таблица успешно загружена из файла " << filename << std::endl;
    }

    Human get(const string &full_name) {
        return arr[hashFunction(full_name)].get(full_name, collision_count);
    }


};

int main() {
    HashTable table;
    string person_name_to_check;
    setlocale(LC_ALL, "ru-RU.UTF-8");
    
    cout << "1. 40 элементов в хэш-таблице:" << endl << endl;
    table.createBlankTable(40);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].last().full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
    cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.get(person_name_to_check).full_name;
    table.clearTable();

    cout << endl << endl << "2. 75 элементов в хэш-таблице: " << endl << endl;
    table.createBlankTable(75);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].last().full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
    cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.get(person_name_to_check).full_name;
    table.clearTable();

    cout << endl << endl << "3. 90 элементов в хэш-таблице: " << endl << endl;
    table.createBlankTable(90);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].last().full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
    cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.get(person_name_to_check).full_name;
    table.clearTable();
    cout << endl << endl;

    return 0;
}
