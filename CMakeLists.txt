cmake_minimum_required(VERSION 3.23)
project(flanck)

set(CMAKE_CXX_STANDARD 17)

add_executable(flanck src/flanck.cpp src/Stack.h)