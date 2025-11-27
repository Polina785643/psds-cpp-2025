#include <iostream>

/*функцию, преобразующая целое число 
и размер в байтах и выводит на экран битовое представление числа в формате 0bXXXX'XXXX.*/
void PrintBits(long long value, size_t bytes) {
    // Проверка допустимости размера
    if (bytes == 0 || bytes > 8) {
        return;
    }
    
    // Вывод префикс
    std::cout << "0b";
    
    // Цикл по всем битам от старшего к младшему
    for (int byte = bytes - 1; byte >= 0; --byte) {

        // Текущий байт
        unsigned char current_byte = (value >> (byte * 8)) & 0xFF;
        
        // Вывод битов текущего байта
        for (int bit = 7; bit >= 0; --bit) {
            // Текущий бит (7-й бит - старший)
            unsigned char current_bit = (current_byte >> bit) & 1;
            std::cout << (current_bit ? '1' : '0');
            
            // Добавление апострофа после 4-го бита в каждом байте
            if (bit == 4) {
                std::cout << "'";
            }
        }
        
        // Добавление апострофа между байтами (кроме последнего)
        if (byte > 0) {
            std::cout << "'";
        }
    }
    
    // Завершение вывода
    std::cout << "\n";
}