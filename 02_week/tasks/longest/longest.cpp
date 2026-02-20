#include <stdexcept>
#include <cstddef>

/*Функции для поиска наибольшей подпоследовательности*/

const char* FindLongestSubsequence(const char* begin, const char* end, size_t& count) {
    // Проверка на некорректные указатели
    if (!begin || !end || end < begin) {
        count = 0;
        return nullptr;
    }
    
    // Проверка на пустой диапазон
    if (begin == end) {
        count = 0;
        return nullptr;
    }
    
    const char* current_start = begin;
    const char* longest_start = begin;
    size_t current_length = 1;
    size_t max_length = 1;
    
    // Проходим по всему диапазону [begin, end)
    for (const char* it = begin + 1; it != end; ++it) {
        if (*it == *(it - 1)) {
            // Продолжение текущей подпоследовательности
            current_length++;
        } else {
            // Новая подпоследовательность
            current_start = it;
            current_length = 1;
        }
        
        // Обновление максимальной длины и указателя на начало
        if (current_length > max_length) {
            max_length = current_length;
            longest_start = current_start;
        }
    }
    
    count = max_length;
    return longest_start;
}

// Перегрузка для неконстантных указателей
char* FindLongestSubsequence(char* begin, char* end, size_t& count) {
    // Используем const-версию, а затем снимаем константность
    const char* result = FindLongestSubsequence(
        static_cast<const char*>(begin),
        static_cast<const char*>(end),
        count
    );
    return const_cast<char*>(result);
}