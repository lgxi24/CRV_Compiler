#ifndef AST_JUMP_STATEMENT_HPP
#define AST_JUMP_STATEMENT_HPP

#include "ast_node.hpp"

class ReturnStatement : public Node
{
private:
protected:
    Node *expression_;
public:
    ReturnStatement(Node * expresion)
    :expression_(expresion)
    {}
    ~ReturnStatement(){
        delete expression_;
    };

    void EmitRISC(std::ostream &stream, Context &context,int destRegister) const override;
    void Print(std::ostream &stream) const override;
    int getSize(Context &context)const override{
        std::cerr<<"return statement size "<<expression_->getSize(context)<<std::endl;
        return expression_->getSize(context);
    }
};

class ContinueStatement
    : public Node
{
private:
protected:
public:
    ContinueStatement(){}
    ~ContinueStatement(){};

    virtual void EmitRISC(std::ostream &stream, Context &context,int destRegister) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual int getSize(Context &context)const override;
};

class BreakStatement
    : public Node
{
private:
protected:
public:
    BreakStatement(){}
    ~BreakStatement(){};

    virtual void EmitRISC(std::ostream &stream, Context &context,int destRegister) const override;
    virtual void Print(std::ostream &stream) const override;
    virtual int getSize(Context &context)const override;
};

#endif
