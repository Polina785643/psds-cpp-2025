/*Функция для поиска последнего элемента удовлетворяющего условию*/

const int* FindLastElement(const int* begin, const int* end, bool (*predicate)(int)) {
    // Проверка на некорректные указатели
    if (begin == nullptr || end == nullptr) {
        return end;
    }
    
    // Проверка на некорректный диапазон
    if (begin > end) {
        return end;
    }
    
    const int* last_found = end;
    
    // Ищем с конца к началу для нахождения последнего элемента
    // Но можно идти и с начала, запоминая последний найденный
    const int* current = begin;
    while (current != end) {
        if (predicate(*current)) {
            last_found = current;
        }
        ++current;
    }
    
    return last_found;
}