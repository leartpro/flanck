cmake_minimum_required(VERSION 3.23)

project(simple_library VERSION 1.0)

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols")

add_subdirectory(library)

add_subdirectory(demo)

add_library(
        ${PROJECT_NAME} SHARED $<TARGET_OBJECTS:FLANCK>
)