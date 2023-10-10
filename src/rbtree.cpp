#include "../inc/rbtree.hpp"

//-------------------------------------------------------------------------------//

RBTree::RBTree()
{
    root_ = new Node();
    if (root_ == nullptr)
    {
        std::cerr << "Failed allocation memory for root in " << __PRETTY_FUNCTION__ << std::endl;
        return;
    }
}

//-------------------------------------------------------------------------------//

size_t RBTree::Size() const
{
    return size_;
}

//-------------------------------------------------------------------------------//

Node* RBTree::Root() const
{
    return root_;
}

//-------------------------------------------------------------------------------//

void RBTree::LeftRotate(RBTree* tree, Node* x)
{
    Node* y = x->right_;
    
    x->right_ = y->left_;

    if (y->left_ != nullptr)
        y->left_->parent_ = x;

    y->parent_ = x->parent_;

    if (x->parent_ == nullptr)
        tree->root_ = y;

    else if (x == x->parent_->left_)
        x->parent_->left_  = y;

    else
        x->parent_->right_ = y;

    y->left_   = x;
    
    x->parent_ = y;
}

//-------------------------------------------------------------------------------//

void RBTree::RightRotate(RBTree* tree, Node* y)
{
    Node* x = y->left_;

    y->left_ = x->right_;

    if (x->right_ != nullptr)
        x->right_->parent_ = y;

    x->parent_ = y->parent_;

    if (y->parent_ == nullptr)
        tree->root_ = x;

    else if (y == y->parent_->left_)
        y->parent_->left_  = x;

    else
        y->parent_->right_ = x;

    x->right_  = y;

    y->parent_ = x;
}

//-------------------------------------------------------------------------------//

RBTree::~RBTree()
{
    CleanTree(root_);

    size_ = 0;
}

//-------------------------------------------------------------------------------//

void RBTree::CleanTree(Node* node)
{
    if (!node)
        return;

    CleanTree(node->left_);

    CleanTree(node->right_);

    delete node;

    node = nullptr;
}

//-------------------------------------------------------------------------------//