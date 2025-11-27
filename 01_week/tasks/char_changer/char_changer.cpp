#include <cstddef>
#include <cctype>

/* Преобразует строку по правилам:
 - Повторяющиеся символы (кроме пробелов) заменяются на символ+число повторений
 - Цифры заменяются на '*'
 - Строчные латинские буквы не изменяются
 - Прописные латинские буквы заменяются на строчные
 - Последовательные пробелы заменяются на разделитель
 - Остальные символы заменяются на '_'
 Возвращает новую длину строки */

size_t CharChanger(char array[], size_t size, char delimiter) {
    if (size == 0) return 0; // Проверка на нулевую строку
    
    size_t write_pos = 0;  // Позиция записи в результирующий массив 
    char prev_char = '\0'; // Предыдущий преобразованный символ
    size_t count = 1;      // Счетчик повторений текущего символа
    
    // Цикл по строке пока не встретим нуль-терминатор
    for (size_t read_pos = 0; read_pos < size && array[read_pos] != '\0'; read_pos++) {
        char current_char = array[read_pos];
        
        // Преобразуем символ по правилам
        char transformed_char = current_char;
        
        // Цифры -> '*'
        if (std::isdigit(current_char)) { 
            transformed_char = '*';
        } 
        // Прописные буквы -> строчные
        else if (std::isupper(current_char)) { 
            transformed_char = std::tolower(current_char);
        }
        // Строчные латинские буквы остаются без изменений
        // Остальные символы -> '_' (кроме пробелов и латинских букв)
        else if (current_char != ' ' && !std::islower(current_char) && !std::isupper(current_char)) {
            transformed_char = '_';
        }
        
        // Обработка пробелов
        if (current_char == ' ') {
            // Добавляем разделитель только если он не дублируется
            if (write_pos == 0 || array[write_pos - 1] != delimiter) {
                array[write_pos++] = delimiter;
            }

            // Сброс состояния последовательности
            prev_char = '\0';
            count = 1;
            continue;
        }
        
        // Проверяем, продолжается ли последовательность
        if (transformed_char == prev_char) {
            count++;
        } else {
            // Записываем предыдущую последовательность
            if (prev_char != '\0') {
                // Записываем сам символ
                array[write_pos++] = prev_char;

                // Записываем число повторений
                if (count > 1) {
                    if (count >= 10) {
                        array[write_pos++] = '0';
                    } else {
                        array[write_pos++] = '0' + count;
                    }
                }
            }
            // Начинаем новую последовательность
            prev_char = transformed_char;
            count = 1;
        }
    }
    
    // Записываем последнюю последовательность
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

    // Проверка того, что строка правильно завершена нуль-терминатором
    if (write_pos < size) {
        array[write_pos] = '\0';
    }
    // Если буфер меньше чем строка
    else if (size > 0) {
        array[size - 1] = '\0';
    }
    
    return write_pos;
}