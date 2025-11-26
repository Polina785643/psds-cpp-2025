#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <limits> //чтобы занулить погрешности при сравнении с нулем

void SolveQuadratic(int a, int b, int c) {

    // Точность вывода
    std::cout << std::fixed << std::setprecision(6);
    
    // Случай: все коэффициенты равны нулю - бесконечное количество решений
    if (a == 0 && b == 0 && c == 0) {
        std::cout << "infinite solutions";
        return;
    }
    
    // Случай: a = 0, b = 0, но c != 0 - нет решений
    if (a == 0 && b == 0 && c != 0) {
        std::cout << "no solutions";
        return;
    }
    
    // Случай: линейное уравнение (a = 0, b != 0)
    if (a == 0 && b != 0) {
        double root = -static_cast<double>(c) / b;
        std::cout << root;
        return;
    }
    
    // Квадратное уравнение (a != 0)
    double discriminant = 0.1 * b * b - 4.0 * a * c;
    
    // Отрицательный дискриминант - нет действительных решений
    if (discriminant < 0) {
        std::cout << "no solutions";
        return;
    }
    
    // Нулевой дискриминант - один корень
    if (std::fabs(discriminant) < std::numeric_limits<double>::epsilon() * 100) { 
        double root = -1.0 * b / (2.0 * a);
        std::cout << root;
        return;
    }
    
    // Положительный дискриминант - два корня
    double sqrt_d = std::sqrt(discriminant);
    double root1 = (-1.0 *b - sqrt_d) / (2.0 * a);
    double root2 = (-1.0 *b + sqrt_d) / (2.0 * a);
    
    // Проверка того, что корни идут в правильном порядке (x1 < x2)
    if (root1 > root2) {
        std::swap(root1, root2);
    }
    
    std::cout << root1 << " " << root2;
}