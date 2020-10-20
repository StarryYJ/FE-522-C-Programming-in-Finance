cmake_minimum_required(VERSION 3.15)
project(Q6)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Q6
        include/Q6.h
        include/std_lib_facilities.h
        input/apple.csv
        input/BOA.csv
        input/facebook.csv
        input/macdonald.csv
        input/nintendo.csv
        scr/main.cpp)
