cmake_minimum_required(VERSION 3.20)
project(MyMalloc)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 17)

add_executable(MyMalloc src/main.c src/dPartition.c src/my_malloc.cpp)

target_include_directories(MyMalloc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
