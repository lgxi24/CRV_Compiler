#ifndef AST_NODE_HPP
#define AST_NODE_HPP

#include <iostream>
#include <vector>
#include <stdexcept>

#include "ast_context.hpp"

class Node
{
protected:
    std::vector<Node *> branches_;

public:
    Node(){};
    virtual ~Node();
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const = 0;
    virtual void Print(std::ostream &stream) const = 0;
    virtual int getValue(Context &context) {std::cerr<<"unable to get value for the class"<<std::endl; exit(1);}
    virtual int getSize(Context &context) const {exit(1);}
    virtual std::string getIdentifier() const {return "Incorrect";}
    virtual void leftCompile (std::ostream &stream, Context &context, int destRegister) const
    {
        // std::cerr<<"unable to compile array offset for the class"<<std::endl;
        std::cerr<<"leftcompile error"<<std::endl;
        exit(1);
    };
    virtual bool isPointer(Context &context){
        return false;
    }
};

// Represents a list of nodes.
class NodeList : public Node
{
private:
    std::vector<Node*> nodes_;

public:
    NodeList(Node *first_node) : nodes_({first_node}) {}

    ~NodeList()
    {
        for (auto node : nodes_)
        {
            delete node;
        }
    }

    void PushBack(Node *item);
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual void Print(std::ostream &stream) const override;

    std::size_t vecSize() const {
        std::cerr<<"listSize:"<<std::endl;
        std::cerr<<nodes_.size()<<std::endl;
        return nodes_.size();
    }
    Node* at(std::size_t index) const {
        if (index < nodes_.size()) {
            return nodes_[index];
        } else {
            throw std::out_of_range("Index out of range");
        }
    }
};

#endif
