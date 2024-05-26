#include "ast_binary_operation.hpp"

void BinaryOperation::EmitRISC(std::ostream &stream, Context &Context, int destRegister) const
{
    std::cerr<<"binary operation"<<std::endl;
}


void BinaryOperation::Print(std::ostream &stream) const
{
    stream<<"(";
    left->Print(stream);
    stream<<" "<<getOpcode()<<" ";
    right->Print(stream);
    stream<<")";
}

int BinaryOperation::doLeft(std::ostream &stream, Context &context, int destRegister) const {
    left->EmitRISC(stream, context, destRegister);
    return destRegister;
}

int BinaryOperation::doRight(std::ostream &stream, Context &context, int destRegister) const{
    std::cerr<<"allocating register"<<std::endl;
    int RightReg = context.RegisterFile.allocate();
    right->EmitRISC(stream, context, RightReg);
    return RightReg;
}

std::string BinaryOperation::getIdentifier() const
{
    std::cerr<<"getting identifier of binary expression";
    exit(1);
}

// logical_or_expression
void logicalOrOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"logical Or"<<std::endl;
    std::string L2 = context.Labeling("logicalOr_TRUE");
    std::string L3 = context.Labeling("logicalOR_FALSE");
    std::string L5 = context.Labeling("logicalOR_END");

    left->EmitRISC(stream, context, destRegister);
    stream<<"bne x"<<destRegister<<", zero, "<<L2<<std::endl; //if left is true, jump to L2
    right->EmitRISC(stream, context, destRegister);
    stream<<"beq x"<<destRegister<<", zero, "<<L3<<std::endl; //if right is false & left is false, jump to L3

    stream<<L2<<":"<<std::endl;
    stream<<"add x"<<destRegister<<", zero, 1"<<std::endl; // return true
    stream<<"j "<<L5<<std::endl;

    stream<<L3<<":"<<std::endl;
    stream<<"mv x"<<destRegister<<", zero"<<std::endl; // return false

    stream<<L5<<":"<<std::endl;
}

int logicalOrOperator::getValue(Context &context)
{
    return left->getValue(context) || right->getValue(context);
}

// logical_and_expression
void logicalAndOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"Logical AND"<<std::endl;

    std::string L2 = context.Labeling("logicalAND_FALSE");
    std::string L4 = context.Labeling("logicalAND_END");

    left->EmitRISC(stream, context, destRegister);
    stream<<"beq x"<<destRegister<<", zero, "<<L2<<std::endl; //if left is false, Logical AND is false
    right->EmitRISC(stream, context, destRegister);
    stream<<"beq x"<<destRegister<<", zero, "<<L2<<std::endl; //if right is false, Logical AND is false

    stream<<"add x"<<destRegister<<",zero, 1"<<std::endl; // all true, return true
    stream<<"j "<<L4<<std::endl;

    stream<<L2<<":"<<std::endl;
    stream<<"mv x"<<destRegister<<", zero"<<std::endl; // return false

    stream<<L4<<":"<<std::endl;
}

int logicalAndOperator::getValue(Context &context)
{
    return left->getValue(context) && right->getValue(context);
}

// inclusive_or_expression
void orOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"or x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int orOperator::getValue(Context &context)
{
    return left->getValue(context) | right->getValue(context);
}

// exclusive_or_expression
void xorOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"xor x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int xorOperator::getValue(Context &context)
{
    return left->getValue(context) ^ right->getValue(context);
}

// and_expression
void andOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"and x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int andOperator::getValue(Context &context)
{
    return left->getValue(context) & right->getValue(context);
}

// euqality_expression
void equalOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sub x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl; //evaluate left - right
    stream <<"seqz x"<<destRegister<<", x"<<destRegister<<std::endl; //if result is 0, then equal
    context.RegisterFile.freeReg(RightReg);
}

int equalOperator::getValue(Context &context)
{
    return left->getValue(context) == right->getValue(context);
}

void notEqualOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sub x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl; //evaluate left - right
    stream <<"snez x"<<destRegister<<", x"<<destRegister<<std::endl;    //if result is not 0, then not equal
    context.RegisterFile.freeReg(RightReg);
}

int notEqualOperator::getValue(Context &context)
{
    return left->getValue(context) != right->getValue(context);
}

// relational_expression
void lessThanOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"slt x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int lessThanOperator::getValue(Context &context)
{
    return left->getValue(context) < right->getValue(context);
}

void greaterThanOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sgt x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int greaterThanOperator::getValue(Context &context)
{
    return left->getValue(context) > right->getValue(context);
}

void lessEqualOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sgt x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl; // <= is the opposite of >
    stream <<"xori x"<<destRegister<<", x"<<destRegister<<", 1"<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int lessEqualOperator::getValue(Context &context)
{
    return left->getValue(context) <= right->getValue(context);
}

void greaterEqualOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"slt x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl; // >= is the opposite of <
    stream <<"xori x"<<destRegister<<", x"<<destRegister<<", 1"<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int greaterEqualOperator::getValue(Context &context)
{
    return left->getValue(context) >= right->getValue(context);
}

