cmake_minimum_required(VERSION 3.27)
project(YARAOSUD)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA2G195 main.cpp
        src/Menu.cpp
        include/Menu.h
        src/Graph.cpp
        include/Graph.h
        src/ReadFunctions.cpp
        include/ReadFunctions.h
        include/Include.h)

