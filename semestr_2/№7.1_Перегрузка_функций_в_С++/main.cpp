#include <iostream>
using namespace std;

void my_pow(int &n, int degree) {
	for (int i = 1; i < degree; i++) {
		n*=n;
	}
}

void my_pow(long long &n, int degree) {
	for (int i = 1; i < degree; i++) {
		n*=n;
	}
}

void root(float& n, int degree) {

}

void root(double& n, int degree) {

}

int main() {
	int integer = 10;
	long long integer_long = 100;
	float float_number = 27.0;
	my_pow(integer, 2);
	my_pow(integer_long, 2);
	root(float_number, 3);
	cout << integer << ' ' << integer_long << endl;
	cout << float_number;
	return 0;
}