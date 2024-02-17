#include "rbtree.hpp"
#include "graphics.hpp"

#include <iostream>
#include <vector>

using KeyT = int;

int main()
{
    using namespace SearchTree;

    RBTree<KeyT, std::less<KeyT>> tree;

    char cmd{};

    std::vector<KeyT> answers{};

    bool mode = true;

    while (mode && std::cin >> cmd)
    {
        switch (cmd)
        {
            case 'k':
            {
                KeyT n = 0;

                std::cin >> n;

                tree.Insert(n);

                // TreeDump(&tree);

                break;
            }

            case 'm':
            {
                KeyT index{};

                std::cin >> index;

                answers.push_back(tree.MinimumElement(index));

                // std::cout << answers[answers.size() - 1] << std::endl;

                break;
            }

            case 'n':
            {
                KeyT number{};

                std::cin >> number;

                answers.push_back(static_cast<KeyT>(tree.LessThan(number)));

                // std::cout << answers[answers.size() - 1] << std::endl;

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    for (size_t i = 0; i < answers.size() - 1; i++)
        std::cout << answers[i] << " ";

    std::cout << answers[answers.size() - 1];

#ifdef TREE_DUMP

    TreeDump(&tree);

#endif

    std::cout << std::endl;

    return 0;
}