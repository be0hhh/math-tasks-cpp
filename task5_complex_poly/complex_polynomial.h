#ifndef COMPLEX_POLYNOMIAL_H
#define COMPLEX_POLYNOMIAL_H

#include <vector>
#include <complex>
#include <tuple>
#include <string>
#include <cmath>

namespace Task5 {

/**
 * Класс для представления комплексных чисел
 */
class Complex {
public:
    double real;
    double imag;
    
    Complex() : real(0.0), imag(0.0) {}
    Complex(double r, double i = 0.0) : real(r), imag(i) {}
    
    // Арифметические операции
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }
    
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag,
                      real * other.imag + imag * other.real);
    }
    
    Complex operator/(const Complex& other) const {
        double denom = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denom,
                      (imag * other.real - real * other.imag) / denom);
    }
    
    Complex conjugate() const {
        return Complex(real, -imag);
    }
    
    double modulus() const {
        return std::sqrt(real * real + imag * imag);
    }
    
    std::string toString() const {
        if (std::abs(imag) < 1e-10) {
            return std::to_string(real);
        } else if (std::abs(real) < 1e-10) {
            return std::to_string(imag) + "i";
        } else {
            return std::to_string(real) + (imag >= 0 ? "+" : "") + std::to_string(imag) + "i";
        }
    }
};

/**
 * Класс для работы с полиномами с вещественными коэффициентами
 * и вычисления их значений в комплексных точках
 */
class ComplexPolynomial {
private:
    std::vector<double> coefficients; // Коэффициенты от младшей степени к старшей
    
public:
    /**
     * Конструктор из вектора коэффициентов
     * @param coeffs коэффициенты [a₀, a₁, a₂, ..., aₙ]
     */
    explicit ComplexPolynomial(const std::vector<double>& coeffs);
    
    /**
     * Конструктор из списка инициализации
     */
    ComplexPolynomial(std::initializer_list<double> coeffs);
    
    /**
     * Вычисляет значение полинома в комплексной точке z
     * Использует схему Горнера
     * @param z комплексная точка
     * @return значение полинома
     */
    Complex evaluate(const Complex& z) const;
    
    /**
     * Вычисляет значение полинома в точке z = u + iv
     * @param u0 вещественная часть
     * @param v0 мнимая часть
     * @return значение полинома
     */
    Complex evaluate(double u0, double v0) const;
    
    /**
     * Делит полином на квадратичный множитель (x - z₀)(x - ẑ₀) = x² + px + q
     * где z₀ = u₀ + iv₀, p = -2u₀, q = u₀² + v₀²
     * 
     * @param u0 вещественная часть комплексного числа z₀
     * @param v0 мнимая часть комплексного числа z₀
     * @return пара (частное, остаток), где остаток - линейный полином (или константа)
     */
    std::tuple<ComplexPolynomial, std::pair<double, double>> divideByQuadratic(
        double u0, double v0) const;
    
    /**
     * Возвращает степень полинома
     */
    int degree() const;
    
    /**
     * Возвращает коэффициент при степени k
     */
    double coefficient(int k) const;
    
    /**
     * Вычисляет коэффициенты p и q для квадратичного множителя
     * @param u0 вещественная часть z₀
     * @param v0 мнимая часть z₀
     * @return пара (p, q) где p = -2u₀, q = u₀² + v₀²
     */
    static std::pair<double, double> computeQuadraticCoeffs(double u0, double v0);
};

} // namespace Task5

#endif // COMPLEX_POLYNOMIAL_H

