cmake_minimum_required(VERSION 3.8)

project(Unit LANGUAGES CXX)

add_executable(unit1 unit.cpp)

target_link_libraries(unit1 PRIVATE ${GTEST_LIBRARIES})