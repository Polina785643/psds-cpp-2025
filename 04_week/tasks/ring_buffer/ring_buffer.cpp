#include <vector>
#include <initializer_list>
#include <algorithm>
#include <stdexcept>

class RingBuffer {
private:
    std::vector<int> data;     // хранилище данных
    size_t head;               // индекс самого старого элемента
    size_t tail;               // индекс, куда будет добавлен следующий элемент
    size_t count;              // текущее количество элементов
    bool is_full;              // флаг полного заполнения буфера
    
    // Получение следующей позиции с учетом кольцевого буфера
    size_t next_pos(size_t pos) const {
        return (pos + 1) % data.size();
    }
    
    // Преобразование логического индекса в физический
    size_t logical_to_physical(size_t logical_idx) const {
        return (head + logical_idx) % data.size();
    }

public:
    // Конструкторы
    RingBuffer(size_t capacity);
    RingBuffer(size_t capacity, int initial_value);
    RingBuffer(std::initializer_list<int> init);
    
    // Копирующие операции
    RingBuffer(const RingBuffer& other);
    RingBuffer& operator=(const RingBuffer& other);
    
    // Основные операции
    void Push(int value);
    bool TryPush(int value);
    void Pop();
    bool TryPop(int& value);
    
    // Доступ к элементам
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    int& Front();
    const int& Front() const;
    int& Back();
    const int& Back() const;
    
    // Информация о состоянии
    bool Empty() const;
    bool Full() const;
    size_t Size() const;
    size_t Capacity() const;
    
    // Управление буфером
    void Clear();
    void Resize(size_t new_capacity);
    std::vector<int> Vector() const;
};

// Конструктор от вместимости буфера
RingBuffer::RingBuffer(size_t capacity) {
    size_t actual_capacity = (capacity == 0) ? 1 : capacity;
    data.resize(actual_capacity);
    head = 0;
    tail = 0;
    count = 0;
    is_full = false;
}

// Конструктор от вместимости буфера и начального значения
RingBuffer::RingBuffer(size_t capacity, int initial_value) 
    : RingBuffer(capacity) {
    
    for (size_t i = 0; i < data.size(); ++i) {
        data[i] = initial_value;
    }
    count = data.size();
    tail = data.size();
    is_full = true;
}

// Конструктор от std::initializer_list
RingBuffer::RingBuffer(std::initializer_list<int> init) {
    size_t capacity = init.size();
    size_t actual_capacity = (capacity == 0) ? 1 : capacity;
    data.resize(actual_capacity);
    
    size_t i = 0;
    for (int val : init) {
        data[i++] = val;
    }
    
    head = 0;
    tail = (capacity == 0) ? 0 : capacity % data.size();
    count = capacity;
    is_full = (count == data.size());
}

// Копирующий конструктор
RingBuffer::RingBuffer(const RingBuffer& other) 
    : data(other.data), head(other.head), tail(other.tail), 
      count(other.count), is_full(other.is_full) {}

// Копирующее присваивание
RingBuffer& RingBuffer::operator=(const RingBuffer& other) {
    if (this != &other) {
        data = other.data;
        head = other.head;
        tail = other.tail;
        count = other.count;
        is_full = other.is_full;
    }
    return *this;
}

// Добавляет элемент в буфер, перезаписывает старый если буфер полон
void RingBuffer::Push(int value) {
    if (is_full) {
        // Перезаписываем самый старый элемент
        data[tail] = value;
        tail = next_pos(tail);
        head = tail;
    } else {
        data[tail] = value;
        tail = next_pos(tail);
        ++count;
        is_full = (count == data.size());
    }
}

// Пытается добавить элемент без перезаписи, возвращает true при успехе
bool RingBuffer::TryPush(int value) {
    if (is_full) {
        return false;
    }
    
    data[tail] = value;
    tail = next_pos(tail);
    ++count;
    is_full = (count == data.size());
    return true;
}

// Убирает самый старый элемент из буфера, безопасен для пустого буфера
void RingBuffer::Pop() {
    if (Empty()) {
        return;
    }
    
    head = next_pos(head);
    --count;
    is_full = false;
}

// Пытается извлечь самый старый элемент, возвращает true при успехе
bool RingBuffer::TryPop(int& value) {
    if (Empty()) {
        return false;
    }
    
    value = data[head];
    head = next_pos(head);
    --count;
    is_full = false;
    return true;
}

// Доступ к элементу по логическому индексу (0 - самый старый)
int& RingBuffer::operator[](size_t index) {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[logical_to_physical(index)];
}

// Константный доступ к элементу по логическому индексу
const int& RingBuffer::operator[](size_t index) const {
    if (index >= count) {
        throw std::out_of_range("Index out of range");
    }
    return data[logical_to_physical(index)];
}

// Доступ на запись и чтение к самому новому элементу (UB для пустого)
int& RingBuffer::Front() {
    if (Empty()) {
        static int dummy;
        return dummy;
    }
    return data[(tail == 0) ? data.size() - 1 : tail - 1];
}

// Константный доступ к самому новому элементу
const int& RingBuffer::Front() const {
    if (Empty()) {
        static const int dummy = 0;
        return dummy;
    }
    return data[(tail == 0) ? data.size() - 1 : tail - 1];
}

// Доступ на запись и чтение к самому старому элементу (UB для пустого)
int& RingBuffer::Back() {
    if (Empty()) {
        static int dummy;
        return dummy;
    }
    return data[head];
}

// Константный доступ к самому старому элементу
const int& RingBuffer::Back() const {
    if (Empty()) {
        static const int dummy = 0;
        return dummy;
    }
    return data[head];
}

// Проверяет, пуст ли буфер
bool RingBuffer::Empty() const {
    return (count == 0);
}

// Проверяет, заполнен ли буфер
bool RingBuffer::Full() const {
    return is_full;
}

// Возвращает текущее количество элементов в буфере
size_t RingBuffer::Size() const {
    return count;
}

// Возвращает вместимость буфера
size_t RingBuffer::Capacity() const {
    return data.size();
}

// Очищает буфер, сбрасывает позиции в начало
void RingBuffer::Clear() {
    head = 0;
    tail = 0;
    count = 0;
    is_full = false;
}

// Изменяет вместимость буфера, сохраняя элементы
void RingBuffer::Resize(size_t new_capacity) {
    if (new_capacity == 0) {
        new_capacity = 1;
    }
    
    if (new_capacity == data.size()) {
        return;
    }
    
    std::vector<int> new_data(new_capacity);
    
    if (new_capacity >= count) {
        // Увеличиваем - копируем все элементы
        for (size_t i = 0; i < count; ++i) {
            new_data[i] = (*this)[i];
        }
        head = 0;
        tail = count % new_capacity;
        is_full = (count == new_capacity);
    } else {
        // Уменьшаем - копируем только самые новые элементы
        size_t start_idx = count - new_capacity;
        for (size_t i = 0; i < new_capacity; ++i) {
            new_data[i] = (*this)[start_idx + i];
        }
        head = 0;
        tail = 0;
        count = new_capacity;
        is_full = true;
    }
    
    data = std::move(new_data);
}

// Возвращает линейное представление буфера (от старого к новому)
std::vector<int> RingBuffer::Vector() const {
    std::vector<int> result(count);
    for (size_t i = 0; i < count; ++i) {
        result[i] = (*this)[i];
    }
    return result;
}