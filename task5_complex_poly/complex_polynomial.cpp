#include "complex_polynomial.h"
#include <cmath>
#include <algorithm>
#include <sstream>

namespace Task5 {

ComplexPolynomial::ComplexPolynomial(const std::vector<double>& coeffs) 
    : coefficients(coeffs) {
    // Удаляем ведущие нули
    while (coefficients.size() > 1 && std::abs(coefficients.back()) < 1e-15) {
        coefficients.pop_back();
    }
    if (coefficients.empty()) {
        coefficients = {0.0};
    }
}

ComplexPolynomial::ComplexPolynomial(std::initializer_list<double> coeffs)
    : coefficients(coeffs.begin(), coeffs.end()) {
    // Удаляем ведущие нули
    while (coefficients.size() > 1 && std::abs(coefficients.back()) < 1e-15) {
        coefficients.pop_back();
    }
    if (coefficients.empty()) {
        coefficients = {0.0};
    }
}

int ComplexPolynomial::degree() const {
    if (coefficients.size() <= 1 && std::abs(coefficients[0]) < 1e-15) {
        return -1;
    }
    return static_cast<int>(coefficients.size() - 1);
}

double ComplexPolynomial::coefficient(int k) const {
    if (k < 0 || k >= static_cast<int>(coefficients.size())) {
        return 0.0;
    }
    return coefficients[k];
}

Complex ComplexPolynomial::evaluate(const Complex& z) const {
    // Схема Горнера для комплексных чисел
    Complex result(0.0, 0.0);
    for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; --i) {
        result = result * z + Complex(coefficients[i], 0.0);
    }
    return result;
}

Complex ComplexPolynomial::evaluate(double u0, double v0) const {
    return evaluate(Complex(u0, v0));
}

std::pair<double, double> ComplexPolynomial::computeQuadraticCoeffs(double u0, double v0) {
    // (x - z₀)(x - ẑ₀) = (x - u₀ - iv₀)(x - u₀ + iv₀)
    //                   = (x - u₀)² + v₀²
    //                   = x² - 2u₀x + u₀² + v₀²
    //                   = x² + px + q
    // где p = -2u₀, q = u₀² + v₀²
    double p = -2.0 * u0;
    double q = u0 * u0 + v0 * v0;
    return {p, q};
}

std::tuple<ComplexPolynomial, std::pair<double, double>> 
ComplexPolynomial::divideByQuadratic(double u0, double v0) const {
    // Вычисляем p и q
    auto [p, q] = computeQuadraticCoeffs(u0, v0);
    
    int n = degree();
    if (n < 2) {
        // Полином степени меньше 2, деление невозможно
        return {ComplexPolynomial({0.0}), {coefficients[0], 0.0}};
    }
    
    // Деление полинома на x² + px + q методом синтетического деления
    // P(x) = Q(x)(x² + px + q) + остаток, где остаток = Ax + B
    std::vector<double> quotient_coeffs;
    std::vector<double> work = coefficients;
    
    // Деление от старшей степени к младшей
    // Для полинома степени n частное будет степени n-2
    for (int i = n; i >= 2; --i) {
        if (i < static_cast<int>(work.size())) {
            double coeff = work[i];
            if (std::abs(coeff) > 1e-15) {
                // Добавляем коэффициент в частное
                quotient_coeffs.insert(quotient_coeffs.begin(), coeff);
                
                // Вычитаем coeff * x^(i-2) * (x² + px + q)
                // Это дает: coeff*x^i + coeff*p*x^(i-1) + coeff*q*x^(i-2)
                work[i] = 0.0; // Обнуляем коэффициент при x^i
                if (i - 1 < static_cast<int>(work.size())) {
                    work[i - 1] -= coeff * p;
                }
                if (i - 2 < static_cast<int>(work.size())) {
                    work[i - 2] -= coeff * q;
                }
            } else {
                quotient_coeffs.insert(quotient_coeffs.begin(), 0.0);
            }
        }
    }
    
    // Остаток - это коэффициенты при x^1 и x^0
    double remainder_a = (work.size() > 1) ? work[1] : 0.0; // коэффициент при x
    double remainder_b = (work.size() > 0) ? work[0] : 0.0; // свободный член
    
    // Удаляем ведущие нули из частного
    while (quotient_coeffs.size() > 1 && std::abs(quotient_coeffs.back()) < 1e-15) {
        quotient_coeffs.pop_back();
    }
    if (quotient_coeffs.empty()) {
        quotient_coeffs = {0.0};
    }
    
    return {ComplexPolynomial(quotient_coeffs), {remainder_b, remainder_a}};
}

} // namespace Task5

