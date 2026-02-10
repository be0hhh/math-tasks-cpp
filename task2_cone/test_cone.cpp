#include "cone.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace Task2;

// Простой фреймворк для тестирования
class TestRunner {
private:
    static int tests_passed;
    static int tests_failed;
    
public:
    static void assert_true(bool condition, const std::string& test_name) {
        if (condition) {
            ++tests_passed;
            std::cout << "✓ " << test_name << std::endl;
        } else {
            ++tests_failed;
            std::cout << "✗ " << test_name << " FAILED" << std::endl;
        }
    }
    
    static void assert_approx_equal(double a, double b, double epsilon, const std::string& test_name) {
        if (std::abs(a - b) < epsilon) {
            ++tests_passed;
            std::cout << "✓ " << test_name << std::endl;
        } else {
            ++tests_failed;
            std::cout << "✗ " << test_name << " FAILED (expected " << b 
                      << ", got " << a << ", diff: " << std::abs(a - b) << ")" << std::endl;
        }
    }
    
    static void print_summary() {
        std::cout << "\n=== Test Summary ===" << std::endl;
        std::cout << "Passed: " << tests_passed << std::endl;
        std::cout << "Failed: " << tests_failed << std::endl;
        std::cout << "Total: " << (tests_passed + tests_failed) << std::endl;
    }
};

int TestRunner::tests_passed = 0;
int TestRunner::tests_failed = 0;

void test_geometry() {
    std::cout << "\n=== Testing Geometry ===" << std::endl;
    
    double R = 1.0;
    double phi = ConeOptimizer::PI; // 180 градусов
    
    double r = ConeOptimizer::baseRadius(phi, R);
    double h = ConeOptimizer::height(phi, R);
    double l = ConeOptimizer::slantHeight(phi, R);
    
    std::cout << "For phi = π, R = 1:" << std::endl;
    std::cout << "  Base radius r = " << std::setprecision(10) << r << std::endl;
    std::cout << "  Height h = " << std::setprecision(10) << h << std::endl;
    std::cout << "  Slant height l = " << std::setprecision(10) << l << std::endl;
    
    // Проверка: l² = r² + h² (теорема Пифагора)
    double pythagorean = r * r + h * h;
    TestRunner::assert_approx_equal(pythagorean, l * l, 1e-6, "Pythagorean theorem check");
}

void test_volume_calculation() {
    std::cout << "\n=== Testing Volume Calculation ===" << std::endl;
    
    double R = 1.0;
    
    // Тест 1: phi = π
    double phi1 = ConeOptimizer::PI;
    double V1 = ConeOptimizer::coneVolume(phi1, R);
    std::cout << "Volume for phi = π: " << std::setprecision(10) << V1 << std::endl;
    TestRunner::assert_true(V1 > 0, "Volume should be positive for phi = π");
    
    // Тест 2: phi = π/2
    double phi2 = ConeOptimizer::PI / 2.0;
    double V2 = ConeOptimizer::coneVolume(phi2, R);
    std::cout << "Volume for phi = π/2: " << std::setprecision(10) << V2 << std::endl;
    TestRunner::assert_true(V2 > 0, "Volume should be positive for phi = π/2");
    
    // Тест 3: phi близко к 0
    double phi3 = 0.1;
    double V3 = ConeOptimizer::coneVolume(phi3, R);
    std::cout << "Volume for phi = 0.1: " << std::setprecision(10) << V3 << std::endl;
    TestRunner::assert_true(V3 > 0, "Volume should be positive for small phi");
}

