#ifndef AST_SELECTION_STATEMENT
#define AST_SELECTION_STATEMENT

#include "ast_node.hpp"
#include <string>

class SelectionStatement : public Node
{
private:
protected:
    Node* condition;
    Node* ifStatement;
    Node* elseStatement;

public:
    SelectionStatement(Node* _condition, Node* _ifStatement, Node* _elseStatement)
        : condition(_condition), ifStatement(_ifStatement), elseStatement(_elseStatement) {}
    virtual ~SelectionStatement();

    virtual const std::string getOpcode() const = 0;
    virtual void Print(std::ostream &stream) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override; 
    virtual int getSize(Context &context) const override;

};

class IfStatement : public SelectionStatement
{
private:
protected:
    virtual const std::string getOpcode() const override { return "if"; }
public:
    IfStatement(Node* _condition, Node* _ifStatement)
        : SelectionStatement(_condition, _ifStatement, nullptr) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
};

class IfElseStatement : public SelectionStatement
{
private:
protected:
    virtual const std::string getOpcode() const override { return "if else"; }
public:
    IfElseStatement(Node* _condition, Node* _ifStatement, Node* _elseStatement)
        : SelectionStatement(_condition, _ifStatement, _elseStatement) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
};

#endif
