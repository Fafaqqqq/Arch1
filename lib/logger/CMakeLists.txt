cmake_minimum_required(VERSION 3.16)

set(target logger)

project(${target})

file(GLOB_RECURSE sources 
    inc/*.h
    src/*.h
    src/*.cpp
)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${target} ${sources})

target_include_directories(${target} PUBLIC inc/)
target_include_directories(${target} PRIVATE src/)


