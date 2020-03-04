cmake_minimum_required(VERSION 3.15)
project(day11)

set(CMAKE_CXX_STANDARD 17)

add_executable(day11 main.cpp ProgramMemory.cpp Program.cpp util.cpp Robot.cpp Robot.h RobotInterface.h)