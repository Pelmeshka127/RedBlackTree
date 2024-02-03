#include <iostream>
#include <gtest/gtest.h>
#include <fstream>
#include <gmock/gmock.h>

#include "rbtree.hpp"
#include "graphics.hpp"

// g++ tests.cpp -std=c++17 -o test -lgtest -lgmock -pthread

using namespace std;

//-------------------------------------------------------------------------------//

TEST(MyClassTest, init_class)
{
    SearchTree::Node<int> node1(3, SearchTree::Black);

    SearchTree::Node<int> node2(3, SearchTree::Black);

    ASSERT_EQ(node1.key_, node2.key_);

    ASSERT_EQ(node1.color_, node2.color_);
}

//-------------------------------------------------------------------------------//

TEST(NodeSizeTest, NodeSizeTest)
{
    SearchTree::RBTree<int> tree;

    tree.Insert(0);

    tree.Insert(-9);

    tree.Insert(-4);

    tree.Insert(17);

    tree.Insert(-6);

    tree.Insert(4);

    tree.Insert(-16);

    tree.Insert(-2);

    tree.Insert(19);

    tree.Insert(15);

    tree.Insert(10);

    #ifdef TREE_DUMP

        TreeDump(&tree);

    #endif
}

//-------------------------------------------------------------------------------//

TEST(CopyCtor, CopyCtor)
{
    using namespace SearchTree;

    RBTree<int> tree1{};

    tree1.Insert(1);

    tree1.Insert(2);

    tree1.Insert(3);

    tree1.Insert(4);

    tree1.Insert(5);

    tree1.Insert(6);

    RBTree<int> tree2(tree1);

    #ifdef TREE_DUMP

        TreeDump(&tree1);

        TreeDump(&tree2);

    #endif

    ASSERT_EQ(tree1.Size(), tree2.Size());
}

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

            case 'q':
            {
                int first = 0, second = 0, answer = 0;

                test_file >> first >> second;

                if (first > second)
                    answer = 0;

                else
                    answer = tree.Distance(first, second);

                test_answers.push_back(answer);

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

TEST(EteTest, test14)
{
    EteTestRunner("../../../tests/ete/014.dat", "../../../tests/ete/014.answer");
}

//-------------------------------------------------------------------------------//

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

//-------------------------------------------------------------------------------//