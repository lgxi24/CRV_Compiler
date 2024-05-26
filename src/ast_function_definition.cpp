#include "ast_function_definition.hpp"

void FunctionDefinition::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{

    std::cerr<<"functionDefinition"<<std::endl;

    std::string identifier = declarator_->getIdentifier();

    std::cerr<<"compoundS Size"<<std::endl;
    std::cerr<<compound_statement_->getSize(context)<<std::endl;
    int totalOffset = compound_statement_->getSize(context) + declarator_->getSize(context)+56;

    std::cerr<<"total Offset "<<totalOffset<<std::endl;

    stream << ".text" << std::endl;
    stream << ".global " << identifier <<std::endl;
    stream<<identifier<<":"<<std::endl;

    stream<<"addi sp, sp, "<<-(totalOffset)<<std::endl; //shift sp
    stream<<"sw ra, "<<totalOffset-4<<"(sp)"<<std::endl; //store previous return addess 4 below the fp

    for (int i = 0; i < 12; i++){
        stream<<"sw s"<<i<<", "<<totalOffset-8-4*i<<"(sp)"<<std::endl;
    }

    stream<<"addi s0, sp, "<<totalOffset<<std::endl; //shift s0


    declarator_->EmitRISC(stream, context, destRegister);

    std::string returnlabel = context.Labeling(identifier);

    context.local.back().returnLabel = returnlabel;

    if (compound_statement_ != nullptr)
    {
        compound_statement_->EmitRISC(stream, context,destRegister);
    }

    std::cerr<<returnlabel<<":"<<std::endl;
    stream<<returnlabel<<":"<<std::endl; //print end of function, used for return.

    stream<<"lw ra, "<<totalOffset-4<<"(sp)"<<std::endl; //restore  previous return addess

    for (int i = 0; i < 12; i++){
        stream<<"lw s"<<i<<", "<<totalOffset-8-4*i<<"(sp)"<<std::endl;
    }

    stream<<"addi sp, sp, "<<totalOffset<<std::endl; //restore sp
    stream<<"ret"<<std::endl;

    context.local.pop_back(); //exit table opened during compiling declarator
    std::cerr<<"exit symbolTable for function "<< identifier <<std::endl;

}

void FunctionDefinition::Print(std::ostream &stream) const
{
    stream<<"function definition:  ";
    declaration_specifiers_->Print(stream);
    stream<<" ";
    declarator_->Print(stream);
    stream<<"{"<<std::endl;
    compound_statement_->Print(stream);
    stream<<"}";
}



std::string FunctionDeclarator::getIdentifier()const
{
    return declarator->getIdentifier();
}

void FunctionDeclarator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{

    int parameterOffset=0;
    int size=0;
    std::string functionId = getIdentifier();

    symbolTable newSymbolTable;
    context.local.push_back(newSymbolTable); // new table for local variables
    std::cerr<<"new scope for function "<<functionId<<std::endl;


    if (list != NULL){
        std::cerr<<"list not empty(functionDec)"<<std::endl;
        std::string parameterId;
        int parameterSize;

        for(std::size_t i=0; i<list->vecSize() ;i++){

            parameterId = list->at(i)->getIdentifier();
            parameterSize = list->at(i)->getSize(context);

            list->at(i)->EmitRISC(stream,context,destRegister); // call declaration and add the parameters to context

            if(i > 7){//more than  8
                context.functions[functionId].parameterOffset.push_back(size);
                context.local.back().variableBindings[parameterId] = {parameterSize,size};
                std::cerr<<"parameter "<<parameterId<<"not in a register declared and stored at offset"<<size<<std::endl;
                size += parameterSize;
            }
            else{
                if (context.RegisterFile.type == "float" || context.RegisterFile.type == "double"){
                    std::cerr << "fsd fa"<<i<<", "<<parameterOffset<<"(s0)"<<std::endl;
                    stream << "fsd fa"<<i<<", "<<context.local.back().offset<<"(s0)"<<std::endl;
                    std::cerr<<"parameter "<<parameterId<<"at register f"<<destRegister<<"declared and stored at offset "<<context.local.back().offset<<std::endl;
                }
                else {
                    std::cerr<<"sw a"<<i<<", "<<context.local.back().offset<<"(s0)"<<std::endl;
                    stream<<"sw a"<<i<<", "<<context.local.back().offset<<"(s0)"<<std::endl; // store each parameter
                    std::cerr<<"parameter "<<parameterId<<"at register a"<<i<<"declared and stored at offset "<<context.local.back().offset<<std::endl;
                }
            }

        }
        context.functions[functionId].size = size;
        std::cerr<<"function "<<getIdentifier()<<" declared with total parameter size "<<size<<std::endl;
    }
    else{
        std::cerr<<"function "<<getIdentifier()<<" declared with no paramters"<<std::endl;
    }
}

int FunctionDeclarator::getSize(Context &context)const {
    if (list == NULL){
        return 0;
    }
    else{
        int size = 0;
        for(std::size_t i = 0; i< list->vecSize();i++){ // add each size of the arguments
            size += list->at(i)->getSize(context);
        }
        std::cerr<<"declarator size:"<<size;
        return size;
    }
}

void FunctionDeclarator::Print(std::ostream &stream)const{
    stream<<getIdentifier();
    if (list!=NULL){
        list->Print(stream);
    }
}
