cmake_minimum_required(VERSION 3.2)
project(wroclaw)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(stack_float STATIC stack_float.c)
add_library(stack_string STATIC stack_string.c)
add_library(queue_string STATIC queue_string.c)
add_library(functions STATIC functions.c)
add_executable(wroclaw main.c)

add_executable(test_queue_string test_queue_string.c)

target_link_libraries(wroclaw functions stack_float stack_string queue_string)
target_link_libraries(test_queue_string queue_string)
