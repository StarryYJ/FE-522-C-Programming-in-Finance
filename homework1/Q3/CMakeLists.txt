cmake_minimum_required(VERSION 3.15)
project(Q3)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Q3
        include/Q3.h
        include/std_lib_facilities.h
        scr/main.cpp)
