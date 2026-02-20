#include <algorithm>
#include <cstddef>
#include <initializer_list>

class SimpleVector {
public:
    // Конструкторы
    SimpleVector();
    SimpleVector(size_t size);
    SimpleVector(size_t size, int value);
    SimpleVector(std::initializer_list<int> init);
    
    // Копирование и перемещение
    SimpleVector(const SimpleVector& other);
    SimpleVector(SimpleVector&& other) noexcept;
    SimpleVector& operator=(const SimpleVector& other);
    SimpleVector& operator=(SimpleVector&& other) noexcept;
    ~SimpleVector();
    
    // Основные методы
    void Swap(SimpleVector& other) noexcept;
    int& operator[](size_t index);
    const int& operator[](size_t index) const;
    size_t Size() const;
    size_t Capacity() const;
    bool Empty() const;
    const int* Data() const;
    
    // Методы модификации
    void PushBack(int value);
    void PopBack();
    int* Insert(const int* pos, int value);
    int* Erase(const int* pos);
    void Clear();
    void Resize(size_t new_size, int value = 0);
    void Reserve(size_t new_capacity);
    
    // Поддержка range-based for
    int* begin();
    const int* begin() const;
    int* end();
    const int* end() const;
    
    // Операторы сравнения
    bool operator==(const SimpleVector& other) const;
    bool operator!=(const SimpleVector& other) const;

private:
    int* data_;
    size_t size_;
    size_t capacity_;
};

// Внешняя функция swap
void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept;

// Конструктор по умолчанию
SimpleVector::SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}

// Конструктор с размером (заполнение нулями)
SimpleVector::SimpleVector(size_t size) : data_(new int[size]), size_(size), capacity_(size) {
    std::fill(data_, data_ + size_, 0);
}

// Конструктор с размером и значением
SimpleVector::SimpleVector(size_t size, int value) : data_(new int[size]), size_(size), capacity_(size) {
    std::fill(data_, data_ + size_, value);
}

// Конструктор от initializer_list
SimpleVector::SimpleVector(std::initializer_list<int> init) 
    : data_(new int[init.size()]), size_(init.size()), capacity_(init.size()) {
    std::copy(init.begin(), init.end(), data_);
}

// Конструктор копирования (с запасом по capacity)
SimpleVector::SimpleVector(const SimpleVector& other) 
    : data_(new int[other.capacity_]), size_(other.size_), capacity_(other.capacity_) {
    std::copy(other.data_, other.data_ + other.size_, data_);
}

// Конструктор перемещения
SimpleVector::SimpleVector(SimpleVector&& other) noexcept 
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

// Оператор присваивания копированием
SimpleVector& SimpleVector::operator=(const SimpleVector& other) {
    if (this != &other) {
        SimpleVector tmp(other);
        Swap(tmp);
    }
    return *this;
}

// Оператор присваивания перемещением
SimpleVector& SimpleVector::operator=(SimpleVector&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

// Деструктор
SimpleVector::~SimpleVector() {
    delete[] data_;
}

void SimpleVector::Swap(SimpleVector& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}

int& SimpleVector::operator[](size_t index) {
    return data_[index];
}

const int& SimpleVector::operator[](size_t index) const {
    return data_[index];
}

// Методы

size_t SimpleVector::Size() const {
    return size_;
}


size_t SimpleVector::Capacity() const {
    return capacity_;
}

bool SimpleVector::Empty() const {
    return size_ == 0;
}

const int* SimpleVector::Data() const {
    return data_;
}

void SimpleVector::PushBack(int value) {
    if (size_ == capacity_) {
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        Reserve(new_capacity);
    }
    data_[size_++] = value;
}

void SimpleVector::PopBack() {
    if (size_ > 0) {
        --size_;
    }
}

int* SimpleVector::Insert(const int* pos, int value) {
    if (pos < data_ || pos > data_ + size_) {
        return data_ + size_;
    }
    
    size_t index = pos - data_;
    
    if (size_ == capacity_) {
        size_t new_capacity = capacity_ == 0 ? 1 : capacity_ * 2;
        int* new_data = new int[new_capacity];
        
        // Копируем элементы до позиции вставки
        std::copy(data_, data_ + index, new_data);
        // Вставляем новый элемент
        new_data[index] = value;
        // Копируем оставшиеся элементы
        std::copy(data_ + index, data_ + size_, new_data + index + 1);
        
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    } else {
        // Сдвигаем элементы вправо
        std::copy_backward(data_ + index, data_ + size_, data_ + size_ + 1);
        data_[index] = value;
    }
    
    ++size_;
    return data_ + index;
}

int* SimpleVector::Erase(const int* pos) {
    if (pos < data_ || pos >= data_ + size_) {
        return data_ + size_;
    }
    
    size_t index = pos - data_;
    
    // Сдвигаем элементы влево
    std::copy(data_ + index + 1, data_ + size_, data_ + index);
    --size_;
    
    return data_ + index;
}

void SimpleVector::Clear() {
    size_ = 0;
}

void SimpleVector::Resize(size_t new_size, int value) {
    if (new_size <= size_) {
        size_ = new_size;
    } else {
        if (new_size > capacity_) {
            Reserve(new_size);
        }
        // Заполняем новые элементы значением value
        std::fill(data_ + size_, data_ + new_size, value);
        size_ = new_size;
    }
}

void SimpleVector::Reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        int* new_data = new int[new_capacity];
        std::copy(data_, data_ + size_, new_data);
        
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }
}

int* SimpleVector::begin() {
    return data_;
}

const int* SimpleVector::begin() const {
    return data_;
}

int* SimpleVector::end() {
    return data_ + size_;
}

const int* SimpleVector::end() const {
    return data_ + size_;
}

bool SimpleVector::operator==(const SimpleVector& other) const {
    if (size_ != other.size_) {
        return false;
    }
    return std::equal(data_, data_ + size_, other.data_);
}

bool SimpleVector::operator!=(const SimpleVector& other) const {
    return !(*this == other);
}

// Внешняя функция swap
void swap(SimpleVector& lhs, SimpleVector& rhs) noexcept {
    lhs.Swap(rhs);
}

