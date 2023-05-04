cmake_minimum_required(VERSION 3.23)

project(libary)

set(CMAKE_CXX_STANDARD 11)


set(libary PARENT_SCOPE)

include_directories(include)

add_library(
        libary SHARED
        src/Lexer.cpp
        src/Parser.cpp
        src/Interpreter.cpp
        include/flanck/flanck.h
)

target_include_directories(
        libary PUBLIC include
)