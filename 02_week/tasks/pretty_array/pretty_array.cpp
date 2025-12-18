#include <iostream>

/*Функция для форматированного вывода массива*/

void PrintArray(const int* begin, const int* end, size_t limit = 0) {
    std::cout << "[";
    
    if (begin == nullptr || end == nullptr || begin == end) {
        std::cout << "]\n";
        return;
    }
    
    bool reverse = end < begin;
    const int* current = begin;
    size_t count = 0;
    bool first = true;
    
    // Исправленное условие для обратного порядка
    while (reverse ? (current > end) : (current < end)) {
        // Если достигли лимита (limit > 0) и это не первый элемент в строке
        if (limit > 0 && count >= limit) {
            std::cout << ", ...\n ";
            count = 0;
            first = true;
        }
        
        // Первый элемент без запятой перед ним
        if (!first) {
            std::cout << ", ";
        }
        
        std::cout << *current;
        first = false;
        count++;
        
        // Если массив передан в обратном порядке 
        if (reverse) {
            current--;
        } else {
            current++;
        }
    }
    
    std::cout << "]\n";
}