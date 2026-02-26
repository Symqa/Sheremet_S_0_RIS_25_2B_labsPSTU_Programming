#include <iostream>
#include <clocale>
#include <cmath>
using namespace std;

double f(double &x) {
	return exp(x);
}

double Sn(int &N, double &x) {
	double a_n = x;
	double s = x;
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
	int n;
	double x;
	setlocale(LC_ALL, "ru");
	cout << "¬ведите N: ";
	cin >> n;
	cout << "¬ведите x: ";
	cin >> x;
	setlocale(LC_ALL, "ru");

	cout << "x=" << x << ": " << "f(x)=" << f(x) << ' ' << "S=" << Sn(n, x) << endl;
	
	cin >> x;
	return 0;
}