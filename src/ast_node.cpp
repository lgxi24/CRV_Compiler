#include "ast_node.hpp"

Node::~Node()
{
    for (auto branch : branches_)
    {
        delete branch;
    }
}


void NodeList::PushBack(Node *item)
{

    std::cerr<<"nodelist"<<std::endl;
    nodes_.push_back(item);
}

void NodeList::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        std::cerr<<"nodelist"<<std::endl;
        node->EmitRISC(stream, context,destRegister);
    }
}

void NodeList::Print(std::ostream &stream) const
{
    for (auto node : nodes_)
    {
        if (node == nullptr)
        {
            continue;
        }
        node->Print(stream);
    }
}
