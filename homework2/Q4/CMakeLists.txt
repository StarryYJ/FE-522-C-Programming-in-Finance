cmake_minimum_required(VERSION 3.15)
project(Q4Q5)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Q4Q5
        include/Q4Q5.h
        include/std_lib_facilities.h
        input/Options.txt
        scr/main.cpp)
