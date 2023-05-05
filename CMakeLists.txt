cmake_minimum_required(VERSION 3.23)

project(flanck VERSION 1.0)

#set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

add_subdirectory(simple_library)

add_subdirectory(demo)

add_library(
        ${PROJECT_NAME} SHARED $<TARGET_OBJECTS:simple_library>
)

target_include_directories(
        flanck PUBLIC simple_library/include
        flanck PUBLIC simple_library
)