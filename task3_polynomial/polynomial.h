#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>

namespace Task3 {

/**
 * Класс для работы с полиномами
 * 
 * Полином представляется как: a₀ + a₁x + a₂x² + ... + aₙxⁿ
 * Коэффициенты хранятся в векторе [a₀, a₁, a₂, ..., aₙ]
 */
class Polynomial {
private:
    std::vector<double> coefficients; // Коэффициенты от младшей степени к старшей
    
public:
    /**
     * Конструктор по умолчанию (нулевой полином)
     */
    Polynomial();
    
    /**
     * Конструктор из вектора коэффициентов
     * @param coeffs коэффициенты [a₀, a₁, a₂, ..., aₙ]
     */
    explicit Polynomial(const std::vector<double>& coeffs);
    
    /**
     * Конструктор из списка инициализации
     * @param coeffs коэффициенты
     */
    Polynomial(std::initializer_list<double> coeffs);
    
    /**
     * Вычисляет значение полинома в точке x
     * Использует схему Горнера для эффективности
     * @param x точка вычисления
     * @return значение полинома
     */
    double evaluate(double x) const;
    
    /**
     * Вычисляет производную полинома заданного порядка
     * @param order порядок производной (0 = сам полином, 1 = первая производная, и т.д.)
     * @return новый полином - производная
     */
    Polynomial derivative(int order = 1) const;
    
    /**
     * Вычисляет значение производной в точке
     * @param x точка вычисления
     * @param order порядок производной
     * @return значение производной
     */
    double evaluateDerivative(double x, int order) const;
    
    /**
     * Вычисляет разложение в ряд Тейлора вокруг точки center
     * @param center центр разложения
     * @param maxDegree максимальная степень в разложении
     * @return вектор коэффициентов [c₀, c₁, c₂, ..., cₙ] для (x-center)ᵏ
     */
    std::vector<double> taylorExpansion(double center, int maxDegree) const;
    
    /**
     * Возвращает степень полинома
     * @return степень (для нулевого полинома возвращает -1)
     */
    int degree() const;
    
    /**
     * Возвращает коэффициент при степени k
     * @param k степень
     * @return коэффициент
     */
    double coefficient(int k) const;
    
    /**
     * Возвращает строковое представление полинома
     * @return строка вида "x^5 - 2x^4 + 3x^3 - x^2 + x - 2"
     */
    std::string toString() const;
    
    /**
     * Создает полином из задания: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2
     * @return полином p(x)
     */
    static Polynomial createTaskPolynomial();
};

} // namespace Task3

#endif // POLYNOMIAL_H

