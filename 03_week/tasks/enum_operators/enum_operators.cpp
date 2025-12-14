#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

enum class CheckFlags : uint8_t {
    NONE = 0,
    TIME = (1 << 0),
    DATE = (1 << 1),
    USER = (1 << 2),
    CERT = (1 << 3),
    KEYS = (1 << 4),
    DEST = (1 << 5),
    ALL = TIME | DATE | USER | CERT | KEYS | DEST
};

// Вспомогательная функция для фильтрации бит,
// биты 0-5 установлены, биты 6-7 нули
constexpr CheckFlags sanitize(CheckFlags flags) {
    return static_cast<CheckFlags>(static_cast<uint8_t>(flags) & 
                                   static_cast<uint8_t>(CheckFlags::ALL));
}

// Оператор побитового ИЛИ
constexpr CheckFlags operator|(CheckFlags lhs, CheckFlags rhs) {
    return sanitize(static_cast<CheckFlags>(
        static_cast<uint8_t>(sanitize(lhs)) | 
        static_cast<uint8_t>(sanitize(rhs))
    ));
}

/// Оператор побитового И 
bool operator&(CheckFlags lhs, CheckFlags rhs) {
    CheckFlags sanitized_lhs = sanitize(lhs);
    CheckFlags sanitized_rhs = sanitize(rhs);
    
    // Если один из операндов NONE, возвращаем false
    if (sanitized_lhs == CheckFlags::NONE || sanitized_rhs == CheckFlags::NONE) {
        return false;
    }
    
    uint8_t lhs_bits = static_cast<uint8_t>(sanitized_lhs);
    uint8_t rhs_bits = static_cast<uint8_t>(sanitized_rhs);
    
    return ((lhs_bits & rhs_bits) == lhs_bits) || 
           ((rhs_bits & lhs_bits) == rhs_bits);
}

// Оператор исключающего ИЛИ
constexpr CheckFlags operator^(CheckFlags lhs, CheckFlags rhs) {
    return sanitize(static_cast<CheckFlags>(
        static_cast<uint8_t>(sanitize(lhs)) ^ 
        static_cast<uint8_t>(sanitize(rhs))
    ));
}

// Оператор побитового отрицания
constexpr CheckFlags operator~(CheckFlags flags) {
    uint8_t mask = static_cast<uint8_t>(CheckFlags::ALL);

    // Берем исходное значение flags, чтобы инвертировать все биты
    uint8_t original = static_cast<uint8_t>(flags);
    
    // Инвертируем и оставляем только валидные биты
    uint8_t inverted = (~original) & mask;
    
    // Если inverted == 0, это означает, что все биты были установлены
    // В этом случае возвращаем NONE
    if (inverted == 0) {
        return CheckFlags::NONE;
    }
    
    return static_cast<CheckFlags>(inverted);
}

// Оператор вывода в поток
std::ostream& operator<<(std::ostream& os, CheckFlags flags) {
    CheckFlags sanitized = sanitize(flags);
    
    // Если флагов нет или они вне диапазона
    if (sanitized == CheckFlags::NONE) {
        os << "NONE";
        return os;
    }
    
    // Собираем названия активных флагов
    std::vector<std::string> active_flags;
    
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::TIME)) {
        active_flags.push_back("TIME");
    }
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::DATE)) {
        active_flags.push_back("DATE");
    }
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::USER)) {
        active_flags.push_back("USER");
    }
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::CERT)) {
        active_flags.push_back("CERT");
    }
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::KEYS)) {
        active_flags.push_back("KEYS");
    }
    if (static_cast<uint8_t>(sanitized) & static_cast<uint8_t>(CheckFlags::DEST)) {
        active_flags.push_back("DEST");
    }
    
    // Выводим через запятую
    for (size_t i = 0; i < active_flags.size(); ++i) {
        if (i > 0) {
            os << ", ";
        }
        os << active_flags[i];
    }
    
    return os;
}