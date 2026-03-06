#include <initializer_list>
#include <algorithm>
#include <utility>

template<typename T, std::size_t N>
class Array {
private:
    T data_[N];

public:
    // Конструкторы
    Array();
    Array(std::initializer_list<T> init);
    Array(const Array& other);
    Array(Array&& other) noexcept;
    
    // Операторы присваивания
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    
    // Деструктор
    ~Array();
    
    // Операторы индексирования
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    
    // Методы
    T& Front();
    const T& Front() const;
 
    T& Back();
    const T& Back() const;
    
    T* Data();
    const T* Data() const;
    
    bool Empty() const;
    
    std::size_t Size() const;
    
    void Fill(const T& value);
    
    void Swap(Array& other);
    
    // Итераторы
    T* begin();
    const T* begin() const;
    T* end();
    const T* end() const;
    
    const T* cbegin() const;
    const T* cend() const;
};

// Конструкторы
template<typename T, std::size_t N>
Array<T, N>::Array() = default;

template<typename T, std::size_t N>
Array<T, N>::Array(std::initializer_list<T> init) {
    std::size_t i = 0;
    for (auto& item : init) {
        if (i < N) {
            data_[i] = item;
            ++i;
        }
    }
    // Оставшиеся элементы будут value-initialized
}

template<typename T, std::size_t N>
Array<T, N>::Array(const Array& other) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = other.data_[i];
    }
}

template<typename T, std::size_t N>
Array<T, N>::Array(Array&& other) noexcept {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = std::move(other.data_[i]);
    }
}

// Операторы присваивания
template<typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(const Array& other) {
    if (this != &other) {
        for (std::size_t i = 0; i < N; ++i) {
            data_[i] = other.data_[i];
        }
    }
    return *this;
}

template<typename T, std::size_t N>
Array<T, N>& Array<T, N>::operator=(Array&& other) noexcept {
    if (this != &other) {
        for (std::size_t i = 0; i < N; ++i) {
            data_[i] = std::move(other.data_[i]);
        }
    }
    return *this;
}

// Деструктор
template<typename T, std::size_t N>
Array<T, N>::~Array() = default;

// Операторы индексирования (только один раз!)
template<typename T, std::size_t N>
T& Array<T, N>::operator[](std::size_t index) {
    return data_[index];
}

template<typename T, std::size_t N>
const T& Array<T, N>::operator[](std::size_t index) const {
    return data_[index];
}

// Получение первого элемента - можно изменять
template<typename T, std::size_t N>
T& Array<T, N>::Front() {
    return data_[0];
}

// Получение первого элемента - только для чтения
template<typename T, std::size_t N>
const T& Array<T, N>::Front() const {
    return data_[0];
}

// Получение последнего элемента - можно изменять
template<typename T, std::size_t N>
T& Array<T, N>::Back() {
    return data_[N - 1];
}

// Получение последнего элемента - только для чтения
template<typename T, std::size_t N>
const T& Array<T, N>::Back() const {
    return data_[N - 1];
}

// Получение сырого указателя на данные - можно изменять через указатель
template<typename T, std::size_t N>
T* Array<T, N>::Data() {
    return data_;
}

// Получение сырого указателя на данные - данные только для чтения
template<typename T, std::size_t N>
const T* Array<T, N>::Data() const {
    return data_;
}

// Проверка на пустоту - true если размер 0
template<typename T, std::size_t N>
bool Array<T, N>::Empty() const {
    return N == 0;
}

// Получение размера массива (константное время)
template<typename T, std::size_t N>
std::size_t Array<T, N>::Size() const {
    return N;
}

// Заполнение всего массива одним значением
template<typename T, std::size_t N>
void Array<T, N>::Fill(const T& value) {
    for (std::size_t i = 0; i < N; ++i) {
        data_[i] = value;
    }
}

// Обмен содержимым с другим массивом (поэлементный swap)
template<typename T, std::size_t N>
void Array<T, N>::Swap(Array& other) {
    for (std::size_t i = 0; i < N; ++i) {
        std::swap(data_[i], other.data_[i]);
    }
}

// Итераторы
template<typename T, std::size_t N>
T* Array<T, N>::begin() {
    return data_;
}

template<typename T, std::size_t N>
const T* Array<T, N>::begin() const {
    return data_;
}

template<typename T, std::size_t N>
T* Array<T, N>::end() {
    return data_ + N;
}

template<typename T, std::size_t N>
const T* Array<T, N>::end() const {
    return data_ + N;
}

// Const итераторы
template<typename T, std::size_t N>
const T* Array<T, N>::cbegin() const {
    return data_;
}

template<typename T, std::size_t N>
const T* Array<T, N>::cend() const {
    return data_ + N;
}

// Операторы сравнения
template<typename T, std::size_t N>
bool operator==(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] != rhs[i]) return false;
    }
    return true;
}

template<typename T, std::size_t N>
bool operator!=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs == rhs);
}

template<typename T, std::size_t N>
bool operator<(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    for (std::size_t i = 0; i < N; ++i) {
        if (lhs[i] < rhs[i]) return true;
        if (rhs[i] < lhs[i]) return false;
    }
    return false;
}

template<typename T, std::size_t N>
bool operator<=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(rhs < lhs);
}

template<typename T, std::size_t N>
bool operator>(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return rhs < lhs;
}

template<typename T, std::size_t N>
bool operator>=(const Array<T, N>& lhs, const Array<T, N>& rhs) {
    return !(lhs < rhs);
}

// Внешняя функция для обмена содержимым двух массивов
template<typename T, std::size_t N>
void swap(Array<T, N>& lhs, Array<T, N>& rhs) {
    lhs.Swap(rhs);
}

// Доступ к элементу по индексу I (шаблонный параметр) для обычного массива
template<std::size_t I, typename T, std::size_t N>
T& get(Array<T, N>& arr) {
    static_assert(I < N, "Index out of bounds");
    return arr[I];
}

// Доступ к элементу по индексу I для константного массива
template<std::size_t I, typename T, std::size_t N>
const T& get(const Array<T, N>& arr) {
    static_assert(I < N, "Index out of bounds");
    return arr[I];
}

// Доступ к элементу по индексу I для временного массива (move-семантика)
template<std::size_t I, typename T, std::size_t N>
T&& get(Array<T, N>&& arr) {
    static_assert(I < N, "Index out of bounds");
    return std::move(arr[I]);
}