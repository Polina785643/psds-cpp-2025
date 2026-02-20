#include <cmath>

// Константы для перевода
constexpr double CM_IN_METER = 100.0;
constexpr double METERS_IN_FOOT = 0.3048;
constexpr double INCHES_IN_FOOT = 12.0;
constexpr double CM_IN_INCH = 2.54;

// Метры в футы
constexpr double operator"" _m_to_ft(long double meters) {
    return static_cast<long double>(meters / METERS_IN_FOOT);
}

// Метры в дюймы
constexpr double operator"" _m_to_in(long double meters) {
    return static_cast<double>(meters * CM_IN_METER / CM_IN_INCH);
}

// Метры в сантиметры
constexpr double operator"" _m_to_cm(long double meters) {
    return static_cast<double>(meters * CM_IN_METER);
}

// Сантиметры в метры
constexpr double operator"" _cm_to_m(long double centimeters) {
    return static_cast<long double>(centimeters / CM_IN_METER);
}

// Сантиметры в футы
constexpr double operator"" _cm_to_ft(long double centimeters) {
    return static_cast<double>(centimeters / CM_IN_METER / METERS_IN_FOOT);
}

// Сантиметры в дюймы
constexpr double operator"" _cm_to_in(long double centimeters) {
    return static_cast<double>(centimeters / CM_IN_INCH);
}

// Футы в метры
constexpr double operator"" _ft_to_m(long double feet) {
    return static_cast<double>(feet * METERS_IN_FOOT);
}

// Футы в сантиметры
constexpr double operator"" _ft_to_cm(long double feet) {
    return static_cast<double>(feet * METERS_IN_FOOT * CM_IN_METER);
}

// Футы в дюймы
constexpr double operator"" _ft_to_in(long double feet) {
    return static_cast<double>(feet * INCHES_IN_FOOT);
}


// Дюймы в метры
constexpr double operator"" _in_to_m(long double inches) {
    return static_cast<double>(inches * CM_IN_INCH / CM_IN_METER);
}

// Дюймы в сантиметры
constexpr double operator"" _in_to_cm(long double inches) {
    return static_cast<double>(inches * CM_IN_INCH);
}

// Дюймы в футы
constexpr double operator"" _in_to_ft(long double inches) {
    return static_cast<double>(inches / INCHES_IN_FOOT);
}