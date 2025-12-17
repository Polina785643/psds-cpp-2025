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
    char current_sequence_char = '\0';
    size_t count = 0;
    bool in_space_sequence = false;
    bool just_wrote_delimiter = false;
    
    for (size_t read_pos = 0; read_pos < size && array[read_pos] != '\0'; read_pos++) {
        char current_char = array[read_pos];
        
        // Обработка пробелов
        if (current_char == ' ') {
            // Если у нас есть незаписанная последовательность, записываем ее
            if (current_sequence_char != '\0') {
                array[write_pos++] = current_sequence_char;
                if (count > 1) {
                    if (count >= 10) {
                        array[write_pos++] = '0';
                    } else {
                        array[write_pos++] = '0' + count;
                    }
                }
                current_sequence_char = '\0';
                count = 0;
                just_wrote_delimiter = false;
            }
            
            // Добавляем разделитель для каждой группы пробелов
            if (!in_space_sequence) {
                array[write_pos++] = delimiter;
                in_space_sequence = true;
                just_wrote_delimiter = true;
            }
            continue;
        }
        
        // Не пробел - сбрасываем флаг последовательности пробелов
        in_space_sequence = false;
        just_wrote_delimiter = false;
        
        // Преобразование символа
        char transformed_char = current_char;
        
        if (std::isdigit(current_char)) {
            transformed_char = '*';
        } else if (std::isalpha(current_char)) {
            transformed_char = std::toupper(current_char);
        } else if (current_char != ' ') {
            transformed_char = '_';
        }
        
        // Обработка последовательностей символов
        if (current_char == prev_char) {
            count++;
        } else {
            // Запись предыдущей последовательности
            if (current_sequence_char != '\0') {
                array[write_pos++] = current_sequence_char;
                if (count > 1) {
                    if (count >= 10) {
                        array[write_pos++] = '0';
                    } else {
                        array[write_pos++] = '0' + count;
                    }
                }
            }
            // Начало новой последовательности
            prev_char = current_char;
            current_sequence_char = transformed_char;
            count = 1;
        }
    }
    
    // Запись последней последовательности (если не пробел)
    if (current_sequence_char != '\0') {
        array[write_pos++] = current_sequence_char;
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