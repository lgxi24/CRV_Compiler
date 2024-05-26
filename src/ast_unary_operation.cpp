#include "ast_unary_operation.hpp"

void UnaryOperation::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"Unary operation RISC"<<std::endl;
}

UnaryOperation::~UnaryOperation()
{
    delete expression;
}

void UnaryOperation::Print(std::ostream &stream) const
{
    stream << getOpcode() << "(";
    expression->Print(stream);
    stream << ")";
}

int UnaryOperation::getSize(Context &context) const
{
    return 0;
}

std::string UnaryOperation::getIdentifier() const
{
    std::cerr<<"getting identifier of unary expression";
    exit(1);
}

void negOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    expression->EmitRISC(stream, context, destRegister);
    stream << "neg x" << destRegister << ", x" << destRegister << std::endl;
}

int negOperator::getValue(Context &context)
{
    return -expression->getValue(context);
}

void notOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    expression->EmitRISC(stream, context, destRegister);
    stream << "seqz x" << destRegister << ", x" << destRegister << std::endl;
    stream << "andi x" << destRegister << ", x" << destRegister << ", 0xff" << std::endl;
}

int notOperator::getValue(Context &context)
{
    return !expression->getValue(context);
}

void bitwiseNotOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    expression->EmitRISC(stream, context, destRegister);
    stream << "not x" << destRegister << ", x" << destRegister << std::endl;
}

int bitwiseNotOperator::getValue(Context &context)
{
    return ~expression->getValue(context);
}

void preincOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int arraySize = context.local.back().variableBindings[expression->getIdentifier()].arraySize;
    expression->EmitRISC(stream, context, destRegister);
    stream << "lw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl; //load value of variable
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", "<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", 1" << std::endl;
    }
    stream << "sw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl; //store incremented value
}

void predecOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int arraySize = context.local.back().variableBindings[expression->getIdentifier()].arraySize;
    expression->EmitRISC(stream, context, destRegister);
    stream << "lw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl;
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", -"<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", -1" << std::endl;
    }
    stream << "sw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl;
}

void postincOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int arraySize = context.local.back().variableBindings[expression->getIdentifier()].arraySize;
    expression->EmitRISC(stream, context, destRegister);
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", "<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", 1" << std::endl; //increment first
    }
    stream << "sw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl; //store incremented value
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", -"<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", -1" << std::endl; //decrement back
    }
}

void postdecOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int arraySize = context.local.back().variableBindings[expression->getIdentifier()].arraySize;
    expression->EmitRISC(stream, context, destRegister);
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", -"<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", -1" << std::endl;
    }
    stream << "sw x" << destRegister << ", " << context.local.back().variableBindings[expression->getIdentifier()].offset << "(s0)" << std::endl;
    if (expression->isPointer(context)){
        stream<<"addi x"<<destRegister<<", x"<<destRegister<<", "<<arraySize<<std::endl;
    }
    else{
        stream << "addi x" << destRegister << ", x" << destRegister << ", 1" << std::endl;
    }
}

void sizeofOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int size = context.local.back().variableBindings[expression->getIdentifier()].size;
    stream << "li x" << destRegister << ", " << size << std::endl;
}

int sizeofOperator::getValue(Context &context)
{
    return context.local.back().variableBindings[expression->getIdentifier()].size;
}

std::string sizeofOperator::getIdentifier() const
{
    return expression->getIdentifier();
}

void sizeofTypeOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    int size = expression->getSize(context);
    stream << "li x" << destRegister << ", " << size << std::endl;
}

int sizeofTypeOperator::getValue(Context &context)
{
    std::cerr<< "sizeofTypeOperator Value"<< context.local.back().variableBindings[expression->getIdentifier()].size<<std::endl;
    return context.local.back().variableBindings[expression->getIdentifier()].size;
}


void addressOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const
{
    std::string id = expression->getIdentifier();
    int offset = context.local.back().variableBindings[id].offset; //define new function to directly get offset
    stream<<"addi x"<<destRegister<<", s0, "<<offset<<std::endl; //absolute addess to the variable
}


 void dereferenceOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister)const
{
    std::string id = expression->getIdentifier();
    int offset = context.local.back().variableBindings[id].offset;
    stream<<"lw x"<<destRegister<<", "<<offset<<"(s0)"<<std::endl;
    stream<<"lw x"<<destRegister<<", 0(x"<<destRegister<<")"<<std::endl;
}

void dereferenceOperator::leftCompile(std::ostream &stream, Context &context, int destRegister)const
{
    std::string id = expression->getIdentifier();
    int offset = context.local.back().variableBindings[id].offset;
    stream<<"lw x"<<destRegister<<", "<<offset<<"(s0)"<<std::endl;
    std::cerr<<"getting pointer address"<<std::endl;
}
