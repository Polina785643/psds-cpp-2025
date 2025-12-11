#include <cmath>
#include <vector>

struct DataStats {
    double avg = 0.0;  // среднее значение (average)
    double sd = 0.0;   // стандартное отклонение (standard deviation)
};

// Вычисление среднего и суммы квадратов отклонений
DataStats CalculateDataStats(const std::vector<int>& data) {
    DataStats result;
    size_t n = data.size();  // размер вектора
    
    if (n == 0) {
        return result;
    }

    double mean = 0.0;
    double s = 0.0;  // сумма для дисперсии

    // Алгоритм Уэлфорда
    
    for (size_t i = 0; i < n; ++i) {
        double x = static_cast<double>(data[i]);
        
        // Обновление среднего
        double old_mean = mean;
        mean = old_mean + (x - old_mean) / (i + 1);
        
        // Обновление суммы квадратов отклонений
        s = s + (x - old_mean) * (x - mean);
    }
    
    result.avg = mean;
    
    if (n > 1) {
        result.sd = std::sqrt(s / n);
    } else {
        result.sd = 0.0;
    }
    
    return result;
}