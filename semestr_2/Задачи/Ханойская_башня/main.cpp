#include <iostream>
#include <clocale>
using namespace std;

int A[10], B[10], C[10];
int a = 0, b = 0, c = 0;

void print()
{
    cout << "\nA: ";
    for (int i = 0; i < a; i++)
        cout << A[i] << " ";

    cout << "\nB: ";
    for (int i = 0; i < b; i++)
        cout << B[i] << " ";

    cout << "\nC: ";
    for (int i = 0; i < c; i++)
        cout << C[i] << " ";

    cout << "\n-----------------\n";
}

void move(char from, char to)
{
    int disk;

    if (from == 'A') disk = A[--a];
    if (from == 'B') disk = B[--b];
    if (from == 'C') disk = C[--c];

    if (to == 'A') A[a++] = disk;
    if (to == 'B') B[b++] = disk;
    if (to == 'C') C[c++] = disk;

    cout << "Перенести диск " << disk << " с " << from << " на " << to << endl;

    print();
}

void hanoi(int n, char from, char to, char temp)
{
    if (n == 1)
    {
        move(from, to);
        return;
    }

    hanoi(n - 1, from, temp, to);
    move(from, to);
    hanoi(n - 1, temp, to, from);
}

int main()
{
    setlocale(LC_ALL, "ru-RU.UTF-8g");

    int n;

    cout << "Введите кол-во дисков: ";
    cin >> n;

    for (int i = n; i >= 1; i--)
    {
        A[a++] = i;
    }

    print();

    hanoi(n, 'A', 'C', 'B');

    return 0;
}