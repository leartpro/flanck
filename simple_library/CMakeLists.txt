cmake_minimum_required(VERSION 3.23)

project(simple_library)

set(CMAKE_CXX_STANDARD 11)

set(simple_library PARENT_SCOPE)

include_directories(include)

add_library(
        simple_library STATIC
        src/Lexer.cpp
        src/Parser.cpp
        src/Interpreter.cpp
        include/flanck.h
)

target_include_directories(
        simple_library PUBLIC include
)