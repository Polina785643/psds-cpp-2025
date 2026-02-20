#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

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

void PrintCheckFlags(CheckFlags flags) {
    // Проверка того, что значение находится в допустимом диапазоне
    uint8_t value = static_cast<uint8_t>(flags);
    if (value > static_cast<uint8_t>(CheckFlags::ALL)) {
        return; // выход за пределы диапазона - оставляем вывод пустым
    }
    
    // Если флаг NONE
    if (flags == CheckFlags::NONE) {
        std::cout << "[]";
        return;
    }
    
    std::vector<std::string> active_flags;
    
    // Проверка того, что каждый флаг по порядку
    if ((value & static_cast<uint8_t>(CheckFlags::TIME)) != 0) {
        active_flags.push_back("TIME");
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DATE)) != 0) {
        active_flags.push_back("DATE");
    }
    if ((value & static_cast<uint8_t>(CheckFlags::USER)) != 0) {
        active_flags.push_back("USER");
    }
    if ((value & static_cast<uint8_t>(CheckFlags::CERT)) != 0) {
        active_flags.push_back("CERT");
    }
    if ((value & static_cast<uint8_t>(CheckFlags::KEYS)) != 0) {
        active_flags.push_back("KEYS");
    }
    if ((value & static_cast<uint8_t>(CheckFlags::DEST)) != 0) {
        active_flags.push_back("DEST");
    }
    
    // Вывод
    std::cout << "[";
    for (size_t i = 0; i < active_flags.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }
        std::cout << active_flags[i];
    }
    std::cout << "]";
}