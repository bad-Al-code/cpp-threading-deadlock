cmake_minimum_required(VERSION 3.10)
project(deadlock)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(deadlock
    src/main.cpp
    src/thread.cpp
)

