cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(lab-1)

add_subdirectory(./linalg/)
add_executable(goal ./main.cpp)

target_link_libraries(goal PUBLIC linalg)
