# CMakeList.txt: проект CMake для BilderTest; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

project ("BilderTest")

# Добавьте источник в исполняемый файл этого проекта.
add_executable (BilderTest "BilderTest.cpp" "BilderTest.h" "FooF.h")

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
