cmake_minimum_required(VERSION 3.8)

project(Ete LANGUAGES CXX)

add_executable(ete1 rbtreetest.cpp)

target_link_libraries(ete1 PRIVATE ${GTEST_LIBRARIES})