cmake_minimum_required(VERSION 3.22)

project(advent_2022 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

option(ENABLE_GPROF "Enable gprof profiling")
if(${ENABLE_GPROF})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg") 
endif()

add_executable(day_01 src/day_01.cpp)
add_executable(day_02 src/day_02.cpp)
add_executable(day_03 src/day_03.cpp)
add_executable(day_04 src/day_04.cpp)
add_executable(day_05 src/day_05.cpp)
add_executable(day_06 src/day_06.cpp)
add_executable(day_07 src/day_07.cpp)
add_executable(day_08 src/day_08.cpp)
