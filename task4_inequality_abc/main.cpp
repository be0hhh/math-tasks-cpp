#include "inequality_abc.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace Task4;

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
    std::cout << "ЗАДАЧА 13: НЕРАВЕНСТВО" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nУСЛОВИЕ:" << std::endl;
    std::cout << "Для a, b, c >= 0 доказать неравенство:" << std::endl;
    std::cout << "  a³b + b³c + c³a >= a²bc + b²ca + c²ab" << std::endl;
    std::cout << "Найти случаи равенства." << std::endl;
    
    std::cout << "\nАЛГОРИТМ РЕШЕНИЯ (подробно):" << std::endl;
    std::cout << "\n1. ВЫЧИСЛЕНИЕ ЛЕВОЙ ЧАСТИ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно вычислить значение левой части неравенства" << std::endl;
    std::cout << "   ПОЧЕМУ такая структура:" << std::endl;
    std::cout << "   - L = a³b + b³c + c³a" << std::endl;
    std::cout << "   - Каждое слагаемое имеет вид: (переменная)³ × (следующая переменная)" << std::endl;
    std::cout << "   - Это циклическая структура: a→b→c→a" << std::endl;
    
    std::cout << "\n2. ВЫЧИСЛЕНИЕ ПРАВОЙ ЧАСТИ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно сравнить с левой частью" << std::endl;
    std::cout << "   ПОЧЕМУ можно упростить:" << std::endl;
    std::cout << "   - R = a²bc + b²ca + c²ab" << std::endl;
    std::cout << "   - Выносим общий множитель: R = abc(a + b + c)" << std::endl;
    std::cout << "   - Это показывает симметрию правой части" << std::endl;
    
    std::cout << "\n3. ПРОВЕРКА НЕРАВЕНСТВА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Доказать, что L >= R для всех a, b, c >= 0" << std::endl;
    std::cout << "   ПОЧЕМУ через разность:" << std::endl;
    std::cout << "   - Вычисляем D = L - R" << std::endl;
    std::cout << "   - Если D >= 0, то неравенство выполняется" << std::endl;
    std::cout << "   - Учитываем погрешность вычислений" << std::endl;
    
    std::cout << "\n4. СЛУЧАИ РАВЕНСТВА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Найти, когда неравенство обращается в равенство" << std::endl;
    std::cout << "   ПОЧЕМУ a = b = c:" << std::endl;
    std::cout << "   - При a = b = c = t:" << std::endl;
    std::cout << "     L = t³t + t³t + t³t = 3t⁴" << std::endl;
    std::cout << "     R = t²tt + t²tt + t²tt = 3t⁴" << std::endl;
    std::cout << "   - Обе части равны, значит равенство!" << std::endl;
    std::cout << "   ПОЧЕМУ две переменные равны нулю:" << std::endl;
    std::cout << "   - Если, например, b = c = 0:" << std::endl;
    std::cout << "     L = a³·0 + 0 + 0 = 0" << std::endl;
    std::cout << "     R = a²·0·0 + 0 + 0 = 0" << std::endl;
    std::cout << "   - Опять равенство!" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "\nВыберите режим:" << std::endl;
    std::cout << "  0 - РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ (алгоритм + вычисления)" << std::endl;
    std::cout << "  1 - Проверить неравенство для своих чисел" << std::endl;
    std::cout << "\nВаш выбор (0-1): ";
    
    int mode;
    std::cin >> mode;
    
    double a, b, c;
    
    if (mode == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "\nПОЛНЫЙ АЛГОРИТМ РЕШЕНИЯ:" << std::endl;
        std::cout << "\nШАГ 1: Вычисление левой части" << std::endl;
        std::cout << "  L = a³b + b³c + c³a" << std::endl;
        std::cout << "\nШАГ 2: Вычисление правой части" << std::endl;
        std::cout << "  R = a²bc + b²ca + c²ab = abc(a + b + c)" << std::endl;
        std::cout << "\nШАГ 3: Проверка неравенства" << std::endl;
        std::cout << "  D = L - R >= 0" << std::endl;
        std::cout << "\nШАГ 4: Случаи равенства" << std::endl;
        std::cout << "  - a = b = c (любые неотрицательные)" << std::endl;
        std::cout << "  - Две переменные равны нулю" << std::endl;
        std::cout << "\n========================================" << std::endl;
        std::cout << "\nВЫЧИСЛЕНИЯ ДЛЯ ПРИМЕРА:" << std::endl;
    }
    
    std::cout << "\nВведите неотрицательное число a: ";
    std::cin >> a;
    
    std::cout << "Введите неотрицательное число b: ";
    std::cin >> b;
    
    std::cout << "Введите неотрицательное число c: ";
    std::cin >> c;
    
    if (a < 0 || b < 0 || c < 0) {
        std::cout << "Ошибка: все числа должны быть неотрицательными!" << std::endl;
        return 1;
    }
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    double left = InequalityABC::leftSide(a, b, c);
    double right = InequalityABC::rightSide(a, b, c);
    double diff = InequalityABC::verifyInequality(a, b, c);
    bool holds = InequalityABC::checkInequality(a, b, c);
    bool is_eq = InequalityABC::isEquality(a, b, c);
    
    std::cout << std::setprecision(15);
    
    if (mode == 0) {
        std::cout << "\nПОДРОБНЫЕ ВЫЧИСЛЕНИЯ:" << std::endl;
        std::cout << "1. Левая часть:" << std::endl;
        std::cout << "   L = a³b + b³c + c³a" << std::endl;
        double term1 = a*a*a*b;
        double term2 = b*b*b*c;
        double term3 = c*c*c*a;
        std::cout << "   L = " << a << "³·" << b << " + " << b << "³·" << c 
                  << " + " << c << "³·" << a << std::endl;
        std::cout << "   L = " << formatNumber(a*a*a) << "·" << formatNumber(b) 
                  << " + " << formatNumber(b*b*b) << "·" << formatNumber(c) 
                  << " + " << formatNumber(c*c*c) << "·" << formatNumber(a) << std::endl;
        std::cout << "   Промежуточные результаты:" << std::endl;
        std::cout << "     a³b = " << formatNumber(a*a*a) << "·" << formatNumber(b) 
                  << " = " << formatNumber(term1) << std::endl;
        std::cout << "     b³c = " << formatNumber(b*b*b) << "·" << formatNumber(c) 
                  << " = " << formatNumber(term2) << std::endl;
        std::cout << "     c³a = " << formatNumber(c*c*c) << "·" << formatNumber(a) 
                  << " = " << formatNumber(term3) << std::endl;
        std::cout << "   L = " << formatNumber(term1) << " + " << formatNumber(term2) 
                  << " + " << formatNumber(term3) << " = " << formatNumber(left) << std::endl;
        std::cout << "\n2. Правая часть:" << std::endl;
        std::cout << "   R = a²bc + b²ca + c²ab" << std::endl;
        double r_term1 = a*a*b*c;
        double r_term2 = b*b*c*a;
        double r_term3 = c*c*a*b;
        std::cout << "   R = " << a << "²·" << b << "·" << c << " + " << b << "²·" << c 
                  << "·" << a << " + " << c << "²·" << a << "·" << b << std::endl;
        std::cout << "   R = " << formatNumber(a*a) << "·" << formatNumber(b) << "·" << formatNumber(c) 
                  << " + " << formatNumber(b*b) << "·" << formatNumber(c) << "·" << formatNumber(a) 
                  << " + " << formatNumber(c*c) << "·" << formatNumber(a) << "·" << formatNumber(b) << std::endl;
        std::cout << "   Промежуточные результаты:" << std::endl;
        std::cout << "     a²bc = " << formatNumber(a*a) << "·" << formatNumber(b) << "·" << formatNumber(c) 
                  << " = " << formatNumber(r_term1) << std::endl;
        std::cout << "     b²ca = " << formatNumber(b*b) << "·" << formatNumber(c) << "·" << formatNumber(a) 
                  << " = " << formatNumber(r_term2) << std::endl;
        std::cout << "     c²ab = " << formatNumber(c*c) << "·" << formatNumber(a) << "·" << formatNumber(b) 
                  << " = " << formatNumber(r_term3) << std::endl;
        std::cout << "   R = " << formatNumber(r_term1) << " + " << formatNumber(r_term2) 
                  << " + " << formatNumber(r_term3) << " = " << formatNumber(right) << std::endl;
        std::cout << "   (альтернативно: R = abc(a+b+c) = " << formatNumber(a*b*c) << "·" 
                  << formatNumber(a+b+c) << " = " << formatNumber(right) << ")" << std::endl;
        std::cout << "\n3. Разность:" << std::endl;
        std::cout << "   D = L - R = " << formatNumber(left) << " - " << formatNumber(right) 
                  << " = " << formatNumber(diff) << std::endl;
        std::cout << "\n4. Проверка:" << std::endl;
        std::cout << "   D >= 0: " << (holds ? "ДА" : "НЕТ") << std::endl;
        if (is_eq) {
            std::cout << "   Равенство выполняется!" << std::endl;
        }
        
        std::cout << "\n5. Анализ случаев равенства:" << std::endl;
        if (a == b && b == c) {
            std::cout << "   Случай 1: a = b = c = " << a << std::endl;
            std::cout << "   При a = b = c = t:" << std::endl;
            std::cout << "   L = t³t + t³t + t³t = 3t⁴ = 3·" << formatNumber(a) << "⁴ = " 
                      << formatNumber(3*a*a*a*a) << std::endl;
            std::cout << "   R = t²tt + t²tt + t²tt = 3t⁴ = 3·" << formatNumber(a) << "⁴ = " 
                      << formatNumber(3*a*a*a*a) << std::endl;
            std::cout << "   L = R, значит равенство!" << std::endl;
        } else if ((std::abs(a) < 1e-10 && std::abs(b) < 1e-10) || 
                   (std::abs(b) < 1e-10 && std::abs(c) < 1e-10) || 
                   (std::abs(c) < 1e-10 && std::abs(a) < 1e-10)) {
            std::cout << "   Случай 2: Две переменные равны нулю" << std::endl;
            std::cout << "   При этом обе части равны 0" << std::endl;
        } else {
            std::cout << "   Для данных значений равенство не выполняется" << std::endl;
            std::cout << "   (равенство только при a=b=c или когда две переменные = 0)" << std::endl;
        }
    } else {
        std::cout << "Левая часть:  a³b + b³c + c³a = " << formatNumber(left) << std::endl;
        std::cout << "Правая часть: a²bc + b²ca + c²ab = " << formatNumber(right) << std::endl;
        std::cout << "Разность (левая - правая): " << formatNumber(diff) << std::endl;
        std::cout << "\nНеравенство " << (holds ? "ВЫПОЛНЯЕТСЯ" : "НЕ ВЫПОЛНЯЕТСЯ") << std::endl;
        if (is_eq) {
            std::cout << "Равенство выполняется!" << std::endl;
        } else {
            std::cout << "Равенство не выполняется." << std::endl;
        }
        if (a == b && b == c) {
            std::cout << "\nПримечание: a = b = c - это случай равенства!" << std::endl;
        }
    }
    
    return 0;
}

