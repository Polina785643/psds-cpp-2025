#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>
#include <limits> // чтобы занулить погрешности при сравнении с нулем

void SolveQuadratic(int a, int b, int c) {
    std::ostringstream oss;
    
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
        // Убираем лишние нули и .0 если число целое
        if (root == std::floor(root)) {
            std::cout << static_cast<int>(root);
        } else {
            std::cout << std::setprecision(6) << root;
        }
        return;
    }
    
    // Квадратное уравнение (a != 0)
    double discriminant = static_cast<double>(b) * b - 4.0 * a * c;
    
    // Отрицательный дискриминант - нет действительных решений
    if (discriminant < -std::numeric_limits<double>::epsilon() * 100) {
        std::cout << "no solutions";
        return;
    }
    
    // Нулевой дискриминант - один корень
    if (std::fabs(discriminant) < std::numeric_limits<double>::epsilon() * 100) {
        double root = -static_cast<double>(b) / (2.0 * a);
        // Убираем отрицательный ноль
        if (std::fabs(root) < std::numeric_limits<double>::epsilon() * 100) root = 0.0;
        
        if (root == std::floor(root)) {
            std::cout << static_cast<int>(root);
        } else {
            std::cout << std::setprecision(6) << root;
        }
        return;
    }
    
    // Положительный дискриминант - два корня
    double sqrt_d = std::sqrt(discriminant);
    double root1 = (-static_cast<double>(b) - sqrt_d) / (2.0 * a);
    double root2 = (-static_cast<double>(b) + sqrt_d) / (2.0 * a);
    
    // Убираем отрицательные нули
    if (std::fabs(root1) < std::numeric_limits<double>::epsilon() * 100) root1 = 0.0;
    if (std::fabs(root2) < std::numeric_limits<double>::epsilon() * 100) root2 = 0.0;
    
    // Проверка того, что корни идут в правильном порядке (x1 < x2)
    if (root1 > root2) {
        std::swap(root1, root2);
    }
    
    // Форматируем вывод
    if (root1 == std::floor(root1)) {
        std::cout << static_cast<int>(root1);
    } else {
        std::cout << std::setprecision(6) << root1;
    }
    
    std::cout << " ";
    
    if (root2 == std::floor(root2)) {
        std::cout << static_cast<int>(root2);
    } else {
        std::cout << std::setprecision(6) << root2;
    }
}