#include <vector>
#include <functional>

/*
Фильтрует вектор целых чисел по заданному предикату.
Оставляет в векторе только элементы, удовлетворяющие условию предиката,
сохраняя их исходный относительный порядок. Работает изменяя
переданный вектор.
*/

void Filter(std::vector<int>& vec, bool (*predicate)(int)) {
    // Проверка на nullptr предиката
    if (!predicate) {
        return;
    }

    // Индекс для записи подходящих элементов
    size_t write_index = 0;

    // Проходим по всем элементам вектора
    for (size_t i = 0; i < vec.size(); ++i) {
        // Если элемент удовлетворяет предикату, сохраняем его
        if (predicate(vec[i])) {
            vec[write_index] = vec[i];
            ++write_index;
        }
    }

    // Удаляем лишние элементы из конца вектора
    vec.resize(write_index);
}