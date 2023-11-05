#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

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

static FILE* graph_file = nullptr;

static int graph_num = 1;

//-------------------------------------------------------------------------------//

template<typename KeyT>
int TreeDump(RBTree<KeyT>* const tree)
{
    graph_file = fopen("../../graphics/graph.dot", "w");
    if (graph_file == nullptr)
    {
        std::cerr << "Failed openning graph file in " << __PRETTY_FUNCTION__ << std::endl;
        return Config::FileError; 
    }

    fprintf(graph_file, "digraph Tree\n{\n");
    fprintf(graph_file, "   rankdir = HR;\n");
    fprintf(graph_file, "   node[fontsize=14];\n   edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n");
    fprintf(graph_file, "   tree[shape = Mrecord, style = filled, fillcolor = \"chartreuse1\", "
                        "label = \"My Tree | size = %zu\"];\n", tree->Size());
    TreeDraw(tree->Root());
    fprintf(graph_file, "   tree -> \"%p\" [color = \"gray0\"];\n", tree->Root());
    fprintf(graph_file, "}");

    if (fclose(graph_file) == EOF)
    {
        std::cerr << "Failed closing graph.dot in function " << __PRETTY_FUNCTION__ << std::endl;
        return Config::FileError;
    }

    char call_graph[100] = " ";

    // system("cd ../../");

    sprintf(call_graph, "dot ../../graphics/graph.dot -Tpng -o ../../graphics/graph%d.png", graph_num++);
    
    system(call_graph);

    return Config::NoErr;
}

//-------------------------------------------------------------------------------//

template<typename KeyT>
void TreeDraw(Node<KeyT>* const node)
{
    if (node->color_ == Black)
    {
        fprintf(graph_file, "   \"%p\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" key = %d | size = %zu\"];\n", node, node->key_, node->subtree_size_);
    }

    else if (node->color_ == Red)
    {
        fprintf(graph_file, "  \"%p\"[shape = Mrecord, color = \"black\", style = filled, fillcolor = \"firebrick2\","
                            "   label = \" key = %d | size = %zu\"];\n", node, node->key_, node->subtree_size_);
    }

    if (node->left_ != nullptr)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->left_);
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->left_, node->left_->parent_);
    }

    else if (node->left_ == nullptr)
    {
        fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" <value> %s\"];\n", node, "left", "nill");
        fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "left");
    }

    if (node->right_ != nullptr)
    {
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->right_);
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node->right_, node->right_->parent_);
    }

    else if (node->right_ == nullptr)
    {
        fprintf(graph_file, "   \"%p%s\"[shape = Mrecord, color = \"red\", style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" <value> %s\"];\n", node, "right", "nill");
        fprintf(graph_file, "  \"%p\" -> \"%p%s\" [color = \"green\"];\n", node, node, "right");
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