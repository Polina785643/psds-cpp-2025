#include <iostream>

/*Функция для вывода представления целого числа в памяти*/

void PrintMemory(int value, bool reverse = false) {

    // Преобразование указателя на int в указатель на беззнаковые байты
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    // Вывод префикса шестнадцатеричного числа
    std::cout << "0x";
    
    // Массив для преобразования числового значения в шестнадцатеричный символ
    const char* hexDigits = "0123456789ABCDEF";
    
    if (reverse) {
        // Обратный порядок (big-endian): от старшего байта к младшему
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            // Получение текущего байта из памяти
            unsigned char byte = bytes[i];
            // Вывод 4 старших бита байта
            std::cout << hexDigits[byte >> 4];
            // Вывод 4 младших бита байта
            std::cout << hexDigits[byte & 0x0F];
        }
    } else {
        // Прямой порядок (little-endian): от младшего байта к старшему
        for (size_t i = 0; i < sizeof(value); ++i) {
            // Получение текущего байта из памяти
            unsigned char byte = bytes[i];
            // Вывод 4 старших бита байта
            std::cout << hexDigits[byte >> 4];
            // Вывод 4 младших бита байта
            std::cout << hexDigits[byte & 0x0F];
        }
    }
    // Завершение строки вывода
    std::cout << std::endl;
}

/*Функция для вывода представления числа с плавающей точкой в памяти*/

void PrintMemory(double value, bool reverse = false) {

    // Преобразование указателя на double в указатель на беззнаковые байты
    const unsigned char* bytes = reinterpret_cast<const unsigned char*>(&value);
    
    // Вывод префикса шестнадцатеричного числа
    std::cout << "0x";
    
    // Массив для преобразования числового значения в шестнадцатеричный символ
    const char* hexDigits = "0123456789ABCDEF";
    
    if (reverse) {
        // Обратный порядок (big-endian): от старшего байта к младшему
        for (int i = sizeof(value) - 1; i >= 0; --i) {
            // Получение текущего байта из памяти
            unsigned char byte = bytes[i];
            // Вывод 4 старших бита байта
            std::cout << hexDigits[byte >> 4];
            // Вывод 4 младших бита байта
            std::cout << hexDigits[byte & 0x0F];
        }
    } else {
        // Прямой порядок (little-endian): от младшего байта к старшему
        for (size_t i = 0; i < sizeof(value); ++i) {
            // Получение текущего байта из памяти
            unsigned char byte = bytes[i];
            // Вывод 4 старших бита байта
            std::cout << hexDigits[byte >> 4];
            // Вывод 4 младших бита байта
            std::cout << hexDigits[byte & 0x0F];
        }
    }
    // Завершение строки вывода
    std::cout << std::endl;
}