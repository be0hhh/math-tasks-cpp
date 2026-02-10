@echo off
chcp 65001 >nul
echo ========================================
echo МАТЕМАТИЧЕСКИЕ ЗАДАЧИ
echo ========================================
echo.

REM Проверяем наличие собранных программ
if not exist "build\Release\run_task1.exe" (
    echo ВНИМАНИЕ: Программы не собраны!
    echo.
    echo Запустите сначала: собрать.bat
    echo.
    pause
    exit /b 1
)

echo.
echo Выберите задачу:
echo.
echo   1 - Задача A.2: Неравенство
echo      Условие: Для всех m, n из N доказать неравенство
echo      1/(m^(1/n)) + 1/(n^(1/m)) ^> 1
echo      (неравенство Коши)
echo.
echo   2 - Задача о конусе максимального объема
echo      Условие: Из круга радиуса R вырезан сектор углом ф радиан.
echo      Из оставшейся части делается прямой круговой конус.
echo      При каком ф конус будет иметь максимальный объем?
echo.
echo   3 - Задача с полиномом
echo      Условие: Дано p(x) = x^5 - 2x^4 + 3x^3 - x^2 + x - 2
echo      Найти: p(2), p'(1), p''(3), p'''(-1)
echo      Разложить по (x-1)^k, k=0,...,5
echo.
echo   4 - Задача 13: Неравенство
echo      Условие: Для a, b, c ^>= 0 доказать неравенство
echo      a^3b + b^3c + c^3a ^>= a^2bc + b^2ca + c^2ab
echo      Найти случаи равенства.
echo.
echo   5 - Задача 5: Полином в комплексной точке
echo      Условие: Вычислить алгебраический полином P_n(x) с вещ.
echo      коэффициентами в комплексной точке z0 = u0 + iv0.
echo      Разделить полином на (x-z0)(x-z0*) = x^2 + px + q
echo      где p = -2u0, q = u0^2 + v0^2
echo.
echo   0 - Запустить все задачи подряд
echo.
set /p choice="Ваш выбор (0-5): "

if "%choice%"=="1" goto task1
if "%choice%"=="2" goto task2
if "%choice%"=="3" goto task3
if "%choice%"=="4" goto task4
if "%choice%"=="5" goto task5
if "%choice%"=="0" goto all
goto error

:task1
echo.
echo ========================================
echo ЗАДАЧА 1: НЕРАВЕНСТВО
echo ========================================
echo.
cd build\Release
run_task1.exe
cd ..\..
pause
goto end

:task2
echo.
echo ========================================
echo ЗАДАЧА 2: КОНУС МАКСИМАЛЬНОГО ОБЪЕМА
echo ========================================
echo.
cd build\Release
run_task2.exe
cd ..\..
pause
goto end

:task3
echo.
echo ========================================
echo ЗАДАЧА 3: ПОЛИНОМ И ПРОИЗВОДНЫЕ
echo ========================================
echo.
cd build\Release
run_task3.exe
cd ..\..
pause
goto end

:task4
echo.
echo ========================================
echo ЗАДАЧА 4: НЕРАВЕНСТВО С A, B, C
echo ========================================
echo.
cd build\Release
run_task4.exe
cd ..\..
pause
goto end

:task5
echo.
echo ========================================
echo ЗАДАЧА 5: КОМПЛЕКСНЫЕ ПОЛИНОМЫ
echo ========================================
echo.
cd build\Release
run_task5.exe
cd ..\..
pause
goto end

:all
echo.
echo ========================================
echo ЗАПУСК ВСЕХ ЗАДАЧ
echo ========================================
echo.
cd build\Release

echo.
echo --- ЗАДАЧА 1 ---
run_task1.exe
echo.
pause

echo.
echo --- ЗАДАЧА 2 ---
run_task2.exe
echo.
pause

echo.
echo --- ЗАДАЧА 3 ---
run_task3.exe
echo.
pause

echo.
echo --- ЗАДАЧА 4 ---
run_task4.exe
echo.
pause

echo.
echo --- ЗАДАЧА 5 ---
run_task5.exe
echo.
pause

cd ..\..

:end
exit

:error
echo Неверный выбор!
pause
goto end

