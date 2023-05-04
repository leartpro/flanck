 cmake_minimum_required(VERSION 3.23)

 project(demo)

 set(CMAKE_CXX_STANDARD 11)

 add_executable(
         demo
         main.cpp
 )

 target_link_libraries(${PROJECT_NAME}
         libary
         # Add any other libs you want to use here
         )

