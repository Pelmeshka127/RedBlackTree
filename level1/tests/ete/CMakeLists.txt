cmake_minimum_required(VERSION 3.8)

project(Ete LANGUAGES CXX)

add_executable(rbtreetest1 rbtreetest.cpp)

add_executable(stdsettest1 stdsettest.cpp)

target_link_libraries(rbtreetest1 PRIVATE ${GTEST_LIBRARIES})

target_link_libraries(stdsettest1 PRIVATE ${GTEST_LIBRARIES})