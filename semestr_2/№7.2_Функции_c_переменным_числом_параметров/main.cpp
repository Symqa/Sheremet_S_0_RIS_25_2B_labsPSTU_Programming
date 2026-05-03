#include <iostream>
#include <clocale>
#include <string>
#include <cstdarg>
#include <cmath>
using namespace std;

void my_dex(int count, ...) {
	va_list args;
	va_start(args, count);
	for (int i = 0; i < count; ++i) {
		string oct_number = va_arg(args, const char*);

		int index = oct_number.length()-1, dex_number = 0;
		for (char c : oct_number) {
			if (c == '.') continue;
			if (c == '-') {
				index--;
				continue;
			}
			int number = c - '0'; // '0' имеет код 48, '1' - 49, '2' - 50... -> из-за этого при операции "-" вычитаются числовые значения char и сдвиг работает корректно
			dex_number += number * (pow(8, index));
			index--;
		}
		if (oct_number[0] == '-') {
			dex_number*=(-1);
		}
		cout << dex_number << ' ';
	}
	va_end(args);
	

}

int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	system("chcp 1251");
	system("cls");
	cout << "8-ая система: -23, 10" << endl << "Вывод: ";
	my_dex(2, "-23", "10");

	return 0;
}