cmake_minimum_required(VERSION 3.10)
project(MathTasks CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опции для сборки
option(BUILD_TESTS "Build test programs" ON)

# Task 1: Inequality
add_library(task1_inequality STATIC
    task1_inequality/inequality.cpp
)

target_include_directories(task1_inequality PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
    add_executable(test_task1 task1_inequality/test_inequality.cpp)
    target_link_libraries(test_task1 task1_inequality)
endif()

# Task 2: Cone
add_library(task2_cone STATIC
    task2_cone/cone.cpp
)

target_include_directories(task2_cone PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
    add_executable(test_task2 task2_cone/test_cone.cpp)
    target_link_libraries(test_task2 task2_cone)
endif()

# Task 3: Polynomial
add_library(task3_polynomial STATIC
    task3_polynomial/polynomial.cpp
)

target_include_directories(task3_polynomial PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
    add_executable(test_task3 task3_polynomial/test_polynomial.cpp)
    target_link_libraries(test_task3 task3_polynomial)
endif()

# Task 4: Inequality ABC
add_library(task4_inequality_abc STATIC
    task4_inequality_abc/inequality_abc.cpp
)

target_include_directories(task4_inequality_abc PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
    add_executable(test_task4 task4_inequality_abc/test_inequality_abc.cpp)
    target_link_libraries(test_task4 task4_inequality_abc)
endif()

# Task 5: Complex Polynomial
add_library(task5_complex_poly STATIC
    task5_complex_poly/complex_polynomial.cpp
)

target_include_directories(task5_complex_poly PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if(BUILD_TESTS)
    add_executable(test_task5 task5_complex_poly/test_complex_polynomial.cpp)
    target_link_libraries(test_task5 task5_complex_poly)
endif()

# Исполняемые программы для каждой задачи
add_executable(run_task1 task1_inequality/main.cpp)
target_link_libraries(run_task1 task1_inequality)

add_executable(run_task2 task2_cone/main.cpp)
target_link_libraries(run_task2 task2_cone)

add_executable(run_task3 task3_polynomial/main.cpp)
target_link_libraries(run_task3 task3_polynomial)

add_executable(run_task4 task4_inequality_abc/main.cpp)
target_link_libraries(run_task4 task4_inequality_abc)

add_executable(run_task5 task5_complex_poly/main.cpp)
target_link_libraries(run_task5 task5_complex_poly)

# Создаем цель для запуска всех тестов
if(BUILD_TESTS)
    add_custom_target(run_all_tests
        COMMAND test_task1
        COMMAND test_task2
        COMMAND test_task3
        COMMAND test_task4
        COMMAND test_task5
        DEPENDS test_task1 test_task2 test_task3 test_task4 test_task5
        COMMENT "Running all tests"
    )
endif()

# Вывод информации
message(STATUS "MathTasks project configured")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build tests: ${BUILD_TESTS}")

