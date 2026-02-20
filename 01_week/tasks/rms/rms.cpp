#include <cmath>

double CalculateRMS(double values[], size_t size) {
    // Обработка случаев с пустым массивом или nullptr
    if (values == nullptr || size == 0) {
        return 0.0;
    }
    
    // Вычисление суммы квадратов элементов
    double sum_of_squares = 0.0;
    for (size_t i = 0; i < size; ++i) {
        sum_of_squares += values[i] * values[i];
    }
    
    // Вычисление среднеквадратического значения
    double mean_square = sum_of_squares / size;
    double rms = std::sqrt(mean_square);
    
    return rms;
}

