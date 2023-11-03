cmake_minimum_required(VERSION 3.8)

project(Ete LANGUAGES CXX)

add_executable(rbtreetest rbtreetest.cpp)

add_executable(stdsettest stdsettest.cpp)

target_link_libraries(rbtreetest PRIVATE ${GTEST_LIBRARIES})

target_link_libraries(stdsettest PRIVATE ${GTEST_LIBRARIES})