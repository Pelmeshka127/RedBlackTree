#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>
#include <list>
#include <cassert>
#include <stdexcept>

#include "node.hpp"

namespace SearchTree
{

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator = std::less<KeyT>> 
class RBTree
{
    using node_t = Node<KeyT>;

//-------------------------------------------------------------------------------//

private:

//-------------------------------------------------------------------------------//

    size_t size_ = 0;

    node_t* root_  = nullptr;

//-------------------------------------------------------------------------------//

public:

    size_t      Size() const noexcept { return size_; }

    node_t*     Root() const noexcept { return root_; }

//-------------------------------------------------------------------------------//

    RBTree() {};                                // constructor

//-------------------------------------------------------------------------------//

    RBTree(const RBTree& rhs)                   // copy constructor
    {
        if (rhs.root_ == nullptr)
        {
            root_ = nullptr;
            return;
        }

        RBTree tmp;

        tmp.CopyTree(rhs);

        //----------------------//

        *this = std::move(tmp);
    }

//-------------------------------------------------------------------------------//

    RBTree(RBTree&& rhs) noexcept                   // move constructor
    {
        std::swap(root_, rhs.root_);

        std::swap(size_, rhs.size_);

        rhs.root_ = nullptr;

        rhs.size_ = 0;
    }

//-------------------------------------------------------------------------------//

    RBTree& operator=(const RBTree& rhs)            // copy assignment
    {
        if (this == &rhs)
            return *this;

        RBTree tmp{rhs};

        //----------------------//

        *this = std::move(tmp);

        return *this;
    }

//-------------------------------------------------------------------------------//

    RBTree& operator=(RBTree&& rhs) noexcept        // move assignment
    {
        if (this == &rhs)
            return *this;

        std::swap(root_, rhs.root_);

        std::swap(size_, rhs.size_);

        return *this;
    }

//-------------------------------------------------------------------------------//

    ~RBTree()                                       // destructor
    {
        CleanTree();
    }                                    


//-------------------------------------------------------------------------------//

private:

    void            CopyTree(const RBTree<KeyT, Comparator>& rhs);

    void            CopyData(node_t* dst, node_t* src, const Part& part) noexcept;

    void            LeftRotate(node_t* x)  noexcept;

    void            RightRotate(node_t* y) noexcept;

    size_t          GetSubSizeRotate(const node_t* x, const node_t* y, const Part part) const noexcept;

    void            ResizeNode(const node_t* inserting_node) const noexcept;
        
    void            InsertFixUp(node_t* node);

    node_t*         SeparateFixUp(node_t* node, const Part part);

    void            ReColor(node_t* node, node_t* uncle);

    void            CleanTree();

public:

    node_t*         TreeSearch(KeyT key) const;

    void            Insert(KeyT key);

    size_t          Distance(const KeyT first, const KeyT second) const;

    size_t          LessThan(const KeyT number) const;

