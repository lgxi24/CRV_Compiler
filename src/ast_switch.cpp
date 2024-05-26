#include "ast_switch.hpp"

void SwitchCase::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"Switch operation RISC"<<std::endl;
}

SwitchCase::~SwitchCase()
{
    if (expression != NULL){
        delete expression;
    }
    delete statement;
}

void SwitchCase::Print(std::ostream &stream) const
{
    stream<<"switch case: {";
    stream<<"expression:"<<std::endl;
    if (expression != NULL){
        expression->Print(stream);
    }
    stream<<"statement:"<<std::endl;
    statement->Print(stream);
    stream << "}" << std::endl;
}

int SwitchCase::getSize(Context &context) const
{
    std::cerr<<"getting size of switch case";

}

std::string SwitchCase::getIdentifier() const
{
    std::cerr<<"getting identifier of switch case";
    exit(1);
}

int SwitchStatement::getSize(Context &context) const
{
    return statement->getSize(context);
}

void SwitchStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string startlabel = context.Labeling("SWITCH_START");
    std::string endlabel = context.Labeling("SWITCH_END");
    context.local.back().startLabel = startlabel;
    context.local.back().endLabel = endlabel;

    expression -> EmitRISC(stream, context, destRegister); // variable to be evaluated
    stream << "j " << startlabel << std::endl; // jump to start of switch
    stream << context.local.back().startLabel << ":" << std::endl;
    statement -> EmitRISC(stream, context, destRegister); // execute inside part of switch
    stream << endlabel << ":" << std::endl;
}

int CaseStatement::getSize(Context &context) const
{
    return statement->getSize(context);
}

void CaseStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string nextCase = context.Labeling("CASE");
    if (expression != NULL){
        int tempReg = context.RegisterFile.allocate();
        expression->EmitRISC(stream,context,tempReg);
        stream<<"bne x"<<destRegister<<", x"<<tempReg<<", "<<nextCase<<std::endl;
        context.RegisterFile.freeReg(tempReg);
    }
    statement->EmitRISC(stream,context,destRegister);
    stream<<nextCase<<":"<<std::endl;
}

int CaseBreakStatement::getSize(Context &context) const
{
    return statement->getSize(context);
}

void CaseBreakStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string nextCase = context.Labeling("CASE");
    if (expression != NULL){ // not default case
        int tempReg = context.RegisterFile.allocate(); // allocate another register for TRUE/FALSE expression
        expression->EmitRISC(stream,context,tempReg); // evaluate expression
        stream<<"bne x"<<destRegister<<", x"<<tempReg<<", "<<nextCase<<std::endl; // if not equal, jump to next case
        context.RegisterFile.freeReg(tempReg);
    }
    statement->EmitRISC(stream,context,destRegister); // execution
    stream << "j " << context.local.back().endLabel << std::endl;
    stream<<nextCase<<":"<<std::endl;
}


