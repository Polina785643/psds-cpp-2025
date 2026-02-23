#include <string>
#include <cstddef>
#include <utility>

// Предварительные объявления классов
class SharedPtr;
class WeakPtr;

// Класс ControlBlock - управляющий блок для подсчета ссылок
class ControlBlock {
private:
    std::string* ptr_;
    size_t shared_count_;
    size_t weak_count_;

public:
    explicit ControlBlock(std::string* ptr);
    
    void IncrementShared();
    void DecrementShared();
    void IncrementWeak();
    void DecrementWeak();
    
    size_t GetSharedCount() const;
    size_t GetWeakCount() const;
    std::string* GetPtr() const;
};

// Конструктор ControlBlock
ControlBlock::ControlBlock(std::string* ptr) 
    : ptr_(ptr), shared_count_(1), weak_count_(0) {}

// Увеличить счетчик владельцев
void ControlBlock::IncrementShared() { 
    ++shared_count_; 
}

// Уменьшить счетчик владельцев и удалить объект/блок при необходимости
void ControlBlock::DecrementShared() { 
    --shared_count_; 
    if (shared_count_ == 0) {
        delete ptr_;                    // удаляем управляемый объект
        ptr_ = nullptr;
        if (weak_count_ == 0) {
            delete this;                 // удаляем сам блок, если нет наблюдателей
        }
    }
}

// Увеличить счетчик наблюдателей
void ControlBlock::IncrementWeak() { 
    ++weak_count_; 
}

// Уменьшить счетчик наблюдателей и удалить блок при необходимости
void ControlBlock::DecrementWeak() { 
    --weak_count_; 
    if (shared_count_ == 0 && weak_count_ == 0) {
        delete this;                     // удаляем блок, если нет ни владельцев, ни наблюдателей
    }
}

// Получить количество владельцев
size_t ControlBlock::GetSharedCount() const { 
    return shared_count_; 
}

// Получить количество наблюдателей
size_t ControlBlock::GetWeakCount() const { 
    return weak_count_; 
}

// Получить указатель на объект
std::string* ControlBlock::GetPtr() const { 
    return ptr_; 
}

// Класс SharedPtr - умный указатель с разделяемым владением
class SharedPtr {
private:
    std::string* ptr_;
    ControlBlock* block_;

public:
    // Конструкторы
    SharedPtr();
    explicit SharedPtr(std::string* ptr);
    SharedPtr(const SharedPtr& other);
    SharedPtr(SharedPtr&& other) noexcept;
    
    // Деструктор
    ~SharedPtr();
    
    // Операторы присваивания
    SharedPtr& operator=(const SharedPtr& other);
    SharedPtr& operator=(SharedPtr&& other) noexcept;
    
    // Операторы разыменования
    std::string& operator*() const;
    std::string* operator->() const;
    explicit operator bool() const;
    
    // Методы
    std::string* Get() const;
    void Reset(std::string* new_ptr = nullptr);
    void Swap(SharedPtr& other);
    size_t UseCount() const;

    friend class WeakPtr;
    friend SharedPtr MakeShared(const std::string& str);
    friend SharedPtr MakeShared(std::string&& str);
    friend void Swap(SharedPtr& lhs, SharedPtr& rhs);
};

// Конструктор по умолчанию
SharedPtr::SharedPtr() : ptr_(nullptr), block_(nullptr) {}

// Конструктор от сырого указателя
SharedPtr::SharedPtr(std::string* ptr) : ptr_(ptr), block_(nullptr) {
    if (ptr_) {
        block_ = new ControlBlock(ptr_);
    }
}

// Копирующий конструктор
SharedPtr::SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), block_(other.block_) {
    if (block_) {
        block_->IncrementShared();  // увеличиваем счетчик владельцев
    }
}

// Перемещающий конструктор
SharedPtr::SharedPtr(SharedPtr&& other) noexcept : ptr_(other.ptr_), block_(other.block_) {
    other.ptr_ = nullptr;           // обнуляем указатели источника
    other.block_ = nullptr;
}

// Деструктор
SharedPtr::~SharedPtr() {
    if (block_) {
        block_->DecrementShared();  // уменьшаем счетчик владельцев
    }
}

// Копирующее присваивание
SharedPtr& SharedPtr::operator=(const SharedPtr& other) {
    if (this != &other) {           // защита от самоприсваивания
        if (block_) {
            block_->DecrementShared();  // освобождаем текущий ресурс
        }
        ptr_ = other.ptr_;
        block_ = other.block_;
        if (block_) {
            block_->IncrementShared();  // захватываем новый ресурс
        }
    }
    return *this;
}

// Перемещающее присваивание
SharedPtr& SharedPtr::operator=(SharedPtr&& other) noexcept {
    if (this != &other) {           // защита от самоприсваивания
        if (block_) {
            block_->DecrementShared();  // освобождаем текущий ресурс
        }
        ptr_ = other.ptr_;           // перемещаем указатели
        block_ = other.block_;
        other.ptr_ = nullptr;        // обнуляем источник
        other.block_ = nullptr;
    }
    return *this;
}

// Оператор разыменования
std::string& SharedPtr::operator*() const { 
    return *ptr_; 
}

// Оператор доступа к членам
std::string* SharedPtr::operator->() const { 
    return ptr_; 
}

// Оператор преобразования к bool
SharedPtr::operator bool() const { 
    return ptr_ != nullptr; 
}

// Получить сырой указатель
std::string* SharedPtr::Get() const { 
    return ptr_; 
}

