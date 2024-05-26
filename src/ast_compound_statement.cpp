#include "ast_compound_statement.hpp"

int compoundStatement::getSize(Context &context)const{
    std::cerr<<"compound statement"<<std::endl;
    int size = 0;
    if (list == NULL){
        return 0;
    }
    else{
        std::cerr<<" compound statement List not null"<<std::endl;
        for (int i = 0; i < list->vecSize();i++){
            size += list->at(i)->getSize(context);
        }
    }
    std::cerr<<"compound statement size "<< size<<std::endl;
    return size;
}

void compoundStatement::Print(std::ostream &stream) const
{
    if (list != NULL){
        stream << "CompoundStatement(";
        list->Print(stream);
        stream << ")";
    }
    else{
        stream << "CompoundStatement()";
    }
}

void compoundStatement::EmitRISC(std::ostream &stream, Context &context, int destRegister) const {
        std::cerr<<"entering compoundStatement"<<std::endl; // enter the table of compound statenment
        context.enterSymbolTable();
        if (list != NULL){
            std::cerr<<list->vecSize()<<std::endl;
            list->EmitRISC(stream,context,destRegister);
        }
        context.exitSymbolTable();
        std::cerr<<"exiting compoundStatement"<<std::endl;
}

std::string  compoundStatement::getIdentifier()const {
    std::cerr<<"Error: getting id of compound statement";
}
