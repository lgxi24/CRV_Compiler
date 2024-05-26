#include "ast_array.hpp"

std::string ArrayDeclarator::getIdentifier() const
{
    std::cerr<<"array declarator"<<std::endl;
    return declarator->getIdentifier();
}

int ArrayDeclarator::getSize(Context &context) const
{
    int arraySize = 0;

    for (size_t i = 0; i < size->vecSize(); i++){
        arraySize += size->at(i)->getValue(context); //total size of memory required for this array
    }

    std::cerr<<"array size "<<arraySize<<std::endl;
    return arraySize;
}


void ArrayDeclarator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<" array declared"<<std::endl;
}

void ArrayDeclarator::Print(std::ostream &stream) const
{
    stream <<"array declarator"<<std::endl;
}

std::string arrayIndex::getIdentifier() const
{
    return identifier->getIdentifier();
}

int arrayIndex::getSize(Context &context) const
{
    return 0;
}

void arrayIndex::leftCompile(std::ostream &stream, Context &context, int destRegister) const
{
    int scale = 1;

    if (context.local.size() == 0){ // base size of the array
        scale *= context.global.variableBindings[getIdentifier()].arraySize;
    }
    else {
        scale *= context.local.back().variableBindings[getIdentifier()].arraySize;
    }

    int offsetRegister = context.RegisterFile.allocate(); //allocate a new register to store the offset
    int scaleRegister = context.RegisterFile.allocate();

    identifier->leftCompile(stream, context,destRegister); // base address of array into destregister

    if (identifier->isPointer(context)){
        stream<<"lw x"<<destRegister<<", 0(x"<<destRegister<<")"<<std::endl;
    }

    for (int i = index->vecSize(); i > 0; i--){ // unsign can't be <0, thus use int not size_t
        index->at(i-1)->EmitRISC(stream,context,offsetRegister);
        stream<<"li x"<<scaleRegister<<", "<<scale<<std::endl;
        stream<<"mul x"<<offsetRegister<<", x"<<offsetRegister<<", x"<<scaleRegister<<std::endl;
        stream<<"add x"<<destRegister<<", x"<<destRegister<<", x"<<offsetRegister<<std::endl;
    }

    context.RegisterFile.freeReg(offsetRegister);
    context.RegisterFile.freeReg(scaleRegister);
}


void arrayIndex::EmitRISC(std::ostream &stream, Context &context, int destRegister) const{
    leftCompile(stream,context,destRegister);

    int scale = 1;
    if (context.local.size() == 0){
        scale = context.global.variableBindings[getIdentifier()].arraySize;
    }
    else{
        scale = context.local.back().variableBindings[getIdentifier()].arraySize;
    }

    if (scale == 1){
        stream<<"lbu x"<<destRegister<<", 0(x"<<destRegister<<")"<<std::endl;
    }
    else{
        stream<<"lw x"<<destRegister<<", 0(x"<<destRegister<<")"<<std::endl;
    }
}

void arrayIndex::Print(std::ostream &stream) const
{
    stream<<"array index"<<std::endl;
}

