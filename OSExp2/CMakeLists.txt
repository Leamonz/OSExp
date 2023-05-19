cmake_minimum_required(VERSION 3.23)
project(OSExp2)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSExp2 main.cpp utils.cpp Job.cpp Job.h)
