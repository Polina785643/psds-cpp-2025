#include <iostream>
#include <vector>
#include <utility>
#include <stdexcept>

struct Coord2D {
    int x = 0;
    int y = 0;
};

struct Circle {
    Coord2D coord;
    unsigned radius = 1;
    
    Circle() = default;
    
    Circle(Coord2D center, unsigned r = 1) : coord(center), radius(r) {}
};

using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;

// Перегрузка оператора вывода для Coord2D
std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;
}

// Перегрузка оператора вывода для Circle
std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    os << "circle[";
    if (circle.radius > 0) {
        os << circle.coord << ", r = " << circle.radius;
    }
    os << "]";
    return os;
}

// Перегрузка оператора вывода для CircleRegion
std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    // Выводим знак + для внутренней зоны (< radius), - для внешней (> radius)
    os << (region.second ? "+" : "-");
    os << region.first;
    return os;
}

// Перегрузка оператора вывода для CircleRegionList
std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    os << "{";
    if (!list.empty()) {
        os << "\n";
        for (size_t i = 0; i < list.size(); ++i) {
            os << "\t" << list[i];
            if (i != list.size() - 1) {
                os << ",";
            }
            os << "\n";
        }
    }
    os << "}";
    return os;
}