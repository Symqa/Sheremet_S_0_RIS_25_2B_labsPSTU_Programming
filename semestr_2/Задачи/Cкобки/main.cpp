#include <iostream>
#include <clocale>
#include <string>
using namespace std;

bool checkText(string s) {
	int balance = 0;
	for (char c : s) {
		if (c == '(') {
			balance++;
		}
		else if (c == ')') {
			if (balance == 0) return false;
			balance--;
		}
	}
	return balance == 0;
}

int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	string s;
	cout << "Введите текст со скобочками: ";
	getline(cin, s);
	cout << boolalpha << checkText(s);


	return 0;
}