// Сбросить указатель
void SharedPtr::Reset(std::string* new_ptr) {
    if (block_) {
        block_->DecrementShared();  // освобождаем текущий ресурс
    }
    ptr_ = new_ptr;                  // устанавливаем новый указатель
    if (ptr_) {
        block_ = new ControlBlock(ptr_);  // создаем новый управляющий блок
    } else {
        block_ = nullptr;
    }
}

// Обмен с другим SharedPtr
void SharedPtr::Swap(SharedPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(block_, other.block_);
}

// Получить количество владельцев
size_t SharedPtr::UseCount() const {
    return block_ ? block_->GetSharedCount() : 0;
}

// Класс WeakPtr - умный указатель-наблюдатель
class WeakPtr {
private:
    std::string* ptr_;          // указатель на наблюдаемый объект
    ControlBlock* block_;       // указатель на управляющий блок

public:
    // Конструкторы
    WeakPtr();
    WeakPtr(const SharedPtr& sp);
    WeakPtr(const WeakPtr& other);
    WeakPtr(WeakPtr&& other) noexcept;
    
    // Деструктор
    ~WeakPtr();
    
    // Операторы присваивания
    WeakPtr& operator=(const WeakPtr& other);
    WeakPtr& operator=(WeakPtr&& other) noexcept;
    WeakPtr& operator=(const SharedPtr& sp);
    
    // Методы
    void Reset();
    void Swap(WeakPtr& other);
    size_t UseCount() const;
    bool Expired() const;
    SharedPtr Lock() const;

    friend void Swap(WeakPtr& lhs, WeakPtr& rhs);
};

// Конструктор по умолчанию
WeakPtr::WeakPtr() : ptr_(nullptr), block_(nullptr) {}

// Конструктор от SharedPtr
WeakPtr::WeakPtr(const SharedPtr& sp) : ptr_(sp.ptr_), block_(sp.block_) {
    if (block_) {
        block_->IncrementWeak();  // увеличиваем счетчик наблюдателей
    }
}

// Копирующий конструктор
WeakPtr::WeakPtr(const WeakPtr& other) : ptr_(other.ptr_), block_(other.block_) {
    if (block_) {
        block_->IncrementWeak();  // увеличиваем счетчик наблюдателей
    }
}

// Перемещающий конструктор
WeakPtr::WeakPtr(WeakPtr&& other) noexcept : ptr_(other.ptr_), block_(other.block_) {
    other.ptr_ = nullptr;          // обнуляем указатели источника
    other.block_ = nullptr;
}

// Деструктор
WeakPtr::~WeakPtr() {
    if (block_) {
        block_->DecrementWeak();  // уменьшаем счетчик наблюдателей
    }
}

// Копирующее присваивание
WeakPtr& WeakPtr::operator=(const WeakPtr& other) {
    if (this != &other) {         
        if (block_) {
            block_->DecrementWeak();  // освобождаем текущий ресурс
        }
        ptr_ = other.ptr_;
        block_ = other.block_;
        if (block_) {
            block_->IncrementWeak();  // захватываем новый ресурс
        }
    }
    return *this;
}

// Перемещающее присваивание
WeakPtr& WeakPtr::operator=(WeakPtr&& other) noexcept {
    if (this != &other) {          
        if (block_) {
            block_->DecrementWeak();  
        }
        ptr_ = other.ptr_;          // перемещаем указатели
        block_ = other.block_;
        other.ptr_ = nullptr;       // обнуляем источник
        other.block_ = nullptr;
    }
    return *this;
}

// Присваивание от SharedPtr
WeakPtr& WeakPtr::operator=(const SharedPtr& sp) {
    if (block_) {
        block_->DecrementWeak();  // освобождаем текущий ресурс
    }
    ptr_ = sp.ptr_;                 // устанавливаем новые указатели
    block_ = sp.block_;
    if (block_) {
        block_->IncrementWeak();  // увеличиваем счетчик наблюдателей
    }
    return *this;
}

// Сбросить указатель
void WeakPtr::Reset() {
    if (block_) {
        block_->DecrementWeak();  // уменьшаем счетчик наблюдателей
        ptr_ = nullptr;             // обнуляем указатели
        block_ = nullptr;
    }
}

// Обмен с другим WeakPtr
void WeakPtr::Swap(WeakPtr& other) {
    std::swap(ptr_, other.ptr_);
    std::swap(block_, other.block_);
}

// Получить количество владельцев
size_t WeakPtr::UseCount() const {
    return block_ ? block_->GetSharedCount() : 0;
}

// Проверка, жив ли объект
bool WeakPtr::Expired() const {
    return block_ ? (block_->GetSharedCount() == 0) : true;
}

// Получить SharedPtr на объект, если он еще жив
SharedPtr WeakPtr::Lock() const {
    if (block_ && block_->GetSharedCount() > 0) {
        SharedPtr sp;
        sp.ptr_ = ptr_;
        sp.block_ = block_;
        sp.block_->IncrementShared();  // увеличиваем счетчик владельцев
        return sp;
    }
    return SharedPtr();  // возвращаем пустой SharedPtr, если объект мертв
}

// Функция MakeShared для создания SharedPtr (копирование)
SharedPtr MakeShared(const std::string& str) {
    return SharedPtr(new std::string(str));
}

// Функция MakeShared для создания SharedPtr (перемещение)
SharedPtr MakeShared(std::string&& str) {
    return SharedPtr(new std::string(std::move(str)));
}

// Функция Swap для обмена SharedPtr
void Swap(SharedPtr& lhs, SharedPtr& rhs) {
    lhs.Swap(rhs);
}

// Функция Swap для обмена WeakPtr
void Swap(WeakPtr& lhs, WeakPtr& rhs) {
    lhs.Swap(rhs);
}