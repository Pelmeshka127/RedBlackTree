cmake_minimum_required(VERSION 3.8)

project(Tests LANGUAGES CXX)

add_executable(tests tests.cpp)

target_link_libraries(tests PRIVATE ${GTEST_LIBRARIES})