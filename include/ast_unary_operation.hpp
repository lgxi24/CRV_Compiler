#ifndef AST_UNARY_OPERATION
#define AST_UNARY_OPERATION

#include "ast_node.hpp"
#include <cmath>
#include <string>

class UnaryOperation : public Node
{
private:
protected:
    Node* expression;
public:
    UnaryOperation(Node* _expression) : expression(_expression) {}
    virtual ~UnaryOperation();

    virtual const std::string getOpcode() const = 0;
    virtual void Print(std::ostream &stream) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getSize(Context &context) const override;
    virtual std::string getIdentifier() const override;
};

class negOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "neg"; }
public:
    negOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getValue(Context &context)  override;
};

class notOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "not"; }
public:
    notOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getValue(Context &context) override;
};

class bitwiseNotOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "bit wise not"; }
public:
    bitwiseNotOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getValue(Context &context) override;
};

class preincOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "preinc"; }
public:
    preincOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    bool isPointer(Context &context)override{
        return expression->isPointer(context);
    }
};

class predecOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "predec"; }
public:
    predecOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    bool isPointer(Context &context)override{
        return expression->isPointer(context);
    }
};

class postincOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "postinc"; }
public:
    postincOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    bool isPointer(Context &context)override{
        return expression->isPointer(context);
    }
};

class postdecOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "postdec"; }
public:
    postdecOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    bool isPointer(Context &context)override{
        return expression->isPointer(context);
    }
};

class sizeofOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "sizeof"; }
public:
    sizeofOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getValue(Context &context) override;
    virtual std::string getIdentifier() const override;
};

class sizeofTypeOperator : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "sizeof"; }
public:
    sizeofTypeOperator(Node* _expression) : UnaryOperation(_expression) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual int getValue(Context &context) override;
};

//pointer
class addressOperator
    : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "&"; }
public:
    addressOperator(Node* _expression)
        :UnaryOperation(_expression)
    {}

    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister)const override;
    bool isPointer(Context &context)override{
        return true;
    }
};

class dereferenceOperator
    : public UnaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "*"; }
public:
    dereferenceOperator(Node* _expression)
        :UnaryOperation(_expression)
    {}

    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister)const override;
    virtual void leftCompile(std::ostream &stream, Context &context, int destRegister)const override;

};

#endif
