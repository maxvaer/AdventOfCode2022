cmake_minimum_required(VERSION 3.24)
project(AoC22)

set(CMAKE_CXX_STANDARD 20)

add_executable(AoC22 main.cpp Day1/day1.cpp Day2/day2.cpp Day3/day3.cpp Day4/day4.cpp Day5/day5.cpp Day6/day6.cpp Day7/day7.cpp Day8/day8.cpp Day9/day9.cpp Day10/day10.cpp Day11/day11.cpp Day12/day12.cpp Day13/day13.cpp)
if (MSVC)
    target_compile_options(AoC22 PRIVATE /W4 /WX)
endif ()