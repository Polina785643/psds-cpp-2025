#include <vector>
#include <stack>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class Queue {
private:
    // Входной стек - элементы добавляются в конец
    std::vector<int> input_stack;
    // Выходной стек - элементы извлекаются из начала
    std::vector<int> output_stack;
    
    // Перекладывает элементы из input_stack в output_stack
    void TransferElements();

public:
    // Конструкторы
    Queue();  // конструктор по умолчанию
    Queue(std::stack<int> s);  // конструктор от std::stack<int>
    Queue(const std::vector<int>& vec);  // конструктор от std::vector<int>
    Queue(std::initializer_list<int> init_list);  // конструктор от initializer_list
    explicit Queue(size_t capacity);  // конструктор от размера с резервированием
    
    // Основные методы
    void Push(int value);  // добавляет элемент в конец очереди
    bool Pop();  // убирает элемент из начала очереди, возвращает успех операции
    
    int& Front();  // доступ на чтение и запись к элементу в начале очереди
    const int& Front() const;  // константная версия Front
    
    int& Back();  // доступ на чтение и запись к элементу в конце очереди
    const int& Back() const;  // константная версия Back
    
    bool Empty() const;  // проверка очереди на отсутствие элементов
    size_t Size() const;  // возвращает количество элементов в очереди
    void Clear();  // очищает очередь
    void Swap(Queue& other);  // меняется элементами с другой очередью
    
    // Операторы сравнения
    bool operator==(const Queue& other) const;  // сравнение очередей на равенство
    bool operator!=(const Queue& other) const;  // сравнение очередей на неравенство
};


// Вспомогательный метод: перекладывает элементы из input_stack в output_stack
void Queue::TransferElements() {
    // Если input_stack пуст, ничего не делаем
    if (input_stack.empty()) return;
    
    // Оптимизация: reserve перед копированием
    output_stack.reserve(output_stack.size() + input_stack.size());
    
    // Копируем в обратном порядке
    for (auto it = input_stack.rbegin(); it != input_stack.rend(); ++it) {
        output_stack.push_back(*it);
    }
    
    // Очищаем input_stack
    input_stack.clear();
}

// Конструктор по умолчанию: создает пустую очередь
Queue::Queue() = default;

// Конструктор от std::stack<int> 
Queue::Queue(std::stack<int> s) {
    // Стек: последний добавленный наверху
    // Нужно создать очередь в том же порядке, что и в стеке при извлечении
    std::vector<int> temp;
    while (!s.empty()) {
        temp.push_back(s.top());  // берем сверху
        s.pop();
    }
    
    // Помещаем в input_stack в обратном порядке для сохранения 
    // или в output_stack с правильным порядком
    for (auto it = temp.rbegin(); it != temp.rend(); ++it) {
        input_stack.push_back(*it);  
    }
}

// Конструктор от std::vector<int>
Queue::Queue(const std::vector<int>& vec) {
    // Вектор уже в правильном порядке FIFO
    input_stack = vec;  
}

// Конструктор от std::initializer_list<int> 
Queue::Queue(std::initializer_list<int> init_list) {
    // initializer_list уже в правильном порядке 
    input_stack.assign(init_list.begin(), init_list.end());  // {1, 2, 3, 4, 5}
}

// Конструктор от размера очереди
// Выделяет достаточное количество памяти для работы с очередью заданного размера без реаллокации
// explicit запрещает неявное преобразование: Queue q = 100; не сработает, нужно Queue q(100);
Queue::Queue(size_t capacity) {
    // Резервируем память для обоих стеков примерно поровну
    // +1 так как мы резервируем достаточно при нечетной capacity
    input_stack.reserve(capacity / 2 + 1);
    output_stack.reserve(capacity / 2 + 1);
}

// Метод Push: добавляет элемент в конец очереди
void Queue::Push(int value) {
    // Все новые элементы добавляются в конец input_stack
    input_stack.push_back(value);
}

