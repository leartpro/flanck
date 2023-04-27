
    cmake_minimum_required(VERSION 3.23)

    project(flanck)

    set(CMAKE_CXX_STANDARD 11)
    set(PROJECT_NAME "flanck")

    add_library(
            flanck SHARED
            src/Stack.h
            src/Lexer.cpp src/Lexer.h
            src/Parser.cpp src/Parser.h
            src/Interpreter.cpp src/Interpreter.h
    )