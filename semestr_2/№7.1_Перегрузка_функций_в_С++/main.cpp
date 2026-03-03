#include <iostream>
#include <cmath>
#include <clocale>
using namespace std;

int my_pow(int &x, int degree) {
	int start_value = x;
	for (int i = 1; i < degree; i++) {
		x*=start_value;
	}
	return x;
}

long long my_pow(long long &x, int degree) {
	long long start_value = x;
	for (int i = 1; i < degree; i++) {
		x *= start_value;
	}
	return x;
}

float my_pow(float& x, int degree) {
	float start_value = x;
	for (int i = 1; i < degree; i++) {
		x *= start_value;
	}
	return x;
}

double my_pow(double& x, int degree) {
	double start_value = x;
	for (int i = 1; i < degree; i++) {
		x *= start_value;
	}
	return x;
}

float f(float x, int n, const int A) {
	return my_pow(x, n) - A;
}

double f(double x, int n, const int A) {
	return my_pow(x, n) - A;
}

float df(float x, int n) {
	return n*my_pow(x, n-1);
}

double df(double x, int n) {
	return n * my_pow(x, n - 1);
}

float root(float& x, int degree, const double Eps) {
	if (x < 0 && degree % 2 == 0) {
		cout << "Невозможно вычислить четный корень из отрицательного числа" << endl;
		return 0;
	}
	else if (x == 0) return 0;
	const int A = x;
	float x_n = x - f(x, degree, A)/df(x, degree);
	while (abs(x_n - x) > Eps) {
		x = x_n;
		x_n = x_n - f(x_n, degree, A)/df(x_n, degree);
	}
	return x_n;
	
	
}

double root(double& x, int degree, const double Eps) {
	if (x < 0 && degree % 2 == 0) {
		cout << "Невозможно вычислить четный корень из отрицательного числа" << endl;
		return 0;
	}
	else if (x == 0) return 0;
	const int A = x;
	double x_n = x - f(x, degree, A) / df(x, degree);
	while (abs(x_n - x) > Eps) {
		x = x_n;
		x_n = x_n - f(x_n, degree, A) / df(x_n, degree);
	}
	return x_n;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int integer;
	long long long_integer;
	float float_number;
	double double_number;
	int integer_degree, long_degree, float_degree, double_degree;

	cout << "Введите целое число и целую степень через пробел: " << endl;
	cin >> integer >> integer_degree;
	cout << "Введите большое целое число и целую степень через пробел: " << endl;
	cin >> long_integer >> long_degree;
	cout << "Введите дробное число и целую степень через пробел: " << endl;
	cin >> float_number >> float_degree;
	cout << "Введите более точное дробное число и целую степень через пробел: " << endl;
	cin >> double_number >> double_degree;
	cout << endl << endl;

	const double Eps = 1e-6;

	cout << "Тип int: " << integer << " в степени 4 = " << my_pow(integer, 4) << endl;
	cout << "Тип long long: " << long_integer << " в степени 2 = " << my_pow(long_integer, 2) << endl;
	cout << "Тип float: " << float_number << " в корне 2-ой степени = " << root(float_number, 2, Eps) << endl;
	cout << "Тип double: " << double_number << " в корне 3-ей степени = " << root(double_number, 3, Eps) << endl;

	return 0;
}