cmake_minimum_required(VERSION 3.15)
project(day21)

set(CMAKE_CXX_STANDARD 17)

add_executable(day21
        main.cpp
        util.h
        util.cpp
        Program.h
        Program.cpp
        ProgramMemory.h
        ProgramMemory.cpp
        ProgramInputInterface.h ProgramInput.cpp ProgramInput.h)