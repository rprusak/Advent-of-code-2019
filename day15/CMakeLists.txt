cmake_minimum_required(VERSION 3.15)
project(day15)

set(CMAKE_CXX_STANDARD 17)

add_executable(day15
        main.cpp
        ProgramMemory.cpp
        Program.cpp
        util.cpp
        Droid.cpp Droid.h ProgramInterface.h dijkstra.h dijkstra.cpp)