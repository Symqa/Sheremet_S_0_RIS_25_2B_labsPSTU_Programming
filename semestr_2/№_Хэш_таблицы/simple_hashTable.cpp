#include <iostream>
#include <clocale>
#include ".\Random.h"
#include <fstream>
using namespace std;




struct HashTable {
    Human *arr;
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
        arr = new Human[sz]();
        size = sz;
    }

    void clearTable() {
        delete[] arr;
        arr = nullptr;
        collision_count = 0;
        size = 0;
    }

    void add(const Human &person) {
        int index = hashFunction(person.full_name); // получение хэш-кода из ФИО
        int hash = index;

        // Проверка на ячейку, если пустая - записываем
        if (arr[index].full_name == "") {
            arr[index] = person;
            return;
        } else { // если не пустая
            while (index < size) { // идём в конец таблицы из полученного индекса и ищем пустое место
                if (arr[index].full_name == "") { // находим - добавляем
                    arr[index] = person;
                    return;
                }
                index++;
                collision_count++; // если не нашли - идём на следующий индекс и добавляем счётчик коллизий
            }
            if (index >= size) { // если индекс ушёл за пределы размера
                index = 0;
                while (index < hash) { // идём с начала таблицы до индекса, полученного из хэш функции
                    if (arr[index].full_name == "") {
                        arr[index] = person;
                        return;
                    }
                    index++;
                    collision_count++;
                }
                if (index >= hash) { // если так и не нашли - значит таблица заполнена
                    cout << "Таблица заполнена, элемент не может быть добавлен. \n\n";
                    return;
                }
            }
        }
    }

    void pop(const string &full_name) {
        int index = findIndex(full_name); // находим индекс в хэш таблице по имени

        if (index != -1) { // если нашли
            arr[index] = Human(); // делаем пустого human
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

    int findIndex(const string &full_name) {
        int start = hashFunction(full_name);
        int index = start;

        if (arr[index].full_name == full_name) {
            return index;
        }
        index = (index + 1) % size;
        while (index != start) {
            if (arr[index].full_name == full_name) {
                return index;
            }
            index = (index + 1) % size;
        }
        return -1;  // не найдено
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

    out.write(reinterpret_cast<const char*>(&size), sizeof(size));

    for (int i = 0; i < size; ++i) {
        const Human& h = arr[i];

        int len = h.full_name.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(h.full_name.data(), len);

        len = h.birthday.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(h.birthday.data(), len);

        len = h.address.size();
        out.write(reinterpret_cast<const char*>(&len), sizeof(len));
        out.write(h.address.data(), len);
    }

    std::cout << "Хеш-таблица успешно сохранена в файл " << filename << std::endl;
}

void loadFromFile(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Ошибка открытия файла для чтения: " << filename << std::endl;
        return;
    }

    clearTable();

    int newSize = 0;
    in.read(reinterpret_cast<char*>(&newSize), sizeof(newSize));
    if (!in) {
        std::cerr << "Ошибка чтения размера таблицы\n";
        return;
    }

    arr = new Human[newSize]();
    size = newSize;

    for (int i = 0; i < size; ++i) {
        int len;

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!in) break;
        arr[i].full_name.resize(len);
        in.read(&arr[i].full_name[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!in) break;
        arr[i].birthday.resize(len);
        in.read(&arr[i].birthday[0], len);

        in.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!in) break;
        arr[i].address.resize(len);
        in.read(&arr[i].address[0], len);
    }

    std::cout << "Хеш-таблица успешно загружена из файла " << filename << std::endl;
}
};

int main() {
    HashTable table;
    string person_name_to_check;
    setlocale(LC_ALL, "ru-RU.UTF-8");
    
    cout << "1. 40 элементов в хэш-таблице:" << endl << endl;
    table.createBlankTable(40);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
    cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.arr[table.findIndex(person_name_to_check)].full_name;
    table.clearTable();

    cout << endl << endl << "2. 75 элементов в хэш-таблице: " << endl << endl;
    table.createBlankTable(75);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
    cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.arr[table.findIndex(person_name_to_check)].full_name;
    table.clearTable();

    cout << endl << endl << "3. 90 элементов в хэш-таблице: " << endl << endl;
    table.createBlankTable(90);
    table.generateHumans();
    person_name_to_check = table.arr[rand()%table.size].full_name;
    cout << "Количество коллизий: " << table.collision_count << endl;
        cout << "Поиск элементов (что было/что нашлось): " << person_name_to_check << " vs " << table.arr[table.findIndex(person_name_to_check)].full_name;
    table.clearTable();
    
    return 0;
}
