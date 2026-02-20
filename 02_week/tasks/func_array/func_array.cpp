/* Суммирует результаты всех операций из массива, примененных к a и b.*/
double ApplyOperations(double a, double b, double (**operations)(double, double)
    , size_t size) {

    double sum = 0.0;
    
    // Если массив пустой или size == 0, возвращаем 0.0
    if (operations == nullptr || size == 0) {
        return 0.0;
    }
    
    // Проход по всем операциям в массиве
    for (size_t i = 0; i < size; ++i) {
        // Проверка того, что операция не является nullptr
        if (operations[i] != nullptr) {
            // Выполнение операции и добавление результата к сумме
            sum += operations[i](a, b);
        }
        // Если операция равна nullptr, пропускаем её
    }
    
    return sum;
}