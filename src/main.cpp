#include "rbtree.hpp"
#include "graphics.hpp"

int main(int argc, char** argv)
{
    using namespace SearchTree;

    RBTree<int> tree;

    tree.InsertKey(5);

    TreeDump(&tree);

    tree.InsertKey(2);

    TreeDump(&tree);

    tree.InsertKey(4);

    TreeDump(&tree);

    tree.InsertKey(1);

    TreeDump(&tree);

    tree.InsertKey(6);

    TreeDump(&tree);

    tree.InsertKey(3);
    
    TreeDump(&tree);

    tree.DeleteKey(3);

    TreeDump(&tree);

    return 0;
}