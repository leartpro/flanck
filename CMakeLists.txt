cmake_minimum_required(VERSION 3.23)
project(flanck)
set(CMAKE_CXX_STANDARD 11)
add_library(
        flanck
        SHARED
        src/Stack.h
        src/Lexer.cpp src/Lexer.h
        src/Parser.cpp src/Parser.h
        src/Interpreter.cpp src/Interpreter.h
)
target_include_directories(
        flanck PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)
install(
        TARGETS flanck EXPORT flanckConfig
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        INCLUDES DESTINATION include
)
install(EXPORT flanckConfig DESTINATION share/flanck/cmake)
install(FILES flanck/Parser.h DESTINATION include/flanck)