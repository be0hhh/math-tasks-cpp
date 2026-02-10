#ifndef INEQUALITY_H
#define INEQUALITY_H

#include <vector>
#include <utility>

namespace Task1 {

/**
 * Проверяет неравенство: 1/(m^(1/n)) + 1/(n^(1/m)) > 1
 * для натуральных чисел m и n
 */
class InequalityChecker {
public:
    /**
     * Проверяет неравенство для заданных m и n
     * @param m натуральное число
     * @param n натуральное число
     * @return true если неравенство выполняется, false иначе
     */
    static bool checkInequality(int m, int n);
    
    /**
     * Вычисляет значение левой части неравенства
     * @param m натуральное число
     * @param n натуральное число
     * @return значение 1/(m^(1/n)) + 1/(n^(1/m))
     */
    static double evaluateInequality(int m, int n);
    
    /**
     * Проверяет неравенство для диапазона значений
     * @param m_max максимальное значение m
     * @param n_max максимальное значение n
     * @return вектор пар (m, n), для которых неравенство не выполняется
     */
    static std::vector<std::pair<int, int>> verifyForRange(int m_max, int n_max);
    
    /**
     * Проверяет неравенство для всех пар в диапазоне и выводит статистику
     * @param m_max максимальное значение m
     * @param n_max максимальное значение n
     * @return количество пар, для которых неравенство выполняется
     */
    static int countValidPairs(int m_max, int n_max);

private:
    /**
     * Вычисляет n-й корень из m: m^(1/n)
     * @param m основание
     * @param n степень корня
     * @return значение корня
     */
    static double nthRoot(double m, int n);
    
    static constexpr double EPSILON = 1e-10;
};

} // namespace Task1

#endif // INEQUALITY_H

