#include <vector>
#include <algorithm>

class Stack {
private:
    std::vector<int> data;

public:
    void Push(int value);          // добавляет элемент на верхушку стека
    bool Pop();                    // убирает элемент с верхушки стека, возвращает успех операции
    int& Top();                    // доступ к верхнему элементу (неконстантная версия)
    const int& Top() const;        // доступ к верхнему элементу (константная версия)
    bool Empty() const;            // проверяет, пуст ли стек
    size_t Size() const;           // возвращает количество элементов в стеке
    void Clear();                  // очищает стек
    void Swap(Stack& other);       // меняется содержимым с другим стеком
    
    bool operator==(const Stack& other) const;  // сравнение на равенство
    bool operator!=(const Stack& other) const;  // сравнение на неравенство
    
    Stack() = default;                         // конструктор по умолчанию
    Stack(const Stack&) = default;             // конструктор копирования
    Stack& operator=(const Stack&) = default;  // оператор присваивания
};

// Реализации методов

// Добавляет элемент на верхушку стека
void Stack::Push(int value) {
    data.push_back(value);
}

// Убирает элемент с верхушки стека, возвращает true если операция выполнена
bool Stack::Pop() {
    if (data.empty()) {
        return false;
    }
    data.pop_back();
    return true;
}

// Возвращает ссылку на верхний элемент стека, для пустого стека - статическую переменную
int& Stack::Top() {
    if (data.empty()) {
        static int dummy = 0;
        return dummy;
    }
    return data.back();
}

// Константная версия метода Top()
const int& Stack::Top() const {
    if (data.empty()) {
        static const int dummy = 0;
        return dummy;
    }
    return data.back();
}

// Проверяет, пуст ли стек
bool Stack::Empty() const {
    return data.empty();
}

// Возвращает количество элементов в стеке
size_t Stack::Size() const {
    return data.size();
}

// Очищает стек
void Stack::Clear() {
    data.clear();
}

// Меняется содержимым с другим стеком
void Stack::Swap(Stack& other) {
    data.swap(other.data);
}

// Сравнивает два стека на равенство
bool Stack::operator==(const Stack& other) const {
    return data == other.data;
}

// Сравнивает два стека на неравенство
bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}