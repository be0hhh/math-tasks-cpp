#include "complex_polynomial.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <sstream>

using namespace Task5;

// Функция для красивого вывода чисел (целые без .0000000)
std::string formatNumber(double value, int precision = 10) {
    if (std::abs(value - std::round(value)) < 1e-10) {
        return std::to_string(static_cast<long long>(std::round(value)));
    } else {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << value;
        std::string str = oss.str();
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') str.pop_back();
        return str;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "ЗАДАЧА 5: ПОЛИНОМ В КОМПЛЕКСНОЙ ТОЧКЕ" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nУСЛОВИЕ:" << std::endl;
    std::cout << "Рассмотрим вопрос о вычислении алгебраического" << std::endl;
    std::cout << "полинома P_n(x) с вещественными коэффициентами" << std::endl;
    std::cout << "в комплексной точке z₀ = u₀ + iv₀." << std::endl;
    std::cout << "\nРазделим полином P_n(x) на (x - z₀)(x - ẑ₀):" << std::endl;
    std::cout << "  (x - z₀)(x - ẑ₀) = (x - u₀ - iv₀)(x - u₀ + iv₀)" << std::endl;
    std::cout << "                    = (x - u₀)² + v₀²" << std::endl;
    std::cout << "                    = x² - 2u₀x + u₀² + v₀²" << std::endl;
    std::cout << "                    = x² + px + q" << std::endl;
    std::cout << "где p = -2u₀, q = u₀² + v₀²" << std::endl;
    
    std::cout << "\nАЛГОРИТМ РЕШЕНИЯ (подробно):" << std::endl;
    std::cout << "\n1. ВЫЧИСЛЕНИЕ ПОЛИНОМА В КОМПЛЕКСНОЙ ТОЧКЕ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно найти значение P(z) для комплексного z" << std::endl;
    std::cout << "   ПОЧЕМУ схема Горнера:" << std::endl;
    std::cout << "   - Работает так же, как для вещественных чисел" << std::endl;
    std::cout << "   - Но все операции выполняются с комплексными числами" << std::endl;
    std::cout << "   - P(z) = a₀ + z(a₁ + z(a₂ + z(...)))" << std::endl;
    std::cout << "   - Результат - комплексное число: P(z) = u + iv" << std::endl;
    
    std::cout << "\n2. КВАДРАТИЧНЫЙ МНОЖИТЕЛЬ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Разделить полином на (x-z₀)(x-ẑ₀)" << std::endl;
    std::cout << "   ПОЧЕМУ именно такой множитель:" << std::endl;
    std::cout << "   - Если z₀ - комплексный корень, то ẑ₀ (сопряженный) тоже корень" << std::endl;
    std::cout << "   - (x-z₀)(x-ẑ₀) = (x-u₀-iv₀)(x-u₀+iv₀)" << std::endl;
    std::cout << "   - Раскрываем скобки: (x-u₀)² - (iv₀)² = (x-u₀)² + v₀²" << std::endl;
    std::cout << "   - Получаем: x² - 2u₀x + u₀² + v₀²" << std::endl;
    std::cout << "   - Это вещественный квадратичный полином!" << std::endl;
    
    std::cout << "\n3. КОЭФФИЦИЕНТЫ p И q:" << std::endl;
    std::cout << "   ЗАЧЕМ: Привести к виду x² + px + q" << std::endl;
    std::cout << "   ПОЧЕМУ такие значения:" << std::endl;
    std::cout << "   - Из x² - 2u₀x + u₀² + v₀² = x² + px + q" << std::endl;
    std::cout << "   - Сравниваем коэффициенты:" << std::endl;
    std::cout << "     p = -2u₀  (коэффициент при x)" << std::endl;
    std::cout << "     q = u₀² + v₀²  (свободный член)" << std::endl;
    std::cout << "   - Заметим: q = |z₀|² (квадрат модуля комплексного числа)" << std::endl;
    
    std::cout << "\n4. СИНТЕТИЧЕСКОЕ ДЕЛЕНИЕ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Найти частное Q(x) и остаток R(x)" << std::endl;
    std::cout << "   ПОЧЕМУ этот метод:" << std::endl;
    std::cout << "   - Эффективный способ деления полинома на (x²+px+q)" << std::endl;
    std::cout << "   - Работаем с коэффициентами, не раскрывая скобки" << std::endl;
    std::cout << "   - Остаток будет степени не выше 1 (линейный или константа)" << std::endl;
    std::cout << "   - Если z₀ - корень, то остаток должен быть близок к нулю" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    
    std::cout << "\nВыберите операцию:" << std::endl;
    std::cout << "  0 - РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ (алгоритм + вычисления)" << std::endl;
    std::cout << "  1 - Вычислить полином в комплексной точке" << std::endl;
    std::cout << "  2 - Разделить полином на квадратичный множитель" << std::endl;
    std::cout << "  3 - Использовать полином из задачи 3" << std::endl;
    std::cout << "\nВаш выбор (0-3): ";
    
    int choice;
    std::cin >> choice;
    
    ComplexPolynomial p({0.0}); // Инициализируем нулевым полиномом
    
    if (choice == 0) {
        // Решение задачи из задания
        std::cout << "\n========================================" << std::endl;
        std::cout << "РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "\nПОЛНЫЙ АЛГОРИТМ РЕШЕНИЯ:" << std::endl;
        std::cout << "\nШАГ 1: Вычисление полинома в комплексной точке (схема Горнера)" << std::endl;
        std::cout << "Для вычисления P(z) используем схему Горнера:" << std::endl;
        std::cout << "P(z) = a₀ + z(a₁ + z(a₂ + z(a₃ + ... + z·aₙ)...))" << std::endl;
        std::cout << "Это эффективный способ вычисления полинома в комплексной точке" << std::endl;
        std::cout << "\nШАГ 2: Вычисление коэффициентов p и q" << std::endl;
        std::cout << "Для комплексной точки z₀ = u₀ + iv₀:" << std::endl;
        std::cout << "(x - z₀)(x - ẑ₀) = (x - u₀ - iv₀)(x - u₀ + iv₀)" << std::endl;
        std::cout << "                  = (x - u₀)² + v₀²" << std::endl;
        std::cout << "                  = x² - 2u₀x + u₀² + v₀²" << std::endl;
        std::cout << "                  = x² + px + q" << std::endl;
        std::cout << "\nОтсюда: p = -2u₀, q = u₀² + v₀²" << std::endl;
        std::cout << "\nШАГ 3: Деление полинома" << std::endl;
        std::cout << "P(x) = Q(x)(x² + px + q) + остаток" << std::endl;
        std::cout << "где остаток - линейный полином: остаток = Ax + B" << std::endl;
        std::cout << "\nШАГ 4: Проверка" << std::endl;
        std::cout << "Если z₀ - корень, то P(z₀) = 0" << std::endl;
        std::cout << "Остаток в точке z₀: остаток(z₀) = A·z₀ + B ≈ P(z₀)" << std::endl;
        std::cout << "\n========================================" << std::endl;
        std::cout << "\nВведите данные для вычисления:" << std::endl;
        
        // Используем полином из задачи 3
        p = ComplexPolynomial({-2.0, 1.0, -1.0, 3.0, -2.0, 1.0});
        std::cout << "Полином: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2" << std::endl;
        
        double u0, v0;
        std::cout << "\nВведите вещественную часть z₀: ";
        std::cin >> u0;
        std::cout << "Введите мнимую часть z₀: ";
        std::cin >> v0;
        
        std::cout << "\n========================================" << std::endl;
        std::cout << "ВЫЧИСЛЕНИЯ:" << std::endl;
        std::cout << "========================================" << std::endl;
        
        std::cout << "\n1. Вычисление P(z₀) по схеме Горнера:" << std::endl;
        Complex z0_check(u0, v0);
        std::cout << "   Полином: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2" << std::endl;
        std::cout << "   Коэффициенты: a₀ = -2, a₁ = 1, a₂ = -1, a₃ = 3, a₄ = -2, a₅ = 1" << std::endl;
        std::cout << "   Точка: z₀ = " << formatNumber(u0) << " + " << formatNumber(v0) << "i" << std::endl;
        std::cout << "   Схема Горнера: P(z) = a₀ + z(a₁ + z(a₂ + z(a₃ + z(a₄ + z·a₅))))" << std::endl;
        std::cout << "   Вычисляем от старшей степени к младшей:" << std::endl;
        std::cout << "     Шаг 1: result = a₅ = 1" << std::endl;
        std::cout << "     Шаг 2: result = result·z + a₄ = 1·z - 2" << std::endl;
        std::cout << "     Шаг 3: result = result·z + a₃ = (z - 2)·z + 3" << std::endl;
        std::cout << "     Шаг 4: result = result·z + a₂ = ...·z - 1" << std::endl;
        std::cout << "     Шаг 5: result = result·z + a₁ = ...·z + 1" << std::endl;
        std::cout << "     Шаг 6: result = result·z + a₀ = ...·z - 2" << std::endl;
        Complex p_at_z0_check = p.evaluate(z0_check);
        std::cout << "   Результат: P(z₀) = " << formatNumber(p_at_z0_check.real) << " + " 
                  << formatNumber(p_at_z0_check.imag) << "i" << std::endl;
        
        auto [p_coeff, q_coeff] = ComplexPolynomial::computeQuadraticCoeffs(u0, v0);
        std::cout << "\n2. Коэффициенты квадратичного множителя:" << std::endl;
        std::cout << "   z₀ = " << formatNumber(u0) << " + " << formatNumber(v0) << "i" << std::endl;
        double u0_sq = u0*u0;
        double v0_sq = v0*v0;
        std::cout << "   p = -2u₀ = -2·" << formatNumber(u0) << " = " << formatNumber(p_coeff) << std::endl;
        std::cout << "   q = u₀² + v₀²" << std::endl;
        std::cout << "   q = " << formatNumber(u0) << "² + " << formatNumber(v0) << "²" << std::endl;
        std::cout << "   q = " << formatNumber(u0_sq) << " + " << formatNumber(v0_sq) << " = " 
                  << formatNumber(q_coeff) << std::endl;
        std::cout << "   Квадратичный множитель: x² + (" << formatNumber(p_coeff) << ")x + (" 
                  << formatNumber(q_coeff) << ")" << std::endl;
        
        auto [quotient, remainder] = p.divideByQuadratic(u0, v0);
        
        std::cout << "\n3. Результат деления:" << std::endl;
        std::cout << "   Остаток: " << formatNumber(remainder.second) << "x + " 
                  << formatNumber(remainder.first) << std::endl;
        
        Complex z0(u0, v0);
        Complex p_at_z0 = p.evaluate(z0);
        Complex remainder_at_z0(remainder.first + remainder.second * z0.real, 
                               remainder.second * z0.imag);
        
        std::cout << "\n4. Проверка:" << std::endl;
        std::cout << "   P(z₀) = " << formatNumber(p_at_z0.real) << " + " 
                  << formatNumber(p_at_z0.imag) << "i" << std::endl;
        std::cout << "   Остаток(z₀) = " << formatNumber(remainder.second) << "·(" 
                  << formatNumber(z0.real) << " + " << formatNumber(z0.imag) << "i) + " 
                  << formatNumber(remainder.first) << std::endl;
        std::cout << "   Остаток(z₀) = " << formatNumber(remainder_at_z0.real) << " + " 
                  << formatNumber(remainder_at_z0.imag) << "i" << std::endl;
        double diff_real = p_at_z0.real - remainder_at_z0.real;
        double diff_imag = p_at_z0.imag - remainder_at_z0.imag;
        std::cout << "   Разница: " << formatNumber(diff_real) << " + " 
                  << formatNumber(diff_imag) << "i" << std::endl;
        
        return 0;
    }
    
    if (choice == 3) {
        // Полином из задачи 3: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2
        p = ComplexPolynomial({-2.0, 1.0, -1.0, 3.0, -2.0, 1.0});
        std::cout << "\nИспользуется полином: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2" << std::endl;
    } else {
        int degree;
        std::cout << "\nВведите степень полинома: ";
        std::cin >> degree;
        
        std::vector<double> coeffs;
        std::cout << "Введите коэффициенты от младшей степени к старшей:" << std::endl;
        for (int i = 0; i <= degree; ++i) {
            double coeff;
            std::cout << "  Коэффициент при x^" << i << ": ";
            std::cin >> coeff;
            coeffs.push_back(coeff);
        }
        
        p = ComplexPolynomial(coeffs);
    }
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    if (choice == 1) {
        double u0, v0;
        std::cout << "Введите вещественную часть z: ";
        std::cin >> u0;
        std::cout << "Введите мнимую часть z: ";
        std::cin >> v0;
        
        Complex z(u0, v0);
        Complex result = p.evaluate(z);
        
        std::cout << "\np(" << formatNumber(z.real) << " + " << formatNumber(z.imag) << "i) = " 
                  << formatNumber(result.real) << " + " << formatNumber(result.imag) << "i" << std::endl;
        std::cout << "  Вещественная часть: " << formatNumber(result.real) << std::endl;
        std::cout << "  Мнимая часть: " << formatNumber(result.imag) << std::endl;
        std::cout << "  Модуль: " << formatNumber(result.modulus()) << std::endl;
        
    } else if (choice == 2) {
        double u0, v0;
        std::cout << "Введите вещественную часть z₀: ";
        std::cin >> u0;
        std::cout << "Введите мнимую часть z₀: ";
        std::cin >> v0;
        
        auto [p_coeff, q_coeff] = ComplexPolynomial::computeQuadraticCoeffs(u0, v0);
        std::cout << "\nКвадратичный множитель: (x - z₀)(x - ẑ₀) = x² + px + q" << std::endl;
        std::cout << "  где z₀ = " << formatNumber(u0) << " + " << formatNumber(v0) << "i" << std::endl;
        std::cout << "  p = " << formatNumber(p_coeff) << std::endl;
        std::cout << "  q = " << formatNumber(q_coeff) << std::endl;
        
        auto [quotient, remainder] = p.divideByQuadratic(u0, v0);
        
        std::cout << "\nРезультат деления:" << std::endl;
        std::cout << "  Остаток: " << formatNumber(remainder.second) << "x + " 
                  << formatNumber(remainder.first) << std::endl;
        
        // Проверяем значение в точке z₀
        Complex z0(u0, v0);
        Complex p_at_z0 = p.evaluate(z0);
        std::cout << "\nПроверка: p(z₀) = " << formatNumber(p_at_z0.real) << " + " 
                  << formatNumber(p_at_z0.imag) << "i" << std::endl;
        
    } else {
        std::cout << "Неверный выбор!" << std::endl;
        return 1;
    }
    
    return 0;
}

