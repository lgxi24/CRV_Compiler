#ifndef AST_TYPE_SPECIFIER
#define AST_TYPE_SPECIFIER

#include "ast_node.hpp"
#include <cmath>
#include <string>


class TypeSpecifier : public Node
{
private:
    std::string type;

public:
    TypeSpecifier(std::string type) : type(type){};
    ~TypeSpecifier(){};

    virtual void EmitRISC(std::ostream &stream, Context &context,int destRegister) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual int getSize(Context &context) const override;
    virtual std::string getIdentifier()const override{
        std::cerr<<"typespecifier id:"<<std::endl;
        return type;
    }
};

#endif
