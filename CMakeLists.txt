cmake_minimum_required(VERSION 3.8)

project(RBT LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(GTest REQUIRED)
enable_testing()

include_directories(inc)

add_subdirectory(./level1)

add_subdirectory(./level2)