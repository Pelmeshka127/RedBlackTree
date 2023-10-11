#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>

#include "node.hpp"

//-------------------------------------------------------------------------------//

template<typename KeyT>
class RBTree
{
    private:
        size_t size_ = 0;

        Node<KeyT> *root_  = nullptr;

    public:
        RBTree() {};

        // RBTree(int key);

        ~RBTree();

        size_t Size() const;

        Node<KeyT>*  Root() const;

        int InsertKey(int key);

        int DeleteKey(int key);

    private:
        void LeftRotate(Node<KeyT>* rotated_node);

        void RightRotate(Node<KeyT>* rotated_node);

        void InsertNode(Node<KeyT>* node);

        void InsertFixUp(Node<KeyT>* node);

        // void Transplant(Node<KeyT>* u, Node<KeyT>* v);
        
        // void DeleteNode(Node<KeyT>* node);

        // void DeleteFixUp(Node<KeyT>* node);

        void CleanTree(Node<KeyT>* node);

};

//-------------------------------------------------------------------------------//

template<typename KeyT>
size_t RBTree<KeyT>::Size() const
{
    return size_;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::Root() const
{
    return root_;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::LeftRotate(Node<KeyT>* x)
{
    Node<KeyT>* y = x->right_;
    
    x->right_ = y->left_;

    if (y->left_ != nullptr)
        y->left_->parent_ = x;

    y->parent_ = x->parent_;

    if (x->parent_ == nullptr)
        root_ = y;

    else if (x == x->parent_->left_)
        x->parent_->left_  = y;

    else
        x->parent_->right_ = y;

    y->left_   = x;
    
    x->parent_ = y;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::RightRotate(Node<KeyT>* y)
{
    Node<KeyT>* x = y->left_;

    y->left_ = x->right_;

    if (x->right_ != nullptr)
        x->right_->parent_ = y;

    x->parent_ = y->parent_;

    if (y->parent_ == nullptr)
        root_ = x;

    else if (y == y->parent_->left_)
        y->parent_->left_  = x;

    else
        y->parent_->right_ = x;

    x->right_  = y;

    y->parent_ = x;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
int RBTree<KeyT>::InsertKey(int key)
{
    Node<KeyT>* inserting_node = new Node(key);

    if (inserting_node == nullptr)
    {
        std::cerr << "Failed allocation memory for node with key " << key << " in function " << __PRETTY_FUNCTION__ << std::endl;
        return Config::BadAlloc;
    }

    InsertNode(inserting_node);

    return Config::NoErr;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::InsertNode(Node<KeyT>* inserting_node)
{
    Node<KeyT>* x = root_;

    Node<KeyT>* y = nullptr;

    while (x != nullptr)
    {
        y = x;

        if (inserting_node->key_ < x->key_)
            x = x->left_;

        else if (inserting_node->key_ > x->key_)
            x = x->right_;

        inserting_node->parent_ = y;
    }

    if (y == nullptr)
        root_ = inserting_node;

    else if (inserting_node->key_ < y->key_)
        y->left_    = inserting_node;

    else if (inserting_node->key_ > y->key_)
        y->right_   = inserting_node;

    inserting_node->color_ = Red;

    size_++;

    InsertFixUp(inserting_node);
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::InsertFixUp(Node<KeyT>* node)
{
    while (node != root_ && node->parent_->color_ == Red)
    {
        if (node->parent_ == node->parent_->parent_->left_)
        {
            Node<KeyT>* y = node->parent_->parent_->right_;

            if (y && y->color_ == Red)
            {
                node->parent_->color_ = Black;

                y->color_ = Black;

                node->parent_->parent_->color_ = Red;

                node = node->parent_->parent_;
            }

            else
            {
                if (node == node->parent_->right_)
                {
                    node = node->parent_;

                    LeftRotate(node);
                }

                node->parent_->color_ = Black;

                node->parent_->parent_->color_ = Red;

                RightRotate(node->parent_->parent_);

                break;
            }
        }

        else
        {
            Node<KeyT>* y = node->parent_->parent_->left_;

            if (y && y->color_ == Red)
            {
                node->parent_->color_ = Black;

                y->color_ = Black;

                node->parent_->parent_->color_ = Red;

                node = node->parent_->parent_;
            }

            else
            {
                if (node == node->parent_->left_)
                {
                    node = node->parent_;

                    RightRotate(node);
                }

                node->parent_->color_ = Black;

                node->parent_->parent_->color_ = Red;

                LeftRotate(node->parent_->parent_);

                break;
            }
        }
    }

    root_->color_ = Black;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
RBTree<KeyT>::~RBTree()
{
    CleanTree(root_);

    size_ = 0;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::CleanTree(Node<KeyT>* node)
{
    if (!node)
        return;

    CleanTree(node->left_);

    CleanTree(node->right_);

    delete node;

    node = nullptr;

    size_ = 0;
}

//-------------------------------------------------------------------------------//

#endif