#ifndef CONE_H
#define CONE_H

#include <cmath>

namespace Task2 {

/**
 * Класс для решения задачи о конусе максимального объема
 * 
 * Задача: Из круга радиуса R вырезан сектор с углом φ радиан.
 * Из оставшейся части делается прямой круговой конус.
 * Найти φ, при котором конус имеет максимальный объем.
 */
class ConeOptimizer {
public:
    /**
     * Вычисляет объем конуса, полученного из круга радиуса R
     * с вырезанным сектором угла φ
     * 
     * @param phi угол вырезанного сектора в радианах
     * @param R радиус исходного круга
     * @return объем конуса
     */
    static double coneVolume(double phi, double R);
    
    /**
     * Вычисляет производную объема по φ
     * 
     * @param phi угол вырезанного сектора в радианах
     * @param R радиус исходного круга
     * @return значение производной dV/dφ
     */
    static double coneVolumeDerivative(double phi, double R);
    
    /**
     * Находит оптимальный угол φ, при котором объем максимален
     * Использует метод Ньютона для решения уравнения V'(φ) = 0
     * 
     * @param R радиус исходного круга
     * @return оптимальный угол φ в радианах
     */
    static double findOptimalPhi(double R);
    
    /**
     * Находит оптимальный угол φ аналитически
     * Решение: φ = 2π(1 - √(2/3))
     * 
     * @param R радиус исходного круга (не используется, но оставлен для совместимости)
     * @return оптимальный угол φ в радианах
     */
    static double findOptimalPhiAnalytical(double R = 1.0);
    
    /**
     * Вычисляет радиус основания конуса
     * 
     * @param phi угол вырезанного сектора в радианах
     * @param R радиус исходного круга
     * @return радиус основания конуса
     */
    static double baseRadius(double phi, double R);
    
    /**
     * Вычисляет высоту конуса
     * 
     * @param phi угол вырезанного сектора в радианах
     * @param R радиус исходного круга
     * @return высота конуса
     */
    static double height(double phi, double R);
    
    /**
     * Вычисляет образующую конуса
     * 
     * @param phi угол вырезанного сектора в радианах
     * @param R радиус исходного круга
     * @return образующая конуса (равна R)
     */
    static double slantHeight(double phi, double R);
    
    // Константы
    static constexpr double PI = 3.14159265358979323846;

private:
    static constexpr double EPSILON = 1e-10;
    static constexpr int MAX_ITERATIONS = 100;
};

} // namespace Task2

#endif // CONE_H

