#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>

using namespace std;

// Класс Pair из лабораторной работы №3
class Pair {
private:
    double first;
    double second;
public:
    Pair() : first(0), second(0) {}
    Pair(double f, double s) : first(f), second(s) {}

    double getFirst() const { return first; }
    double getSecond() const { return second; }
    void setFirst(double f) { first = f; }
    void setSecond(double s) { second = s; }

    // Операции сравнения (по ключевому полю first)
    bool operator<(const Pair& other) const {
        return first < other.first;
    }
    bool operator>(const Pair& other) const {
        return first > other.first;
    }
    bool operator==(const Pair& other) const {
        return first == other.first && second == other.second;
    }
    bool operator!=(const Pair& other) const {
        return !(*this == other);
    }

    // Арифметические операции (поэлементные)
    Pair operator+(const Pair& other) const {
        return Pair(first + other.first, second + other.second);
    }
    Pair operator-(const Pair& other) const {
        return Pair(first - other.first, second - other.second);
    }
    Pair operator*(const Pair& other) const {
        return Pair(first * other.first, second * other.second);
    }
    Pair operator/(const Pair& other) const {
        if (other.first == 0 || other.second == 0) {
            throw runtime_error("Division by zero in Pair");
        }
        return Pair(first / other.first, second / other.second);
    }
    Pair& operator=(const Pair& other) = default;

    // Ввод/вывод
    friend istream& operator>>(istream& in, Pair& p) {
        cout << "Enter first and second: ";
        in >> p.first >> p.second;
        return in;
    }
    friend ostream& operator<<(ostream& out, const Pair& p) {
        out << "(" << p.first << ", " << p.second << ")";
        return out;
    }
};

// -------------------------------------------------------------------
// Задача 1: Вектор (vector)
// -------------------------------------------------------------------

// Предикат для поиска по ключевому полю
struct EqualFirst {
    double key;
    EqualFirst(double k) : key(k) {}
    bool operator()(const Pair& p) const {
        return p.getFirst() == key;
    }
};

// Предикат для удаления элементов, меньших среднего арифметического first
class LessThanAverage {
    double avg;
public:
    LessThanAverage(double a) : avg(a) {}
    bool operator()(const Pair& p) const {
        return p.getFirst() < avg;
    }
};

// Функция деления Pair на заданное Pair (глобальная переменная для for_each)
Pair divisor;
void dividePair(Pair& p) {
    if (divisor.getFirst() != 0 && divisor.getSecond() != 0)
        p = p / divisor;
    else
        throw runtime_error("Division by zero in dividePair");
}

// Вывод вектора
void printVector(const vector<Pair>& v, const string& msg = "") {
    if (!msg.empty()) cout << msg << endl;
    for (size_t i = 0; i < v.size(); ++i)
        cout << v[i] << " ";
    cout << endl;
}

