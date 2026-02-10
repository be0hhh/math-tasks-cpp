#include "inequality_abc.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace Task4;

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

void test_basic_inequality() {
    std::cout << "\n=== Testing Basic Inequality ===" << std::endl;
    
    // Тест 1: a=1, b=2, c=3
    double a1 = 1.0, b1 = 2.0, c1 = 3.0;
    bool result1 = InequalityABC::checkInequality(a1, b1, c1);
    double diff1 = InequalityABC::verifyInequality(a1, b1, c1);
    
    std::cout << "For a=1, b=2, c=3:" << std::endl;
    std::cout << "  Left side: " << InequalityABC::leftSide(a1, b1, c1) << std::endl;
    std::cout << "  Right side: " << InequalityABC::rightSide(a1, b1, c1) << std::endl;
    std::cout << "  Difference: " << diff1 << std::endl;
    
    TestRunner::assert_true(result1, "Inequality should hold for a=1, b=2, c=3");
    TestRunner::assert_true(diff1 >= 0, "Difference should be non-negative");
    
    // Тест 2: a=2, b=3, c=1
    double a2 = 2.0, b2 = 3.0, c2 = 1.0;
    bool result2 = InequalityABC::checkInequality(a2, b2, c2);
    double diff2 = InequalityABC::verifyInequality(a2, b2, c2);
    
    std::cout << "For a=2, b=3, c=1:" << std::endl;
    std::cout << "  Difference: " << diff2 << std::endl;
    
    TestRunner::assert_true(result2, "Inequality should hold for a=2, b=3, c=1");
}

void test_equality_case_abc() {
    std::cout << "\n=== Testing Equality Case: a = b = c ===" << std::endl;
    
    // Когда a = b = c, должно быть равенство
    double values[] = {0.0, 1.0, 2.0, 5.0, 10.0};
    
    for (double val : values) {
        bool is_eq = InequalityABC::isEquality(val, val, val);
        double diff = InequalityABC::verifyInequality(val, val, val);
        
        std::cout << "For a=b=c=" << val << ":" << std::endl;
        std::cout << "  Is equality: " << (is_eq ? "yes" : "no") << std::endl;
        std::cout << "  Difference: " << std::setprecision(10) << diff << std::endl;
        
        TestRunner::assert_true(is_eq, "Equality should hold when a=b=c=" + std::to_string(val));
        TestRunner::assert_approx_equal(diff, 0.0, 1e-9, 
                                         "Difference should be zero when a=b=c");
    }
}

void test_equality_case_zero() {
    std::cout << "\n=== Testing Equality Case: Zero Values ===" << std::endl;
    
    // Случай 1: a=1, b=0, c=0
    bool eq1 = InequalityABC::isEquality(1.0, 0.0, 0.0);
    std::cout << "For a=1, b=0, c=0: " << (eq1 ? "equality" : "inequality") << std::endl;
    TestRunner::assert_true(eq1, "Equality should hold when two variables are zero (case 1)");
    
    // Случай 2: a=0, b=2, c=0
    bool eq2 = InequalityABC::isEquality(0.0, 2.0, 0.0);
    std::cout << "For a=0, b=2, c=0: " << (eq2 ? "equality" : "inequality") << std::endl;
    TestRunner::assert_true(eq2, "Equality should hold when two variables are zero (case 2)");
    
    // Случай 3: a=0, b=0, c=3
    bool eq3 = InequalityABC::isEquality(0.0, 0.0, 3.0);
    std::cout << "For a=0, b=0, c=3: " << (eq3 ? "equality" : "inequality") << std::endl;
    TestRunner::assert_true(eq3, "Equality should hold when two variables are zero (case 3)");
    
    // Случай 4: a=0, b=0, c=0
    bool eq4 = InequalityABC::isEquality(0.0, 0.0, 0.0);
    std::cout << "For a=0, b=0, c=0: " << (eq4 ? "equality" : "inequality") << std::endl;
    TestRunner::assert_true(eq4, "Equality should hold when all variables are zero");
}

void test_various_cases() {
    std::cout << "\n=== Testing Various Cases ===" << std::endl;
    
    // Тест различных комбинаций
    std::vector<std::tuple<double, double, double, std::string>> test_cases = {
        {1.0, 1.0, 1.0, "Equal values"},
        {1.0, 2.0, 3.0, "Increasing values"},
        {3.0, 2.0, 1.0, "Decreasing values"},
        {5.0, 1.0, 2.0, "Mixed values"},
        {0.5, 0.5, 0.5, "Small equal values"},
        {10.0, 10.0, 10.0, "Large equal values"}
    };
    
    for (const auto& [a, b, c, desc] : test_cases) {
        bool holds = InequalityABC::checkInequality(a, b, c);
        double diff = InequalityABC::verifyInequality(a, b, c);
        
        std::cout << desc << " (a=" << a << ", b=" << b << ", c=" << c << "): ";
        std::cout << (holds ? "holds" : "fails") << ", diff=" << diff << std::endl;
        
        TestRunner::assert_true(holds, "Inequality should hold for " + desc);
    }
}

void test_find_equality_cases() {
    std::cout << "\n=== Testing Find Equality Cases ===" << std::endl;
    
    auto cases = InequalityABC::findEqualityCases(5.0, 0.5);
    
    std::cout << "Found " << cases.size() << " equality cases:" << std::endl;
    for (const auto& [a, b, c] : cases) {
        std::cout << "  (" << a << ", " << b << ", " << c << ")" << std::endl;
    }
    
    TestRunner::assert_true(cases.size() > 0, "Should find at least some equality cases");
}

void test_analysis() {
    std::cout << "\n=== Testing Analysis ===" << std::endl;
    
    std::string analysis = InequalityABC::analyzeEqualityCases();
    std::cout << analysis << std::endl;
    
    TestRunner::assert_true(!analysis.empty(), "Analysis should provide information");
}

void test_edge_cases() {
    std::cout << "\n=== Testing Edge Cases ===" << std::endl;
    
    // Очень малые значения
    bool small = InequalityABC::checkInequality(1e-10, 1e-10, 1e-10);
    TestRunner::assert_true(small, "Inequality should hold for very small values");
    
    // Очень большие значения
    bool large = InequalityABC::checkInequality(1e10, 1e10, 1e10);
    TestRunner::assert_true(large, "Inequality should hold for very large values");
    
    // Смешанные малые и большие
    bool mixed = InequalityABC::checkInequality(1e-5, 1.0, 1e5);
    TestRunner::assert_true(mixed, "Inequality should hold for mixed values");
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "Testing Task 4: Inequality ABC" << std::endl;
    std::cout << "========================================" << std::endl;
    
    test_basic_inequality();
    test_equality_case_abc();
    test_equality_case_zero();
    test_various_cases();
    test_find_equality_cases();
    test_analysis();
    test_edge_cases();
    
    TestRunner::print_summary();
    
    return 0;
}

