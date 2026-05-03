#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void buildShiftTable(const string& pattern, vector<int>& shift) {
    int m = pattern.size();
    fill(shift.begin(), shift.end(), m);
    for (int i = 0; i < m - 1; ++i) {
        shift[(unsigned char)pattern[i]] = m - 1 - i;
    }
}

int horspoolSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> shift(256);
    buildShiftTable(pattern, shift);

    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (j >= 0 && text[i - (m - 1 - j)] == pattern[j]) {
            --j;
        }
        if (j < 0) {
            return i - (m - 1);
        }
        i += shift[(unsigned char)text[i]];
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");

    string text = "Пример текста с буквами и буераком";
    string pattern = "буера";

    int pos = horspoolSearch(text, pattern);

    if (pos != -1) {
        cout << "Подстрока \"" << pattern << "\" найдена на позиции " << pos << endl;
        cout << "Контекст: " << text.substr(pos, pattern.size() + 5) << "..." << endl;
    } else {
        cout << "Подстрока \"" << pattern << "\" не найдена." << endl;
    }

    string text2 = "Иванов, Петров, Бойер, Сидоров";
    string pattern2 = "Бойер";
    pos = horspoolSearch(text2, pattern2);
    cout << "\nПоиск \"" << pattern2 << "\" в \"" << text2 << "\": позиция " << pos << endl;

    return 0;
}