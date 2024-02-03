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

                break;
            }

            case 'm':
            {
                KeyT index{};

                std::cin >> index;

                answers.push_back(tree.MinimumElement(index));

                break;
            }

            case 'n':
            {
                KeyT number{};

                std::cin >> number;

                answers.push_back(static_cast<KeyT>(tree.LessThan(number)));

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    for (size_t i = 0; i < answers.size(); i++)
        std::cout << answers[i] << " ";

    TreeDump(&tree);

    std::cout << std::endl;

    return 0;
}