#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

#include <fstream>

#include "rbtree.hpp"

// #define TREE_DUMP

namespace SearchTree
{

#ifdef TREE_DUMP

//-------------------------------------------------------------------------------//

template<typename KeyT>
int TreeDump(RBTree<KeyT>* const tree);

//-------------------------------------------------------------------------------//

template<typename KeyT>
void TreeDraw(Node<KeyT>* const node);

//-------------------------------------------------------------------------------//

static std::ofstream graph_file;

// static FILE* graph_file = nullptr;

static int graph_num = 1;

//-------------------------------------------------------------------------------//

template<typename KeyT>
int TreeDump(RBTree<KeyT>* const tree)
{
    graph_file.open("../../../graphics/graph.dot");

    graph_file << "digraph Tree\n{\n";
    
    graph_file << "   rankdir = HR;\n";
    
    graph_file << "   node[fontsize=14];\n   edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n";
    
    graph_file << "   tree[shape = Mrecord, style = filled, fillcolor = \"chartreuse1\", "
                        "label = \"My Tree | size = " << tree->Size() << "\"];\n";

    TreeDraw(tree->Root());
    
    graph_file << "   tree -> \"" << tree->Root() << "\" [color = \"gray0\"];\n";
    
    graph_file << "}";

    graph_file.close();

    char call_graph[100] = " ";

    sprintf(call_graph, "dot ../../../graphics/graph.dot -Tpng -o ../../../graphics/graph%d.png", graph_num++);
    
    system(call_graph);

    return 0;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void TreeDraw(Node<KeyT>* const node)
{
    if (node->color_ == Black)
    {
        graph_file << "   \"" << node << "\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\",";
        
        graph_file << "   label = \" key = " << node->key_ << " | size = " << node->subtree_size_ << "\"];\n";
    }

    else if (node->color_ == Red)
    {
        graph_file << "   \"" << node << "\"[shape = Mrecord, color = \"black\", style = filled, fontcolor = \"black\", fillcolor = \"firebrick2\",";
        
        graph_file << "   label = \" key = " << node->key_ << " | size = " << node->subtree_size_ << "\"];\n";
    }

    if (node->left_ != nullptr)
    {
        graph_file << "  \"" << node << "\" -> \"" << node->left_ << "\" [color = \"green\"];\n";
        
        graph_file << "  \"" << node->left_ << "\" -> \"" << node->left_->parent_ << "\" [color = \"red\"];\n";
    }

    else if (node->left_ == nullptr)
    {
        graph_file << "   \"" << node << "left\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\"," <<
                            "   label = \" <value> nill\"];\n";
        graph_file << "  \"" << node << "\" -> \"" << node << "left\" [color = \"green\"];\n";
    }

    if (node->right_ != nullptr)
    {
        graph_file << "  \"" << node << "\" -> \"" << node->right_ << "\" [color = \"green\"];\n";
        
        graph_file << "  \"" << node->right_ << "\" -> \"" << node->right_->parent_ << "\" [color = \"red\"];\n";
    }

    else if (node->right_ == nullptr)
    {
        graph_file << "   \"" << node << "right\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\"," <<
                            "   label = \" <value> nill\"];\n";
        graph_file << "  \"" << node << "\" -> \"" << node << "right\" [color = \"green\"];\n";
    }

    if (node->left_ != nullptr)
        TreeDraw(node->left_);

    if (node->right_ != nullptr)
        TreeDraw(node->right_);
}

//-------------------------------------------------------------------------------//

#endif

} // end of SeacrhTree namespace

#endif