void test_optimal_phi() {
    std::cout << "\n=== Testing Optimal Phi ===" << std::endl;
    
    double R = 1.0;
    double phi_opt = ConeOptimizer::findOptimalPhi(R);
    
    std::cout << "Optimal phi (analytical): " << std::setprecision(10) << phi_opt << " radians" << std::endl;
    std::cout << "Optimal phi (degrees): " << std::setprecision(10) << (phi_opt * 180.0 / ConeOptimizer::PI) << " degrees" << std::endl;
    
    // Проверяем, что производная в оптимальной точке близка к нулю
    double derivative = ConeOptimizer::coneVolumeDerivative(phi_opt, R);
    std::cout << "Derivative at optimal point: " << std::setprecision(10) << derivative << std::endl;
    TestRunner::assert_approx_equal(derivative, 0.0, 1e-6, "Derivative should be zero at optimum");
    
    // Проверяем, что объем в оптимальной точке больше, чем в соседних точках
    double V_opt = ConeOptimizer::coneVolume(phi_opt, R);
    double V_left = ConeOptimizer::coneVolume(phi_opt - 0.1, R);
    double V_right = ConeOptimizer::coneVolume(phi_opt + 0.1, R);
    
    std::cout << "Volume at optimum: " << std::setprecision(10) << V_opt << std::endl;
    std::cout << "Volume at phi - 0.1: " << std::setprecision(10) << V_left << std::endl;
    std::cout << "Volume at phi + 0.1: " << std::setprecision(10) << V_right << std::endl;
    
    TestRunner::assert_true(V_opt >= V_left, "Optimal volume should be >= volume at phi - 0.1");
    TestRunner::assert_true(V_opt >= V_right, "Optimal volume should be >= volume at phi + 0.1");
}

void test_derivative() {
    std::cout << "\n=== Testing Derivative ===" << std::endl;
    
    double R = 1.0;
    double phi = ConeOptimizer::PI / 2.0;
    
    double derivative = ConeOptimizer::coneVolumeDerivative(phi, R);
    std::cout << "Derivative at phi = π/2: " << std::setprecision(10) << derivative << std::endl;
    
    // Численная проверка производной
    double h = 1e-6;
    double V1 = ConeOptimizer::coneVolume(phi + h, R);
    double V2 = ConeOptimizer::coneVolume(phi - h, R);
    double numerical_derivative = (V1 - V2) / (2.0 * h);
    
    std::cout << "Numerical derivative: " << std::setprecision(10) << numerical_derivative << std::endl;
    std::cout << "Analytical derivative: " << std::setprecision(10) << derivative << std::endl;
    
    TestRunner::assert_approx_equal(derivative, numerical_derivative, 1e-4, 
                                     "Analytical and numerical derivatives should match");
}

void test_edge_cases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    double R = 1.0;
    
    // Тест 1: phi очень близко к 0
    double phi1 = 0.01;
    double V1 = ConeOptimizer::coneVolume(phi1, R);
    TestRunner::assert_true(V1 > 0, "Volume should be positive for small phi");
    
    // Тест 2: phi близко к 2π
    double phi2 = 2.0 * ConeOptimizer::PI - 0.01;
    double V2 = ConeOptimizer::coneVolume(phi2, R);
    std::cout << "Volume for phi close to 2π: " << std::setprecision(10) << V2 << std::endl;
    TestRunner::assert_true(V2 >= 0, "Volume should be non-negative");
}

void test_different_radii() {
    std::cout << "\n=== Testing Different Radii ===" << std::endl;
    
    // Оптимальный phi не должен зависеть от R
    double R1 = 1.0;
    double R2 = 2.0;
    double R3 = 5.0;
    
    double phi1 = ConeOptimizer::findOptimalPhi(R1);
    double phi2 = ConeOptimizer::findOptimalPhi(R2);
    double phi3 = ConeOptimizer::findOptimalPhi(R3);
    
    std::cout << "Optimal phi for R=1: " << std::setprecision(10) << phi1 << std::endl;
    std::cout << "Optimal phi for R=2: " << std::setprecision(10) << phi2 << std::endl;
    std::cout << "Optimal phi for R=5: " << std::setprecision(10) << phi3 << std::endl;
    
    TestRunner::assert_approx_equal(phi1, phi2, 1e-10, "Optimal phi should be independent of R (R1 vs R2)");
    TestRunner::assert_approx_equal(phi1, phi3, 1e-10, "Optimal phi should be independent of R (R1 vs R3)");
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Testing Task 2: Cone Optimizer" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_geometry();
    test_volume_calculation();
    test_optimal_phi();
    test_derivative();
    test_edge_cases();
    test_different_radii();
    
    TestRunner::print_summary();
    
    return 0;
}

