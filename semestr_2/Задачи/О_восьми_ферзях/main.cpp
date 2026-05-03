#include <iostream>
#include <vector>
#include <cstdlib>
#include <clocale>

using namespace std;

const int BOARD_SIZE = 8;  // размер доски (8×8)

// Проверка, можно ли поставить ферзя в текущую строку на указанный столбец
bool isSafe(const vector<int>& board, int row, int col) {
    for (int prevRow = 0; prevRow < row; ++prevRow) {
        int prevCol = board[prevRow];
        // Если ферзь уже стоит в том же столбце или на одной диагонали — нельзя
        if (prevCol == col || abs(prevCol - col) == abs(prevRow - row))
            return false;
    }
    return true;
}

// Вывод шахматной доски с ферзями
void printBoard(const vector<int>& board) {
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            if (board[row] == col)
                cout << " Q ";
            else
                cout << " . ";
        }
        cout << endl;
    }
    cout << endl;
}

// Рекурсивная функция для расстановки ферзей
void solveNQueens(vector<int>& board, int row, int& solutionCount) {
    // Если все строки заполнены — нашли решение
    if (row == BOARD_SIZE) {
        cout << "Решение №" << ++solutionCount << ":\n";
        printBoard(board);
        cout << "Нажмите Enter для продолжения...";
        cin.get();   // ожидание нажатия Enter для пошагового просмотра
        return;
    }

    // Пробуем поставить ферзя в каждый столбец текущей строки
    for (int col = 0; col < BOARD_SIZE; ++col) {
        if (isSafe(board, row, col)) {
            board[row] = col;          // ставим ферзя
            solveNQueens(board, row + 1, solutionCount); // переходим к следующей строке
            
        }
    }
}

int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");

    vector<int> board(BOARD_SIZE, -1);  // инициализируем доску: -1 означает, что ферзь ещё не поставлен
    int totalSolutions = 0;

    cout << "Поиск всех решений для " << BOARD_SIZE << " ферзей...\n\n";
    solveNQueens(board, 0, totalSolutions);

    cout << "Всего найдено решений: " << totalSolutions << endl;
    return 0;
}