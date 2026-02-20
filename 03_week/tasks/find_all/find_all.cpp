#include <vector>

/*Функция, которая возвращает контейнер позиций всех 
элементов, удовлетворяющих предикату.*/

std::vector<size_t> FindAll(const std::vector<int>& vec
    , bool (*predicate)(int)) {
        
    std::vector<size_t> result;
    
    // Коррекность предиката
    if (!predicate) return result;  
    
    for (size_t i = 0; i < vec.size(); ++i) {
        if (predicate(vec[i])) {
            result.push_back(i);
        }
    }
    
    result.shrink_to_fit(); //подгоняем под количество элементов 
    return result;
}