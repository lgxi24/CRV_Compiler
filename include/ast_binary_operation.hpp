#ifndef AST_BINARY_OPERATION
#define AST_BINARY_OPERATION

#include "ast_node.hpp"
#include <cmath>
#include <string>

class BinaryOperation : public Node
{
private:
protected:
    Node *left;
    Node *right;


public:
    BinaryOperation(Node *_left, Node *_right):left(_left),right(_right){}
    virtual ~BinaryOperation()
    {
        if (left != nullptr) {
            delete left;
        } else {
            std::cerr << "left is nullptr" << std::endl;
        }

        if (right != nullptr) {
            delete right;
        } else {
            std::cerr << "right is nullptr" << std::endl;
        }
    }

    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual const std::string getOpcode() const =0;

    virtual void Print(std::ostream &stream) const override;
    virtual int doLeft(std::ostream &stream, Context &context,int  destRegister)const;
    virtual int doRight(std::ostream &stream, Context &context, int  destRegister)const;
    virtual int getSize(Context &context) const override{
        return 0; //only declarations have memory declared
    };
    virtual std::string getIdentifier() const override;
    bool isPointer(Context &context) const{
        return left->isPointer(context) ^ right->isPointer(context);
    }
};


// logical_or_expression
class logicalOrOperator
    : public BinaryOperation
{
    private:
    protected:
        virtual const std::string getOpcode() const override
            { return "||"; }
    public:
    logicalOrOperator(Node* left,Node* right): BinaryOperation(left,right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context);
};

// logical_and_expression
class logicalAndOperator
    : public BinaryOperation
{
    private:
    protected:
        virtual const std::string getOpcode() const override
            { return "&&"; }
    public:
    logicalAndOperator(Node* left,Node* right): BinaryOperation(left,right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context);
};

// inclusive_or_expression
class orOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "|"; }
public:
    orOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context);
};

// exclusive_or_expression
class xorOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "^"; }
public:
    xorOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// and_expression
class andOperator : public BinaryOperation
{private:
protected:
    virtual const std::string getOpcode() const override { return "&"; }
public:
    andOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// euqality_expression
class equalOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "=="; }
public:
    equalOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class notEqualOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "!="; }
public:
    notEqualOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// relational_expression
class lessThanOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "<"; }
public:
    lessThanOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class greaterThanOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return ">"; }
public:
    greaterThanOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class lessEqualOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "<=";}
public:
    lessEqualOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class greaterEqualOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return ">="; }
public:
    greaterEqualOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}

    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context);
};

// shift_expression
class leftShiftOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "<<"; }
public:
    leftShiftOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class rightShiftOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return ">>"; }
public:
    rightShiftOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// additive_expression
class addOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "+"; }

public:
    addOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class subOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "-"; }

public:
    subOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// multiplicative_expression
class mulOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "*"; }
public:
    mulOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class divOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "/"; }
public:
    divOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

class modOperator : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override { return "%"; }
public:
    modOperator(Node *_left, Node *_right): BinaryOperation(_left, _right) {}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
    virtual int getValue(Context &context) ;
};

// assignment
class assignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "="; }
public:
    assignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class addAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "+=" ;}
public:
    addAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class subAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "-=" ;}
public:
    subAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class divAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "/=" ;}
public:
    divAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class mulAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "*=" ;}
public:
    mulAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class modAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "%=" ;}
public:
    modAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class leftAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "<<=" ;}
public:
    leftAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class rightAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return ">>=" ;}
public:
    rightAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class andAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "&=" ;}
public:
    andAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class orAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "|=" ;}
public:
    orAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

class xorAssignmentOperator
    : public BinaryOperation
{
private:
protected:
    virtual const std::string getOpcode() const override
        { return "^=" ;}
public:
    xorAssignmentOperator(Node* _left,Node* _right):BinaryOperation(_left,_right){}
    virtual void EmitRISC(std::ostream &stream, Context &context, int  destRegister) const override;
};

#endif
