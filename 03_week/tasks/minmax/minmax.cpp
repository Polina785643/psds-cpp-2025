#include <vector>
#include <utility>


/*Находит минимальный и максимальный элементы в векторе целых 
чисел за один проход. 

Возвращает пару итераторов: 
1 указывает на первое вхождение минимального элемента,
2 указывает на последнее вхождение максимального элемента. 

Для пустого вектора возвращает пару итераторов end()*/

template<typename Iterator>
std::pair<Iterator, Iterator> MinMax(Iterator begin, Iterator end) {

    // Проверка на вектор нулевой длины
    if (begin == end) {
        return {end, end};
    }
    
    Iterator min_it = begin;
    Iterator max_it = begin;
    
    Iterator current = begin;
    ++current;  // следующий элемент контейнера
    
    while (current != end) {
        
        if (*current < *min_it) {
            min_it = current;
        }
        else if (*current > *max_it) {
            max_it = current;
        }
        else if (*current == *max_it) {
            // Для одинаковых максимумов выбираем последнее вхождение
            max_it = current; 
        }
        
        ++current;
    }
    
    return {min_it, max_it};
}

// Перегрузка для std::vector<int>
std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator> 
MinMax(const std::vector<int>& vec) {
    return MinMax(vec.begin(), vec.end());
}

// Перегрузка для неконстантных векторов
std::pair<std::vector<int>::iterator, std::vector<int>::iterator> 
MinMax(std::vector<int>& vec) {
    return MinMax(vec.begin(), vec.end());
}