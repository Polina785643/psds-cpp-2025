#include <cmath>
#include <iostream>

struct ExpTag {};
struct DegTag {};
struct AlgTag {};

class Phasor {
private:
    double real_;
    double imag_;
    
    static constexpr double PI = 3.14159265358979323846;
    
    // Нормализация фазы в диапазон (-π, π]
    static double normalize_angle(double angle) {
        const double two_pi = 2.0 * PI;
        
        // Для больших углов используем remainder
        angle = std::remainder(angle, two_pi);
        
        // Обрабатываем граничный случай remainder(-π) = -π
        if (angle <= -PI) {
            angle += two_pi;
        } else if (angle > PI) {
            angle -= two_pi;
        }
        
        return angle;
    }
    
public:
    // Конструктор по умолчанию
    Phasor() : real_(0.0), imag_(0.0) {}
    
    // Конструктор из полярных координат
    Phasor(double magnitude, double phase_rad) {
        // Обработка отрицательной амплитуды
        if (magnitude < 0) {
            magnitude = -magnitude;
            phase_rad += PI;
        }
        
        // Нормализуем фазу
        phase_rad = normalize_angle(phase_rad);
        
        real_ = magnitude * std::cos(phase_rad);
        imag_ = magnitude * std::sin(phase_rad);
    }
    
    // Конструкторы с тегами
    Phasor(double magnitude, double phase, ExpTag) 
        : Phasor(magnitude, phase) {}
    
    Phasor(double magnitude, double degrees, DegTag) 
        : Phasor(magnitude, degrees * PI / 180.0) {}
    
    Phasor(double real, double imag, AlgTag) 
        : real_(real), imag_(imag) {}
    
    // Методы доступа
    double Magnitude() const { 
        return std::hypot(real_, imag_); 
    }
    
    double Phase() const { 
        return std::atan2(imag_, real_); 
    }
    
    double PhaseDeg() const { 
        return Phase() * 180.0 / PI; 
    }
    
    double Real() const { 
        return real_; 
    }
    
    double Imag() const { 
        return imag_; 
    }
    
    // Синонимы
    double Abs() const { return Magnitude(); }
    double Angle() const { return Phase(); }
    double AngleDeg() const { return PhaseDeg(); }
    
    // Методы модификации
    void SetPolar(double magnitude, double phase_rad) {
        *this = Phasor(magnitude, phase_rad);
    }
    
    void SetCartesian(double real, double imag) {
        real_ = real;
        imag_ = imag;
    }
    
    // Арифметические операции
    Phasor operator-() const {
        return Phasor(-real_, -imag_, AlgTag{});
    }
    
    Phasor& operator+=(const Phasor& other) {
        real_ += other.real_;
        imag_ += other.imag_;
        return *this;
    }
    
    Phasor& operator-=(const Phasor& other) {
        real_ -= other.real_;
        imag_ -= other.imag_;
        return *this;
    }
    
    Phasor& operator*=(const Phasor& other) {
        double mag = Magnitude() * other.Magnitude();
        double phase = Phase() + other.Phase();
        SetPolar(mag, phase);
        return *this;
    }
    
    Phasor& operator/=(const Phasor& other) {
        double mag = Magnitude() / other.Magnitude();
        double phase = Phase() - other.Phase();
        SetPolar(mag, phase);
        return *this;
    }
    
    // Методы специального назначения
    Phasor Conj() const {
        return Phasor(real_, -imag_, AlgTag{});
    }
    
    Phasor Inv() const {
        double mag = Magnitude();
        if (mag == 0.0) {
            throw std::runtime_error("Division by zero");
        }
        return Phasor(1.0 / mag, -Phase());
    }
    
    // Операторы сравнения
    bool operator==(const Phasor& other) const {
        const double eps = 1e-10;
        return std::abs(real_ - other.real_) < eps && 
               std::abs(imag_ - other.imag_) < eps;
    }
    
    bool operator!=(const Phasor& other) const {
        return !(*this == other);
    }
};

// Арифметические операторы для Phasor + Phasor
inline Phasor operator+(Phasor lhs, const Phasor& rhs) {
    lhs += rhs;
    return lhs;
}

inline Phasor operator-(Phasor lhs, const Phasor& rhs) {
    lhs -= rhs;
    return lhs;
}

inline Phasor operator*(Phasor lhs, const Phasor& rhs) {
    lhs *= rhs;
    return lhs;
}

inline Phasor operator/(Phasor lhs, const Phasor& rhs) {
    lhs /= rhs;
    return lhs;
}

// Арифметические операторы для Phasor + scalar
inline Phasor operator+(const Phasor& p, double scalar) {
    return Phasor(p.Real() + scalar, p.Imag(), AlgTag{});
}

inline Phasor operator+(double scalar, const Phasor& p) {
    return p + scalar;
}

inline Phasor operator-(const Phasor& p, double scalar) {
    return Phasor(p.Real() - scalar, p.Imag(), AlgTag{});
}

inline Phasor operator-(double scalar, const Phasor& p) {
    return Phasor(scalar - p.Real(), -p.Imag(), AlgTag{});
}

inline Phasor operator*(const Phasor& p, double scalar) {
    return Phasor(p.Abs() * scalar, p.Phase());
}

inline Phasor operator*(double scalar, const Phasor& p) {
    return p * scalar;
}

inline Phasor operator/(const Phasor& p, double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return Phasor(p.Abs() / scalar, p.Phase());
}

inline Phasor operator/(double scalar, const Phasor& p) {
    return Phasor(scalar, 0.0, AlgTag{}) / p;
}

// Составные присваивания со скалярами
inline Phasor& operator+=(Phasor& p, double scalar) {
    p.SetCartesian(p.Real() + scalar, p.Imag());
    return p;
}

inline Phasor& operator-=(Phasor& p, double scalar) {
    p.SetCartesian(p.Real() - scalar, p.Imag());
    return p;
}

inline Phasor& operator*=(Phasor& p, double scalar) {
    p.SetPolar(p.Abs() * scalar, p.Phase());
    return p;
}

inline Phasor& operator/=(Phasor& p, double scalar) {
    if (scalar == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    p.SetPolar(p.Abs() / scalar, p.Phase());
    return p;
}

// Фабричные функции
inline Phasor MakePhasorCartesian(double real, double imag) {
    return Phasor(real, imag, AlgTag{});
}

inline Phasor MakePhasorPolar(double magnitude, double phase_rad) {
    return Phasor(magnitude, phase_rad);
}

inline Phasor MakePhasorPolarDeg(double magnitude, double degrees) {
    return Phasor(magnitude, degrees, DegTag{});
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Phasor& p) {
    const double mag = p.Magnitude();
    const double phase_deg = p.PhaseDeg();
    const double real = p.Real();
    const double imag = p.Imag();
    
    os.precision(6);
    os << std::fixed;
    os << mag << "*e(j*" << phase_deg << ") [" 
       << real << " + j*" << imag << "]";
    
    return os;
}