#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

#include "rbtree.hpp"
#include "graphics.hpp"

//-------------------------------------------------------------------------------//

int main(int argc, char** argv)
{
    std::ifstream test_file{};

    test_file.open(argv[1]);

    SearchTree::RBTree<int> tree;

    std::vector<int> answers{};

    char cmd{};

    bool mode = true;

    std::clock_t start = clock();

    while(mode && test_file >> cmd)
    {
        switch (cmd)
        {
            case 'k':
            {
                int n = 0;

                test_file >> n;

                tree.Insert(n);

                break;
            }

            case 'q':
            {
                int first = 0, second = 0, answer = 0;

                test_file >> first >> second;

                if (first > second)
                    answer = 0;

                else
                    answer = tree.Distance(first, second);

                answers.push_back(answer);

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    for (int i = 0; i < answers.size(); i++)
        std::cout << answers[i] << " ";

    std::cout << std::endl;
    
    std::cout << "Total time is " << double (clock() - start) / CLOCKS_PER_SEC << std::endl;

    test_file.close();

    #ifdef TREE_DUMP

        TreeDump(&tree);

    #endif

    return 0;
}

//-------------------------------------------------------------------------------//