void task1_vector() {
    cout << "\n========== Задача 1: Вектор ==========\n";
    int n;
    cout << "Количество элементов: ";
    cin >> n;

    vector<Pair> v;
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        v.push_back(p);
    }
    printVector(v, "Исходный вектор:");

    // 1. Сортировка по возрастанию ключевого поля (first)
    sort(v.begin(), v.end(), [](const Pair& a, const Pair& b) { return a.getFirst() < b.getFirst(); });
    printVector(v, "После сортировки по возрастанию first:");

    // 2. Сортировка по убыванию
    sort(v.begin(), v.end(), [](const Pair& a, const Pair& b) { return a.getFirst() > b.getFirst(); });
    printVector(v, "После сортировки по убыванию first:");

    // 3. Поиск элемента с заданным ключом
    double key;
    cout << "Введите ключ (first) для поиска: ";
    cin >> key;
    auto it = find_if(v.begin(), v.end(), EqualFirst(key));
    if (it != v.end())
        cout << "Найден: " << *it << endl;
    else
        cout << "Элемент с ключом " << key << " не найден.\n";

    // 4. Задание 3: найти минимальный элемент и добавить его на заданную позицию
    auto minIt = min_element(v.begin(), v.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    Pair minElem = *minIt;
    cout << "Минимальный элемент: " << minElem << endl;
    int pos;
    cout << "Введите позицию для вставки (индекс от 0 до " << v.size() << "): ";
    cin >> pos;
    if (pos < 0) pos = 0;
    if (pos > (int)v.size()) pos = v.size();
    v.insert(v.begin() + pos, minElem);
    printVector(v, "После добавления минимального элемента на позицию " + to_string(pos) + ":");

    // 5. Задание 4: найти среднее арифметическое first и удалить элементы, меньшие его
    double sumFirst = 0;
    for (const auto& p : v) sumFirst += p.getFirst();
    double avgFirst = sumFirst / v.size();
    cout << "Среднее арифметическое first = " << avgFirst << endl;
    v.erase(remove_if(v.begin(), v.end(), LessThanAverage(avgFirst)), v.end());
    printVector(v, "После удаления элементов, меньших среднего арифметического first:");

    // 6. Задание 5: каждый элемент разделить на максимальный элемент
    auto maxIt = max_element(v.begin(), v.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    divisor = *maxIt;
    cout << "Максимальный элемент (делитель): " << divisor << endl;
    for_each(v.begin(), v.end(), dividePair);
    printVector(v, "После деления каждого элемента на максимальный:");
}

// -------------------------------------------------------------------
// Задача 2: Адаптер контейнера - очередь (queue)
// -------------------------------------------------------------------

// Вспомогательные функции для работы с очередью через вектор
void task2_queue() {
    cout << "\n========== Задача 2: Очередь (queue) ==========\n";
    int n;
    cout << "Количество элементов: ";
    cin >> n;

    queue<Pair> q;
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        q.push(p);
    }

    // Преобразуем очередь в вектор для использования алгоритмов
    vector<Pair> v;
    while (!q.empty()) {
        v.push_back(q.front());
        q.pop();
    }

    printVector(v, "Исходная очередь (в виде вектора):");

    // 1. Сортировка по возрастанию
    sort(v.begin(), v.end(), [](const Pair& a, const Pair& b) { return a.getFirst() < b.getFirst(); });
    printVector(v, "После сортировки по возрастанию first:");

    // 2. Сортировка по убыванию
    sort(v.begin(), v.end(), [](const Pair& a, const Pair& b) { return a.getFirst() > b.getFirst(); });
    printVector(v, "После сортировки по убыванию first:");

    // 3. Поиск по ключу
    double key;
    cout << "Введите ключ (first) для поиска: ";
    cin >> key;
    auto it = find_if(v.begin(), v.end(), EqualFirst(key));
    if (it != v.end())
        cout << "Найден: " << *it << endl;
    else
        cout << "Элемент с ключом " << key << " не найден.\n";

    // 4. Задание 3: найти минимальный и вставить на позицию
    auto minIt = min_element(v.begin(), v.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    Pair minElem = *minIt;
    cout << "Минимальный элемент: " << minElem << endl;
    int pos;
    cout << "Введите позицию для вставки (индекс от 0 до " << v.size() << "): ";
    cin >> pos;
    if (pos < 0) pos = 0;
    if (pos > (int)v.size()) pos = v.size();
    v.insert(v.begin() + pos, minElem);
    printVector(v, "После добавления минимального элемента:");

    // 5. Задание 4: удалить элементы меньше среднего first
    double sumFirst = 0;
    for (const auto& p : v) sumFirst += p.getFirst();
    double avgFirst = sumFirst / v.size();
    cout << "Среднее арифметическое first = " << avgFirst << endl;
    v.erase(remove_if(v.begin(), v.end(), LessThanAverage(avgFirst)), v.end());
    printVector(v, "После удаления элементов, меньших среднего first:");

    // 6. Задание 5: деление на максимальный
    auto maxIt = max_element(v.begin(), v.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    divisor = *maxIt;
    cout << "Максимальный элемент (делитель): " << divisor << endl;
    for_each(v.begin(), v.end(), dividePair);
    printVector(v, "После деления каждого элемента на максимальный:");

    // Обратно в очередь (если нужно)
    for (const auto& p : v) q.push(p);
    cout << "Очередь восстановлена.\n";
}

// -------------------------------------------------------------------
// Задача 3: Ассоциативный контейнер - мультимножество (multiset)
// -------------------------------------------------------------------

void task3_multiset() {
    cout << "\n========== Задача 3: Мультимножество (multiset) ==========\n";
    int n;
    cout << "Количество элементов: ";
    cin >> n;

    multiset<Pair, less<Pair>> ms;   // стандартный порядок по first (возрастание)
    cout << "Введите " << n << " элементов:\n";
    for (int i = 0; i < n; ++i) {
        Pair p;
        cin >> p;
        ms.insert(p);
    }

    // Вывод мультимножества (уже отсортировано по возрастанию)
    cout << "Исходное мультимножество (возрастание):\n";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    // "Сортировка" по убыванию: создаём новое мультимножество с компаратором greater
    multiset<Pair, greater<Pair>> ms_desc(ms.begin(), ms.end());
    cout << "Мультимножество по убыванию first:\n";
    for (const auto& p : ms_desc) cout << p << " ";
    cout << endl;

    // Поиск элемента с заданным ключом
    double key;
    cout << "Введите ключ (first) для поиска: ";
    cin >> key;
    auto it = find_if(ms.begin(), ms.end(), EqualFirst(key));
    if (it != ms.end())
        cout << "Найден: " << *it << endl;
    else
        cout << "Элемент с ключом " << key << " не найден.\n";

    // Для дальнейших операций преобразуем мультимножество в вектор
    vector<Pair> v(ms.begin(), ms.end());

    // Задание 3: найти минимальный элемент и добавить на позицию
    auto minIt = min_element(v.begin(), v.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    Pair minElem = *minIt;
    cout << "Минимальный элемент: " << minElem << endl;
    int pos;
    cout << "Введите позицию для вставки (индекс от 0 до " << v.size() << "): ";
    cin >> pos;
    if (pos < 0) pos = 0;
    if (pos > (int)v.size()) pos = v.size();
    v.insert(v.begin() + pos, minElem);
    printVector(v, "Вектор после добавления минимального элемента (для обновления мультимножества):");

    // Обновим мультимножество
    ms.clear();
    ms.insert(v.begin(), v.end());

    // Задание 4: удалить элементы, меньшие среднего арифметического first
    double sumFirst = 0;
    for (const auto& p : ms) sumFirst += p.getFirst();
    double avgFirst = sumFirst / ms.size();
    cout << "Среднее арифметическое first = " << avgFirst << endl;
    // Удаление из мультимножества через итераторы (нельзя remove_if напрямую)
    for (auto it = ms.begin(); it != ms.end(); ) {
        if (it->getFirst() < avgFirst)
            it = ms.erase(it);
        else
            ++it;
    }
    cout << "Мультимножество после удаления элементов, меньших среднего first:\n";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;

    // Задание 5: разделить каждый элемент на максимальный
    auto maxIt = max_element(ms.begin(), ms.end(), [](const Pair& a, const Pair& b) {
        return a.getFirst() < b.getFirst();
    });
    divisor = *maxIt;
    cout << "Максимальный элемент (делитель): " << divisor << endl;
    // Создаём новый контейнер с результатом деления
    multiset<Pair> ms2;
    for (const auto& p : ms) {
        if (divisor.getFirst() != 0 && divisor.getSecond() != 0)
            ms2.insert(p / divisor);
        else
            throw runtime_error("Division by zero in multiset task");
    }
    ms = ms2;
    cout << "Мультимножество после деления каждого элемента на максимальный:\n";
    for (const auto& p : ms) cout << p << " ";
    cout << endl;
}

// -------------------------------------------------------------------
// Главная функция
// -------------------------------------------------------------------
int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    try {
        task1_vector();
        task2_queue();
        task3_multiset();
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}