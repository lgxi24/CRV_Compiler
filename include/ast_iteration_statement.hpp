#ifndef AST_ITERATION_STATEMENT
#define AST_ITERATION_STATEMENT

#include "ast_node.hpp"
#include <string>

class IterationStatement : public Node
{
private:
protected:
    Node* first_expression;
    Node* second_expression;
    Node* third_expression;
    Node* iteration_body;
public:
    IterationStatement(Node* _first_expression, Node* _second_expression, Node* _third_expression, Node* _iteration_body)
        : first_expression(_first_expression), second_expression(_second_expression), third_expression(_third_expression), iteration_body(_iteration_body) {}
    virtual ~IterationStatement();

    virtual const std::string getOpcode() const = 0;
    virtual void Print(std::ostream &stream) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override; // helper
    virtual int getSize(Context &context) const override;

};

class WhileStatement : public IterationStatement
{
private:
protected:
    virtual const std::string getOpcode() const override { return "while"; }
public:
    WhileStatement(Node* _first_expression, Node* _iteration_body)
        : IterationStatement(_first_expression, nullptr, nullptr, _iteration_body) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
};

class DoWhileStatement : public IterationStatement
{
private:
protected:
    virtual const std::string getOpcode() const override { return "do-while"; }
public:
    DoWhileStatement(Node* _iteration_body, Node* _first_expression)
        : IterationStatement(_first_expression, nullptr, nullptr, _iteration_body) {};
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
};

class ForStatement : public IterationStatement
{
private:
protected:
    virtual const std::string getOpcode() const override { return "for"; }
public:
    ForStatement(Node* _first_expression, Node* _second_expression, Node* _third_expression, Node* _iteration_body)
        : IterationStatement(_first_expression, _second_expression, _third_expression, _iteration_body) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
};


#endif
