cmake_minimum_required(VERSION 3.23)

project(flanck VERSION 1.0)

add_subdirectory(library)

add_subdirectory(demo)

add_library(
        ${PROJECT_NAME} SHARED $<TARGET_OBJECTS:simple_library>
)

#TODO: do not include both
target_include_directories(
        flanck PUBLIC library/include
        flanck PUBLIC library
)