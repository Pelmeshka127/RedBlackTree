#ifndef RBTREE_HPP_
#define RBTREE_HPP_

#include <iostream>

#include "node.hpp"

namespace SearchTree
{

//-------------------------------------------------------------------------------//
//---------------------------Start Red Black Tree Class--------------------------//

template<typename KeyT>
class RBTree
{
    using node_type = Node<KeyT>;

    private:
        size_t size_ = 0;

        node_type *root_  = nullptr;

    public:
        
        RBTree() {};                            // constructor

        RBTree(const RBTree& rhs);              // copy constructor

        RBTree(RBTree&& rhs);                   // move constructor

        RBTree& operator=(const RBTree& rhs);   // copy assignment

        RBTree& operator=(RBTree&& rhs);        // move assignment

        ~RBTree();                              // destructor

        size_t Size() const;

        node_type*  Root() const;

        int InsertKey(KeyT key);

        int DeleteKey(KeyT key);

        node_type* TreeSearch(KeyT key, node_type* root) const;

    private:

        Node<KeyT>* TreeMinimum(node_type* node) const;

        Node<KeyT>* TreeMaximum(node_type* node) const;

        Node<KeyT>* LowerBound(const KeyT& key) const;

        Node<KeyT>* UpperBound(const KeyT& key) const;

        void LeftRotate(node_type* rotated_node);

        void RightRotate(node_type* rotated_node);

        void InsertNode(node_type* node);

        void InsertFixUp(node_type* node);

        void Transplant(node_type* u, node_type* v);
        
        void DeleteNode(node_type* node);

        void DeleteFixUp(node_type* node, node_type* parent);

