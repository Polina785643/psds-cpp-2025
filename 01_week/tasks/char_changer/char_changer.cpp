#include <cstddef>
#include <cctype>

/* Преобразует строку по правилам:
 - Повторяющиеся символы (кроме пробелов) заменяются на символ+число повторений
 - Цифры заменяются на '*'
 - Все латинские буквы преобразуются в прописные
 - Последовательные пробелы заменяются на разделитель
 - Остальные символы заменяются на '_'
 Возвращает новую длину строки */

size_t CharChanger(char array[], size_t size, char delimiter) {
    if (size == 0) return 0;
    
    size_t write_pos = 0;
    char prev_char = '\0';
    size_t count = 1;
    
    for (size_t read_pos = 0; read_pos < size && array[read_pos] != '\0'; read_pos++) {
        char current_char = array[read_pos];
        char transformed_char = current_char;
        
        // Цифры -> '*'
        if (std::isdigit(current_char)) {
            transformed_char = '*';
        }
        // Латинские буквы -> прописные
        else if (std::isalpha(current_char)) {
            transformed_char = std::toupper(current_char);
        }
        // Остальные символы -> '_' (кроме пробелов)
        else if (current_char != ' ') {
            transformed_char = '_';
        }
        
        // Пробелы -> разделитель
        if (current_char == ' ') {
            if (write_pos == 0 || array[write_pos - 1] != delimiter) {
                array[write_pos++] = delimiter;
            }
            prev_char = '\0';
            count = 1;
            continue;
        }
        
        // Обработка последовательностей символов
        if (transformed_char == prev_char) {
            count++;
        } else {
            // Запись предыдущей последовательности
            if (prev_char != '\0') {
                array[write_pos++] = prev_char;
                if (count > 1) {
                    if (count >= 10) {
                        array[write_pos++] = '0';
                    } else {
                        array[write_pos++] = '0' + count;
                    }
                }
            }
            // Начало новой последовательности
            prev_char = transformed_char;
            count = 1;
        }
    }
    
    // Запись последней последовательности
    if (prev_char != '\0') {
        array[write_pos++] = prev_char;
        if (count > 1) {
            if (count >= 10) {
                array[write_pos++] = '0';
            } else {
                array[write_pos++] = '0' + count;
            }
        }
    }
    
    // Завершение строки
    if (write_pos < size) {
        array[write_pos] = '\0';
    } else if (size > 0) {
        array[size - 1] = '\0';
    }
    
    return write_pos;
}