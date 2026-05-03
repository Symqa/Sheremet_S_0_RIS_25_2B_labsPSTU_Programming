#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> computePrefixFunction(const string& pattern) {
    int m = pattern.size();
    vector<int> pi(m);
    for (int i = 1; i < m; ++i) {
        int j = pi[i - 1];
        while (j > 0 && pattern[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            ++j;
        }
        pi[i] = j;
    }
    return pi;
}

int kmpSearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();
    if (m == 0) return 0;
    if (n < m) return -1;

    vector<int> pi = computePrefixFunction(pattern);
    int j = 0;
    for (int i = 0; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]) {
            ++j;
        }
        if (j == m) {
            return i - m + 1;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");

    string text = "абракадабра";
    string pattern = "када";

    int pos = kmpSearch(text, pattern);

    if (pos != -1) {
        cout << "Подстрока \"" << pattern << "\" найдена на позиции " << pos << endl;
        cout << "Контекст: " << text.substr(pos, pattern.size() + 3) << "..." << endl;
    } else {
        cout << "Подстрока \"" << pattern << "\" не найдена." << endl;
    }

    string text2 = "Иванов, Петров, Кнут, Сидоров";
    string pattern2 = "Кнут";
    pos = kmpSearch(text2, pattern2);
    cout << "\nПоиск \"" << pattern2 << "\" в \"" << text2 << "\": позиция " << pos << endl;

    return 0;
}