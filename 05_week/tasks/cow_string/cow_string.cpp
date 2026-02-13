#include <cstring>
#include <string>

class CowString {
public:
    // Вспомогательные типы
    using size_type = size_t;
    static const size_type npos;  // Только объявление

    // Конструкторы
    CowString();
    CowString(const char* str);
    CowString(const std::string& str);
    CowString(const CowString& other);
    CowString(CowString&& other) noexcept;
    
    // Операторы присваивания
    CowString& operator=(const CowString& other);
    CowString& operator=(CowString&& other) noexcept;
    
    // Деструктор
    ~CowString();

    // Методы без копирования
    size_type Size() const;
    const char* ToCstr() const;
    std::string ToString() const;
    
    // Оператор [] для чтения
    const char& operator[](size_type pos) const;
    
    // Оператор неявного преобразования к C-строке
    operator const char*() const;

    // Методы для модификации
    char& operator[](size_type pos);
    CowString& Append(const char* str);
    CowString& Append(const std::string& str);
    CowString Substr(size_type pos = 0, size_type count = npos) const;
    void Clear();
    
    // Дополнительные методы из тестов
    size_type Find(const char* str) const;
    size_type Find(char ch) const;
    bool Empty() const;

private:
    // Структура для хранения данных и счетчика ссылок
    struct StringData {
        char* data;
        size_type size;
        size_type capacity;
        int ref_count;

        StringData(const char* str = "");
        StringData(size_type count, char ch);
        ~StringData();

        void Reserve(size_type new_capacity);
        void Resize(size_type new_size);
    };

    StringData* data_;

    // Вспомогательные методы
    void Detach();
    void Release();
    void CreateEmpty();
    bool IsUnique() const;
    size_type Length() const;
    void CheckAndCopy();
};

// Определение статического члена npos
const CowString::size_type CowString::npos = -1;

// Реализация StringData

CowString::StringData::StringData(const char* str) {
    if (str == nullptr) str = "";
    size = strlen(str);
    capacity = size + 1;
    data = new char[capacity];
    memcpy(data, str, size + 1);
    ref_count = 1;
}

CowString::StringData::StringData(size_type count, char ch) {
    size = count;
    capacity = size + 1;
    data = new char[capacity];
    memset(data, ch, size);
    data[size] = '\0';
    ref_count = 1;
}

CowString::StringData::~StringData() {
    delete[] data;
}

void CowString::StringData::Reserve(size_type new_capacity) {
    if (new_capacity <= capacity) return;
    
    char* new_data = new char[new_capacity];
    memcpy(new_data, data, size + 1);
    delete[] data;
    data = new_data;
    capacity = new_capacity;
}

void CowString::StringData::Resize(size_type new_size) {
    if (new_size >= capacity) {
        size_type new_capacity = capacity * 2;
        if (new_capacity < new_size + 1) {
            new_capacity = new_size + 1;
        }
        Reserve(new_capacity);
    }
    size = new_size;
    data[size] = '\0';
}

// Реализация CowString

// Конструкторы
CowString::CowString() {
    data_ = new StringData("");
}

CowString::CowString(const char* str) {
    if (str == nullptr) {
        data_ = new StringData("");
    } else {
        data_ = new StringData(str);
    }
}

CowString::CowString(const std::string& str) {
    data_ = new StringData(str.c_str());
}

CowString::CowString(const CowString& other) {
    data_ = other.data_;
    ++data_->ref_count;
}

CowString::CowString(CowString&& other) noexcept {
    data_ = other.data_;
    other.data_ = new StringData("");
}

// Операторы присваивания
CowString& CowString::operator=(const CowString& other) {
    if (this != &other) {
        Release();
        data_ = other.data_;
        ++data_->ref_count;
    }
    return *this;
}

CowString& CowString::operator=(CowString&& other) noexcept {
    if (this != &other) {
        Release();
        data_ = other.data_;
        other.data_ = new StringData("");
    }
    return *this;
}

// Деструктор
CowString::~CowString() {
    Release();
}

// Методы без копирования
CowString::size_type CowString::Size() const {
    return data_->size;
}

const char* CowString::ToCstr() const {
    return data_->data;
}

std::string CowString::ToString() const {
    return std::string(data_->data, data_->size);
}

// Оператор [] для чтения
const char& CowString::operator[](size_type pos) const {
    return data_->data[pos];
}

// Оператор неявного преобразования к C-строке
CowString::operator const char*() const {
    return data_->data;
}

// Методы для модификации
char& CowString::operator[](size_type pos) {
    Detach();
    return data_->data[pos];
}

CowString& CowString::Append(const char* str) {
    if (str == nullptr || *str == '\0') return *this;
    
    size_type len = strlen(str);
    if (len == 0) return *this;
    
    Detach();
    
    size_type new_size = data_->size + len;
    data_->Resize(new_size);
    memcpy(data_->data + data_->size - len, str, len + 1);
    
    return *this;
}

CowString& CowString::Append(const std::string& str) {
    return Append(str.c_str());
}

CowString CowString::Substr(size_type pos, size_type count) const {
    if (pos >= data_->size) {
        return CowString();
    }
    
    size_type real_count = count;
    if (real_count == npos || pos + real_count > data_->size) {
        real_count = data_->size - pos;
    }
    
    CowString result;
    result.Detach(); // Создаем свою копию
    
    result.data_->Resize(real_count);
    memcpy(result.data_->data, data_->data + pos, real_count);
    result.data_->data[real_count] = '\0';
    
    return result;
}

void CowString::Clear() {
    if (data_->size == 0) return;
    
    if (!IsUnique()) {
        Release();
        data_ = new StringData("");
    } else {
        data_->size = 0;
        data_->data[0] = '\0';
    }
}

// Дополнительные методы
CowString::size_type CowString::Find(const char* str) const {
    if (str == nullptr) return npos;
    if (*str == '\0') return 0;
    
    const char* result = strstr(data_->data, str);
    if (result == nullptr) return npos;
    return result - data_->data;
}

CowString::size_type CowString::Find(char ch) const {
    const char* result = strchr(data_->data, ch);
    if (result == nullptr) return npos;
    return result - data_->data;
}

bool CowString::Empty() const {
    return data_->size == 0;
}

// Вспомогательные методы
void CowString::Detach() {
    if (!IsUnique()) {
        StringData* new_data = new StringData(data_->data);
        --data_->ref_count;
        data_ = new_data;
    }
}

void CowString::Release() {
    if (data_) {
        --data_->ref_count;
        if (data_->ref_count == 0) {
            delete data_;
        }
        data_ = nullptr;
    }
}

void CowString::CreateEmpty() {
    data_ = new StringData("");
}

bool CowString::IsUnique() const {
    return data_->ref_count == 1;
}

CowString::size_type CowString::Length() const {
    return data_->size;
}

void CowString::CheckAndCopy() {
    if (!IsUnique()) {
        StringData* new_data = new StringData(data_->data);
        --data_->ref_count;
        data_ = new_data;
    }
}