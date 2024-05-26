#include "ast_ternary_operation.hpp"

ternaryOperator::~ternaryOperator(){
    if (condition != nullptr){
        delete condition;
    }
    if (conditionTrue != nullptr){
        delete conditionTrue;
    }
    if (conditionFalse != nullptr){
        delete conditionFalse;
    }
}

void ternaryOperator::Print(std::ostream &stream) const
{
    stream<<"(";
    if (condition != nullptr){
        condition->Print(stream);
    }
    stream<<" ? ";
    if (conditionTrue != nullptr){
        conditionTrue->Print(stream);
    }
    stream<<" : ";
    if (conditionFalse != nullptr){
        conditionFalse->Print(stream);
    }
    stream<<")";
}

// const std::string ternaryOperator::getOpcode() const
// { return " ? " ;}

// int ternaryOperator::doConditionTrue(std::ostream &stream, Context &context, int destRegister) const {
//     conditionTrue->EmitRISC(stream, context, destRegister);
//     return destRegister;
// }

std::string ternaryOperator::getIdentifier() const
{
    std::cerr<<"getting identifier of binary expression";
    exit(1);
}

void ternaryOperator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const {
    std::string elseLabel = context.Labeling("TERNARY_TRUE");
    std::string endLabel = context.Labeling("TERNARY_FALSE");

    condition->EmitRISC(stream,context,destRegister); // decide through condition
    stream << "beqz x" <<destRegister<< ", " << elseLabel << std::endl;
    conditionTrue->EmitRISC(stream, context, destRegister);
    stream << "j " << endLabel << std::endl;
    stream << elseLabel << ":" << std::endl;
    conditionFalse->EmitRISC(stream, context, destRegister);
    stream << endLabel << ":" << std::endl;
}



