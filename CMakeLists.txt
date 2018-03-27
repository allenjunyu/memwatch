# cmake_minimum_required(VERSION <specify CMake version here>)
CMAKE_MINIMUM_REQUIRED(VERSION 3.2.0)
PROJECT(memwatch)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_C_FLAGS "-std=c99")

INCLUDE_DIRECTORIES(include)

SET(SOURCE_memwatch src/memwatch.c include/memwatch.h)

SET(SOURCE_test_memory
        test_memory.c ${SOURCE_memwatch})

add_executable(test_memory ${SOURCE_test_memory})