#include <cmath>

constexpr double CM_IN_METER = 100.0;

// Метры в сантиметры
constexpr double operator"" _m_to_cm(long double meters) {
    return static_cast<double>(meters * CM_IN_METER);
}

// Сантиметры в метры
constexpr double operator"" _cm_to_m(long double centimeters) {
    return static_cast<double>(centimeters / CM_IN_METER);
}