#include <memory>
#include <utility>  // для std::forward

// Создает unique_ptr на объект типа T, передавая аргументы в его конструктор
template<typename T, typename... Args>
std::unique_ptr<T> MakeUnique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

