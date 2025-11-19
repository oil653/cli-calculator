cmake_minimum_required(VERSION 4.0)
project(cli_calc)

set(CMAKE_CXX_STANDARD 20)

add_executable(cli_calc main.cpp
        includes/StrProcessing.h
        src/StrProcessing.cpp
        includes/main.h
        includes/CalcFunctions.h
        src/CalcFunctions.cpp)
