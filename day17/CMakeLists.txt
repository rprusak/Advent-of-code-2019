cmake_minimum_required(VERSION 3.15)
project(day17)

set(CMAKE_CXX_STANDARD 17)

add_executable(day17
        main.cpp
        Program.h
        Program.cpp
        ProgramMemory.h
        ProgramMemory.cpp
        util.h
        util.cpp
        day17.cpp day17.h)