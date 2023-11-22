#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>

#include "node.hpp"

namespace SearchTree
{

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator = std::less<KeyT>> 
class RBTree
{

//-------------------------------------------------------------------------------//

private:

//-------------------------------------------------------------------------------//

    size_t size_ = 0;

    Node<KeyT>* root_  = nullptr;

//-------------------------------------------------------------------------------//

public:

    size_t      Size() const { return size_; }

    Node<KeyT>* Root() const { return root_; }

//-------------------------------------------------------------------------------//

    RBTree() {};                            // constructor

//-------------------------------------------------------------------------------//

    RBTree(const RBTree& rhs)               // copy constructor
    {
        if (rhs.root_ == nullptr)
        {
            root_ = nullptr;
            return;
        }

        root_ = new Node<KeyT>;

        Node<KeyT> *copy = root_, *other = rhs.root_;

        while (other)
        {
            if (copy->left_ == nullptr && other->left_)
            {
                copy->left_ = new Node<KeyT>;

                copy->left_->parent_ = copy;

                copy = copy->left_;

                other = other->left_;
            }

            else if (copy->right_ == nullptr && other->right_)
            {
                copy->right_ = new Node<KeyT>;

                copy->right_->parent_ = copy;

                copy = copy->right_;

                other = other->right_;
            }

            else
            {
                copy->key_ = other->key_;

                copy->color_ = other->color_;

                if (copy != root_)
                {
                    copy = copy->parent_;

                    other = other->parent_;
                }

                else
                    break;
            }
        }
    }

//-------------------------------------------------------------------------------//

    RBTree(RBTree&& rhs)                    // move constructor
    {
        std::swap(root_, rhs.root_);

        std::swap(size_, rhs.size_);

        rhs.root_ = nullptr;

        rhs.size_ = 0;
    }

//-------------------------------------------------------------------------------//

    RBTree& operator=(const RBTree& rhs)    // copy assignment
    {
        if (this == &rhs)
            return *this;

        RBTree tmp{rhs};

        *this = std::move(tmp);

        return *this;
    }

//-------------------------------------------------------------------------------//

    RBTree& operator=(RBTree&& rhs)         // move assignment
    {
        if (this == &rhs)
            return *this;

        std::swap(root_, rhs.root_);

        std::swap(size_, rhs.size_);

        return *this;
    }

//-------------------------------------------------------------------------------//

    ~RBTree()                               // destructor
    {
        CleanTree(root_);
    }

//-------------------------------------------------------------------------------//

private:

    void        LeftRotate(Node<KeyT>* x);

    void        RightRotate(Node<KeyT>* y);
        
    void        InsertFixUp(Node<KeyT>* node);

    void        Transplant(Node<KeyT>* old_node, Node<KeyT>* new_node);

    void        CleanTree(Node<KeyT>* node);

    void        ReColor(Node<KeyT>* node, Node<KeyT>* uncle);

public:

    Node<KeyT>* TreeSearch(KeyT key, Node<KeyT>* root) const;

    void        Insert(KeyT key);

