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

                // tree1.Insert(n);

                break;
            }

            case 'q':
            {
                data.push_back('q');

                KeyT first = 0, second = 0;

                std::cin >> first >> second;

                data.push_back(first);

                data.push_back(second);

                // size_t ans = tree1.Distance(first, second);

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    clock_t start_time = clock();

    auto start  = data.begin(); 
    
    auto end    = data.end();

    RBTree<KeyT, std::less<KeyT>> tree1;

    std::vector<int> answers_tree;

    for (auto elem = start; elem != end; elem++)
    {
        if (*elem == 'k')
        {
            elem++;

            tree1.Insert(*elem);
        }

        else if (*elem == 'q')
        {
            if (*(elem + 2) >= *(elem + 1))
                answers_tree.push_back(tree1.Distance(*(elem + 1), *(elem + 2)));

            elem += 2;
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

        else if (*elem == 'q')
        {
            if (*(elem + 2) >= *(elem + 1))
                answers_set.push_back(std::distance(set_tree.lower_bound(*(elem + 1)), set_tree.upper_bound(*(elem + 2))));

            elem += 2;
        }
    }

    end_time = clock();

    std::cout << "Total time for std::set is " << double (end_time - start_time) / CLOCKS_PER_SEC << std::endl;

    return 0;
}

//-------------------------------------------------------------------------------//