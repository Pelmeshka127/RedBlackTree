#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>

#include "node.hpp"

//-------------------------------------------------------------------------------//

class RBTree
{
    private:
        size_t size_ = 0;

        Node *root_  = nullptr;

    public:
        RBTree() {};

        // RBTree(int key);

        ~RBTree();

        size_t Size() const;

        Node*  Root() const;

        int InsertKey(int key);

    private:
        void LeftRotate(Node* rotated_node);

        void RightRotate(Node* rotated_node);

        void InsertNode(Node* node);

        void InsertFixUp(Node* node);

        void CleanTree(Node* node);

};

//-------------------------------------------------------------------------------//

#endif