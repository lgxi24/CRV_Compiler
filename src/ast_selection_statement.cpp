#include "ast_selection_statement.hpp"

void SelectionStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{

}

SelectionStatement::~SelectionStatement()
{
    if (condition != NULL){
        delete condition;
    }
    if (ifStatement != NULL){
        delete ifStatement;
    }
    if (elseStatement != NULL){
        delete elseStatement;
    }
}

void SelectionStatement::Print(std::ostream &stream) const
{
    stream << "SelectionStatement(";
    condition->Print(stream);
    stream << ", ";
    ifStatement->Print(stream);
    if (elseStatement != NULL) // if there is an else statement
    {
        stream << ", ";
        elseStatement->Print(stream);
    }
    stream << ")";
}

int SelectionStatement::getSize(Context &context) const
{
    if (elseStatement != NULL){
            return ifStatement->getSize(context) + ifStatement->getSize(context);
    }
    return ifStatement->getSize(context);
}

void IfStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string endLabel = context.Labeling("IF_END");
    condition->EmitRISC(stream, context, destRegister);
    stream << "beqz x" << destRegister << ", " << endLabel << std::endl; // false condition
    ifStatement->EmitRISC(stream, context, destRegister); // true condition
    stream << endLabel << ":" << std::endl;
}

int IfStatement::getSize(Context &context) const
{
    return ifStatement->getSize(context);
}

void IfElseStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string elseLabel = context.Labeling("IF_ELSE");
    std::string endLabel = context.Labeling("IF_ELSE_END");

    condition->EmitRISC(stream, context, destRegister);
    stream << "beqz x" <<destRegister<< ", " << elseLabel << std::endl; // false condition
    ifStatement->EmitRISC(stream, context, destRegister); // true condition
    stream << "j " << endLabel << std::endl;
    stream << elseLabel << ":" << std::endl;
    elseStatement->EmitRISC(stream, context, destRegister);
    stream << endLabel << ":" << std::endl;
}

int IfElseStatement::getSize(Context &context) const
{
    return ifStatement->getSize(context) + elseStatement->getSize(context);
}
