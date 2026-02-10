@echo off
chcp 65001 >nul
echo ========================================
echo СБОРКА ПРОЕКТА
echo ========================================
echo.

REM Проверяем наличие CMake
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ОШИБКА: CMake не найден!
    echo.
    echo Установите CMake: https://cmake.org/download/
    echo Или используйте Visual Studio для сборки
    pause
    exit /b 1
)

echo Создаем директорию для сборки...
if not exist build mkdir build
cd build

echo.
echo Настраиваем проект...
cmake .. -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 (
    echo.
    echo ОШИБКА при настройке проекта!
    pause
    exit /b 1
)

echo.
echo Собираем проект...
cmake --build . --config Release
if %errorlevel% neq 0 (
    echo.
    echo ОШИБКА при сборке проекта!
    pause
    exit /b 1
)

cd ..

echo.
echo ========================================
echo СБОРКА ЗАВЕРШЕНА УСПЕШНО!
echo ========================================
echo.
echo Исполняемые файлы находятся в: build\Release\
echo.
echo Теперь можно запустить программы через: запустить_все.bat
echo.
pause

