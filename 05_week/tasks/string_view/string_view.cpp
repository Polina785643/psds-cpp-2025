#include <cstring>
#include <string>

class StringView {
public:
    static const size_t npos;

    // Конструкторы
    StringView();
    StringView(const std::string& str, size_t pos = 0, size_t count = npos);
    StringView(const char* cstr);
    StringView(const char* cstr, size_t count);

    // Методы доступа
    char operator[](size_t index) const;
    const char* Data() const;
    char Front() const;
    char Back() const;

    // Методы информации
    size_t Size() const;
    size_t Length() const;
    bool Empty() const;

    // Методы модификации представления
    void RemovePrefix(size_t n);
    void RemoveSuffix(size_t n);

    // Методы для работы с подстроками
    StringView Substr(size_t pos = 0, size_t count = npos) const;
    size_t Find(char ch, size_t pos = 0) const;
    size_t Find(const StringView& sv, size_t pos = 0) const;

    // Преобразование
    std::string ToString() const;

private:
    const char* data_;
    size_t size_;
};

// Определение статического члена класса
const size_t StringView::npos = static_cast<size_t>(-1);

// Реализация конструкторов
StringView::StringView() : data_(nullptr), size_(0) {}

StringView::StringView(const std::string& str, size_t pos, size_t count)
    : data_(nullptr), size_(0) {
    if (pos < str.size()) {
        data_ = str.data() + pos;
        size_ = str.size() - pos;
        
        if (count != npos && count < size_) {
            size_ = count;
        }
    }
    // Если pos >= str.size(), оставляем data_ = nullptr и size_ = 0
}

StringView::StringView(const char* cstr) : data_(cstr), size_(0) {
    if (cstr != nullptr) {
        size_ = std::strlen(cstr);
    }
}

StringView::StringView(const char* cstr, size_t count) : data_(cstr), size_(0) {
    if (cstr != nullptr && count > 0) {
        size_ = count;
    }
}

// Реализация методов доступа
char StringView::operator[](size_t index) const {
    return data_[index];
}

const char* StringView::Data() const {
    return data_;
}

char StringView::Front() const {
    return data_[0];
}

char StringView::Back() const {
    return data_[size_ - 1];
}

// Реализация методов информации
size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

// Реализация методов модификации представления
void StringView::RemovePrefix(size_t n) {
    if (n < size_) {
        data_ += n;
        size_ -= n;
    } else {
        data_ = nullptr; // Если просят удалить больше, чем есть
        size_ = 0;       // делаем представление пустым
    }
}

void StringView::RemoveSuffix(size_t n) {
    if (n < size_) {
        size_ -= n;
    } else {
        data_ = nullptr;
        size_ = 0;
    }
}

// Реализация методов для работы с подстроками
StringView StringView::Substr(size_t pos, size_t count) const {
    if (pos >= size_) {
        return StringView();
    }
    
    StringView result;
    result.data_ = data_ + pos;
    result.size_ = size_ - pos;
    
    if (count != npos && count < result.size_) {
        result.size_ = count;
    }
    return result;
}

size_t StringView::Find(char ch, size_t pos) const {
    if (pos >= size_) {
        return npos;
    }
    
    for (size_t i = pos; i < size_; ++i) {
        if (data_[i] == ch) {
            return i;
        }
    }
    return npos;
}

size_t StringView::Find(const StringView& sv, size_t pos) const {
    // Обработка пустой строки
    if (sv.Empty()) {
        if (pos <= size_) {
            return pos;
        }
        return npos;
    }
    
    if (pos >= size_ || sv.size_ > size_ - pos) {
        return npos;
    }
    
    for (size_t i = pos; i <= size_ - sv.size_; ++i) {
        bool found = true;
        for (size_t j = 0; j < sv.size_; ++j) {
            if (data_[i + j] != sv.data_[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }
    return npos;
}

// Реализация преобразования
std::string StringView::ToString() const {
    if (Empty()) {
        return "";
    }
    return std::string(data_, size_);
}