#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "rbtree.hpp"
#include "graphics.hpp"

// g++ tests.cpp -std=c++17 -o test -lgtest -lgmock -pthread

using namespace std;

//-------------------------------------------------------------------------------//

TEST(MyClassTest, init_class)
{
    SearchTree::Node<int> node1(3, SearchTree::Black);

    SearchTree::Node<int> node2(3, SearchTree::Black);

    ASSERT_EQ(node1.key_, node2.key_);

    ASSERT_EQ(node1.color_, node2.color_);
}

//-------------------------------------------------------------------------------//

TEST(NodeSizeTest, NodeSizeTest)
{
    SearchTree::RBTree<int> tree;

    tree.Insert(0);

    tree.Insert(-9);

    tree.Insert(-4);

    tree.Insert(17);

    tree.Insert(-6);

    tree.Insert(4);

    tree.Insert(-16);

    tree.Insert(-2);

    tree.Insert(19);

    tree.Insert(15);

    tree.Insert(10);

    TreeDump(&tree);
}

//-------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//-------------------------------------------------------------------------------//