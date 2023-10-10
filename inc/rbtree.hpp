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

        void LeftRotate(RBTree* tree, Node* rotated_node);

        void RightRotate(RBTree* tree, Node* rotated_node);

        void CleanTree(Node* node);

    public:
        RBTree();

        ~RBTree();

        size_t Size() const;

        Node*  Root() const;
};

//-------------------------------------------------------------------------------//

#endif