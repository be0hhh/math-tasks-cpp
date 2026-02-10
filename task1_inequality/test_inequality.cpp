#include "inequality.h"
#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace Task1;

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
                      << ", got " << a << ")" << std::endl;
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

void test_basic_inequality() {
    std::cout << "\n=== Testing Basic Inequality ===" << std::endl;
    
    // Тест 1: m=2, n=2
    double val1 = InequalityChecker::evaluateInequality(2, 2);
    TestRunner::assert_true(val1 > 1.0, "Inequality for m=2, n=2");
    std::cout << "  1/(2^(1/2)) + 1/(2^(1/2)) = " << std::setprecision(10) << val1 << std::endl;
    
    // Тест 2: m=3, n=4
    double val2 = InequalityChecker::evaluateInequality(3, 4);
    TestRunner::assert_true(val2 > 1.0, "Inequality for m=3, n=4");
    std::cout << "  1/(3^(1/4)) + 1/(4^(1/3)) = " << std::setprecision(10) << val2 << std::endl;
    
    // Тест 3: m=5, n=3
    double val3 = InequalityChecker::evaluateInequality(5, 3);
    TestRunner::assert_true(val3 > 1.0, "Inequality for m=5, n=3");
    std::cout << "  1/(5^(1/3)) + 1/(3^(1/5)) = " << std::setprecision(10) << val3 << std::endl;
}

void test_edge_cases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Тест 1: m=1, n=1
    double val1 = InequalityChecker::evaluateInequality(1, 1);
    TestRunner::assert_true(val1 == 2.0, "Inequality for m=1, n=1 (should be 2.0)");
    std::cout << "  1/(1^(1/1)) + 1/(1^(1/1)) = " << val1 << std::endl;
    
    // Тест 2: m=1, n=2
    double val2 = InequalityChecker::evaluateInequality(1, 2);
    TestRunner::assert_true(val2 > 1.0, "Inequality for m=1, n=2");
    std::cout << "  1/(1^(1/2)) + 1/(2^(1/1)) = " << val2 << std::endl;
    
    // Тест 3: m=2, n=1
    double val3 = InequalityChecker::evaluateInequality(2, 1);
    TestRunner::assert_true(val3 > 1.0, "Inequality for m=2, n=1");
    std::cout << "  1/(2^(1/1)) + 1/(1^(1/2)) = " << val3 << std::endl;
}

void test_large_values() {
    std::cout << "\n=== Testing Large Values ===" << std::endl;
    
    // Тест с большими значениями
    double val1 = InequalityChecker::evaluateInequality(10, 10);
    TestRunner::assert_true(val1 > 1.0, "Inequality for m=10, n=10");
    std::cout << "  1/(10^(1/10)) + 1/(10^(1/10)) = " << std::setprecision(10) << val1 << std::endl;
    
    double val2 = InequalityChecker::evaluateInequality(100, 50);
    TestRunner::assert_true(val2 > 1.0, "Inequality for m=100, n=50");
    std::cout << "  1/(100^(1/50)) + 1/(50^(1/100)) = " << std::setprecision(10) << val2 << std::endl;
}

void test_range_verification() {
    std::cout << "\n=== Testing Range Verification ===" << std::endl;
    
    // Проверка для небольшого диапазона
    auto violations = InequalityChecker::verifyForRange(5, 5);
    std::cout << "Violations found for range [1,5]x[1,5]: " << violations.size() << std::endl;
    
    int valid_count = InequalityChecker::countValidPairs(5, 5);
    std::cout << "Valid pairs in range [1,5]x[1,5]: " << valid_count << " out of 25" << std::endl;
    TestRunner::assert_true(valid_count > 0, "At least some pairs should satisfy inequality");
}

void test_symmetry() {
    std::cout << "\n=== Testing Symmetry ===" << std::endl;
    
    // Неравенство должно быть симметричным (или почти симметричным)
    double val1 = InequalityChecker::evaluateInequality(3, 5);
    double val2 = InequalityChecker::evaluateInequality(5, 3);
    
    std::cout << "  Value for (3,5): " << std::setprecision(10) << val1 << std::endl;
    std::cout << "  Value for (5,3): " << std::setprecision(10) << val2 << std::endl;
    
    // Значения могут отличаться, но оба должны быть > 1
    TestRunner::assert_true(val1 > 1.0 && val2 > 1.0, "Both symmetric pairs satisfy inequality");
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Testing Task 1: Inequality Checker" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_basic_inequality();
    test_edge_cases();
    test_large_values();
    test_range_verification();
    test_symmetry();
    
    TestRunner::print_summary();
    
    return 0;
}

