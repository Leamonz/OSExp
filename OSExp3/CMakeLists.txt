cmake_minimum_required(VERSION 3.23)
project(OSExp3)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSExp3 Reader_Writer.cpp Producer_Customer.cpp utils.h utils.cpp Philosopher.cpp Bridge.cpp)
