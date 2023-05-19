cmake_minimum_required(VERSION 3.23)
project(OSExp4)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSExp4 memoryAlloc.cpp virtumem.cpp LRU.cpp CheckMemoInfo.cpp Manager.cpp Manager.h main.cpp)
