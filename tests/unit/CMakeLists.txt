cmake_minimum_required(VERSION 3.8)

project(Unit LANGUAGES CXX)

add_executable(unit unit.cpp)

target_link_libraries(unit PRIVATE ${GTEST_LIBRARIES})