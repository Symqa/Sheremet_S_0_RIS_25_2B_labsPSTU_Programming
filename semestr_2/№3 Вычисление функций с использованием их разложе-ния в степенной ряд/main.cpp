#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

double f(double &x) {
	return exp(x);
}

double Sn(const int &N, double &x, double start_value) {
	double a_n = start_value;
	double s = start_value;
	for (int i = 1; i <= N; i++) {
		a_n = (a_n * x / i);
		s += a_n;
	}
	return s;
}

double Sn(double &x, double start_value) {
	double a_n = start_value;
	double s = start_value;
	const double Eps = 1e-4;
	int n = 1;
	while ((a_n * x / n) >= Eps) {
		a_n = (a_n * x / n);
		s += a_n;
		n++;
	}
	cout << "S=" << s << " (n=" << n << ")" << endl;
	return 0;
}
int main() {
	const int N = 15, k = 10;
	double a = 1, b = 2;
	double step = (b-a)/k;
	double x = a;
	setlocale(LC_ALL, "ru");

	cout << endl << "a)" << endl;

	while (x <= b + 1e-12) {
		cout << "x=" << x << ": " << "f(x)=" << f(x) << ' ' << "S=" << Sn(N, x, 1) << endl;
		x+=step;
	}
	x = a;
	cout << endl << "á)" << endl;
	while (x <= b + 1e-12) {
		cout << "x=" << x << ": " << "f(x)=" << f(x) << ' ';
		Sn(x, 1);
		x+=step;
	}
	cin >> a;
	return 0;
}