        void CleanTree(node_type* node);
};

//-----------------------------End Red Black Tree Class--------------------------//
//-------------------------------------------------------------------------------//
//-------------------------------Start Rule Of Five------------------------------//

template<typename KeyT>
RBTree<KeyT>::RBTree(const RBTree<KeyT>& rhs) // copy constructor
{
    std::cout << "copy constructor" << std::endl;

    if (rhs.root_ == nullptr)
    {
        root_ = nullptr;
        return;
    }

    root_ = new Node<KeyT>;

    if (root_ == nullptr)
    {
        std::cerr << "Failed allocation memory for root_ in " << __PRETTY_FUNCTION__<< std::endl;
        return;
    }

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

template<typename KeyT>
RBTree<KeyT>::RBTree(RBTree<KeyT>&& rhs) // move constructor
{
    std::cout << "move constructor" << std::endl;

    std::swap(root_, rhs.root_);

    std::swap(size_, rhs.size_);

    rhs.root_ = nullptr;

    rhs.size_ = 0;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
RBTree<KeyT>& RBTree<KeyT>::operator=(const RBTree& rhs) // copy assignment
{
    std::cout << "copy assignment" << std::endl;

    if (this == &rhs)
        return *this;

    RBTree tmp{rhs};

    *this = std::move(tmp);

    return *this;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
RBTree<KeyT>& RBTree<KeyT>::operator=(RBTree&& rhs) // move assignment
{
    std::cout << "move assignment" << std::endl;

    if (this == &rhs)
        return *this;

    std::swap(root_, rhs.root_);

    std::swap(size_, rhs.size_);

    return *this;
}

//--------------------------------End Rule Of Five-------------------------------//
//-------------------------------------------------------------------------------//
//--------------------------------Start Selectors--------------------------------//

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

//-------------------------------End Selectors-----------------------------------//
//-------------------------------------------------------------------------------//
//------------------------------Start Bounds-------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::LowerBound(const KeyT& key) const
{
    Node<KeyT> *node = nullptr, *curr = root_;

    while (curr != nullptr)
    {
        if (key < curr->key_)
        {
            node = curr;

            curr = curr->left_;
        }

        else
            curr = curr->right_;
    }

    return node;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::UpperBound(const KeyT& key) const
{
    Node<KeyT> *node = nullptr, *curr = nullptr;

    while (curr != nullptr)
    {
        if (key > curr->key)
        {
            node = curr;

            curr = curr->right_;
        }

        else
            curr = curr->left_;
    }

    return node;
}


//--------------------------------End Bounds-------------------------------------//
//-------------------------------------------------------------------------------//
//-----------------------------Start Tree Functions------------------------------//

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

    while(x && x->left_)
        x = x->left_;

    return x;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
Node<KeyT>* RBTree<KeyT>::TreeMaximum(Node<KeyT>* node) const
{
    Node<KeyT>* x = node;

    while(x && x->right_)
        x = x->right_;

    return x;
}

//-----------------------End Tree Functions--------------------------------------//
//-------------------------------------------------------------------------------//
//----------------------Start Rotates and Transplant-----------------------------//

template<typename KeyT>
void RBTree<KeyT>::LeftRotate(Node<KeyT>* x)
{
    if (x == nullptr || x->right_ == nullptr)
        return;

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
    if (y == nullptr || y->left_ == nullptr)
        return;

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

//------------------------End Rotates and Transplant-----------------------------//
//-------------------------------------------------------------------------------//
//-------------------------Start Inserting and Deleting--------------------------//

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
void RBTree<KeyT>::DeleteNode(Node<KeyT>*node)
{
    Node<KeyT> *child = nullptr, *parent = nullptr;

    Color orig_color = Black;

    if (node->left_ && node->right_)    
	{
        Node<KeyT>* replace_node = TreeMinimum(node->right_);

        if (node->parent_)
        {
            if (node->parent_->left_ == node)
                node->parent_->left_ = replace_node;

            else
                node->parent_->right_  = replace_node;
        }

        else
            root_ = replace_node;

        child       = replace_node->right_;

        parent      = replace_node->parent_;

        orig_color  = replace_node->color_;

        if (parent == node)
            parent = replace_node;

        else
        {
            if (child)
                child->parent_ = parent;

            parent->left_         = child;

            replace_node->right_  = node->right_;

            node->right_->parent_ = replace_node;
        }

        replace_node->parent_   = node->parent_;

        replace_node->color_    = node->color_;

        replace_node->left_     = node->left_;

        node->left_->parent_    = replace_node;

        if (orig_color == Black)
            DeleteFixUp(child, parent);

        delete node;

        size_--;

        return;
    }

    if (node->left_)
        child = node->left_;
    
    else
        child = node->right_;

    parent = node->parent_;

    orig_color = node->color_;

    if (child)
        child->parent_ = parent;

    if (parent)
    {
        if (node == parent->left_)
            parent->left_  = child;

        else if (node == parent->right_)
            parent->right_ = child;
    }

    else
        root_ = child;

    if (orig_color == Black)
        DeleteFixUp(child, parent);

    delete node;

    size_--;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void RBTree<KeyT>::DeleteFixUp(Node<KeyT>* node, Node<KeyT>* parent)
{
    Node<KeyT>* brother = nullptr;

    while ((!node) || node->color_ == Black && node != root_)
    {
        if (parent->left_ == node)
        {
            brother = parent->right_;

            if (brother->color_ == Red)
            {
                brother->color_ = Black;

                parent->color_ = Red;

                LeftRotate(parent);

                brother = parent->right_;
            }

            if ((brother->left_ == nullptr || brother->left_->color_ == Black) && (brother->right_ == nullptr || brother->right_->color_ == Black))
            {
                brother->color_ = Red;

                node    = parent;

                parent  = node->parent_;
            }

            else
            {
                if (brother->right_ == nullptr || brother->right_->color_ == Black)
                {
                    brother->left_->color_ = Black;

                    brother->color_        = Red;

                    RightRotate(brother);

                    brother = parent->right_;
                }

                brother->color_         = parent->color_;

                parent->color_          = Black;

                brother->right_->color_ = Black;

                LeftRotate(parent);

                node = root_;

                break;
            }
        }

        else
        {
            brother = parent->left_;

            if (brother->color_ == Red)
            {
                brother->color_ = Black;

                parent->color_  = Black;

                RightRotate(parent);

                brother = parent->left_;
            }

            if ((brother->left_ == nullptr || brother->left_->color_ == Black) && (brother->right_ == nullptr || brother->right_->color_ == Black))
            {
                brother->color_ = Red;

                node    = parent;

                parent  = node->parent_;
            }

            else
            {
                if (brother->left_ == nullptr || brother->left_->color_ == Black)
                {
                    brother->right_->color_ = Black;

                    brother->color_ = Red;

                    LeftRotate(brother);

                    brother = parent->left_;
                }

                brother->color_ = parent->color_;

                parent->color_ = Black;

                brother->left_->color_ = Black;

                RightRotate(parent);

                node = root_;

                break;
            }
        }
    }

    if (node)
        node->color_ = Black;
}

//---------------------------End Inserting and Deleting--------------------------//
//-------------------------------------------------------------------------------//
//---------------------------------Start Dtor------------------------------------//

template<typename KeyT>
RBTree<KeyT>::~RBTree()
{
    std::cout << "Destructor" << std::endl;

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

//---------------------------------End Dtor--------------------------------------//
//-------------------------------------------------------------------------------//

} // end of SearchTree namespace

#endif