#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void buildBadCharTable(const string& pattern, vector<int>& badChar) {
    int m = pattern.size();
    fill(badChar.begin(), badChar.end(), m);
    for (int i = 0; i < m - 1; ++i) {
        badChar[(unsigned char)pattern[i]] = m - 1 - i;
    }
}

int boyerMooreSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> badChar(256);
    buildBadCharTable(pattern, badChar);

    int i = m - 1;
    while (i < n) {
        int j = m - 1;
        while (j >= 0 && text[i - (m - 1 - j)] == pattern[j]) {
            --j;
        }
        if (j < 0) {
            return i - (m - 1);
        }
        int shift = badChar[(unsigned char)text[i]];
        if (shift < 1) shift = 1;
        i += shift;
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");

    string text = "В этом лесу растёт бук, а ещё есть бобры и буерак.";
    string pattern = "буера";

    int pos = boyerMooreSearch(text, pattern);

    if (pos != -1) {
        cout << "Подстрока \"" << pattern << "\" найдена на позиции " << pos << endl;
        cout << "Контекст: " << text.substr(pos, pattern.size() + 5) << "..." << endl;
    } else {
        cout << "Подстрока \"" << pattern << "\" не найдена." << endl;
    }

    string text2 = "Иванов, Петров, Бойер, Сидоров";
    string pattern2 = "Бойер";
    pos = boyerMooreSearch(text2, pattern2);
    cout << "\nПоиск \"" << pattern2 << "\" в \"" << text2 << "\": позиция " << pos << endl;

    return 0;
}