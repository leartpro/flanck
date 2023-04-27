
    cmake_minimum_required(VERSION 3.23)

    project(flanck)

    set(CMAKE_CXX_STANDARD 11)

    add_library(
            flanck
            src/Stack.h
            src/Lexer.h
            src/Parser.h
            src/Interpreter.h
    )