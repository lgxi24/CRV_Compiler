#include "ast_function_call.hpp"


std::string functionCall::getIdentifier() const
{
    std::cerr<<"function call identifier"<<std::endl;
    return identifier->getIdentifier();
}

void functionCall::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::string id = getIdentifier();

    std::cerr<<"calling function "<<id<<std::endl;

    if(arguments == NULL){
        std::cerr<<"no arguments loaded"<<std::endl;
    }
    else{//loading in arguments to memory
        std::cerr<<"loading total of "<<arguments->vecSize()<<" arguments"<<std::endl;

        int argumentReg = 0;
        for (int i = arguments->vecSize()-1; i>= 0 ; i--){
            std::cerr<<"loading arguments"<<std::endl;
            if (i>7){
                argumentReg = 17;
                arguments->at(i)->EmitRISC(stream,context,argumentReg); //process all the rest of arguments through a7, for larger than 8 parameters
                stream<<"sw a7, "<<context.functions[id].parameterOffset[i-8]<<"(sp)"<<std::endl;
            }
            else{
                argumentReg = i + 10; //a0-a7 = x10-x17
                arguments->at(i)->EmitRISC(stream,context,argumentReg);
            }
            std::cerr<<i<<"th argument loaded"<<std::endl;
        }
    }

    std::cerr<<id<<" called"<<std::endl;

    stream<<"call "<<id<<std::endl;
    stream<<"mv x"<<destRegister<<", a0"<<std::endl;
}

void functionCall::Print(std::ostream &stream) const
{
    stream<<"functionCall: ";
    identifier->Print(stream);
    stream<<" (";
    stream<<")\n";
}






