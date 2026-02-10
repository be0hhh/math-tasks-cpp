#include "inequality.h"
#include <cmath>
#include <algorithm>

namespace Task1 {

double InequalityChecker::nthRoot(double m, int n) {
    if (n <= 0) {
        return 0.0; // Некорректный вход
    }
    if (m < 0 && n % 2 == 0) {
        return 0.0; // Четный корень из отрицательного числа
    }
    if (m == 0) {
        return 0.0;
    }
    
    // Используем pow для вычисления корня
    return std::pow(std::abs(m), 1.0 / n) * (m < 0 ? -1.0 : 1.0);
}

double InequalityChecker::evaluateInequality(int m, int n) {
    if (m <= 0 || n <= 0) {
        return 0.0;
    }
    
    // Вычисляем m^(1/n) и n^(1/m)
    double m_to_1_over_n = nthRoot(static_cast<double>(m), n);
    double n_to_1_over_m = nthRoot(static_cast<double>(n), m);
    
    // Проверяем на деление на ноль
    if (std::abs(m_to_1_over_n) < EPSILON || std::abs(n_to_1_over_m) < EPSILON) {
        return 0.0;
    }
    
    // Вычисляем 1/(m^(1/n)) + 1/(n^(1/m))
    return 1.0 / m_to_1_over_n + 1.0 / n_to_1_over_m;
}

bool InequalityChecker::checkInequality(int m, int n) {
    double value = evaluateInequality(m, n);
    return value > 1.0 + EPSILON; // Учитываем погрешность вычислений
}

std::vector<std::pair<int, int>> InequalityChecker::verifyForRange(int m_max, int n_max) {
    std::vector<std::pair<int, int>> violations;
    
    for (int m = 1; m <= m_max; ++m) {
        for (int n = 1; n <= n_max; ++n) {
            if (!checkInequality(m, n)) {
                violations.push_back({m, n});
            }
        }
    }
    
    return violations;
}

int InequalityChecker::countValidPairs(int m_max, int n_max) {
    int count = 0;
    
    for (int m = 1; m <= m_max; ++m) {
        for (int n = 1; n <= n_max; ++n) {
            if (checkInequality(m, n)) {
                ++count;
            }
        }
    }
    
    return count;
}

} // namespace Task1

