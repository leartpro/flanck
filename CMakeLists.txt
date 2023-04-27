cmake_minimum_required(VERSION 3.23)
project(flanck)
set(CMAKE_CXX_STANDARD 11)

# Define flanck library
add_library(
        flanck
        SHARED
        src/Stack.h
        src/Lexer.cpp src/Lexer.h
        src/Parser.cpp src/Parser.h
        src/Interpreter.cpp src/Interpreter.h
)

# Install flanck library and export targets
install(
        TARGETS flanck
        EXPORT flanck-targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)

# Install flanck header files
install(
        DIRECTORY include/
        DESTINATION include/flanck
        FILES_MATCHING PATTERN "*.h"
)
