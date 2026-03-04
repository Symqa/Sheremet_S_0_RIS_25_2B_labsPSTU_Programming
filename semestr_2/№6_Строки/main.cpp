#include <iostream>
#include <clocale>
#include <string>
#include <chrono>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");
    system("chcp 1251");
    system("cls");
    string s;
    cout << "Для завершения программы впишите: 0" << endl << endl;
    cout << "Введите строку: ";
    getline(cin, s);
    while (s != "0") {
        auto start = std::chrono::high_resolution_clock::now();

        int i = 0;
        while (i < s.length()) {
            // Пропускаем пробелы в начале
            while (i < s.length() && s[i] == ' ') i++;
            if (i >= s.length()) break;

            int startWordIndex = i;
            bool haveNumbers = false, haveLetters = false, haveSomethingElse = false;

            // Собираем слово до пробела или конца строки
            while (i < s.length() && s[i] != ' ') {
                unsigned char c = s[i];
                if (c >= '0' && c <= '9') {
                    haveNumbers = true;
                }
                else if ((c >= 192 && c <= 255) || c == 184 || c == 168) {
                    haveLetters = true;
                }
                else if (c >= 'A' && c <= 'z') {
                    haveLetters = true;
                }
                else {
                    haveSomethingElse = true;
                }
                i++;
            }
            // i указывает на позицию после слова (пробел или конец строки)

            // Проверяем условие: не должно быть одновременно цифр и букв, или есть другие символы
            if (!(haveNumbers && haveLetters) || haveSomethingElse) {
                // Слово не подходит – удаляем его
                if (startWordIndex == 0) {
                    // Слово в начале строки – удаляем только слово
                    s.erase(startWordIndex, i - startWordIndex);
                    i = 0; // начинаем проверять сначала
                }
                else {
                    // Удаляем предшествующий пробел вместе со словом
                    s.erase(startWordIndex - 1, i - startWordIndex + 1);
                    i = startWordIndex - 1; // начинаем проверку с позиции перед удалённым пробелом
                }
            }
            // Если слово подходит, i уже стоит на позиции после слова, и в следующей итерации пробелы будут пропущены
        }

        if (s.length() == 0) {
            cout << "Слов, удовлетворяющих условию не осталось :( ";
        }
        else {
            cout << "Выходная строка: " << s;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> diff = end - start;
        std::cout << endl << "Время выполнения: " << diff.count() << " секунд" << endl << endl;

        cout << "Введите строку: ";
        getline(cin, s);
    }
    return 0;
}