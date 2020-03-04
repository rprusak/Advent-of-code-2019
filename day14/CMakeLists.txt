cmake_minimum_required(VERSION 3.15)
project(day14)

set(CMAKE_CXX_STANDARD 17)

add_executable(day14 main.cpp util.cpp FuelCalculator.cpp FuelCalculator.h)
add_executable(test_all test_all.cpp util.cpp FuelCalculator.cpp FuelCalculator.h)
