#ifndef INEQUALITY_ABC_H
#define INEQUALITY_ABC_H

#include <vector>
#include <utility>
#include <string>
#include <tuple>

namespace Task4 {

/**
 * Класс для работы с неравенством:
 * a³b + b³c + c³a >= a²bc + b²ca + c²ab
 * для неотрицательных a, b, c
 */
class InequalityABC {
public:
    /**
     * Проверяет выполнение неравенства
     * @param a неотрицательное число
     * @param b неотрицательное число
     * @param c неотрицательное число
     * @return true если неравенство выполняется, false иначе
     */
    static bool checkInequality(double a, double b, double c);
    
    /**
     * Вычисляет разность между левой и правой частями неравенства
     * @param a неотрицательное число
     * @param b неотрицательное число
     * @param c неотрицательное число
     * @return значение (левая часть - правая часть)
     */
    static double verifyInequality(double a, double b, double c);
    
    /**
     * Проверяет, выполняется ли равенство (с учетом погрешности)
     * @param a неотрицательное число
     * @param b неотрицательное число
     * @param c неотрицательное число
     * @return true если левая часть равна правой (с точностью до EPSILON)
     */
    static bool isEquality(double a, double b, double c);
    
    /**
     * Находит случаи равенства в заданном диапазоне
     * @param max_value максимальное значение для a, b, c
     * @param step шаг поиска
     * @return вектор троек (a, b, c), для которых выполняется равенство
     */
    static std::vector<std::tuple<double, double, double>> findEqualityCases(
        double max_value = 10.0, double step = 0.1);
    
    /**
     * Анализирует известные случаи равенства
     * @return описание случаев равенства
     */
    static std::string analyzeEqualityCases();
    
    /**
     * Проверяет случай, когда a = b = c
     * @param value значение a = b = c
     * @return true если равенство выполняется
     */
    static bool checkEqualityCase_abc(double value);
    
    /**
     * Проверяет случай, когда одна из переменных равна нулю
     * @param a значение a
     * @param b значение b
     * @param c значение c (должно быть 0)
     * @return true если равенство выполняется
     */
    static bool checkEqualityCase_zero(double a, double b, double c);
    
    /**
     * Вычисляет левую часть неравенства: a³b + b³c + c³a
     * @param a значение a
     * @param b значение b
     * @param c значение c
     * @return значение левой части
     */
    static double leftSide(double a, double b, double c);
    
    /**
     * Вычисляет правую часть неравенства: a²bc + b²ca + c²ab
     * @param a значение a
     * @param b значение b
     * @param c значение c
     * @return значение правой части
     */
    static double rightSide(double a, double b, double c);

private:
    static constexpr double EPSILON = 1e-10;
};

} // namespace Task4

#endif // INEQUALITY_ABC_H

