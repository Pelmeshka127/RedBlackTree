#ifndef NODE_HPP_
#define NODE_HPP_

#include <iostream>

#include "config.hpp"

//-------------------------------------------------------------------------------//

enum Color 
{
    Red,
    Black,
};

//-------------------------------------------------------------------------------//

class Node 
{
    public: 
        int     key_;
        Color   color_;
        Node    *left_   = nullptr;
        Node    *right_  = nullptr;
        Node    *parent_ = nullptr;

    Node(const int& key = 0, const Color& color = Black, Node* left = nullptr,
         Node* right = nullptr,  Node* parent = nullptr) : 
         key_{key}, color_{color}, left_{left}, right_{right}, parent_{parent} {}

    // int Key() const;

    // Color NodeColor() const;

    ~Node() {}
};

//-------------------------------------------------------------------------------//

#endif