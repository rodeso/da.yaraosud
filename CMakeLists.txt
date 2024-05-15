cmake_minimum_required(VERSION 3.20)
project(YARAOSUD)

set(CMAKE_CXX_STANDARD 17)

add_executable(DA2G195 main.cpp
        src/Menu.cpp
        include/Menu.h
        include/Graph.h
        src/ReadFunctions.cpp
        include/ReadFunctions.h
        include/Include.h
        src/OperationFunctions.cpp
        include/OperationFunctions.h
        src/Haversine.cpp
        include/Haversine.h
)

