cmake_minimum_required(VERSION 3.8)

project(Unit2 LANGUAGES CXX)

add_executable(unit2 unit.cpp)

target_link_libraries(unit1 PRIVATE ${GTEST_LIBRARIES})