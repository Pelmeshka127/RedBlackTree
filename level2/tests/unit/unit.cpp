#include <iostream>
#include <gtest/gtest.h>
#include <fstream>
#include <gmock/gmock.h>

#include "rbtree.hpp"

using namespace std;

//-------------------------------------------------------------------------------//

void EteTestRunner(const char* src, const char* ans)
{
    ifstream test_file{};

    test_file.open(src);

    SearchTree::RBTree<int> tree;

    std::vector<int> test_answers{};

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

            case 'm':
            {
                int m = 0;

                test_file >> m;

                test_answers.push_back(tree.MinimumElement(m));

                break;
            }

            case 'n':
            {
                int n = 0;

                test_file >> n;

                test_answers.push_back(static_cast<int>(tree.LessThan(n)));

                break;
            }

            default:
            {
                mode = false;
            }
        }
    }

    test_file.close();

    ifstream ans_file{};

    ans_file.open(ans);

    std::vector<int> answers{};

    while(ans_file.good())
    {
        int elem = 0;

        ans_file >> elem;

        answers.push_back(elem);
    }

    ans_file.close();

    for (int i = 0; i < test_answers.size(); i++)
    {
        ASSERT_EQ(test_answers[i], answers[i]);
    }
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test1)
{
    EteTestRunner("../../../tests/ete/001.dat", "../../../tests/ete/001.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test2)
{
    EteTestRunner("../../../tests/ete/002.dat", "../../../tests/ete/002.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test3)
{
    EteTestRunner("../../../tests/ete/003.dat", "../../../tests/ete/003.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test4)
{
    EteTestRunner("../../../tests/ete/004.dat", "../../../tests/ete/004.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test5)
{
    EteTestRunner("../../../tests/ete/005.dat", "../../../tests/ete/005.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test6)
{
    EteTestRunner("../../../tests/ete/006.dat", "../../../tests/ete/006.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test7)
{
    EteTestRunner("../../../tests/ete/007.dat", "../../../tests/ete/007.answer");
}

//-------------------------------------------------------------------------------//

TEST(EteTest, test8)
{
    EteTestRunner("../../../tests/ete/008.dat", "../../../tests/ete/008.answer");
}

//-------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//-------------------------------------------------------------------------------//