#include "polynomial.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace Task3;

// Функция для красивого вывода чисел (целые без .0000000)
std::string formatNumber(double value, int precision = 10) {
    if (std::abs(value - std::round(value)) < 1e-10) {
        // Целое число
        return std::to_string(static_cast<long long>(std::round(value)));
    } else {
        // Дробное число
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(precision);
        oss << value;
        std::string str = oss.str();
        // Удаляем лишние нули в конце
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') str.pop_back();
        return str;
    }
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "ЗАДАЧА: ПОЛИНОМ И ПРОИЗВОДНЫЕ" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nУСЛОВИЕ:" << std::endl;
    std::cout << "Дано: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2" << std::endl;
    std::cout << "\nНайти:" << std::endl;
    std::cout << "  1. p(2) = ?" << std::endl;
    std::cout << "  2. p'(1)" << std::endl;
    std::cout << "  3. p''(3)" << std::endl;
    std::cout << "  4. p'''(-1)" << std::endl;
    std::cout << "  5. Разложение по (x-1)^k, k=0,...,5" << std::endl;
    
    std::cout << "\nАЛГОРИТМ РЕШЕНИЯ (подробно):" << std::endl;
    std::cout << "\n1. ВЫЧИСЛЕНИЕ ЗНАЧЕНИЯ ПОЛИНОМА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно найти значение p(x) в конкретной точке" << std::endl;
    std::cout << "   ПОЧЕМУ схема Горнера:" << std::endl;
    std::cout << "   - Обычный способ: вычисляем каждую степень отдельно" << std::endl;
    std::cout << "     (x^5, x^4, x^3, ...) - много операций умножения" << std::endl;
    std::cout << "   - Схема Горнера: группируем вычисления" << std::endl;
    std::cout << "     p(x) = a₀ + x(a₁ + x(a₂ + x(a₃ + x(a₄ + x·a₅))))" << std::endl;
    std::cout << "   - Преимущества: меньше операций, выше точность" << std::endl;
    std::cout << "   - Пример для p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2:" << std::endl;
    std::cout << "     p(x) = -2 + x(1 + x(-1 + x(3 + x(-2 + x·1))))" << std::endl;
    
    std::cout << "\n2. ВЫЧИСЛЕНИЕ ПРОИЗВОДНЫХ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Производная показывает скорость изменения функции" << std::endl;
    std::cout << "   ПОЧЕМУ так вычисляем:" << std::endl;
    std::cout << "   - Правило: (x^n)' = n·x^(n-1)" << std::endl;
    std::cout << "   - Применяем к каждому слагаемому:" << std::endl;
    std::cout << "     (x^5)' = 5x^4, (-2x^4)' = -8x^3, (3x^3)' = 9x^2, ..." << std::endl;
    std::cout << "   - Первая производная:" << std::endl;
    std::cout << "     p'(x) = 5x^4 - 8x^3 + 9x^2 - 2x + 1" << std::endl;
    std::cout << "   - Вторая производная (производная от первой):" << std::endl;
    std::cout << "     p''(x) = 20x^3 - 24x^2 + 18x - 2" << std::endl;
    std::cout << "   - Третья производная (производная от второй):" << std::endl;
    std::cout << "     p'''(x) = 60x^2 - 48x + 18" << std::endl;
    std::cout << "   - Затем подставляем нужную точку x" << std::endl;
    
    std::cout << "\n3. РАЗЛОЖЕНИЕ В РЯД ТЕЙЛОРА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Представить полином в виде суммы степеней (x-a)" << std::endl;
    std::cout << "   ПОЧЕМУ это полезно:" << std::endl;
    std::cout << "   - Позволяет анализировать поведение функции около точки a" << std::endl;
    std::cout << "   - Коэффициенты показывают, как функция 'растет' от точки a" << std::endl;
    std::cout << "   - Формула: p(x) = c₀ + c₁(x-a) + c₂(x-a)² + c₃(x-a)³ + ..." << std::endl;
    std::cout << "   - Где: cₖ = p^(k)(a) / k!" << std::endl;
    std::cout << "   - ПОЧЕМУ делим на k!:" << std::endl;
    std::cout << "     При дифференцировании (x-a)^k получаем k·(x-a)^(k-1)" << std::endl;
    std::cout << "     Чтобы получить правильный коэффициент, нужно компенсировать" << std::endl;
    std::cout << "     множитель k, поэтому делим на k!" << std::endl;
    std::cout << "   - Для разложения по (x-1)^k:" << std::endl;
    std::cout << "     c₀ = p(1) / 0! = p(1)" << std::endl;
    std::cout << "     c₁ = p'(1) / 1! = p'(1)" << std::endl;
    std::cout << "     c₂ = p''(1) / 2! = p''(1) / 2" << std::endl;
    std::cout << "     c₃ = p'''(1) / 3! = p'''(1) / 6" << std::endl;
    std::cout << "     и так далее..." << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    
    std::cout << "\nПолином: " << p.toString() << std::endl;
    std::cout << "\nВыберите операцию:" << std::endl;
    std::cout << "  0 - РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ (алгоритм + вычисления)" << std::endl;
    std::cout << "  1 - Вычислить p(x) в точке" << std::endl;
    std::cout << "  2 - Вычислить p'(x) в точке" << std::endl;
    std::cout << "  3 - Вычислить p''(x) в точке" << std::endl;
    std::cout << "  4 - Вычислить p'''(x) в точке" << std::endl;
    std::cout << "  5 - Разложение в ряд Тейлора" << std::endl;
    std::cout << "  6 - Все задания из задачи" << std::endl;
    std::cout << "\nВаш выбор (0-6): ";
    
    int choice;
    std::cin >> choice;
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    switch (choice) {
        case 0: {
            std::cout << "\n========================================" << std::endl;
            std::cout << "РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ" << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "\nПОЛНЫЙ АЛГОРИТМ РЕШЕНИЯ:" << std::endl;
            std::cout << "\nШАГ 1: Вычисление p(2)" << std::endl;
            std::cout << "Используем схему Горнера:" << std::endl;
            std::cout << "p(x) = -2 + x(1 + x(-1 + x(3 + x(-2 + x·1))))" << std::endl;
            std::cout << "Подставляем x = 2:" << std::endl;
            std::cout << "  Шаг 1: -2 + 2·1 = " << formatNumber(-2.0 + 2.0*1.0) << std::endl;
            std::cout << "  Шаг 2: " << formatNumber(-2.0 + 2.0*1.0) << " + 2·(-1) = " 
                      << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0)) << std::endl;
            std::cout << "  Шаг 3: " << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0)) << " + 2²·3 = " 
                      << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0) + 4.0*3.0) << std::endl;
            std::cout << "  Шаг 4: " << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0) + 4.0*3.0) 
                      << " + 2³·(-2) = " << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0) + 4.0*3.0 + 8.0*(-2.0)) << std::endl;
            std::cout << "  Шаг 5: " << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0) + 4.0*3.0 + 8.0*(-2.0)) 
                      << " + 2⁴·1 = " << formatNumber(-2.0 + 2.0*1.0 + 2.0*(-1.0) + 4.0*3.0 + 8.0*(-2.0) + 16.0*1.0) << std::endl;
            double p2 = p.evaluate(2.0);
            std::cout << "\nРезультат: p(2) = " << formatNumber(p2) << std::endl;
            std::cout << "\nПроверка: 2^5 - 2·2^4 + 3·2^3 - 2^2 + 2 - 2" << std::endl;
            std::cout << "        = " << formatNumber(32.0) << " - " << formatNumber(32.0) 
                      << " + " << formatNumber(24.0) << " - " << formatNumber(4.0) 
                      << " + " << formatNumber(2.0) << " - " << formatNumber(2.0) 
                      << " = " << formatNumber(20.0) << std::endl;
            
            std::cout << "\nШАГ 2: Вычисление p'(1)" << std::endl;
            std::cout << "Находим производную:" << std::endl;
            std::cout << "p'(x) = 5x^4 - 8x^3 + 9x^2 - 2x + 1" << std::endl;
            std::cout << "Подставляем x = 1:" << std::endl;
            double term1_p = 5.0 * 1.0 * 1.0 * 1.0 * 1.0;
            double term2_p = -8.0 * 1.0 * 1.0 * 1.0;
            double term3_p = 9.0 * 1.0 * 1.0;
            double term4_p = -2.0 * 1.0;
            double term5_p = 1.0;
            std::cout << "  p'(1) = 5·1⁴ - 8·1³ + 9·1² - 2·1 + 1" << std::endl;
            std::cout << "  p'(1) = " << formatNumber(term1_p) << " - " << formatNumber(-term2_p) 
                      << " + " << formatNumber(term3_p) << " - " << formatNumber(-term4_p) 
                      << " + " << formatNumber(term5_p) << std::endl;
            std::cout << "  p'(1) = " << formatNumber(term1_p) << " + " << formatNumber(term2_p) 
                      << " + " << formatNumber(term3_p) << " + " << formatNumber(term4_p) 
                      << " + " << formatNumber(term5_p) << std::endl;
            double p_prime_1 = p.evaluateDerivative(1.0, 1);
            std::cout << "  Результат: p'(1) = " << formatNumber(p_prime_1) << std::endl;
            std::cout << "\nПроверка: 5 - 8 + 9 - 2 + 1 = " << formatNumber(5.0) << " - " 
                      << formatNumber(8.0) << " + " << formatNumber(9.0) << " - " 
                      << formatNumber(2.0) << " + " << formatNumber(1.0) << " = " 
                      << formatNumber(5.0) << std::endl;
            
            std::cout << "\nШАГ 3: Вычисление p''(3)" << std::endl;
            std::cout << "Вторая производная:" << std::endl;
            std::cout << "p''(x) = 20x^3 - 24x^2 + 18x - 2" << std::endl;
            std::cout << "Подставляем x = 3:" << std::endl;
            double t1_pp = 20.0 * 3.0 * 3.0 * 3.0;
            double t2_pp = -24.0 * 3.0 * 3.0;
            double t3_pp = 18.0 * 3.0;
            double t4_pp = -2.0;
            std::cout << "  p''(3) = 20·3³ - 24·3² + 18·3 - 2" << std::endl;
            std::cout << "  p''(3) = 20·" << formatNumber(27.0) << " - 24·" << formatNumber(9.0) 
                      << " + 18·" << formatNumber(3.0) << " - " << formatNumber(2.0) << std::endl;
            std::cout << "  p''(3) = " << formatNumber(t1_pp) << " + " << formatNumber(t2_pp) 
                      << " + " << formatNumber(t3_pp) << " + " << formatNumber(t4_pp) << std::endl;
            double p_double_prime_3 = p.evaluateDerivative(3.0, 2);
            std::cout << "  Результат: p''(3) = " << formatNumber(p_double_prime_3) << std::endl;
            std::cout << "\nПроверка: 20·27 - 24·9 + 18·3 - 2" << std::endl;
            std::cout << "        = " << formatNumber(540.0) << " - " << formatNumber(216.0) 
                      << " + " << formatNumber(54.0) << " - " << formatNumber(2.0) 
                      << " = " << formatNumber(376.0) << std::endl;
            
            std::cout << "\nШАГ 4: Вычисление p'''(-1)" << std::endl;
            std::cout << "Третья производная:" << std::endl;
            std::cout << "p'''(x) = 60x^2 - 48x + 18" << std::endl;
            std::cout << "Подставляем x = -1:" << std::endl;
            double t1_ppp = 60.0 * (-1.0) * (-1.0);
            double t2_ppp = -48.0 * (-1.0);
            double t3_ppp = 18.0;
            std::cout << "  p'''(-1) = 60·(-1)² - 48·(-1) + 18" << std::endl;
            std::cout << "  p'''(-1) = 60·" << formatNumber(1.0) << " - 48·(" << formatNumber(-1.0) 
                      << ") + " << formatNumber(18.0) << std::endl;
            std::cout << "  p'''(-1) = " << formatNumber(t1_ppp) << " + " << formatNumber(-t2_ppp) 
                      << " + " << formatNumber(t3_ppp) << std::endl;
            double p_triple_prime_minus1 = p.evaluateDerivative(-1.0, 3);
            std::cout << "  Результат: p'''(-1) = " << formatNumber(p_triple_prime_minus1) << std::endl;
            std::cout << "\nПроверка: 60·1 - 48·(-1) + 18" << std::endl;
            std::cout << "        = " << formatNumber(60.0) << " + " << formatNumber(48.0) 
                      << " + " << formatNumber(18.0) << " = " << formatNumber(126.0) << std::endl;
            
            std::cout << "\nШАГ 5: Разложение по (x-1)^k, k=0..5" << std::endl;
            std::cout << "Формула: p(x) = Σ cₖ(x-1)^k, где cₖ = p^(k)(1)/k!" << std::endl;
            std::cout << "\nВычисляем производные в точке x=1:" << std::endl;
            double p_at_1 = p.evaluate(1.0);
            double p1_deriv = p.evaluateDerivative(1.0, 1);
            double p2_deriv = p.evaluateDerivative(1.0, 2);
            double p3_deriv = p.evaluateDerivative(1.0, 3);
            double p4_deriv = p.evaluateDerivative(1.0, 4);
            double p5_deriv = p.evaluateDerivative(1.0, 5);
            std::cout << "  p(1) = " << formatNumber(p_at_1) << std::endl;
            std::cout << "  p'(1) = " << formatNumber(p1_deriv) << std::endl;
            std::cout << "  p''(1) = " << formatNumber(p2_deriv) << std::endl;
            std::cout << "  p'''(1) = " << formatNumber(p3_deriv) << std::endl;
            std::cout << "  p^(4)(1) = " << formatNumber(p4_deriv) << std::endl;
            std::cout << "  p^(5)(1) = " << formatNumber(p5_deriv) << std::endl;
            std::cout << "\nДелим на факториалы:" << std::endl;
            auto taylor = p.taylorExpansion(1.0, 5);
            std::cout << "  c₀ = p(1) / 0! = " << formatNumber(p_at_1) << " / 1 = " << formatNumber(taylor[0]) << std::endl;
            std::cout << "  c₁ = p'(1) / 1! = " << formatNumber(p1_deriv) << " / 1 = " << formatNumber(taylor[1]) << std::endl;
            std::cout << "  c₂ = p''(1) / 2! = " << formatNumber(p2_deriv) << " / 2 = " << formatNumber(taylor[2]) << std::endl;
            std::cout << "  c₃ = p'''(1) / 3! = " << formatNumber(p3_deriv) << " / 6 = " << formatNumber(taylor[3]) << std::endl;
            std::cout << "  c₄ = p^(4)(1) / 4! = " << formatNumber(p4_deriv) << " / 24 = " << formatNumber(taylor[4]) << std::endl;
            std::cout << "  c₅ = p^(5)(1) / 5! = " << formatNumber(p5_deriv) << " / 120 = " << formatNumber(taylor[5]) << std::endl;
            std::cout << "\nИтоговое разложение:" << std::endl;
            std::cout << "p(x) = ";
            bool first = true;
            for (size_t k = 0; k < taylor.size(); ++k) {
                if (std::abs(taylor[k]) < 1e-10) continue;
                if (!first) {
                    if (taylor[k] >= 0) std::cout << " + ";
                    else std::cout << " - ";
                } else {
                    if (taylor[k] < 0) std::cout << "-";
                    first = false;
                }
                std::cout << formatNumber(std::abs(taylor[k]));
                if (k == 1) std::cout << "(x-1)";
                else if (k > 1) std::cout << "(x-1)^" << k;
            }
            std::cout << std::endl;
            break;
        }
        case 1: {
            double x;
            std::cout << "Введите значение x: ";
            std::cin >> x;
            double value = p.evaluate(x);
            std::cout << "p(" << formatNumber(x) << ") = " << formatNumber(value) << std::endl;
            break;
        }
        case 2: {
            double x;
            std::cout << "Введите значение x: ";
            std::cin >> x;
            double value = p.evaluateDerivative(x, 1);
            std::cout << "p'(" << formatNumber(x) << ") = " << formatNumber(value) << std::endl;
            break;
        }
        case 3: {
            double x;
            std::cout << "Введите значение x: ";
            std::cin >> x;
            double value = p.evaluateDerivative(x, 2);
            std::cout << "p''(" << formatNumber(x) << ") = " << formatNumber(value) << std::endl;
            break;
        }
        case 4: {
            double x;
            std::cout << "Введите значение x: ";
            std::cin >> x;
            double value = p.evaluateDerivative(x, 3);
            std::cout << "p'''(" << formatNumber(x) << ") = " << formatNumber(value) << std::endl;
            break;
        }
        case 5: {
            double center;
            int maxDegree;
            std::cout << "Введите центр разложения: ";
            std::cin >> center;
            std::cout << "Введите максимальную степень: ";
            std::cin >> maxDegree;
            auto taylor = p.taylorExpansion(center, maxDegree);
            std::cout << "\nРазложение по (x-" << center << ")^k, k=0.." << maxDegree << ":" << std::endl;
            for (size_t k = 0; k < taylor.size(); ++k) {
                std::cout << "  c_" << k << " = " << formatNumber(taylor[k]) << std::endl;
            }
            break;
        }
        case 6: {
            std::cout << "\nВсе задания из задачи:" << std::endl;
            
            double p2 = p.evaluate(2.0);
            std::cout << "1. p(2) = " << formatNumber(p2) << std::endl;
            
            double p_prime_1 = p.evaluateDerivative(1.0, 1);
            std::cout << "2. p'(1) = " << formatNumber(p_prime_1) << std::endl;
            
            double p_double_prime_3 = p.evaluateDerivative(3.0, 2);
            std::cout << "3. p''(3) = " << formatNumber(p_double_prime_3) << std::endl;
            
            double p_triple_prime_minus1 = p.evaluateDerivative(-1.0, 3);
            std::cout << "4. p'''(-1) = " << formatNumber(p_triple_prime_minus1) << std::endl;
            
            std::cout << "\n5. Разложение по (x-1)^k, k=0..5:" << std::endl;
            auto taylor = p.taylorExpansion(1.0, 5);
            for (size_t k = 0; k < taylor.size(); ++k) {
                std::cout << "   c_" << k << " = " << formatNumber(taylor[k]) << std::endl;
            }
            break;
        }
        default:
            std::cout << "Неверный выбор!" << std::endl;
            return 1;
    }
    
    return 0;
}

