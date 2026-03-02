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
			bool haveNumbers = false, haveLetters = false, haveSomethingElse = false;
			int startWordIndex = i;
			while (s[i] != ' ' && i < s.length()) {
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
			if (!(haveNumbers && haveLetters) || (haveSomethingElse)) {
				s.erase(startWordIndex - 1, i - startWordIndex + 1);
				i = startWordIndex;
			}
			i++;
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