// Метод Pop: убирает элемент из начала очереди
// Возвращает true, если элемент был удален, false если очередь была пуста
bool Queue::Pop() {
    // Если очередь пуста, операция невозможна
    if (Empty()) {
        return false;
    }

    // Если output_stack пуст, нужно переложить элементы из input_stack
    if (output_stack.empty()) {
        TransferElements();
    }

    // Удаляем последний элемент из output_stack (он же первый элемент очереди)
    output_stack.pop_back();
    return true;
}

// Метод Front : доступ на чтение и запись к первому элементу
// Возвращает ссылку на первый элемент очереди
int& Queue::Front() {

    // Если output_stack пуст, перекладываем элементы
    if (output_stack.empty()) {
        TransferElements();
    }

    // Первый элемент очереди - последний элемент output_stack
    return output_stack.back();
}

// Метод Front (константная версия) : доступ только на чтение к первому элементу
// Возвращает константную ссылку на первый элемент очереди
// Не модифицирует объект
const int& Queue::Front() const {
    
    // Константная версия не может вызывать TransferElements()
    // Должна работать с текущим состоянием объекта
    if (output_stack.empty()) {
        // Если output_stack пуст, элементы находятся в input_stack
        // Первый элемент очереди - первый элемент input_stack
        return input_stack.front();
    }
    
    // Иначе первый элемент - последний в output_stack
    return output_stack.back();
}

// Метод Back : доступ на чтение и запись к последнему элементу
// Возвращает ссылку на последний добавленный элемент
int& Queue::Back() {

    // Последний элемент очереди может находиться:
    // 1. В input_stack, если в него добавлялись элементы (последний добавленный)
    // 2. В начале output_stack, если input_stack пуст
    if (!input_stack.empty()) {
        return input_stack.back();
    } else {
        return output_stack.front();
    }
}

// Метод Back (константная версия): доступ только на чтение к последнему элементу
// Возвращает константную ссылку на последний элемент очереди
const int& Queue::Back() const {

    // Возвращает const ссылку
    if (!input_stack.empty()) {
        return input_stack.back();
    } else {
        return output_stack.front();
    }
}

// Метод Empty: проверяет, пуста ли очередь
// Возвращает true, если в очереди нет элементов
bool Queue::Empty() const {
    // Очередь пуста, если оба стека пусты
    return input_stack.empty() && output_stack.empty();
}

// Метод Size: возвращает количество элементов в очереди
size_t Queue::Size() const {
    // Размер очереди = сумма размеров обоих стеков
    return input_stack.size() + output_stack.size();
}

// Метод Clear: очищает очередь, удаляя все элементы
void Queue::Clear() {
    // Очищаем оба стека
    input_stack.clear();
    output_stack.clear();
}

// Метод Swap: обменивается содержимым с другой очередью
void Queue::Swap(Queue& other) {
    // Проверка на самоприсваивание
    if (this != &other) {
        // Обмениваем содержимое стеков
        input_stack.swap(other.input_stack);
        output_stack.swap(other.output_stack);
    }
}

// Оператор ==: сравнивает две очереди на равенство
// Две очереди равны, если они содержат одинаковые элементы в одинаковом порядке
bool Queue::operator==(const Queue& other) const {
    // Быстрая проверка: если размеры разные, очереди точно не равны
    if (Size() != other.Size()) {
        return false;
    }

    // Обе очереди пусты - они равны
    if (Empty() && other.Empty()) {
        return true;
    }

    // Создаем копии для безопасного сравнения
    Queue copy1 = *this;
    Queue copy2 = other;

    // Последовательно сравниваем элементы от начала к концу
    while (!copy1.Empty() && !copy2.Empty()) {
        // Если текущие первые элементы разные, очереди не равны
        if (copy1.Front() != copy2.Front()) {
            return false;
        }
        // Переходим к следующим элементам
        copy1.Pop();
        copy2.Pop();
    }

    // Обе копии должны быть пусты после сравнения всех элементов
    return copy1.Empty() && copy2.Empty();
}

// Оператор !=: сравнивает две очереди на неравенство
bool Queue::operator!=(const Queue& other) const {
    return !(*this == other);
}