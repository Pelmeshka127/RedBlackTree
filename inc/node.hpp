#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>

#include "config.hpp"

namespace SearchTree
{

//-------------------------------------------------------------------------------//

enum Color 
{
    Red,
    Black,
};

//-------------------------------------------------------------------------------//

template<typename KeyT>
class Node 
{
    public: 
        KeyT            key_;
        Color           color_;
        Node<KeyT>      *left_   = nullptr;
        Node<KeyT>      *right_  = nullptr;
        Node<KeyT>      *parent_ = nullptr;

    Node(const KeyT& key = 0, const Color& color = Black, Node<KeyT>* left = nullptr,
         Node<KeyT>* right = nullptr,  Node<KeyT>* parent = nullptr) : 
         key_{key}, color_{color}, left_{left}, right_{right}, parent_{parent} {}

    ~Node() {}
};

//-------------------------------------------------------------------------------//

} // end of SeacrhTree namespace

#endif