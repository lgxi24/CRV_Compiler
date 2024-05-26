#include "ast_type_specifier.hpp"

void TypeSpecifier::EmitRISC(std::ostream &stream, Context &context,int destRegister) const
{
    if (((type == "float") && (context.RegisterFile.type != "double")) || (type == "double")){ // double has higher precedence
        context.RegisterFile.type = type;
        std::cerr<<"TYPE_SPECIFIER"<< " " << context.RegisterFile.type << std::endl;
    }

}

void TypeSpecifier::Print(std::ostream &stream) const
{
    if (type == "int"){
        stream<<"int";
    }
    else if (type == "char"){
        stream<<"char";
    }
    else if (type == "void"){
        stream<<"void";
    }
    else if (type == "bool"){
        stream<<"bool";
    }
    else if (type == "float"){
        stream<<"float";
    }
    else if (type == "double"){
        stream<<"double";
    }
    else if (type == "char"){
        stream<<"char";
    }
    else if (type == "string"){
        stream<<"string";
    }
    else if (type == "unsigned"){
        stream << "unsigned";
    }
    else{
        std::cerr<<"unknown type"<<std::endl;
        exit(1);
    }
}

int TypeSpecifier::getSize(Context &context) const
{
    if (type == "int"){
        return 4;
    }
    else if (type == "char"){
        return 1;
    }
    else if (type == "void"){
        return 0;
    }
    else if (type == "bool"){
        return 1;
    }
    else if (type == "float"){
        return 4;
    }
    else if (type == "double"){
        return 8;
    }
    else if (type == "char"){
        return 1;
    }
    else if (type == "string"){
        return 0;
    }
    else if (type == "unsigned"){
        return 4;
    }
    else{
        std::cerr<<"unknown type"<<std::endl;
        exit(1);
    }
}
