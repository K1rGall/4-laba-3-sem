cmake_minimum_required(VERSION 3.28)
project(laba4)

set(CMAKE_CXX_STANDARD 17)
find_package(Python3 REQUIRED)
add_executable(laba4 main.cpp
        menu.cpp
        DifferentStructures/Graph.cpp
        tests.cpp
        tests.h)
include_directories(${Python3_INCLUDE_DIRS})
target_link_libraries(laba4 ${Python3_LIBRARIES})