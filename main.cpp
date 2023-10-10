#include "inc/rbtree.hpp"
#include "inc/graphics.hpp"


int main(int argc, char** argv)
{
    RBTree tree = RBTree();

    tree.Root()->key_ = 5;

    TreeDump(&tree);

    return 0;
}