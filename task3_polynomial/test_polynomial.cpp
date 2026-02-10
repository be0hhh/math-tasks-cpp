#include "polynomial.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace Task3;

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

void test_task_polynomial_creation() {
    std::cout << "\n=== Testing Task Polynomial Creation ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    std::cout << "p(x) = " << p.toString() << std::endl;
    
    TestRunner::assert_true(p.degree() == 5, "Polynomial degree should be 5");
}

void test_p2() {
    std::cout << "\n=== Testing p(2) ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    double value = p.evaluate(2.0);
    
    // p(2) = 2^5 - 2*2^4 + 3*2^3 - 2^2 + 2 - 2
    //      = 32 - 32 + 24 - 4 + 2 - 2
    //      = 20
    double expected = 20.0;
    
    std::cout << "p(2) = " << std::setprecision(10) << value << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    
    TestRunner::assert_approx_equal(value, expected, 1e-10, "p(2) should equal 20");
}

void test_p_prime_1() {
    std::cout << "\n=== Testing p'(1) ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    double value = p.evaluateDerivative(1.0, 1);
    
    // p'(x) = 5x^4 - 8x^3 + 9x^2 - 2x + 1
    // p'(1) = 5 - 8 + 9 - 2 + 1 = 5
    double expected = 5.0;
    
    std::cout << "p'(1) = " << std::setprecision(10) << value << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    
    TestRunner::assert_approx_equal(value, expected, 1e-10, "p'(1) should equal 5");
}

void test_p_double_prime_3() {
    std::cout << "\n=== Testing p''(3) ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    double value = p.evaluateDerivative(3.0, 2);
    
    // p''(x) = 20x^3 - 24x^2 + 18x - 2
    // p''(3) = 20*27 - 24*9 + 18*3 - 2
    //        = 540 - 216 + 54 - 2
    //        = 376
    double expected = 376.0;
    
    std::cout << "p''(3) = " << std::setprecision(10) << value << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    
    TestRunner::assert_approx_equal(value, expected, 1e-10, "p''(3) should equal 376");
}

void test_p_triple_prime_minus1() {
    std::cout << "\n=== Testing p'''(-1) ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    double value = p.evaluateDerivative(-1.0, 3);
    
    // p'''(x) = 60x^2 - 48x + 18
    // p'''(-1) = 60*1 - 48*(-1) + 18
    //          = 60 + 48 + 18
    //          = 126
    double expected = 126.0;
    
    std::cout << "p'''(-1) = " << std::setprecision(10) << value << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    
    TestRunner::assert_approx_equal(value, expected, 1e-10, "p'''(-1) should equal 126");
}

void test_taylor_expansion() {
    std::cout << "\n=== Testing Taylor Expansion around x=1 ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    std::vector<double> taylor = p.taylorExpansion(1.0, 5);
    
    std::cout << "Taylor expansion coefficients (for (x-1)^k, k=0..5):" << std::endl;
    for (size_t k = 0; k < taylor.size(); ++k) {
        std::cout << "  c_" << k << " = " << std::setprecision(10) << taylor[k] << std::endl;
    }
    
    // Проверяем, что c_k = p^(k)(1) / k!
    // c_0 = p(1) = 1 - 2 + 3 - 1 + 1 - 2 = 0
    // c_1 = p'(1) / 1! = 5 / 1 = 5
    // c_2 = p''(1) / 2! = (20 - 24 + 18 - 2) / 2 = 12 / 2 = 6
    // и т.д.
    
    TestRunner::assert_approx_equal(taylor[0], 0.0, 1e-10, "c_0 should be 0 (p(1)=0)");
    TestRunner::assert_approx_equal(taylor[1], 5.0, 1e-10, "c_1 should be 5 (p'(1)/1!)");
    
    // Проверяем, что разложение работает: вычисляем p(2) через разложение
    double x = 2.0;
    double center = 1.0;
    double reconstructed = 0.0;
    double power = 1.0;
    for (size_t k = 0; k < taylor.size(); ++k) {
        reconstructed += taylor[k] * power;
        power *= (x - center);
    }
    
    double direct_value = p.evaluate(2.0);
    std::cout << "Direct evaluation p(2) = " << direct_value << std::endl;
    std::cout << "Reconstructed from Taylor: " << reconstructed << std::endl;
    
    TestRunner::assert_approx_equal(reconstructed, direct_value, 1e-10, 
                                     "Taylor expansion should reconstruct original polynomial");
}

void test_derivatives() {
    std::cout << "\n=== Testing Derivatives ===" << std::endl;
    
    Polynomial p = Polynomial::createTaskPolynomial();
    
    // Проверяем первую производную
    Polynomial p1 = p.derivative(1);
    std::cout << "p'(x) = " << p1.toString() << std::endl;
    TestRunner::assert_true(p1.degree() == 4, "First derivative should have degree 4");
    
    // Проверяем вторую производную
    Polynomial p2 = p.derivative(2);
    std::cout << "p''(x) = " << p2.toString() << std::endl;
    TestRunner::assert_true(p2.degree() == 3, "Second derivative should have degree 3");
    
    // Проверяем третью производную
    Polynomial p3 = p.derivative(3);
    std::cout << "p'''(x) = " << p3.toString() << std::endl;
    TestRunner::assert_true(p3.degree() == 2, "Third derivative should have degree 2");
    
    // Проверяем, что производная выше степени дает нулевой полином
    Polynomial p10 = p.derivative(10);
    std::cout << "p^(10)(x) = " << p10.toString() << std::endl;
    TestRunner::assert_true(p10.degree() < 0 || std::abs(p10.coefficient(0)) < 1e-10, 
                           "Derivative beyond degree should be zero");
}

void test_basic_operations() {
    std::cout << "\n=== Testing Basic Operations ===" << std::endl;
    
    // Тест простого полинома
    Polynomial p1({1.0, 2.0, 3.0}); // 1 + 2x + 3x^2
    std::cout << "p1(x) = " << p1.toString() << std::endl;
    
    double val1 = p1.evaluate(2.0);
    // 1 + 2*2 + 3*4 = 1 + 4 + 12 = 17
    TestRunner::assert_approx_equal(val1, 17.0, 1e-10, "Simple polynomial evaluation");
    
    Polynomial p1_deriv = p1.derivative(1);
    // Производная: 2 + 6x
    double deriv_val = p1_deriv.evaluate(1.0);
    TestRunner::assert_approx_equal(deriv_val, 8.0, 1e-10, "Simple derivative evaluation");
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Testing Task 3: Polynomial" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_task_polynomial_creation();
    test_p2();
    test_p_prime_1();
    test_p_double_prime_3();
    test_p_triple_prime_minus1();
    test_taylor_expansion();
    test_derivatives();
    test_basic_operations();
    
    TestRunner::print_summary();
    
    return 0;
}

