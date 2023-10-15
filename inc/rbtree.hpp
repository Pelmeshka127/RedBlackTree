#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>

#include "node.hpp"

namespace SearchTree
{

//-------------------------------------------------------------------------------//

template<typename KeyT>
class RBTree
{
    using node_type = Node<KeyT>;

    private:
        size_t size_ = 0;

        node_type *root_  = nullptr;

    public:
        RBTree() {};

        // RBTree(int key);

        ~RBTree();

        size_t Size() const;

        node_type*  Root() const;

        int InsertKey(KeyT key);

        int DeleteKey(KeyT key);

        node_type* TreeSearch(KeyT key, node_type* root) const;

    private:
        Node<KeyT>* TreeMinimum(node_type* node) const;

        Node<KeyT>* TreeMaximum(node_type* node) const;

        void LeftRotate(node_type* rotated_node);

        void RightRotate(node_type* rotated_node);

        void InsertNode(node_type* node);

        void InsertFixUp(node_type* node);

        void Transplant(node_type* u, node_type* v);
        
        void DeleteNode(node_type* node);

        void DeleteFixUp(node_type* node);

        void CleanTree(node_type* node);

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
Node<KeyT>* RBTree<KeyT>::TreeSearch(KeyT key, Node<KeyT>* root) const
{
    if (!(root) || root->key_ == key)
        return root;

    if (key < root->key_)
        return TreeSearch(key, root->left_);

    if (key > root->key_)
        return TreeSearch(key, root->right_);

    return nullptr;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::TreeMinimum(Node<KeyT>* node) const
{
    Node<KeyT>* x = node;

    while(x)
        x = x->left_;

    return x;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::TreeMaximum(Node<KeyT>* node) const
{
    Node<KeyT>* x = node;

    while(x)
        x = x->right_;

    return x;
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
int RBTree<KeyT>::InsertKey(KeyT key)
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
int RBTree<KeyT>::DeleteKey(KeyT key)
{
    Node<KeyT>* erasing_node = TreeSearch(key, root_);

    if (erasing_node)
        DeleteNode(erasing_node);

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
void RBTree<KeyT>::DeleteNode(Node<KeyT>* erasing_node)
{
    Node<KeyT>* node = erasing_node;

    Node<KeyT>* x = nullptr;

    Color orig_color = node->color_;

    // std::cout << "Ok" << std::endl;

    if (erasing_node->left_ == nullptr && erasing_node->right_)
    {
        x = erasing_node->right_;

        Transplant(erasing_node, x);

        // std::cout << "Ok" << std::endl;
    }

    else if (erasing_node->right_ == nullptr && erasing_node->left_)
    {
        x = erasing_node->left_;

        Transplant(erasing_node, x);

        // std::cout << "Ok" << std::endl;
    }

    else if (erasing_node->left_ && erasing_node->right_)
    {
        std::cout << "Ok" << std::endl;
        node = TreeMinimum(erasing_node->right_);

        orig_color = node->color_;

        x = node->right_;

        if (node->parent_ == erasing_node)
            x->parent_ = erasing_node;

        else
        {
            Transplant(node, node->right_);

            node->right_ = erasing_node->right_;

            node->right_->parent_ = node;
        }

        Transplant(erasing_node, node); 

        node->left_ = erasing_node->left_;

        node->left_->parent_ = node;

        node->color_ = erasing_node->color_;
    }

    else
    {
        if (erasing_node == erasing_node->parent_->left_)
            erasing_node->parent_->left_ = nullptr;
        
        else
            erasing_node->parent_->right_ = nullptr;
    }

    // std::cout << "Ok" << std::endl;

    if (orig_color == Color::Black)
    {
        // std::cout << "Ok" << std::endl;
        DeleteFixUp(x);
    }

    // DeleteFixUp(x);

    delete erasing_node;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::DeleteFixUp(Node<KeyT>* node)
{
    while ((!node) || node != root_ && node->color_ == Black)
    {
        if (node == node->parent_->left_)
        {
            Node<KeyT>* brother = node->parent_->right_;

            if (brother->color_ == Red)
            {
                brother->color_ = Black;

                node->parent_->color_ = Red;

                LeftRotate(node->parent_);

                brother = node->parent_->right_;
            }

            if (brother->left_->color_ == Black && brother->right_->color_ == Black)
            {
                brother->color_ = Red;

                node = node->parent_;
            }

            else
            {
                if (brother->right_->color_ == Black)
                {
                    brother->left_->color_ = Black;

                    brother->color_ = Red;

                    RightRotate(brother);

                    brother = node->parent_->right_;
                } 

                brother->color_ = node->parent_->color_;

                node->parent_->color_ = Black;

                brother->right_->color_ = Black;

                LeftRotate(node->parent_);

                node = root_;

                break;
            }
        }

        else
        {
            Node<KeyT>* brother = node->parent_->left_;

            if (brother->color_ == Red)
            {
                brother->color_ = Black;

                node->parent_->color_ = Red;

                RightRotate(node->parent_);

                brother = node->left_->parent_;
            }

            if (brother->left_->color_ == Black && brother->right_->color_ == Black)
            {
                brother->color_ = Red;

                node = node->parent_;
            }

            else
            {
                if (brother->left_->color_ == Black)
                {
                    brother->right_->color_ = Black;

                    brother->color_ = Red;

                    LeftRotate(brother);

                    brother = node->parent_->left_;
                }

                brother->color_ = node->parent_->color_;

                node->parent_->color_ = Black;

                brother->left_->color_ = Black;

                RightRotate(node->parent_);

                node = root_;

                break;
            }
        }
    }

    if (node)
        node->color_ = Black;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::Transplant(Node<KeyT>* old_node, Node<KeyT>* new_node)
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

template<typename KeyT>
RBTree<KeyT>::~RBTree()
{
    CleanTree(root_);
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
}

//-------------------------------------------------------------------------------//

} // end of SearchTree namespace

#endif