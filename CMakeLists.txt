cmake_minimum_required(VERSION 3.23)
project(flanck)
set(CMAKE_CXX_STANDARD 11)
add_library(
        flanck SHARED
        src/Lexer.cpp
        src/Parser.cpp
        src/Interpreter.cpp
)
target_include_directories(
        flanck PUBLIC
)