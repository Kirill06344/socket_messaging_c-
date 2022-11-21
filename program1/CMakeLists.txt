cmake_minimum_required(VERSION 3.16)
project(program1)

set(CMAKE_CXX_STANDARD 14)

add_executable(program1 main.cpp threadGuard.cpp threadGuard.h stringHandler.cpp stringHandler.h sender.cpp sender.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")