    size_t      Distance(KeyT first, KeyT second) const;

//-------------------------------------------------------------------------------//

}; // end of RBTree class

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator> 
Node<KeyT>* RBTree<KeyT, Comparator>::TreeSearch(KeyT key, Node<KeyT>* root) const
{
    if (!(root) || root->key_ == key)
        return root;

    if (Comparator()(key, root->key_))
        return TreeSearch(key, root->left_);

    if (Comparator()(root->key_, key))
        return TreeSearch(key, root->right_);

    return nullptr;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::LeftRotate(Node<KeyT>* x)
{
    if (x == nullptr || x->right_ == nullptr)
        return;

    Node<KeyT>* y = x->right_;

    y->subtree_size_ = x->subtree_size_;

    size_t left_size = 0, right_size = 0;

    if (y->left_)
        left_size  = y->left_->subtree_size_;

    if (x->left_)
        right_size = x->left_->subtree_size_;

    x->subtree_size_ = left_size + right_size + 1;

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

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::RightRotate(Node<KeyT>* y)
{
    if (y == nullptr || y->left_ == nullptr)
        return;

    Node<KeyT>* x = y->left_;

    x->subtree_size_ = y->subtree_size_;

    size_t left_size = 0, right_size = 0;

    if (x->right_)
        left_size  = x->right_->subtree_size_;

    if (y->right_)
        right_size = y->right_->subtree_size_;

    y->subtree_size_ = left_size + right_size + 1;

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

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::Insert(KeyT key)
{
    if (TreeSearch(key, root_))
        return;

    Node<KeyT>* inserting_node = new Node(key);

    Node<KeyT>* x = root_;

    Node<KeyT>* y = nullptr;

    while (x != nullptr)
    {
        y = x;

        ++y->subtree_size_;

        if (Comparator()(inserting_node->key_, x->key_))
            x = x->left_;

        else if (Comparator()(x->key_, inserting_node->key_))
            x = x->right_;
    }

    inserting_node->parent_ = y;

    if (y == nullptr)
        root_ = inserting_node;

    else if (Comparator()(inserting_node->key_, y->key_))
        y->left_    = inserting_node;

    else if (Comparator()(y->key_, inserting_node->key_))
        y->right_   = inserting_node;

    inserting_node->color_ = Red;

    size_++;

    InsertFixUp(inserting_node);
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::InsertFixUp(Node<KeyT>* node)
{
    while (node != root_ && node->parent_->color_ == Red)
    {
        if (node->parent_ == node->parent_->parent_->left_)
        {
            Node<KeyT>* uncle = node->parent_->parent_->right_;

            if (uncle && uncle->color_ == Red)
                ReColor(node, uncle);

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
            Node<KeyT>* uncle = node->parent_->parent_->left_;

            if (uncle && uncle->color_ == Red)
                ReColor(node, uncle);

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

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::ReColor(Node<KeyT>* node, Node<KeyT>* uncle)
{
    node->parent_->color_ = Black;

    uncle->color_ = Black;

    node->parent_->parent_->color_ = Red;

    node = node->parent_->parent_;  
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::Transplant(Node<KeyT>* old_node, Node<KeyT>* new_node)
{
    if (old_node->parent_ == nullptr)
        root_ = new_node;

    else if (old_node == old_node->parent_->left_)
        old_node->parent_->left_  = new_node;

    else if (old_node == old_node->parent_->right_)
        old_node->parent_->right_ = new_node;

    new_node->parent_ = old_node->parent_;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::CleanTree(Node<KeyT>* node)
{
    if (!node)
        return;

    CleanTree(node->left_);

    CleanTree(node->right_);

    delete node;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
size_t RBTree<KeyT, Comparator>::Distance(KeyT first, KeyT second) const
{
    if (first >= second)
        return 0;

    size_t result = size_;

    Node<KeyT>* curr = root_;

    while (curr != nullptr)
    {
        if (Comparator()(first, curr->key_))
            curr = curr->left_;

        else if (Comparator()(curr->key_, first))
        {
            if (curr->left_)
                result -= (curr->left_->subtree_size_);

            result -= 1;
        
            curr = curr->right_;
        }

        else
        {
            if (curr->left_)
                result -= (curr->left_->subtree_size_);

            break;
        }
    }

    curr = root_;

    while (curr != nullptr)
    {
        if (Comparator()(curr->key_, second))
            curr = curr->right_;

        else if (Comparator()(second, curr->key_))
        {
            if (curr->right_)
                result -= (curr->right_->subtree_size_);

            result -= 1;
            
            curr = curr->left_;
        }

        else
        {
            if (curr->right_)
                result -= curr->right_->subtree_size_;

            break;
        }
    }

    return result;
}

//-------------------------------------------------------------------------------//

} // end of SearchTree namespace

#endif