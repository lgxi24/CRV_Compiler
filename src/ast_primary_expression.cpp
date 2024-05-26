#include "ast_primary_expression.hpp"

void Identifier::EmitRISC(std::ostream &stream, Context &context,int destRegister) const
{
    std::cerr<<"primary_expEmit"<<std::endl;
    if (context.RegisterFile.type == "float" || context.RegisterFile.type == "double"){
        std::cerr << "flw f"<<destRegister<<","<<context.local.back().variableBindings[identifier_].offset<<"(s0)"<<std::endl;
        stream << "flw f"<<destRegister<<","<<context.local.back().variableBindings[identifier_].offset<<"(s0)"<<std::endl;
    }
    else {
        std::cerr << "lw x"<<destRegister<<","<<context.local.back().variableBindings[identifier_].offset<<"(s0)"<<std::endl;
        stream << "lw x"<<destRegister<<","<<context.local.back().variableBindings[identifier_].offset<<"(s0)"<<std::endl; // load offset to dest register
    }

}

void Identifier::leftCompile(std::ostream &stream, Context &context,int destRegister)const
{
    // Load address of left operand into destRegisterister
    std::cerr<<"primary_expLeftCompile"<<std::endl;

    stream<<"li x"<<destRegister<<", "<<context.local.back().variableBindings[identifier_].offset<<std::endl;
    std::cerr<<"li x"<<destRegister<<", "<<context.local.back().variableBindings[identifier_].offset<<std::endl;

    stream<<"add x"<<destRegister<<", x"<<destRegister<<",s0"<<std::endl;
    std::cerr<<"add x"<<destRegister<<", x"<<destRegister<<",s0"<<std::endl;

}

bool Identifier::isPointer(Context &context)
{
    if (context.local.size() == 0){
        if (context.global.variableBindings[getIdentifier()].pointer != 0)
        return true;
    }
    else{
        if (context.local.back().variableBindings[getIdentifier()].pointer != 0)
        return true;
    }
    return false;
}

void Identifier::Print(std::ostream &stream) const
{
    stream << identifier_;
};

// int constant
void IntConstant::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    std::cerr<< "li x"<<destRegister<<"," << value << std::endl;
    stream << "li x"<<destRegister<<"," << value << std::endl;
}

void IntConstant::Print(std::ostream &stream) const
{
    std::cerr<<"print int constant"<<std::endl;
    stream << value;
}


// string constant

void stringConstant::EmitRISC(std::ostream &stream, Context &context, int destRegister)const
{
    std::string stringLabel = context.Labeling("string");
    stream<<".data"<<std::endl;
    stream<<stringLabel<<":"<<std::endl;
    stream<<" .string "<<'"'<<val<<'"'<<std::endl;
    stream<<".text"<<std::endl;
    stream<<"lui x"<<destRegister<<", %hi("<<stringLabel<<")"<<std::endl; // load the upper 20 bits of the address of the string into dest register
    stream<<"addi x"<<destRegister<<", x"<<destRegister<<", %lo("<<stringLabel<<")"<<std::endl;// add the lower 12 bits of the address to dest
}

void stringConstant::Print(std::ostream &stream)const
{
    stream<<'"'<<val;
}

int stringConstant::getValue(Context &context)
{
    std::cerr<<"Error: Getting value, of string immediate";
    exit(1);
}

std::string stringConstant::getIdentifier()const{
    std::cerr<<"Error: Getting Id, of string immediate";
    exit(1);
}

// char constant

void charConstant::EmitRISC(std::ostream &stream, Context &context, int destRegister)const
{
    std::string stringLabel = context.Labeling("string");
    stream<<".data"<<std::endl;
    stream<<stringLabel<<":"<<std::endl;
    stream<<" .string "<<'"'<<val<<'"'<<std::endl;
    stream<<".text"<<std::endl;
    stream<<"lui x"<<destRegister<<", %hi("<<stringLabel<<")"<<std::endl;
    stream<<"addi x"<<destRegister<<", x"<<destRegister<<", %lo("<<stringLabel<<")"<<std::endl;
    stream<<"lbu x"<<destRegister<<", 0(x"<<destRegister<<")"<<std::endl; // load the sigle byte

}

void charConstant::Print(std::ostream &stream)const
{
    stream<<'"'<<val;
}

int charConstant::getValue(Context &context) {
    std::cerr<<"Getting value of string";
    exit(1);
}
std::string charConstant::getIdentifier()const
{
    std::cerr<<"Getting identifier of string immediate";
    exit(1);
}

void FloatConstant::EmitRISC(std::ostream &stream, Context &context, int destRegister) const
{
    if (context.RegisterFile.type == "float"){
        std::cerr << "li x"<<destRegister<<"," << context.FloatToInt(value_) << std::endl;
        stream << "li x"<<destRegister<<"," << context.FloatToInt(value_) << std::endl;
    }
    else if (context.RegisterFile.type == "double"){
        std::cerr << "li x"<<destRegister<<"," << context.DoubleToInt(value_) << std::endl;
        stream << "li x"<<destRegister<<"," << context.DoubleToInt(value_) << std::endl;
    }
    else {
        std::cerr << "li x"<<destRegister<<"," << value_ << std::endl;
        stream << "li x"<<destRegister<<"," << value_ << std::endl;
    }
}

void FloatConstant::Print(std::ostream &stream) const
{
    stream << value_;
}

