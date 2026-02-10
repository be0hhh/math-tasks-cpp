#include "cone.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

using namespace Task2;

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
    std::cout << "ЗАДАЧА: КОНУС МАКСИМАЛЬНОГО ОБЪЕМА" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "\nУСЛОВИЕ:" << std::endl;
    std::cout << "Из круга радиуса R вырезан сектор с углом φ радиан." << std::endl;
    std::cout << "Из оставшейся части делается прямой круговой конус." << std::endl;
    std::cout << "При каком φ конус будет иметь максимальный объем?" << std::endl;
    
    std::cout << "\nАЛГОРИТМ РЕШЕНИЯ (подробно):" << std::endl;
    std::cout << "\n1. НАХОЖДЕНИЕ РАДИУСА ОСНОВАНИЯ:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно связать параметры конуса с углом φ" << std::endl;
    std::cout << "   ПОЧЕМУ:" << std::endl;
    std::cout << "   - Длина дуги вырезанного сектора: L = φR" << std::endl;
    std::cout << "   - Оставшаяся часть круга: L_остаток = (2π - φ)R" << std::endl;
    std::cout << "   - Эта дуга становится окружностью основания конуса" << std::endl;
    std::cout << "   - Длина окружности основания: 2πr = (2π - φ)R" << std::endl;
    std::cout << "   - Отсюда: r = R(2π - φ)/(2π)" << std::endl;
    std::cout << "   - Чем больше φ, тем меньше r" << std::endl;
    
    std::cout << "\n2. НАХОЖДЕНИЕ ВЫСОТЫ КОНУСА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Высота нужна для вычисления объема" << std::endl;
    std::cout << "   ПОЧЕМУ по теореме Пифагора:" << std::endl;
    std::cout << "   - Образующая конуса l = R (радиус исходного круга)" << std::endl;
    std::cout << "   - Радиус основания r" << std::endl;
    std::cout << "   - Высота h, образующая l и радиус r образуют прямоугольный треугольник" << std::endl;
    std::cout << "   - По теореме Пифагора: l² = r² + h²" << std::endl;
    std::cout << "   - Отсюда: h = √(R² - r²)" << std::endl;
    
    std::cout << "\n3. ВЫЧИСЛЕНИЕ ОБЪЕМА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Объем - это функция от φ, которую нужно максимизировать" << std::endl;
    std::cout << "   ПОЧЕМУ формула V = (1/3)πr²h:" << std::endl;
    std::cout << "   - Это стандартная формула объема конуса" << std::endl;
    std::cout << "   - Подставляем r и h, выраженные через φ:" << std::endl;
    std::cout << "     V(φ) = (1/3)π · [R(2π-φ)/(2π)]² · √(R² - [R(2π-φ)/(2π)]²)" << std::endl;
    std::cout << "   - Упрощаем и получаем функцию V(φ)" << std::endl;
    
    std::cout << "\n4. НАХОЖДЕНИЕ МАКСИМУМА:" << std::endl;
    std::cout << "   ЗАЧЕМ: Нужно найти φ, при котором объем максимален" << std::endl;
    std::cout << "   ПОЧЕМУ через производную:" << std::endl;
    std::cout << "   - В точке максимума производная равна нулю: V'(φ) = 0" << std::endl;
    std::cout << "   - Вычисляем производную V'(φ)" << std::endl;
    std::cout << "   - Приравниваем к нулю и решаем уравнение" << std::endl;
    std::cout << "   - Получаем: φ = 2π(1 - √(2/3))" << std::endl;
    std::cout << "   - Проверяем, что это действительно максимум (V''(φ) < 0)" << std::endl;
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "\nВыберите режим:" << std::endl;
    std::cout << "  0 - РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ (алгоритм + вычисления)" << std::endl;
    std::cout << "  1 - Найти оптимальный угол для своего R" << std::endl;
    std::cout << "\nВаш выбор (0-1): ";
    
    int mode;
    std::cin >> mode;
    
    double R;
    
    if (mode == 0) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "РЕШЕНИЕ ЗАДАЧИ ИЗ ЗАДАНИЯ" << std::endl;
        std::cout << "========================================" << std::endl;
        std::cout << "\nПОЛНЫЙ АЛГОРИТМ РЕШЕНИЯ:" << std::endl;
        std::cout << "\nШАГ 1: Связь параметров" << std::endl;
        std::cout << "  r = R(2π - φ)/(2π)" << std::endl;
        std::cout << "  h = √(R² - r²)" << std::endl;
        std::cout << "\nШАГ 2: Функция объема" << std::endl;
        std::cout << "  V(φ) = (1/3)πr²h" << std::endl;
        std::cout << "\nШАГ 3: Нахождение максимума" << std::endl;
        std::cout << "  V'(φ) = 0" << std::endl;
        std::cout << "  Решение: φ = 2π(1 - √(2/3))" << std::endl;
        std::cout << "\n========================================" << std::endl;
        std::cout << "\nВЫЧИСЛЕНИЯ:" << std::endl;
    }
    
    std::cout << "\nВведите радиус круга R: ";
    std::cin >> R;
    
    if (R <= 0) {
        std::cout << "Ошибка: радиус должен быть положительным!" << std::endl;
        return 1;
    }
    
    std::cout << "\nРезультат:" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    double optimal_phi = ConeOptimizer::findOptimalPhi(R);
    double max_volume = ConeOptimizer::coneVolume(optimal_phi, R);
    double r = ConeOptimizer::baseRadius(optimal_phi, R);
    double h = ConeOptimizer::height(optimal_phi, R);
    
    if (mode == 0) {
        std::cout << "\nПОДРОБНЫЕ ВЫЧИСЛЕНИЯ:" << std::endl;
        std::cout << "1. Оптимальный угол:" << std::endl;
        double sqrt_2_3 = std::sqrt(2.0/3.0);
        std::cout << "   φ = 2π(1 - √(2/3))" << std::endl;
        std::cout << "   √(2/3) = " << formatNumber(sqrt_2_3) << std::endl;
        std::cout << "   φ = 2π(1 - " << formatNumber(sqrt_2_3) << ")" << std::endl;
        std::cout << "   φ = 2π·" << formatNumber(1.0 - sqrt_2_3) << std::endl;
        std::cout << "   φ = " << formatNumber(optimal_phi) << " радиан" << std::endl;
        std::cout << "   φ = " << formatNumber(optimal_phi * 180.0 / ConeOptimizer::PI) << " градусов" << std::endl;
        std::cout << "\n2. Параметры конуса:" << std::endl;
        double two_pi_minus_phi = 2.0*ConeOptimizer::PI - optimal_phi;
        std::cout << "   r = R(2π - φ)/(2π)" << std::endl;
        std::cout << "   r = " << formatNumber(R) << "·(" << formatNumber(two_pi_minus_phi) 
                  << ")/(2π)" << std::endl;
        std::cout << "   r = " << formatNumber(R) << "·" << formatNumber(two_pi_minus_phi / (2.0*ConeOptimizer::PI)) 
                  << " = " << formatNumber(r) << std::endl;
        double R_sq = R*R;
        double r_sq = r*r;
        std::cout << "   h = √(R² - r²)" << std::endl;
        std::cout << "   h = √(" << formatNumber(R_sq) << " - " << formatNumber(r_sq) << ")" << std::endl;
        std::cout << "   h = √(" << formatNumber(R_sq - r_sq) << ") = " << formatNumber(h) << std::endl;
        std::cout << "   l = R = " << formatNumber(R) << std::endl;
        std::cout << "\n3. Максимальный объем:" << std::endl;
        double r_squared = r*r;
        std::cout << "   V = (1/3)πr²h" << std::endl;
        std::cout << "   V = (1/3)π·" << formatNumber(r_squared) << "·" << formatNumber(h) << std::endl;
        std::cout << "   V = (1/3)π·" << formatNumber(r_squared * h) << std::endl;
        std::cout << "   V = " << formatNumber(max_volume) << std::endl;
        double derivative = ConeOptimizer::coneVolumeDerivative(optimal_phi, R);
        std::cout << "\n4. Проверка:" << std::endl;
        std::cout << "   V'(φ) = " << formatNumber(derivative) << " ≈ 0" << std::endl;
    } else {
        std::cout << "Оптимальный угол φ = " << formatNumber(optimal_phi) << " радиан" << std::endl;
        std::cout << "Оптимальный угол φ = " << formatNumber(optimal_phi * 180.0 / ConeOptimizer::PI) << " градусов" << std::endl;
        std::cout << "\nПараметры конуса:" << std::endl;
        std::cout << "  Радиус основания r = " << formatNumber(r) << std::endl;
        std::cout << "  Высота h = " << formatNumber(h) << std::endl;
        std::cout << "  Образующая l = " << formatNumber(R) << std::endl;
        std::cout << "\nМаксимальный объем V = " << formatNumber(max_volume) << std::endl;
        double derivative = ConeOptimizer::coneVolumeDerivative(optimal_phi, R);
        std::cout << "\nПроверка (производная в оптимальной точке): " << formatNumber(derivative) << " ≈ 0" << std::endl;
    }
    
    return 0;
}

