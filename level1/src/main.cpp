#include <vector>

#include "rbtree.hpp"
#include "graphics.hpp"

//-------------------------------------------------------------------------------//

using KeyT = int;

int main(int argc, char** argv)
{
    using namespace SearchTree;

    RBTree<KeyT, std::less<KeyT>> tree1;

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

                tree1.Insert(n);

                break;
            }

            case 'q':
            {
                KeyT first = 0, second = 0;

                std::cin >> first >> second;

                if (first > second)
                    answers.push_back(0);

                else
                    answers.push_back(tree1.Distance(first, second));

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

    std::cout << std::endl;

    #ifdef TREE_DUMP
    
        TreeDump(&tree1);

    #endif

    return 0;
}

//-------------------------------------------------------------------------------//