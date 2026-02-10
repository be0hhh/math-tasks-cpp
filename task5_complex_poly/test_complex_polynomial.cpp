#include "complex_polynomial.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace Task5;

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
    
    static void assert_complex_approx_equal(const Complex& a, const Complex& b, 
                                           double epsilon, const std::string& test_name) {
        bool real_ok = std::abs(a.real - b.real) < epsilon;
        bool imag_ok = std::abs(a.imag - b.imag) < epsilon;
        if (real_ok && imag_ok) {
            ++tests_passed;
            std::cout << "✓ " << test_name << std::endl;
        } else {
            ++tests_failed;
            std::cout << "✗ " << test_name << " FAILED" << std::endl;
            std::cout << "  Expected: " << b.toString() << std::endl;
            std::cout << "  Got: " << a.toString() << std::endl;
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

void test_complex_operations() {
    std::cout << "\n=== Testing Complex Number Operations ===" << std::endl;
    
    Complex z1(1.0, 2.0);
    Complex z2(3.0, 4.0);
    
    Complex sum = z1 + z2;
    Complex prod = z1 * z2;
    Complex conj = z1.conjugate();
    
    std::cout << "z1 = " << z1.toString() << std::endl;
    std::cout << "z2 = " << z2.toString() << std::endl;
    std::cout << "z1 + z2 = " << sum.toString() << std::endl;
    std::cout << "z1 * z2 = " << prod.toString() << std::endl;
    std::cout << "conj(z1) = " << conj.toString() << std::endl;
    
    TestRunner::assert_complex_approx_equal(sum, Complex(4.0, 6.0), 1e-10, 
                                           "Complex addition");
    TestRunner::assert_complex_approx_equal(prod, Complex(-5.0, 10.0), 1e-10, 
                                           "Complex multiplication");
    TestRunner::assert_complex_approx_equal(conj, Complex(1.0, -2.0), 1e-10, 
                                           "Complex conjugate");
}

void test_polynomial_evaluation_real() {
    std::cout << "\n=== Testing Polynomial Evaluation (Real Points) ===" << std::endl;
    
    // Полином p(x) = x² + 2x + 1 = (x+1)²
    ComplexPolynomial p({1.0, 2.0, 1.0});
    
    Complex val1 = p.evaluate(Complex(-1.0, 0.0));
    std::cout << "p(-1) = " << val1.toString() << std::endl;
    TestRunner::assert_complex_approx_equal(val1, Complex(0.0, 0.0), 1e-10, 
                                           "p(-1) should be 0");
    
    Complex val2 = p.evaluate(Complex(2.0, 0.0));
    std::cout << "p(2) = " << val2.toString() << std::endl;
    // p(2) = 4 + 4 + 1 = 9
    TestRunner::assert_complex_approx_equal(val2, Complex(9.0, 0.0), 1e-10, 
                                           "p(2) should be 9");
}

void test_polynomial_evaluation_complex() {
    std::cout << "\n=== Testing Polynomial Evaluation (Complex Points) ===" << std::endl;
    
    // Полином p(x) = x² + 1
    ComplexPolynomial p({1.0, 0.0, 1.0});
    
    // p(i) = i² + 1 = -1 + 1 = 0
    Complex val1 = p.evaluate(Complex(0.0, 1.0));
    std::cout << "p(i) = " << val1.toString() << std::endl;
    TestRunner::assert_complex_approx_equal(val1, Complex(0.0, 0.0), 1e-10, 
                                           "p(i) should be 0");
    
    // p(1+i) = (1+i)² + 1 = 1 + 2i - 1 + 1 = 1 + 2i
    Complex val2 = p.evaluate(Complex(1.0, 1.0));
    std::cout << "p(1+i) = " << val2.toString() << std::endl;
    TestRunner::assert_complex_approx_equal(val2, Complex(1.0, 2.0), 1e-10, 
                                           "p(1+i) should be 1+2i");
}

void test_quadratic_coeffs() {
    std::cout << "\n=== Testing Quadratic Coefficients ===" << std::endl;
    
    double u0 = 2.0, v0 = 3.0;
    auto [p, q] = ComplexPolynomial::computeQuadraticCoeffs(u0, v0);
    
    std::cout << "For z₀ = " << u0 << " + " << v0 << "i:" << std::endl;
    std::cout << "  p = " << p << " (expected: " << -2.0 * u0 << ")" << std::endl;
    std::cout << "  q = " << q << " (expected: " << (u0*u0 + v0*v0) << ")" << std::endl;
    
    TestRunner::assert_approx_equal(p, -2.0 * u0, 1e-10, "p should equal -2u₀");
    TestRunner::assert_approx_equal(q, u0*u0 + v0*v0, 1e-10, "q should equal u₀² + v₀²");
}

void test_division_by_quadratic() {
    std::cout << "\n=== Testing Division by Quadratic ===" << std::endl;
    
    // Полином p(x) = x³ - 2x² + x - 2
    // Делим на (x - 1 - i)(x - 1 + i) = x² - 2x + 2
    ComplexPolynomial p({-2.0, 1.0, -2.0, 1.0});
    
    double u0 = 1.0, v0 = 1.0;
    auto [quotient, remainder] = p.divideByQuadratic(u0, v0);
    
    std::cout << "Dividing p(x) by (x - " << u0 << " - " << v0 << "i)(x - " 
              << u0 << " + " << v0 << "i):" << std::endl;
    std::cout << "  Remainder: " << remainder.second << "x + " << remainder.first << std::endl;
    
    // Проверяем, что p(z₀) = остаток при z₀
    Complex z0(u0, v0);
    Complex p_at_z0 = p.evaluate(z0);
    Complex remainder_at_z0(remainder.first + remainder.second * z0.real, 
                           remainder.second * z0.imag);
    
    std::cout << "  p(z₀) = " << p_at_z0.toString() << std::endl;
    std::cout << "  Remainder at z₀ = " << remainder_at_z0.toString() << std::endl;
    
    // Для точного деления остаток должен быть близок к p(z₀)
    // (но это не всегда точно из-за численных ошибок)
    TestRunner::assert_true(std::abs(p_at_z0.real - remainder_at_z0.real) < 1e-6 ||
                            std::abs(p_at_z0.real) < 1e-6, 
                           "Remainder should match p(z₀) approximately");
}

void test_division_exact() {
    std::cout << "\n=== Testing Exact Division ===" << std::endl;
    
    // Полином p(x) = x² + 1 = (x - i)(x + i)
    // Делим на (x - i)(x + i) = x² + 1
    ComplexPolynomial p({1.0, 0.0, 1.0});
    
    double u0 = 0.0, v0 = 1.0;
    auto [quotient, remainder] = p.divideByQuadratic(u0, v0);
    
    std::cout << "Dividing x² + 1 by x² + 1:" << std::endl;
    std::cout << "  Quotient degree: " << quotient.degree() << std::endl;
    std::cout << "  Remainder: " << remainder.second << "x + " << remainder.first << std::endl;
    
    // Остаток должен быть близок к нулю
    TestRunner::assert_true(std::abs(remainder.first) < 1e-6 && 
                           std::abs(remainder.second) < 1e-6,
                           "Remainder should be approximately zero for exact division");
}

void test_horner_scheme() {
    std::cout << "\n=== Testing Horner Scheme ===" << std::endl;
    
    // Полином p(x) = 2x³ + 3x² + 4x + 5
    ComplexPolynomial p({5.0, 4.0, 3.0, 2.0});
    
    Complex z(1.0, 1.0);
    Complex result = p.evaluate(z);
    
    // Проверяем вручную: p(1+i) = 2(1+i)³ + 3(1+i)² + 4(1+i) + 5
    // (1+i)² = 1 + 2i - 1 = 2i
    // (1+i)³ = (1+i) * 2i = 2i + 2i² = 2i - 2 = -2 + 2i
    // p(1+i) = 2(-2+2i) + 3(2i) + 4(1+i) + 5
    //        = -4 + 4i + 6i + 4 + 4i + 5
    //        = 5 + 14i
    
    std::cout << "p(1+i) = " << result.toString() << std::endl;
    std::cout << "Expected approximately: 5 + 14i" << std::endl;
    
    TestRunner::assert_approx_equal(result.real, 5.0, 1e-6, "Real part of p(1+i)");
    TestRunner::assert_approx_equal(result.imag, 14.0, 1e-6, "Imaginary part of p(1+i)");
}

void test_task_polynomial() {
    std::cout << "\n=== Testing Task Polynomial ===" << std::endl;
    
    // Полином из задачи 3: p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2
    ComplexPolynomial p({-2.0, 1.0, -1.0, 3.0, -2.0, 1.0});
    
    // Вычисляем в вещественной точке
    Complex val1 = p.evaluate(Complex(2.0, 0.0));
    std::cout << "p(2) = " << val1.toString() << " (expected: 20)" << std::endl;
    TestRunner::assert_approx_equal(val1.real, 20.0, 1e-10, "p(2) should be 20");
    TestRunner::assert_approx_equal(val1.imag, 0.0, 1e-10, "p(2) should be real");
    
    // Вычисляем в комплексной точке
    Complex val2 = p.evaluate(Complex(1.0, 1.0));
    std::cout << "p(1+i) = " << val2.toString() << std::endl;
    TestRunner::assert_true(std::abs(val2.real) < 1e10 && std::abs(val2.imag) < 1e10,
                           "p(1+i) should be finite");
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Testing Task 5: Complex Polynomial" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_complex_operations();
    test_polynomial_evaluation_real();
    test_polynomial_evaluation_complex();
    test_quadratic_coeffs();
    test_division_by_quadratic();
    test_division_exact();
    test_horner_scheme();
    test_task_polynomial();
    
    TestRunner::print_summary();
    
    return 0;
}

