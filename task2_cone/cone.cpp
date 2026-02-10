#include "cone.h"
#include <cmath>
#include <stdexcept>

namespace Task2 {

double ConeOptimizer::baseRadius(double phi, double R) {
    // Длина дуги вырезанного сектора = φR
    // Эта дуга становится окружностью основания конуса
    // 2πr = (2π - φ)R, откуда r = R(2π - φ)/(2π)
    return R * (2.0 * PI - phi) / (2.0 * PI);
}

double ConeOptimizer::height(double phi, double R) {
    // Высота конуса: h = √(R² - r²)
    // где R - образующая (радиус исходного круга)
    double r = baseRadius(phi, R);
    double h_squared = R * R - r * r;
    if (h_squared < 0) {
        return 0.0; // Некорректный случай
    }
    return std::sqrt(h_squared);
}

double ConeOptimizer::slantHeight(double phi, double R) {
    // Образующая равна радиусу исходного круга
    return R;
}

double ConeOptimizer::coneVolume(double phi, double R) {
    if (phi < 0 || phi >= 2.0 * PI) {
        throw std::invalid_argument("phi must be in [0, 2π)");
    }
    if (R <= 0) {
        throw std::invalid_argument("R must be positive");
    }
    
    double r = baseRadius(phi, R);
    double h = height(phi, R);
    
    // Объем конуса: V = (1/3)πr²h
    return (1.0 / 3.0) * PI * r * r * h;
}

double ConeOptimizer::coneVolumeDerivative(double phi, double R) {
    if (phi < 0 || phi >= 2.0 * PI) {
        throw std::invalid_argument("phi must be in [0, 2π)");
    }
    if (R <= 0) {
        throw std::invalid_argument("R must be positive");
    }
    
    // r = R(2π - φ)/(2π)
    // h = √(R² - r²) = √(R² - R²(2π - φ)²/(4π²))
    //    = R√(1 - (2π - φ)²/(4π²))
    //    = R√((4π² - (2π - φ)²)/(4π²))
    //    = (R/(2π))√(4π² - (2π - φ)²)
    
    // V = (1/3)πr²h = (1/3)πR²(2π - φ)²/(4π²) * h
    //    = (R²/(12π))(2π - φ)² * h
    
    // После упрощения производной:
    // dV/dφ = (R³/(12π²)) * (2π - φ) * (2(2π - φ)² - 3(2π - φ)² + 4π²) / √(...)
    // Более простой способ - численное дифференцирование или аналитическое
    
    // Аналитическая формула производной:
    double two_pi_minus_phi = 2.0 * PI - phi;
    double r = baseRadius(phi, R);
    double h = height(phi, R);
    
    if (h < EPSILON) {
        return 0.0;
    }
    
    // dr/dφ = -R/(2π)
    // dh/dφ = (R²/(2π)) * (2π - φ) / (h * 4π²)
    double dr_dphi = -R / (2.0 * PI);
    double dh_dphi = (R * R / (2.0 * PI)) * two_pi_minus_phi / (h * 4.0 * PI * PI);
    
    // dV/dφ = (1/3)π * (2r * h * dr/dφ + r² * dh/dφ)
    return (1.0 / 3.0) * PI * (2.0 * r * h * dr_dphi + r * r * dh_dphi);
}

double ConeOptimizer::findOptimalPhiAnalytical(double R) {
    // Аналитическое решение: φ = 2π(1 - √(2/3))
    // Это получается из условия V'(φ) = 0
    return 2.0 * PI * (1.0 - std::sqrt(2.0 / 3.0));
}

double ConeOptimizer::findOptimalPhi(double R) {
    if (R <= 0) {
        throw std::invalid_argument("R must be positive");
    }
    
    // Используем аналитическое решение
    return findOptimalPhiAnalytical(R);
    
    // Альтернатива: метод Ньютона (если нужно численное решение)
    /*
    double phi = PI; // Начальное приближение
    for (int i = 0; i < MAX_ITERATIONS; ++i) {
        double f = coneVolumeDerivative(phi, R);
        if (std::abs(f) < EPSILON) {
            return phi;
        }
        
        // Численная производная для метода Ньютона
        double h = 1e-6;
        double f_prime = (coneVolumeDerivative(phi + h, R) - f) / h;
        
        if (std::abs(f_prime) < EPSILON) {
            break; // Не можем продолжить
        }
        
        phi = phi - f / f_prime;
        
        // Ограничиваем phi в допустимых пределах
        if (phi < 0) phi = 0;
        if (phi >= 2.0 * PI) phi = 2.0 * PI - EPSILON;
    }
    
    return phi;
    */
}

} // namespace Task2

