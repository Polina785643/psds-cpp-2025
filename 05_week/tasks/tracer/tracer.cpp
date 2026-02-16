#include <string>
#include <utility>

class Tracer {
public:
    // Статические счетчики
    static int count;
    static int default_ctor;
    static int str_ctor;
    static int copy_ctor;
    static int move_ctor;
    static int copy_assign;
    static int move_assign;
    static int dtor;
    static int alive;

private:
    std::string name_;
    int id_;

public:
    // Конструкторы
    Tracer();
    explicit Tracer(const std::string& name);
    Tracer(const Tracer& other);
    Tracer(Tracer&& other) noexcept;
    
    // Операторы присваивания
    Tracer& operator=(const Tracer& other);
    Tracer& operator=(Tracer&& other) noexcept;
    
    // Деструктор
    ~Tracer();
    
    // Геттеры
    int Id() const;
    const std::string& Name() const;
    const char* Data() const;
    
    // Сброс статистики
    static void ResetStats();
};

// Инициализация статических членов класса
int Tracer::count = 0;
int Tracer::default_ctor = 0;
int Tracer::str_ctor = 0;
int Tracer::copy_ctor = 0;
int Tracer::move_ctor = 0;
int Tracer::copy_assign = 0;
int Tracer::move_assign = 0;
int Tracer::dtor = 0;
int Tracer::alive = 0;

// Определения методов

// Конструктор по умолчанию
Tracer::Tracer() : id_(++count) {
    name_ = "obj_" + std::to_string(id_);
    ++default_ctor;
    ++alive;
}

// Конструктор от строки
Tracer::Tracer(const std::string& name) : id_(++count) {
    name_ = name + "_" + std::to_string(id_);
    ++str_ctor;
    ++alive;
}

// Конструктор копирования
Tracer::Tracer(const Tracer& other) : name_(other.name_), id_(++count) {
    ++copy_ctor;
    ++alive;
}

// Конструктор перемещения
Tracer::Tracer(Tracer&& other) noexcept : name_(std::move(other.name_)), id_(++count) {
    ++move_ctor;
    ++alive;
    other.name_.clear();
}

// Оператор копирующего присваивания
Tracer& Tracer::operator=(const Tracer& other) {
    if (this != &other) {
        name_ = other.name_;
        ++copy_assign;
    }
    return *this;
}

// Оператор перемещающего присваивания
Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if (this != &other) {
        name_ = std::move(other.name_);
        other.name_.clear();
        ++move_assign;
    }
    return *this;
}

// Деструктор
Tracer::~Tracer() {
    ++dtor;
    --alive;
}

// Геттеры
int Tracer::Id() const {
    return id_;
}

const std::string& Tracer::Name() const {
    return name_;
}

const char* Tracer::Data() const {
    return name_.data();
}

// Сброс статистики
void Tracer::ResetStats() {
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
}