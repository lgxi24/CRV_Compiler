#include "ast_iteration_statement.hpp"

void IterationStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"intereation "<<std::endl;
}

IterationStatement::~IterationStatement()
{
    if (first_expression != nullptr){
        delete first_expression;
    }
    if (second_expression != nullptr){
        delete second_expression;
    }
    if (third_expression != nullptr){
        delete third_expression;
    }
    if (iteration_body != nullptr){
        delete iteration_body;
    }
}

void IterationStatement::Print(std::ostream &stream) const
{
    stream << "IterationStatement(";
    first_expression->Print(stream);
    if (second_expression != nullptr)
    {
        stream << ", ";
        second_expression->Print(stream);
    }
    if (third_expression != nullptr)
    {
        stream << ", ";
        third_expression->Print(stream);
    }
    stream << ", ";

    if (iteration_body != nullptr)
    {
        iteration_body->Print(stream);
    }
    stream << ")";
}

int IterationStatement::getSize(Context &context) const
{
    return iteration_body->getSize(context); // only need to return the size of the iteration body
}

void WhileStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string startLabel = context.Labeling("WHILE_START");
    std::string endLabel = context.Labeling("WHILE_END");

    context.local.back().endLabel = endLabel;
    context.local.back().startLabel = startLabel;

    stream << startLabel << ":" << std::endl;
    first_expression->EmitRISC(stream, context, destRegister);
    stream << "beqz x" << destRegister << ", " << endLabel << std::endl; // false condition
    iteration_body->EmitRISC(stream, context, destRegister); // true condition
    stream << "j " << startLabel << std::endl;
    stream << endLabel << ":" << std::endl;
}

void DoWhileStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string startLabel = context.Labeling("DO_WHILE_START");
    std::string endLabel = context.Labeling("DO_WHILE_END");

    stream << startLabel << ":" << std::endl;
    iteration_body->EmitRISC(stream, context, destRegister); // true condition
    first_expression->EmitRISC(stream, context, destRegister);
    stream << "bnez x" << destRegister << ", " << startLabel << std::endl; // false condition
    stream << endLabel << ":" << std::endl;
}

void ForStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string startLabel = context.Labeling("FOR_START");
    std::string endLabel = context.Labeling("FOR_END");

    first_expression->EmitRISC(stream, context, destRegister); // initialization
    stream << startLabel << ":" << std::endl;
    second_expression->EmitRISC(stream, context, destRegister); // condition
    stream << "beqz x" << destRegister << ", " << endLabel << std::endl; // false condition
    iteration_body->EmitRISC(stream, context, destRegister); // true condition
    if (third_expression != nullptr){
        third_expression->EmitRISC(stream, context, destRegister); // increment
    }
    stream << "j " << startLabel << std::endl;
    stream << endLabel << ":" << std::endl;
}
