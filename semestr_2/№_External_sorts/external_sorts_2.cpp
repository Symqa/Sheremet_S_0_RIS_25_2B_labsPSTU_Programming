#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Вспомогательные функции
void writeSeriesToFile(ofstream& out, const vector<int>& series) {
    for (size_t i = 0; i < series.size(); ++i) {
        out << series[i];
        if (i != series.size() - 1) out << ' ';
    }
}

vector<vector<int>> readAllSeries(const string& filename) {
    vector<vector<int>> result;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        vector<int> series;
        int num;
        while (iss >> num) series.push_back(num);
        if (!series.empty()) result.push_back(series);
    }
    return result;
}

void writeAllSeries(const string& filename, const vector<vector<int>>& seriesList) {
    ofstream out(filename);
    for (const auto& ser : seriesList) {
        writeSeriesToFile(out, ser);
        out << '\n';
    }
}

// Числа Фибоначчи
int fib(int n) {
    if (n <= 1) return n;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; ++i) {
        c = a + b; a = b; b = c;
    }
    return b;
}

int main() {
    srand(time(nullptr));
    setlocale(LC_ALL, "ru-RU.UTF-8");
    const string srcFile = "data_multiphase_test.txt";
    const int count = 30;

    // Генерируем исходный файл
    ofstream src(srcFile);
    for (int i = 0; i < count; ++i) {
        src << rand() % 1000;
        if (i != count - 1) src << ' ';
    }
    src.close();

    // Читаем все числа
    ifstream in(srcFile);
    vector<int> all;
    int num;
    while (in >> num) all.push_back(num);
    in.close();

    // Создаём начальные серии (длины 1)
    vector<vector<int>> initialSeries;
    for (int v : all) initialSeries.push_back({v});

    // Находим два соседних числа Фибоначчи, сумма которых >= N
    int N = initialSeries.size();
    int k = 2;
    while (fib(k) + fib(k+1) < N) ++k;
    int f1 = fib(k);   // меньшее
    int f2 = fib(k+1); // большее

    // Дополняем фиктивными (пустыми) сериями до f1+f2
    int total = f1 + f2;
    while (initialSeries.size() < total) {
        initialSeries.push_back({}); // фиктивная серия
    }

    // Три временных файла
    string fname[3] = {"mpA.txt", "mpB.txt", "mpC.txt"};
    vector<vector<int>> data[3];

    // Распределяем: в data[0] — f1 серий, в data[1] — f2 серий, data[2] пуст
    for (int i = 0; i < f1; ++i)
        data[0].push_back(initialSeries[i]);
    for (int i = f1; i < total; ++i)
        data[1].push_back(initialSeries[i]);
    data[2].clear();

    writeAllSeries(fname[0], data[0]);
    writeAllSeries(fname[1], data[1]);
    writeAllSeries(fname[2], data[2]);

    cout << "Начальное распределение: файл 0: " << data[0].size()
         << " серий, файл 1: " << data[1].size()
         << " серий, файл 2: " << data[2].size() << " серий\n";

    int step = 1;
    while (data[0].size() + data[1].size() + data[2].size() > 1) {
        // Находим два непустых файла (индексы i1, i2) и один пустой (iout)
        int i1 = -1, i2 = -1, iout = -1;
        for (int i = 0; i < 3; ++i) {
            if (!data[i].empty()) {
                if (i1 == -1) i1 = i;
                else if (i2 == -1) i2 = i;
            } else {
                iout = i;
            }
        }
        if (i1 == -1 || i2 == -1 || iout == -1) {
            cerr << "Ошибка: не удалось определить два непустых файла\n";
            break;
        }

        // Обеспечим, что i1 – файл с меньшим числом серий
        if (data[i1].size() > data[i2].size())
            swap(i1, i2);

        int a = data[i1].size();
        int b = data[i2].size();

        cout << "Шаг " << step << ": сливаем " << a << " пар из файлов "
             << i1 << " и " << i2 << " в файл " << iout
             << " (останется в " << i2 << " ещё " << (b - a) << " серий)\n";

        // Слияние a пар
        vector<vector<int>> merged;
        for (int k = 0; k < a; ++k) {
            const auto& s1 = data[i1][k];
            const auto& s2 = data[i2][k];
            vector<int> m;
            size_t p = 0, q = 0;
            while (p < s1.size() && q < s2.size()) {
                if (s1[p] <= s2[q]) m.push_back(s1[p++]);
                else                m.push_back(s2[q++]);
            }
            while (p < s1.size()) m.push_back(s1[p++]);
            while (q < s2.size()) m.push_back(s2[q++]);
            merged.push_back(m);
        }

        // Оставшиеся серии из большего файла (с индекса a)
        vector<vector<int>> remaining;
        if (b > a) {
            remaining.assign(data[i2].begin() + a, data[i2].end());
        }

        // Обновляем состояния
        data[i1].clear();            // меньший файл становится пустым
        data[i2] = remaining;        // остаток в большем файле
        data[iout] = merged;          // слитые серии в выходной файл

        writeAllSeries(fname[i1], data[i1]);
        writeAllSeries(fname[i2], data[i2]);
        writeAllSeries(fname[iout], data[iout]);

        cout << "После шага: файл 0: " << data[0].size()
             << ", файл 1: " << data[1].size()
             << ", файл 2: " << data[2].size() << "\n\n";
        ++step;
    }

    // Находим непустой файл (должен быть один)
    int fullIdx = -1;
    for (int i = 0; i < 3; ++i)
        if (!data[i].empty()) { fullIdx = i; break; }

    if (fullIdx != -1 && data[fullIdx].size() == 1) {
        const auto& sorted = data[fullIdx][0];
        ofstream res(srcFile);
        writeSeriesToFile(res, sorted);
        res.close();
        cout << "Результат записан в " << srcFile << "\n";
        cout << "Отсортированные числа: ";
        for (int x : sorted) cout << x << ' ';
        cout << endl;
    } else {
        cerr << "Ошибка: не осталось ровно одной серии\n";
    }

    // Удаляем временные файлы (можно закомментировать)
    for (int i = 0; i < 3; ++i) remove(fname[i].c_str());

    return 0;
}