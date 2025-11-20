cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(linalg)

add_library(linalg ./src/linalg.cpp)

target_include_directories(linalg PUBLIC ./include)