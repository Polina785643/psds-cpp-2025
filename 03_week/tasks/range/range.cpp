#include <vector>
#include <stdexcept>

/*Генерирует последовательность целых чисел в указанном диапазоне.*/

std::vector<int> Range(int from, int to, int step) {
    // Обработка некорректных параметров
    if (step == 0) {
        return std::vector<int>(); //пустой вектор
    }
    
    // Если шаг положительный, но from >= to - диапазон пуст
    if (step > 0 && from >= to) {
        return std::vector<int>();
    }
    
    // Если шаг отрицательный, но from <= to - диапазон пуст
    if (step < 0 && from <= to) {
        return std::vector<int>();
    }
    
    // Вычисляем количество элементов заранее, 
    // чтобы сразу выделить необходимую память 

    int count = 0;
    
    if (step > 0) { // для возрастающего диапазона
        count = (to - from + step - 1) / step;
    } else {        // для убывающего диапазона
        count = (to - from + step + 1) / step;
    }
    
    // Создаем вектор с нужной емкостью
    std::vector<int> result;
    result.reserve(count); // выделили память под count элементов
    
    // Заполняем вектор значениями
    if (step > 0) {
        for (int i = from; i < to; i += step) {
            result.push_back(i);
        }
    } else {
        for (int i = from; i > to; i += step) {
            result.push_back(i);
        }
    }
    
    return result;
}


//Функция с шагом по умолчанию (step = 1)
std::vector<int> Range(int from, int to) {
    return Range(from, to, 1);
}