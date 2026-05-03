#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
using namespace std;

void getStringMaxA(ifstream &file) {
	string row, max_string = "";
	int number = 1, max_number = 1, max_count = 1;
	if (file.is_open()) {
		while (getline(file, row)) {
			int count_a = 0;
			for (char c : row) {
				if (c == 'а' || c == 'А' || c == 'a' || c == 'A') {
					count_a++;
				}
			}
			if (count_a > max_count) {
				max_count = count_a;
				max_number = number;
				max_string = row;
			}
			number++;
		}
		cout << endl << "2) Максимальное кол-во А:" << endl << endl;
		cout << "Строка под номером: " << max_number << endl;
		cout << "Строка: " << max_string << endl;
		cout << "Количество А: " << max_count << endl;
	}
	else {
		cout << "Невозможно открыть файл для поиска максимального кол-ва А" << endl;
	}
	
	
}

int main() {
	setlocale(LC_ALL, "ru-RU.UTF-8");
	ifstream fin("F1.txt"); // чтение
	ofstream fout("F2.txt"); // запись
	string row;

	if (fin.is_open()) {
		int n1, n2;
		cout << endl << "Введите промежуток (номера двух строк) через пробел, которые необходимо скопировать: ";
		cin >> n1 >> n2;

		int act_number = 1;
		bool islast = false;
		cout << endl << "1) Найденные строки: " << endl;
		while (getline(fin, row)) {
			if (act_number > n1 && act_number < n2) {
				char last_symbol = row[row.length() - 1];
				if (last_symbol == 'а' || last_symbol == 'А' || last_symbol == 'a' || last_symbol == 'A') {
					fout << row << '\n';
					cout << row << endl;
				}
			}
			else if (act_number == n2) {
				islast = true;
			}
			act_number++;
		}
	}
	else {
		cout << "Ошибка при открытии файла F1.txt" << endl; 
	}
	
	fout.close();
	fin.close();
	ifstream f2in("F2.txt");
	getStringMaxA(f2in);
	f2in.close();

	return 0;
}