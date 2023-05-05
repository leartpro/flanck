cmake_minimum_required(VERSION 3.23)

project(FLANCK)

set(CMAKE_CXX_STANDARD 11)

set(FLANCK PARENT_SCOPE)

include_directories(include)

add_library(
        FLANCK OBJECT
        src/Lexer.cpp
        src/Parser.cpp
        src/Interpreter.cpp
        include/flanck.h
)

target_include_directories(
        FLANCK PUBLIC include
)