    KeyT            MinimumElement(const int index) const;

//-------------------------------------------------------------------------------//

}; // end of RBTree class

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::CopyTree(const RBTree<KeyT, Comparator>& rhs)
{
    root_ = new (std::nothrow) node_t(rhs.root_->key_);

    if (!root_)
    {
        std::cerr << "Failed allocation memory for copy root in " << __PRETTY_FUNCTION__ << std::endl;

        throw std::bad_alloc();
    }

    root_->subtree_size_ = rhs.root_->subtree_size_;

    size_ = rhs.size_;

    node_t *copy = root_, *other = rhs.root_;

    while (other)
    {
        if (copy->left_ == nullptr && other->left_)
        {
            copy->left_ = new (std::nothrow) node_t;

            if (!copy->left_)
            {
                std::cerr << "Failed allocation memory for copy left in " << __PRETTY_FUNCTION__ << std::endl;

                CleanTree();

                throw std::bad_alloc();
            }

            CopyData(copy, other, Left);
            
            copy  = copy->left_;

            other = other->left_;
        }

        else if (copy->right_ == nullptr && other->right_)
        {
            copy->right_ = new (std::nothrow) node_t;

            if (!copy->right_)
            {
                std::cerr << "Failed allocation memory for copy right in " << __PRETTY_FUNCTION__ << std::endl;

                CleanTree();

                throw std::bad_alloc();
            }

            CopyData(copy, other, Right);

            copy  = copy->right_;

            other = other->right_;
        }

        else
        {
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

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::CopyData(node_t* dst, node_t* src, const Part& part) noexcept
{
    if (part == Left)
    {
        dst->left_->parent_        = dst;

        dst->left_->key_           = src->left_->key_;

        dst->left_->color_         = src->left_->color_;

        dst->left_->subtree_size_  = src->left_->subtree_size_;
    }

    else
    {
        dst->right_->parent_        = dst;

        dst->right_->key_           = src->right_->key_;

        dst->right_->color_         = src->right_->color_;

        dst->right_->subtree_size_  = src->right_->subtree_size_;
    }
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
Node<KeyT>* RBTree<KeyT, Comparator>::TreeSearch(KeyT key) const
{
    node_t* cur = root_;

    while (cur != nullptr)
    {
        if (Comparator()(key, cur->key_))
            cur = cur->left_;

        else if (Comparator()(cur->key_, key))
            cur = cur->right_;

        else
            return cur;
    }

    return nullptr;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::LeftRotate(node_t* x) noexcept
{
    node_t* y = x->right_;

    y->subtree_size_ = x->subtree_size_;

    x->subtree_size_ =  GetSubSizeRotate(x, y, Left);

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
void RBTree<KeyT, Comparator>::RightRotate(node_t* y) noexcept
{
    node_t* x = y->left_;

    x->subtree_size_ = y->subtree_size_;

    y->subtree_size_ = GetSubSizeRotate(y, x, Right);

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
size_t RBTree<KeyT, Comparator>::GetSubSizeRotate(const node_t* x, const node_t* y, const Part part) const noexcept
{
    size_t left_size = 0, right_size = 0;

    switch (part)
    {
        case Left:
        {
            if (y->left_)
                left_size   = y->left_->subtree_size_;

            if (x->left_)
                right_size  = x->left_->subtree_size_;

            break;
        }

        case Right:
        {
            if (y->right_)
                left_size   = y->right_->subtree_size_;

            if (x->right_)
                right_size  = x->right_->subtree_size_;

            break;
        }
    }

    return (left_size + right_size + 1);
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::ResizeNode(const node_t* inserting_node) const noexcept
{
    node_t* curr = inserting_node->parent_;

    while (curr != nullptr)
    {
        curr->subtree_size_++;

        curr = curr->parent_;
    }
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::Insert(KeyT key)
{
    if (TreeSearch(key))
        return;

    node_t* x = root_;

    node_t* y = nullptr;

    while (x != nullptr)
    {
        y = x;

        if (Comparator()(key, x->key_))
            x = x->left_;

        else if (Comparator()(x->key_, key))
            x = x->right_;
    }

    node_t* inserting_node = new (std::nothrow) node_t(key);

    if (!inserting_node)
    {
        std::cerr << "Failed allocation memory for node in " << __PRETTY_FUNCTION__ << std::endl;
        throw std::bad_alloc();
    }

    x = inserting_node;

    inserting_node->parent_ = y;

    if (y == nullptr)
        root_ = inserting_node;

    else if (Comparator()(inserting_node->key_, y->key_))
        y->left_    = inserting_node;

    else if (Comparator()(y->key_, inserting_node->key_))
        y->right_   = inserting_node;

    inserting_node->color_ = Red;

    ResizeNode(inserting_node);

    size_++;

    InsertFixUp(inserting_node);
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::InsertFixUp(node_t* node)
{
    while (node != root_ && node->parent_->color_ == Red)
    {
        if (node->parent_ == node->parent_->parent_->left_)
            node = SeparateFixUp(node, Left);

        else if (node->parent_ == node->parent_->parent_->right_)
            node = SeparateFixUp(node, Right);
    }

    root_->color_ = Black;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
Node<KeyT>* RBTree<KeyT, Comparator>::SeparateFixUp(node_t* node, const Part part)
{
    node_t* grand = node->parent_->parent_;

    node_t* uncle = (part == Left) ? grand->right_ : grand->left_;

    if (uncle && uncle->color_ == Red)
    {
        ReColor(node, uncle);

        return grand;
    }

    node_t* cur_node = (part == Left) ? node->parent_->right_ : node->parent_->left_;

    if (node == cur_node)
    {
        node = node->parent_;

        if (part == Left)
            LeftRotate(node);

        else
            RightRotate(node);
    }

    grand->color_           = Red;

    node->parent_->color_   = Black;

    if (part == Left)
        RightRotate(grand);

    else
        LeftRotate(grand);

    return node;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::ReColor(node_t* node, node_t* uncle)
{
    uncle->color_                   = Black;

    node->parent_->color_           = Black;

    node->parent_->parent_->color_  = Red;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
void RBTree<KeyT, Comparator>::CleanTree()
{
    node_t* curr = root_;

    while (curr != nullptr)
    {
        if (curr->left_)
            curr = curr->left_;

        else if (curr->right_)
            curr = curr->right_;

        else
        {
            if (curr == root_)
                break;
            
            node_t* parent = curr->parent_;

            if (curr == parent->left_)
                parent->left_  = nullptr;

            else if (curr == parent->right_)
                parent->right_ = nullptr;

            delete curr;

            curr = parent;
        }
    }
    
    delete root_;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
size_t RBTree<KeyT, Comparator>::Distance(const KeyT first, const KeyT second) const
{
    if (first >= second)
        return 0;

    size_t result = size_;

    node_t* curr = root_;

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

template<typename KeyT, typename Comparator>
size_t RBTree<KeyT, Comparator>::LessThan(const KeyT number) const
{
    size_t count{};

    node_t* curr = root_;

    while (curr != nullptr)
    {
        if (Comparator()(number, curr->key_))
            curr = curr->left_;

        else if (Comparator()(curr->key_, number))
        {
            if (curr->left_)
                count += (curr->left_->subtree_size_ + 1);

            else
                count += 1;

            curr = curr->right_;
        }

        else
        {
            if (curr->left_)
                count += curr->left_->subtree_size_;
            
            break;
        }
    }

    return count;
}

//-------------------------------------------------------------------------------//

template<typename KeyT, typename Comparator>
KeyT RBTree<KeyT, Comparator>::MinimumElement(const int index) const
{
    if (index <= 0)
    {
        std::cout << "Incorrect index of minimum element: " << index << std::endl;

        return Error::IncorrectIndex;
    }

    node_t* curr = root_;

    if (index == 1)
    {
        while (curr->left_)
            curr = curr->left_;

        return curr->key_;
    }

    else if (index >= size_)
    {
        while (curr->right_)
            curr = curr->right_;

        return curr->key_;
    }

    KeyT elem{};

    int current_index = 1;

    while (curr->left_)
    {
        if ((current_index + curr->left_->subtree_size_) < index)
        {
            current_index += (curr->left_->subtree_size_ + 1);

            curr = curr->right_;
        }

        else if ((current_index + curr->left_->subtree_size_) > index)
            curr = curr->left_;

        else
            return curr->key_;

    }

    return curr->key_;
}

//-------------------------------------------------------------------------------//

} // end of SearchTree namespace

#endif