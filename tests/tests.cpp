#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../inc/node.hpp"

// g++ tests.cpp -std=c++17 -o test -lgtest -lgmock -pthread

using namespace std;

TEST(MyClassTest, init_class)
{
    SearchTree::Node<int> node1(3, SearchTree::Black);

    SearchTree::Node<int> node2(3, SearchTree::Black);

    ASSERT_EQ(node1.key_, node2.key_);

    ASSERT_EQ(node1.color_, node2.color_);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}