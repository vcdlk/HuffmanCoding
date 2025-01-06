cmake_minimum_required(VERSION 3.1)

project(my_project) 


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE Debug)

add_executable(huffmanencode 
        src/huffmanencode.cpp 
)

add_executable(huffmandecode
        src/huffmandecode.cpp 
)

target_link_libraries(huffmanencode  comm_logic)
target_link_libraries(huffmandecode  comm_logic)


add_library(comm_logic
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
            src/huffman_decoder.cpp
            src/huffman_decoder.h
)

add_subdirectory(third_party/googletest)

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(huffman_test
               test/frequency_table_test.cpp
               src/frequency_table.h)

target_link_libraries(huffman_test gtest gtest_main comm_logic)

add_test(NAME huffman_test COMMAND huffman_test)