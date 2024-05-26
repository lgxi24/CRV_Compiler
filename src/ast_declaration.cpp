#include "ast_declaration.hpp"

int declaration::getSize(Context &context) const
{
    int listSize=0;
    int declaratorSize =0;

    for (size_t i=0;i<list->vecSize();i++){

        declaratorSize = list->at(i)->getSize(context);
        std::cerr<<"declaration declaratorSize: "<<declaratorSize<<std::endl;

        if (list->at(i)->isPointer(context)){
            listSize += declaratorSize*4; //pointer size 4
        }
        else{
            listSize += declaratorSize*declaration_specifier->getSize(context);
        }

    }
    return listSize;
}

void declaration::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{

    declaration_specifier->EmitRISC(stream,context,destRegister);

    if (list == NULL){
        return;
    }


    std::string identifier;

    int size;
    int arraySize;

    for (size_t i=0; i<list->vecSize();i++){


        identifier = list->at(i)->getIdentifier();

        if (list->at(i)->isPointer(context)){
            size = list->at(i)->getSize(context)*4;
            std::cerr<<"size of pointer declaration "<<size<<std::endl;

        }
        else{
            size = list->at(i)->getSize(context)*declaration_specifier->getSize(context);
        }

        arraySize = declaration_specifier->getSize(context);
        std::cerr<<"declaration arraySize"<<declaration_specifier->getSize(context)<<std::endl;


        if (context.local.size() == 0){

            if (context.global.variableBindings.find(identifier) == context.global.variableBindings.end()){

                context.global.offset -= size;
                context.global.variableBindings[identifier] = {size, context.global.offset, arraySize, 0};
                std::cerr<<"global variable "<<identifier<<" of size "<<size;
            }
            else{
                std::cerr<<"Multiple declaration of variable "<<identifier<<" in global";
                exit(1);
            }
        }
        else{
            if (context.local.back().variableBindings.find(identifier) == context.local.back().variableBindings.end()){
                context.local.back().offset -= size;
                std::cerr<<"size list "<<size<<" "<<context.local.back().offset<<" "<<arraySize<<std::endl;
                std::cerr<<identifier<<std::endl;
                context.local.back().variableBindings[identifier] = {size, context.local.back().offset, arraySize, 0};

            }
            else{
                context.enterSymbolTable();
                context.local.back().offset -= size;
                context.local.back().variableBindings[identifier] = {size, context.local.back().offset, arraySize, 0};
                context.local.back().layer++;
                std::cerr<<"local variable "<<identifier<<" of size "<<size<<std::endl;
                std::cerr<<"multiple declaration of variable "<<identifier<<std::endl;
            }
        }
        std::cerr<<"offset "<<std::endl;
        list->at(i)->EmitRISC(stream, context, destRegister);
    }
}


void declaration::Print(std::ostream &stream) const
{
    stream<<"declaration"<<": "<<std::endl;
    stream<<"(";
    declaration_specifier->Print(stream);
    stream<<" ";
    if(list == NULL){
        stream<<")\n";
        return;
    }
    list->Print(stream);
    stream<<")\n";
}




void initDeclarator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"initDec"<<std::endl;
    std::string id = getIdentifier();
    declarator->EmitRISC(stream, context, destRegister);
    initializer->EmitRISC(stream, context, destRegister);

    if (context.local.size() == 0){
        stream<<"sw x"<<destRegister<<", "<<context.global.variableBindings[id].offset<<"(gp)"<<std::endl;;
    }
    else{
        std::cerr<<"initDec"<<std::endl;

        std::cerr<<"sw x"<<destRegister<<", "<<context.local.back().variableBindings[id].offset<<"(s0)"<<std::endl;
        stream<<"sw x"<<destRegister<<", "<<context.local.back().variableBindings[id].offset<<"(s0)"<<std::endl;

    }
    std::cerr<<" !!and initialized"<<std::endl;

}

void initDeclarator::Print(std::ostream &stream) const
{
    stream<<"initialize:";
    declarator->Print(stream);
    stream<<"=";
    initializer->Print(stream);
    stream<<"\n";
}

bool initDeclarator::isPointer(Context &context)
{
    return declarator->isPointer(context);
}

std::string variableDeclarator::getIdentifier()const
{
    std::cerr<<"variableDec "<<identifier<<std::endl;
    return identifier;
}

int variableDeclarator::getSize(Context &context)const
{
    std::cerr<<"variableDec size: 1"<<std::endl;
    return 1; //default for declarator, total size calculated with specifier in declaration
}
void variableDeclarator::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<<"declared"<<std::endl;
}

void variableDeclarator::Print(std::ostream &stream)const
{
    stream<<identifier;
}
