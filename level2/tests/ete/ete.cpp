#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>

#include "rbtree.hpp"

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

    while(test_file >> cmd)
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

            case 'm':
            {
                int index{};

                test_file >> index;

                answers.push_back(tree.MinimumElement(index));

                break;
            }

            case 'n':
            {
                int number{};

                test_file >> number;

                answers.push_back(static_cast<int>(tree.LessThan(number)));

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

    return 0;
}

//-------------------------------------------------------------------------------//