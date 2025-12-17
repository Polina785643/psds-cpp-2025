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
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;
};

// Вспомогательная функция для преобразования оценки в числовое значение
// Z имеет наименьшее значение (1), A - наибольшее (5)
int markValue(char mark) {
    switch (mark) {
        case 'Z': return 1;
        case 'D': return 2;
        case 'C': return 3;
        case 'B': return 4;
        case 'A': return 5;
        default: return 0;
    }
}

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

bool operator==(const StudentInfo& lhs, const StudentInfo& rhs) {
    return lhs.mark == rhs.mark && lhs.score == rhs.score;
}

bool operator<(const StudentInfo& lhs, const StudentInfo& rhs) {
    // 1. Сравниваем оценки (Z < D < C < B < A)
    int lhsMarkVal = markValue(lhs.mark);
    int rhsMarkVal = markValue(rhs.mark);
    
    if (lhsMarkVal != rhsMarkVal) {
        // Студент с худшей оценкой (меньшее значение) должен быть "меньше"
        return lhsMarkVal < rhsMarkVal;
    }
    
    // 2. Сравниваем баллы (80 < 100)
    if (lhs.score != rhs.score) {
        // Студент с меньшим баллом должен быть "меньше"
        return lhs.score < rhs.score;
    }
    
    // 3. Сравниваем курс (4 < 3)
    if (lhs.course != rhs.course) {
        // Студент с большим курсом (менее опытный) должен быть "меньше"
        return lhs.course > rhs.course;
    }
    
    // 4. Сравниваем дату рождения (более старый < более молодой)
    // Более ранняя дата (старее) должна быть "меньше"
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