#ifndef AST_FUNCTION_DEFINITION_HPP
#define AST_FUNCTION_DEFINITION_HPP

#include "ast_node.hpp"

class FunctionDefinition : public Node
{
private:
    Node *declaration_specifiers_;
    Node *declarator_;
    Node *compound_statement_;

public:
    FunctionDefinition(Node *declaration_specifiers, Node *declarator, Node *compound_statement) : declaration_specifiers_(declaration_specifiers), declarator_(declarator), compound_statement_(compound_statement){};
    ~FunctionDefinition()
    {
        if(declaration_specifiers_ != nullptr){
            delete declaration_specifiers_;
        }
        if(declarator_ != nullptr){
            delete declarator_;
        }
        if(compound_statement_ != nullptr){
            delete compound_statement_;
        }

    };
    void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    void Print(std::ostream &stream) const override;
    int getSize(Context &context) const override{
        std::cerr<<"Error: trying to get Size of function while declaring";
        exit(1);
    }
    std::string getIdentifier() const override{
        return declarator_->getIdentifier();
    }
};


class FunctionDeclarator : public Node
{
private:
protected:
public:
    Node* declarator;
    NodeList* list;

    FunctionDeclarator(Node* _declarator, NodeList* _list)
        :declarator(_declarator),
        list(_list)
    {}
    ~FunctionDeclarator(){
        if(declarator != nullptr){
            delete declarator;
        }
        if(list != nullptr){
            delete list;
        }
    }
    virtual void Print(std::ostream &stream)const override;
    virtual int getSize(Context &context)const override;
    virtual std::string getIdentifier()const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;

};


#endif
