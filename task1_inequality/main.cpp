#include "inequality.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace Task1;

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
    std::cout << "ЗАДАЧА A.2: НЕРАВЕНСТВО" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nУСЛОВИЕ:" << std::endl;
    std::cout << "Для всех m, n из N (натуральных чисел) доказать неравенство:" << std::endl;
    std::cout << "  1/(m^(1/n)) + 1/(n^(1/m)) > 1" << std::endl;
    std::cout << "(неравенство Коши)" << std::endl;
    
    std::cout << "\nАЛГОРИТМ РЕШЕНИЯ (подробно):" << std::endl;
    std::cout << "\n1. ВЫЧИСЛЕНИЕ КОРНЕЙ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно найти m^(1/n) и n^(1/m)" << std::endl;
    std::cout << "   ПОЧЕМУ: m^(1/n) - это n-й корень из m" << std::endl;
    std::cout << "   - Например: 8^(1/3) = ∛8 = 2" << std::endl;
    std::cout << "   - Используем: m^(1/n) = exp(ln(m) / n)" << std::endl;
    std::cout << "   - Или функцию pow(m, 1.0/n)" << std::endl;
    
    std::cout << "\n2. ВЫЧИСЛЕНИЕ ОБРАТНЫХ ЗНАЧЕНИЙ:" << std::endl;
    std::cout << "   ЗАЧЕМ: В неравенстве нужны 1/(m^(1/n)) и 1/(n^(1/m))" << std::endl;
    std::cout << "   ПОЧЕМУ: Это обратные значения к корням" << std::endl;
    std::cout << "   - Если m^(1/n) = a, то 1/(m^(1/n)) = 1/a" << std::endl;
    
    std::cout << "\n3. СУММИРОВАНИЕ И СРАВНЕНИЕ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Проверить выполнение неравенства" << std::endl;
    std::cout << "   ПОЧЕМУ: Неравенство Коши утверждает, что сумма > 1" << std::endl;
    std::cout << "   - Вычисляем: S = 1/(m^(1/n)) + 1/(n^(1/m))" << std::endl;
    std::cout << "   - Проверяем: S > 1" << std::endl;
    std::cout << "   - Учитываем погрешность вычислений (EPSILON)" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "\nВыберите режим:" << std::endl;
    std::cout << "  0 - РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ (алгоритм + вычисления)" << std::endl;
    std::cout << "  1 - Проверить неравенство для своих чисел" << std::endl;
    std::cout << "\nВаш выбор (0-1): ";
    
    int mode;
    std::cin >> mode;
    
    int m, n;
    
    if (mode == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "\nПОЛНЫЙ АЛГОРИТМ РЕШЕНИЯ:" << std::endl;
        std::cout << "\nШАГ 1: Вычисление корней" << std::endl;
        std::cout << "Для натуральных m, n вычисляем:" << std::endl;
        std::cout << "  m^(1/n) - n-й корень из m" << std::endl;
        std::cout << "  n^(1/m) - m-й корень из n" << std::endl;
        std::cout << "\nШАГ 2: Вычисление обратных значений" << std::endl;
        std::cout << "  1/(m^(1/n)) и 1/(n^(1/m))" << std::endl;
        std::cout << "\nШАГ 3: Суммирование и проверка" << std::endl;
        std::cout << "  S = 1/(m^(1/n)) + 1/(n^(1/m))" << std::endl;
        std::cout << "  Проверяем: S > 1" << std::endl;
        std::cout << "\n========================================" << std::endl;
        std::cout << "\nВЫЧИСЛЕНИЯ ДЛЯ ПРИМЕРА:" << std::endl;
        std::cout << "Введите m и n для демонстрации:" << std::endl;
    }
    
    std::cout << "\nВведите натуральное число m: ";
    std::cin >> m;
    
    std::cout << "Введите натуральное число n: ";
    std::cin >> n;
    
    if (m <= 0 || n <= 0) {
        std::cout << "Ошибка: числа должны быть натуральными (положительными)!" << std::endl;
        return 1;
    }
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    double m_root = std::pow(static_cast<double>(m), 1.0/n);
    double n_root = std::pow(static_cast<double>(n), 1.0/m);
    double inv_m_root = 1.0 / m_root;
    double inv_n_root = 1.0 / n_root;
    double value = InequalityChecker::evaluateInequality(m, n);
    bool result = InequalityChecker::checkInequality(m, n);
    
    if (mode == 0) {
        std::cout << "\nПОДРОБНЫЕ ВЫЧИСЛЕНИЯ:" << std::endl;
        std::cout << "1. Вычисляем корни:" << std::endl;
        std::cout << "   m^(1/n) = " << formatNumber(m) << "^(1/" << n << ") = " 
                  << formatNumber(m_root) << std::endl;
        std::cout << "   n^(1/m) = " << formatNumber(n) << "^(1/" << m << ") = " 
                  << formatNumber(n_root) << std::endl;
        std::cout << "\n2. Вычисляем обратные значения:" << std::endl;
        std::cout << "   1/(m^(1/n)) = 1/" << formatNumber(m_root) << " = " 
                  << formatNumber(inv_m_root) << std::endl;
        std::cout << "   1/(n^(1/m)) = 1/" << formatNumber(n_root) << " = " 
                  << formatNumber(inv_n_root) << std::endl;
        std::cout << "\n3. Суммируем:" << std::endl;
        std::cout << "   S = " << formatNumber(inv_m_root) << " + " << formatNumber(inv_n_root) 
                  << " = " << formatNumber(value) << std::endl;
        std::cout << "\n4. Проверка неравенства:" << std::endl;
        std::cout << "   " << formatNumber(value) << " > 1: " 
                  << (result ? "ДА" : "НЕТ") << std::endl;
    } else {
        std::cout << "Значение выражения: " << formatNumber(value) << std::endl;
        std::cout << "Неравенство " << (result ? "ВЫПОЛНЯЕТСЯ" : "НЕ ВЫПОЛНЯЕТСЯ") << std::endl;
        std::cout << "\nДетали:" << std::endl;
        std::cout << "  1/(m^(1/n)) + 1/(n^(1/m)) = " << formatNumber(value) << std::endl;
        std::cout << "  " << formatNumber(value) << " > 1: " << (result ? "ДА" : "НЕТ") << std::endl;
    }
    
    return 0;
}

