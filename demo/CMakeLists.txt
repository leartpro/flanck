 cmake_minimum_required(VERSION 3.23)

 project(DEMO)

 set(CMAKE_CXX_STANDARD 11)

 add_executable(
         DEMO
         main.cpp
 )

 target_link_libraries(${PROJECT_NAME}
         FLANCK
         # Add any other libs you want to use here
 )

