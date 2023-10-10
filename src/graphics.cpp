#include "../inc/graphics.hpp"

//-------------------------------------------------------------------------------//

// static FILE* log_file   = nullptr;

static FILE* graph_file = nullptr;

static int graph_num = 1;

//-------------------------------------------------------------------------------//

int TreeDump(RBTree* const tree)
{
    assert(tree);

    graph_file = fopen("graphics/graph.dot", "w");
    if (graph_file == nullptr)
    {
        std::cerr << "Failed openning graph file in " << __PRETTY_FUNCTION__ << std::endl;
        return Config::FileError; 
    }

    fprintf(graph_file, "digraph Tree\n{\n");
    fprintf(graph_file, "   rankdir = HR;\n");
    fprintf(graph_file, "   node[fontsize=14];\n   edge[color=\"black\",fontcolor=\"blue\",fontsize=12];\n");
    fprintf(graph_file, "   tree[shape = Mrecord, style = filled, fillcolor = \"aliceblue\", "
                        "label = \"My Tree | size = %zu\"];\n", tree->Size());
    TreeDraw(tree->Root());
    fprintf(graph_file, "   tree -> \"%p\" [color = \"red\"];\n", tree->Root());
    fprintf(graph_file, "}");

    if (fclose(graph_file) == EOF)
    {
        std::cerr << "Failed closing graph.dot in function " << __PRETTY_FUNCTION__ << std::endl;
        return Config::FileError;
    }

    char call_graph[100] = " ";

    sprintf(call_graph, "dot graphics/graph.dot -Tpng -o graphics/graph%d.png", graph_num++);
    
    system(call_graph);

    return Config::NoErr;
}

//-------------------------------------------------------------------------------//

void TreeDraw(Node* const node)
{
    assert(node);

    if (node->color_ == Black)
    {
        fprintf(graph_file, "   \"%p\"[shape = Mrecord, style = filled, fontcolor = \"white\", fillcolor = \"black\","
                            "   label = \" <value> %d\"];\n", node, node->key_);
    }

    else if (node->color_ == Red)
    {
        fprintf(graph_file, "  \"%p\"[shape = Mrecord, style = filled, fillcolor = \"firebrick2\","
                            "   label = \" <value> %d\"];\n", node, node->key_);
    }

    if (node->left_ != nullptr)
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"green\"];\n", node, node->left_);

    if (node->right_ != nullptr)
        fprintf(graph_file, "  \"%p\" -> \"%p\" [color = \"red\"];\n", node, node->right_);

    if (node->left_ != nullptr)
        TreeDraw(node->left_);

    if (node->right_ != nullptr)
        TreeDraw(node->right_);
}

//-------------------------------------------------------------------------------//