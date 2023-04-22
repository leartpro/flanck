cmake_minimum_required(VERSION 3.23)
project(flanck)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        flanck
        src/main.cpp
        src/Token.h
        src/Stack.h
        src/Statement.h
        src/Lexer.cpp src/Lexer.h
        src/Parser.cpp src/Parser.h
        src/Interpreter.cpp src/Interpreter.h
)