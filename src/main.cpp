#include <ctime>

#include "rbtree.hpp"
#include "graphics.hpp"

// #include <gtest/gtest.h>
// #include <gmock/gmock.h>

int main(int argc, char** argv)
{
    using namespace SearchTree;

    RBTree<int> tree1;

    tree1.InsertKey(5);

    tree1.InsertKey(2);

    tree1.InsertKey(4);

    TreeDump(&tree1);

    RBTree<int> tree2;

    tree2.InsertKey(8);

    tree2.InsertKey(9);

    tree2.InsertKey(10);

    TreeDump(&tree2);

    tree2 = tree1;

    TreeDump(&tree2);

    return 0;
}