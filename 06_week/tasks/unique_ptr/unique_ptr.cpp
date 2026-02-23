#include <string>
#include <utility> // для std::move

class UniquePtr {
private:
    std::string* ptr_;

public:
    // Конструкторы
    UniquePtr();
    explicit UniquePtr(std::string* ptr);
    
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    
    UniquePtr(UniquePtr&& other) noexcept;
    UniquePtr& operator=(UniquePtr&& other);
    
    // Деструктор
    ~UniquePtr();
    
    // Операторы
    std::string& operator*() const;
    std::string* operator->() const;
    explicit operator bool() const;
    
    // Методы
    std::string* Get() const;
    std::string* Release();
    void Reset(std::string* new_ptr = nullptr);
    void Swap(UniquePtr& other) noexcept;

};

// Конструктор по умолчанию
UniquePtr::UniquePtr() : ptr_(nullptr) {}

// Конструктор от сырого указателя
UniquePtr::UniquePtr(std::string* ptr) : ptr_(ptr) {}

// Перемещающий конструктор
UniquePtr::UniquePtr(UniquePtr&& other) noexcept : ptr_(other.ptr_) {
    other.ptr_ = nullptr;
}

// Перемещающее присваивание
UniquePtr& UniquePtr::operator=(UniquePtr&& other) {
    if (this != &other) {
        delete ptr_;
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
    }
    return *this;
}

// Деструктор
UniquePtr::~UniquePtr() {
    delete ptr_;
}

// Оператор разыменования
std::string& UniquePtr::operator*() const {
    return *ptr_;
}

// Оператор доступа к членам
std::string* UniquePtr::operator->() const {
    return ptr_;
}

// Оператор преобразования к bool
UniquePtr::operator bool() const {
    return ptr_ != nullptr;
}

// Получить сырой указатель
std::string* UniquePtr::Get() const {
    return ptr_;
}

// Освободить владение
std::string* UniquePtr::Release() {
    std::string* temp = ptr_;
    ptr_ = nullptr;
    return temp;
}

// Сбросить указатель
void UniquePtr::Reset(std::string* new_ptr) {
    delete ptr_;
    ptr_ = new_ptr;
}

// Обмен с другим UniquePtr
void UniquePtr::Swap(UniquePtr& other) noexcept {
    std::swap(ptr_, other.ptr_);
}

// Функция MakeUnique с поддержкой копирования и перемещения
UniquePtr MakeUnique(const std::string& str) {
    return UniquePtr(new std::string(str));
}

UniquePtr MakeUnique(std::string&& str) {
    return UniquePtr(new std::string(std::move(str)));
}

// Функция Swap для обмена умными указателями
void Swap(UniquePtr& first, UniquePtr& second) noexcept {
    first.Swap(second);
}