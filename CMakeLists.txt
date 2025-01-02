cmake_minimum_required(VERSION 3.1)

project(my_project) 


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_executable(main 
        src/main.cpp 
        src/frequency_table.cpp
        src/frequency_table.h
        src/code_tree.cpp
        src/code_tree.h 
        src/bitiostream.cpp
        src/bitiostream.h
        src/canonicalcode.cpp
        src/canonicalcode.h
        src/huffman_coder.cpp
        src/huffman_coder.h
)