#include <vector>

/*Возвращает вектор уникальных элементов из исходного отсортированного вектора*/

std::vector<int> Unique(const std::vector<int>& sorted_vec) {
    if (sorted_vec.empty()) {
        return std::vector<int>();
    }
    
    std::vector<int> result;
    result.reserve(sorted_vec.size()); // резервируем максимально возможный размер
    
    result.push_back(sorted_vec[0]);
    
    for (size_t i = 1; i < sorted_vec.size(); ++i) {
        if (sorted_vec[i] != sorted_vec[i - 1]) {
            result.push_back(sorted_vec[i]);
        }
    }
    
    // Устанавливаем емкость, равную размеру
    result.shrink_to_fit();
    
    return result;
}