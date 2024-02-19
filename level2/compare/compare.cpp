#include <chrono>
#include <set>
#include <vector>
#include <cassert>

#include "rbtree.hpp"

//-------------------------------------------------------------------------------//

using KeyT = int;

int main(int argc, char** argv)
{
    using namespace SearchTree;

    char cmd{};

    bool mode = true;

    std::vector<KeyT> data;

    while (mode && std::cin >> cmd)
    {
        switch (cmd)
        {
            case 'k':
            {
                data.push_back('k');

                KeyT n = 0;

                std::cin >> n;

                data.push_back(n);

                break;
            }

            case 'm':
            {
                data.push_back('m');

                KeyT m = 0;
                
                std::cin >> m;

                data.push_back(m);

                break;
            }

            case 'n':
            {
                data.push_back('n');

                KeyT m = 0;
                
                std::cin >> m;

                data.push_back(m);

                break;
            }

            default:
            {
                std::cerr << "Inocorrect command: " << cmd << std::endl;
                mode = false;
            }
        }
    }

    std::cout << data.size() << std::endl;

    clock_t start_time = clock();

    auto start  = data.begin(); 
    
    auto end    = data.end();

    RBTree<KeyT, std::less<KeyT>> tree1;

    std::vector<int> answers_tree;

    for (auto elem = start; elem != end; ++elem)
    {
        if (*elem == 'k')
        {
            elem++;

            tree1.Insert(*elem);
        }

        else if (*elem == 'm')
        {
            elem++;

            answers_tree.push_back(tree1.MinimumElement(*elem));
        }

        else if (*elem == 'n')
        {
            elem++;

            answers_tree.push_back(tree1.LessThan(*elem));
        }
    }

    clock_t end_time = clock();

    std::cout << "Total time for RBTree is " << double (end_time - start_time) / CLOCKS_PER_SEC << std::endl;
     

    start_time = clock();

    start  = data.begin(); 
    
    end    = data.end();

    std::set<int> set_tree;

    std::vector<int> answers_set;

    for (auto elem = start; elem != end; elem++)
    {
        if (*elem == 'k')
        {
            elem++;

            set_tree.insert(*elem);
        }

        else if (*elem == 'm')
        {
            elem++;

            if (tree1.Size())
            {
                if (*elem <= set_tree.size())
                    answers_set.push_back(*std::next(set_tree.begin(), *elem - 1));

                else
                    answers_set.push_back(*set_tree.cend());

            }
        }

        else if (*elem == 'n')
        {
            elem++;

            answers_set.push_back(std::distance(set_tree.begin(), set_tree.lower_bound(*elem)));
        }
    }

    end_time = clock();

    std::cout << "Total time for std::set is " << double (end_time - start_time) / CLOCKS_PER_SEC << std::endl;

    return 0;
}

//-------------------------------------------------------------------------------//