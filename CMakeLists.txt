cmake_minimum_required(VERSION 3.16)
project(lesson)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SRC src/*.cpp)
add_executable(lesson ${SRC})