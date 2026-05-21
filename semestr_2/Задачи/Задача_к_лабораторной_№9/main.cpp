#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

// ─────────────────────────────────────────────
// Вспомогательные функции
// ─────────────────────────────────────────────

// Является ли символ согласной (латинский алфавит)
bool isConsonant(char c) {
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    if (!std::isalpha(static_cast<unsigned char>(c))) return false;
    std::string vowels = "aeiou";
    return vowels.find(c) == std::string::npos;
}

// Подсчёт согласных в слове (знаки препинания / цифры не считаются)
int countConsonants(const std::string& word) {
    int count = 0;
    for (char c : word) {
        if (isConsonant(c)) ++count;
    }
    return count;
}

// Разбить строку на слова (по пробельным символам)
// «Слово» — непрерывная последовательность непробельных символов
std::vector<std::string> splitWords(const std::string& line) {
    std::vector<std::string> words;
    std::istringstream iss(line);
    std::string w;
    while (iss >> w) words.push_back(w);
    return words;
}

// ─────────────────────────────────────────────
// Подзадание А: копирование строк с двумя словами
// ─────────────────────────────────────────────
void copyTwoWordLines(const std::string& f1Name, const std::string& f2Name) {
    std::ifstream f1(f1Name);
    if (!f1.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << f1Name << "\n";
        return;
    }
    std::ofstream f2(f2Name);
    if (!f2.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл " << f2Name << "\n";
        return;
    }

    std::string line;
    int lineNum = 0, copied = 0;
    while (std::getline(f1, line)) {
        ++lineNum;
        auto words = splitWords(line);
        if (words.size() == 2) {
            f2 << line << "\n";
            ++copied;
            std::cout << "  Строка " << lineNum << " скопирована: \"" << line << "\"\n";
        } else {
            std::cout << "  Строка " << lineNum << " пропущена ("
                      << words.size() << " слов): \"" << line << "\"\n";
        }
    }
    std::cout << "Итого скопировано строк: " << copied << "\n\n";
}

// ─────────────────────────────────────────────
// Подзадание Б: слова с максимальным числом согласных
// ─────────────────────────────────────────────
void findMaxConsonantWords(const std::string& f1Name) {
    std::ifstream f1(f1Name);
    if (!f1.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << f1Name << "\n";
        return;
    }

    // Хранилище: для каждого слова — его глобальный номер и число согласных
    struct WordInfo {
        int globalNum;
        std::string word;
        int consonants;
    };

    std::vector<WordInfo> allWords;
    std::string line;
    int globalNum = 0;

    while (std::getline(f1, line)) {
        auto words = splitWords(line);
        for (const auto& w : words) {
            ++globalNum;
            int cons = countConsonants(w);
            allWords.push_back({globalNum, w, cons});
        }
    }

    if (allWords.empty()) {
        std::cout << "Файл не содержит слов.\n";
        return;
    }

    // Найти максимум
    int maxCons = 0;
    for (const auto& wi : allWords)
        maxCons = std::max(maxCons, wi.consonants);

    std::cout << "Максимальное количество согласных: " << maxCons << "\n";
    std::cout << "Слова с максимальным числом согласных:\n";
    for (const auto& wi : allWords) {
        if (wi.consonants == maxCons) {
            std::cout << "  Номер " << wi.globalNum
                      << ": \"" << wi.word
                      << "\" (" << wi.consonants << " согласных)\n";
        }
    }
    std::cout << "\n";
}

// ─────────────────────────────────────────────
// Создание тестового файла F1
// ─────────────────────────────────────────────
void createTestFile(const std::string& fname) {
    std::ofstream f(fname);
    f << "Hello world\n";            // 2 слова — копируем
    f << "The quick brown fox\n";    // 4 слова — пропускаем
    f << "strengths\n";              // 1 слово  — пропускаем (8 согласных!)
    f << "Good morning\n";           // 2 слова — копируем
    f << "  \n";                     // пустая строка (0 слов) — пропускаем
    f << "sky is blue\n";            // 3 слова — пропускаем
    f << "my cat\n";                 // 2 слова — копируем
    f << "rhythms blend\n";          // 2 слова — копируем (много согласных)
}


int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    const std::string F1 = "f1.txt";
    const std::string F2 = "f2.txt";

    std::cout << "=== Задание 2: Обработка текстового файла ===\n\n";

    // Создаём тестовый файл
    createTestFile(F1);
    std::cout << "Тестовый файл \"" << F1 << "\" создан.\n\n";

    // А) Копирование строк с двумя словами
    std::cout << "--- Подзадание А: строки с ровно двумя словами ---\n";
    copyTwoWordLines(F1, F2);

    // Б) Поиск слов с максимальным числом согласных
    std::cout << "--- Подзадание Б: слова с максимальным числом согласных ---\n";
    findMaxConsonantWords(F1);

    // Выведем содержимое F2
    std::cout << "=== Содержимое файла \"" << F2 << "\" ===\n";
    std::ifstream f2(F2);
    std::string line;
    while (std::getline(f2, line))
        std::cout << "  " << line << "\n";

    return 0;
}