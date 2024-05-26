#ifndef AST_SWITCH
#define AST_SWITCH

#include "ast_node.hpp"
#include <string>

class SwitchCase : public Node
{
private:
protected:
    Node* expression;
    Node* statement;
public:
    SwitchCase(Node* _expression, Node* _statement) : expression(_expression), statement(_statement) {}
    virtual ~SwitchCase();

    virtual const std::string getOpcode() const = 0;
    virtual void Print(std::ostream &stream) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
    virtual std::string getIdentifier() const override;
};

class SwitchStatement : public SwitchCase
{
private:
protected:
    virtual const std::string getOpcode() const override { return "switch"; }
public:
    SwitchStatement(Node* _expression, Node* _statement) : SwitchCase(_expression, _statement) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
};

class CaseStatement : public SwitchCase
{
private:
protected:
    virtual const std::string getOpcode() const override { return "case"; }
public:
    CaseStatement(Node* _expression, Node* _statement) : SwitchCase(_expression, _statement) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
};

class CaseBreakStatement : public SwitchCase
{
private:
protected:
    virtual const std::string getOpcode() const override { return "case with break"; }
public:
    CaseBreakStatement(Node* _expression, Node* _statement) : SwitchCase(_expression, _statement) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
};

#endif
