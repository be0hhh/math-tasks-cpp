#include "inequality_abc.h"
#include <cmath>
#include <sstream>
#include <algorithm>

namespace Task4 {

double InequalityABC::leftSide(double a, double b, double c) {
    return a * a * a * b + b * b * b * c + c * c * c * a;
}

double InequalityABC::rightSide(double a, double b, double c) {
    return a * a * b * c + b * b * c * a + c * c * a * b;
}

double InequalityABC::verifyInequality(double a, double b, double c) {
    if (a < 0 || b < 0 || c < 0) {
        return 0.0; // Некорректный вход
    }
    
    double left = leftSide(a, b, c);
    double right = rightSide(a, b, c);
    
    return left - right;
}

bool InequalityABC::checkInequality(double a, double b, double c) {
    double diff = verifyInequality(a, b, c);
    return diff >= -EPSILON; // Учитываем погрешность вычислений
}

bool InequalityABC::isEquality(double a, double b, double c) {
    double diff = verifyInequality(a, b, c);
    return std::abs(diff) < EPSILON;
}

bool InequalityABC::checkEqualityCase_abc(double value) {
    // Когда a = b = c, неравенство становится:
    // a³a + a³a + a³a >= a²aa + a²aa + a²aa
    // 3a⁴ >= 3a⁴
    // Равенство выполняется!
    return isEquality(value, value, value);
}

bool InequalityABC::checkEqualityCase_zero(double a, double b, double c) {
    // Проверяем случаи, когда одна из переменных равна нулю
    // Если c = 0: a³b + 0 + 0 >= a²b*0 + 0 + 0
    //            a³b >= 0 (равенство только если a=0 или b=0)
    
    // Если a = 0: 0 + b³c + 0 >= 0 + b²c*0 + 0
    //            b³c >= 0 (равенство только если b=0 или c=0)
    
    // Если b = 0: a³*0 + 0 + c³a >= a²*0*c + 0 + c²a*0
    //            0 + 0 + c³a >= 0
    //            c³a >= 0 (равенство только если a=0 или c=0)
    
    // Равенство выполняется, когда хотя бы две переменные равны нулю
    int zero_count = 0;
    if (std::abs(a) < EPSILON) ++zero_count;
    if (std::abs(b) < EPSILON) ++zero_count;
    if (std::abs(c) < EPSILON) ++zero_count;
    
    return zero_count >= 2;
}

std::vector<std::tuple<double, double, double>> InequalityABC::findEqualityCases(
    double max_value, double step) {
    std::vector<std::tuple<double, double, double>> cases;
    
    // Проверяем случай a = b = c
    for (double val = 0.0; val <= max_value; val += step) {
        if (isEquality(val, val, val)) {
            cases.push_back({val, val, val});
        }
    }
    
    // Проверяем случаи с нулями
    for (double val = 0.0; val <= max_value; val += step) {
        if (isEquality(val, 0.0, 0.0)) cases.push_back({val, 0.0, 0.0});
        if (isEquality(0.0, val, 0.0)) cases.push_back({0.0, val, 0.0});
        if (isEquality(0.0, 0.0, val)) cases.push_back({0.0, 0.0, val});
    }
    
    // Удаляем дубликаты (приблизительно)
    std::vector<std::tuple<double, double, double>> unique_cases;
    for (const auto& t : cases) {
        bool is_duplicate = false;
        for (const auto& u : unique_cases) {
            if (std::abs(std::get<0>(t) - std::get<0>(u)) < EPSILON &&
                std::abs(std::get<1>(t) - std::get<1>(u)) < EPSILON &&
                std::abs(std::get<2>(t) - std::get<2>(u)) < EPSILON) {
                is_duplicate = true;
                break;
            }
        }
        if (!is_duplicate) {
            unique_cases.push_back(t);
        }
    }
    
    return unique_cases;
}

std::string InequalityABC::analyzeEqualityCases() {
    std::ostringstream oss;
    
    oss << "Анализ случаев равенства для неравенства:\n";
    oss << "a³b + b³c + c³a >= a²bc + b²ca + c²ab\n\n";
    
    oss << "Известные случаи равенства:\n";
    oss << "1. a = b = c (любые неотрицательные значения)\n";
    oss << "   При a = b = c = t: левая часть = 3t⁴, правая часть = 3t⁴\n";
    oss << "   Равенство выполняется!\n\n";
    
    oss << "2. Две переменные равны нулю\n";
    oss << "   Например, a = t, b = 0, c = 0: обе части равны 0\n";
    oss << "   Аналогично для других комбинаций.\n\n";
    
    oss << "3. Все переменные равны нулю (тривиальный случай)\n";
    
    return oss.str();
}

} // namespace Task4

