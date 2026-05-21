#include <iostream>
#include <cstdarg>   // va_list, va_start, va_arg, va_end
#include <cmath>     // sqrt
 

int circuit(double R, int count, ...) {
    va_list args;
    va_start(args, count);
 
    int result = 0;
    for (int i = 0; i < count; ++i) {
        int x = va_arg(args, int);
        int y = va_arg(args, int);
 
        // Точка (x,y) лежит на окружности, если x^2 + y^2 == R^2
        double dist_sq = static_cast<double>(x) * x + static_cast<double>(y) * y;
        double R_sq    = R * R;
 
        // Сравниваем с допуском (на случай вещественного R)
        if (std::abs(dist_sq - R_sq) < 1e-9) {
            std::cout << "  Точка (" << x << ", " << y
                      << ") лежит на окружности\n";
            ++result;
        } else {
            std::cout << "  Точка (" << x << ", " << y
                      << ") НЕ лежит на окружности (dist^2="
                      << dist_sq << ", R^2=" << R_sq << ")\n";
        }
    }
 
    va_end(args);
    return result;
}
 
int main() {
    setlocale(LC_ALL, "ru-RU.UTF-8");
    std::cout << "=== Задание 1: Функция circuit ===\n\n";
 
    // --- Тест 1 ---
    double R1 = 10.0;
    std::cout << "Окружность R = " << R1 << ":\n";
    int cnt1 = circuit(R1, 3,  6, 8,  3, 4,  -6, 8);
    std::cout << "Итого на окружности: " << cnt1 << " из 3\n\n";
 
    // --- Тест 2 (из условия задания) ---
    double R2 = std::sqrt(90.0);
    std::cout << "Окружность R = sqrt(90) ≈ " << R2 << ":\n";
    int cnt2 = circuit(R2, 3,  3, 9,  11, 5,  -4, 7);
    std::cout << "Итого на окружности: " << cnt2 << " из 3\n\n";
 
    // --- Тест 3: одна точка ---
    double R3 = 5.0;
    std::cout << "Окружность R = " << R3 << ", одна точка (3,4):\n";
    int cnt3 = circuit(R3, 1,  3, 4);
    std::cout << "Итого на окружности: " << cnt3 << " из 1\n\n";
 
    // --- Тест 4: нет точек ---
    std::cout << "Окружность R = 7, нет точек:\n";
    int cnt4 = circuit(7.0, 0);
    std::cout << "Итого на окружности: " << cnt4 << " из 0\n";
 
    return 0;
}