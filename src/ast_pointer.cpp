#include "ast_pointer.hpp"
#include <cmath>
#include <string>

void PointerDeclarator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"pointer declared"<<std::endl;
    if (context.local.size() == 0){ //global pointer
        context.global.variableBindings[declarator->getIdentifier()].pointer = 1;
    }
    else{
        context.local.back().variableBindings[declarator->getIdentifier()].pointer = 1;
    }
}

void PointerDeclarator::Print(std::ostream &stream) const
{
    stream<<"*";
}

std::string PointerDeclarator::getIdentifier() const
{
    std::cerr<<"pointer id "<<declarator->getIdentifier()<<std::endl;
    return declarator->getIdentifier();
}

int PointerDeclarator::getSize(Context &context) const
{
    return 1;
}

bool PointerDeclarator::isPointer(Context &context) {
    return true;
}

