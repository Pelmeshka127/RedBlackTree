#include "rbtree.hpp"
#include "graphics.hpp"

//-------------------------------------------------------------------------------//

using KeyT = int;

using CompType = int;

CompType Comparator(KeyT first, KeyT second)
{
    if (first < second)
        return -1;

    else if (first == second)
        return 0;

    else
        return 1;
}

//-------------------------------------------------------------------------------//

int main(int argc, char** argv)
{
    using namespace SearchTree;

    RBTree<KeyT, std::less<KeyT>> tree1;

    char cmd{};

    bool mode = true;

    while (mode && std::cin >> cmd)
    {
        switch (cmd)
        {
            case 'k':
            {
                int n = 0;

                std::cin >> n;

                tree1.InsertKey(n);

                break;
            }

            case 'q':
            {
                int first = 0, second = 0;

                std::cin >> first >> second;

                if (first > second)
                    std::cout << 0 << ' ';

                else
                    std::cout << tree1.Distance(first, second) << std::endl;

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    std::cout << std::endl;
    
    TreeDump(&tree1);

    return 0;
}

//-------------------------------------------------------------------------------//

// int main(int argc, char** argv)
// {
//     using namespace SearchTree;

//     RBTree<int> tree;

//     tree.InsertKey(0);

//     TreeDump(&tree);

//     tree.InsertKey(-9);

//     TreeDump(&tree);

//     tree.InsertKey(-4);

//     TreeDump(&tree);

//     tree.InsertKey(17);

//     TreeDump(&tree);

//     tree.InsertKey(-6);

//     TreeDump(&tree);

//     tree.InsertKey(4);

//     TreeDump(&tree);

//     tree.InsertKey(-16);

//     TreeDump(&tree);

//     tree.InsertKey(-2);

//     TreeDump(&tree);

//     tree.InsertKey(19);

//     TreeDump(&tree);

//     tree.InsertKey(15);

//     TreeDump(&tree);

//     tree.InsertKey(10);

//     TreeDump(&tree);

//     return 0;
// }

//-------------------------------------------------------------------------------//