// shift_expression
void leftShiftOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sll x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int leftShiftOperator::getValue(Context &context)
{
    return left->getValue(context) << right->getValue(context);
}

void rightShiftOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"sra x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int rightShiftOperator::getValue(Context &context)
{
    return left->getValue(context) >> right->getValue(context);
}

// additive_expression
void addOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const{

    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);

    if (left->isPointer(context) && !right->isPointer(context)) {
        stream<<"slli x"<<RightReg<<", x"<<RightReg<<", 2"<<std::endl;
    }
    else if (!left->isPointer(context) && right->isPointer(context)) {
        stream<<"slli x"<<LeftReg<<", x"<<LeftReg<<", 2"<<std::endl;
    }

    if (context.RegisterFile.type == "float"){
        std::cerr<<"float add f"<<destRegister<<", f"<<LeftReg<<", f"<<RightReg<<std::endl;
        stream<<"fadd.s f"<<destRegister<<", f"<<LeftReg<<", f"<<RightReg<<std::endl;
        context.RegisterFile.freeReg(RightReg);
    }
    else if (context.RegisterFile.type == "double"){
        std::cerr<<"double add f"<<destRegister<<", f"<<LeftReg<<", f"<<RightReg<<std::endl;
        stream<<"fadd.d f"<<destRegister<<", f"<<LeftReg<<", f"<<RightReg<<std::endl;
        context.RegisterFile.freeReg(RightReg);
    }
    else {
        std::cerr<<"integer add x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
        stream <<"add x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
        context.RegisterFile.freeReg(RightReg);
    }
}

int addOperator::getValue(Context &context)
{
    return left->getValue(context) + right->getValue(context);
}

void subOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const{

    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);

    if (left->isPointer(context) && !right->isPointer(context)) {
        stream<<"slli x"<<RightReg<<", x"<<RightReg<<", 2"<<std::endl;
    }
    else if (!left->isPointer(context) && right->isPointer(context)) {
        stream<<"slli x"<<LeftReg<<", x"<<LeftReg<<", 2"<<std::endl;
    }

    std::cerr<<"sub x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    stream <<"sub x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;

    context.RegisterFile.freeReg(RightReg);
}

int subOperator::getValue(Context &context)
{
    return left->getValue(context) - right->getValue(context);
}

// multiplicative_expression
void mulOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    std::cerr<<"mul x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    stream <<"mul x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int mulOperator::getValue(Context &context)
{
    return left->getValue(context) * right->getValue(context);
}

void divOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    std::cerr<<"div x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    stream <<"div x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int divOperator::getValue(Context &context)
{
    return left->getValue(context) / right->getValue(context);
}

void modOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const{
    int LeftReg  = doLeft(stream, context, destRegister);
    int RightReg = doRight(stream, context, destRegister);
    stream <<"rem x"<<destRegister<<", x"<<LeftReg<<", x"<<RightReg<<std::endl;
    context.RegisterFile.freeReg(RightReg);
}

int modOperator::getValue(Context &context)
{
    return left->getValue(context) % right->getValue(context);
}

// assignment
void assignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{
    std::cerr<<"assignOp "<<std::endl;
    left->leftCompile(stream, context, destRegister); //store pointer in destRegister
    int RightReg = doRight(stream, context, destRegister); //store value in RightReg

    std::cerr<<"sw x"<<RightReg<<", "<<"0(x"<<destRegister<<")"<<std::endl;
    stream<<"sw x"<<RightReg<<", "<<"0(x"<<destRegister<<")"<<std::endl;

    context.RegisterFile.freeReg(RightReg);
    std::cerr<<"exit assignOp "<<std::endl;
}

void addAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl; // Load the value of the left operand
    if (context.RegisterFile.type == "float")
    {
        stream << "fadd.s f" << additionalReg << ", f" << additionalReg << ", f" << rightReg << std::endl;
    }
    else if (context.RegisterFile.type == "double")
    {
        stream << "fadd.d f" << additionalReg << ", f" << additionalReg << ", f" << rightReg << std::endl;
    }
    else
    {
        stream << "add x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    }
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl; // Store the result in the left operand

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void subAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "sub x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void divAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);
    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "div x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void mulAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "mul x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void modAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);
    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "rem x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void leftAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "sll x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void rightAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "sra x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void xorAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "xor x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void orAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "or x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}

void andAssignmentOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    left->leftCompile(stream, context, destRegister);
    int rightReg = doRight(stream, context, destRegister);

    int additionalReg = context.RegisterFile.allocate();
    stream << "lw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;
    stream << "and x" << additionalReg << ", x" << additionalReg << ", x" << rightReg << std::endl;
    stream << "sw x" << additionalReg << ", 0(x" << destRegister << ")" << std::endl;

    context.RegisterFile.freeReg(rightReg);
    context.RegisterFile.freeReg(additionalReg);
}


