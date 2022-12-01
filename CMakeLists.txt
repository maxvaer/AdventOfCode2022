cmake_minimum_required(VERSION 3.24)
project(AoC22)

set(CMAKE_CXX_STANDARD 20)

add_executable(AoC22 main.cpp Day1/day1.cpp)
if (MSVC)
    target_compile_options(AoC22 PRIVATE /W4 /WX)
endif ()