#include <tuple>
#include <stdexcept>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;
    
    Date() : year(0), month(0), day(0) {}
    Date(unsigned y, unsigned m, unsigned d) : year(y), month(m), day(d) {}
};

struct StudentInfo {
    size_t id;         // идентификация студента
    char mark;         // оценка
    int score;         // баллы
    unsigned course;   // курс
    Date birth_date;   // дата рождения
};

// Вспомогательная функция для преобразования оценки в числовое значение
// Высшая оценка A имеет наименьшее числовое значение для правильного сравнения
int markValue(char mark) {
    switch (mark) {
        case 'A': return 1;
        case 'B': return 2;
        case 'C': return 3;
        case 'D': return 4;
        case 'Z': return 5;
        default: return 6; // на случай некорректной оценки
    }
}

// Операторы сравнения для Date
bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < 
           std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const Date& lhs, const Date& rhs) {
    return !(rhs < lhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return rhs < lhs;
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

// Операторы сравнения для StudentInfo
bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    // Сравниваем оценки (высшая оценка в приоритете)
    // A > B > C > D > Z, поэтому A < B < C < D < Z в сравнении
    int lhsMarkVal = markValue(lhs.mark);
    int rhsMarkVal = markValue(rhs.mark);
    
    if (lhsMarkVal != rhsMarkVal) {
        return lhsMarkVal < rhsMarkVal;
    }
    
    // Сравниваем баллы (больший балл в приоритете)
    // 100 > 80, поэтому 100 < 80 в сравнении
    if (lhs.score != rhs.score) {
        return lhs.score > rhs.score; 
    }
    
    // Сравниваем курс (менее опытные в приоритете)
    // 1 > 2 > 3 > 4, поэтому 1 < 2 < 3 < 4 в сравнении
    if (lhs.course != rhs.course) {
        return lhs.course > rhs.course; 
    }
    
    // Сравниваем дату рождения (более молодые в приоритете)
    // Молодые имеют большую дату рождения
    return lhs.birth_date < rhs.birth_date;
}

bool operator>(const StudentInfo& lhs, const StudentInfo& rhs) {
    return rhs < lhs;
}

bool operator!=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs == rhs);
}

bool operator<=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(rhs < lhs);
}

bool operator>=(const StudentInfo& lhs, const StudentInfo& rhs) {
    return !(lhs < rhs);
}