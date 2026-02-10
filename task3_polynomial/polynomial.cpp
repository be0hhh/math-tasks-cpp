#include "polynomial.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cmath>

namespace Task3 {

Polynomial::Polynomial() : coefficients({0.0}) {}

Polynomial::Polynomial(const std::vector<double>& coeffs) : coefficients(coeffs) {
    // Удаляем ведущие нули
    while (coefficients.size() > 1 && std::abs(coefficients.back()) < 1e-15) {
        coefficients.pop_back();
    }
    if (coefficients.empty()) {
        coefficients = {0.0};
    }
}

Polynomial::Polynomial(std::initializer_list<double> coeffs) 
    : coefficients(coeffs.begin(), coeffs.end()) {
    // Удаляем ведущие нули
    while (coefficients.size() > 1 && std::abs(coefficients.back()) < 1e-15) {
        coefficients.pop_back();
    }
    if (coefficients.empty()) {
        coefficients = {0.0};
    }
}

int Polynomial::degree() const {
    if (coefficients.size() <= 1 && std::abs(coefficients[0]) < 1e-15) {
        return -1; // Нулевой полином
    }
    return static_cast<int>(coefficients.size() - 1);
}

double Polynomial::coefficient(int k) const {
    if (k < 0 || k >= static_cast<int>(coefficients.size())) {
        return 0.0;
    }
    return coefficients[k];
}

double Polynomial::evaluate(double x) const {
    // Схема Горнера: a₀ + x(a₁ + x(a₂ + x(...)))
    double result = 0.0;
    for (int i = static_cast<int>(coefficients.size()) - 1; i >= 0; --i) {
        result = result * x + coefficients[i];
    }
    return result;
}

Polynomial Polynomial::derivative(int order) const {
    if (order <= 0) {
        return *this;
    }
    
    if (order > degree() + 1) {
        // Производная выше степени полинома дает нулевой полином
        return Polynomial({0.0});
    }
    
    Polynomial result = *this;
    
    for (int o = 0; o < order; ++o) {
        std::vector<double> new_coeffs;
        int deg = result.degree();
        
        if (deg < 0) {
            return Polynomial({0.0});
        }
        
        // Производная: если p(x) = a₀ + a₁x + a₂x² + ..., то
        // p'(x) = a₁ + 2a₂x + 3a₃x² + ...
        for (int i = 1; i <= deg; ++i) {
            new_coeffs.push_back(result.coefficient(i) * i);
        }
        
        if (new_coeffs.empty()) {
            new_coeffs = {0.0};
        }
        
        result = Polynomial(new_coeffs);
    }
    
    return result;
}

double Polynomial::evaluateDerivative(double x, int order) const {
    Polynomial deriv = derivative(order);
    return deriv.evaluate(x);
}

std::vector<double> Polynomial::taylorExpansion(double center, int maxDegree) const {
    std::vector<double> taylor_coeffs;
    
    // Коэффициенты Тейлора: cₖ = p⁽ᵏ⁾(center) / k!
    for (int k = 0; k <= maxDegree; ++k) {
        double deriv_value = evaluateDerivative(center, k);
        
        // Вычисляем k!
        double factorial = 1.0;
        for (int i = 1; i <= k; ++i) {
            factorial *= i;
        }
        
        taylor_coeffs.push_back(deriv_value / factorial);
    }
    
    return taylor_coeffs;
}

std::string Polynomial::toString() const {
    if (degree() < 0) {
        return "0";
    }
    
    std::ostringstream oss;
    bool first_term = true;
    
    for (int i = degree(); i >= 0; --i) {
        double coeff = coefficient(i);
        
        if (std::abs(coeff) < 1e-15) {
            continue; // Пропускаем нулевые коэффициенты
        }
        
        if (!first_term) {
            if (coeff > 0) {
                oss << " + ";
            } else {
                oss << " - ";
                coeff = -coeff;
            }
        } else {
            if (coeff < 0) {
                oss << "-";
                coeff = -coeff;
            }
            first_term = false;
        }
        
        if (i == 0) {
            oss << coeff;
        } else if (std::abs(coeff - 1.0) < 1e-15) {
            if (i == 1) {
                oss << "x";
            } else {
                oss << "x^" << i;
            }
        } else {
            if (i == 1) {
                oss << coeff << "x";
            } else {
                oss << coeff << "x^" << i;
            }
        }
    }
    
    return oss.str();
}

Polynomial Polynomial::createTaskPolynomial() {
    // p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2
    // Коэффициенты: [-2, 1, -1, 3, -2, 1]
    return Polynomial({-2.0, 1.0, -1.0, 3.0, -2.0, 1.0});
}

} // namespace Task3

