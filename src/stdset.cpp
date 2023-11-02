#include <iostream>
#include <set>

//-------------------------------------------------------------------------------//

int main()
{
    std::set<int> std_set{};

    char cmd{};

    bool mode = true;

    std::clock_t start = clock();

    while (mode && std::cin >> cmd)
    {
        switch (cmd)
        {
            case 'k':
            {
                int n = 0;

                std::cin >> n;

                std_set.insert(n);

                break;
            }

            case 'q':
            {
                int first = 0, second = 0;

                std::cin >> first >> second;

                if (first > second)
                    std::cout << 0 << ' ' << std::endl;

                else
                    std::cout << std::distance(std_set.lower_bound(first), std_set.upper_bound(second)) << " ";

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    std::cout << std::endl;

    std::cout << "Total time is " << (clock() - start) / CLOCKS_PER_SEC << std::endl;

    return 0;
}

//-------------------------------------------------------------------------------//