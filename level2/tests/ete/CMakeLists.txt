cmake_minimum_required(VERSION 3.8)

project(Ete2 LANGUAGES CXX)

add_executable(ete2 ete.cpp)

target_link_libraries(ete2 PRIVATE ${GTEST_LIBRARIES})