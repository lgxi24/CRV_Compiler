 #include "ast_jump_statement.hpp"

void ReturnStatement::Print(std::ostream &stream) const
{
    stream << "return";
    if (expression_ != nullptr)
    {
        stream << " ";
        expression_->Print(stream);
    }
    stream << ";" << std::endl;
}

void ReturnStatement::EmitRISC(std::ostream &stream, Context &context,int destReg) const
{
    std::cerr<<"enter return statement"<<std::endl;
    if (expression_ != NULL){

        int returnReg = context.RegisterFile.allocate();
        std::cerr<<returnReg<<std::endl;
        expression_->EmitRISC(stream,context,returnReg); //store the result in a0, the return register
        if (context.RegisterFile.type == "float"){
            stream<<"fmv.s fa0, f"<<returnReg<<std::endl;
            std::cerr<<"fmv.s fa0, f"<<returnReg<<std::endl;
            context.RegisterFile.freeReg(returnReg);
        }
        else{
            stream<<"mv a0, x"<<returnReg<<std::endl;
            std::cerr<<"mv a0, x"<<returnReg<<std::endl;
            context.RegisterFile.freeReg(returnReg);
        }
    }

    std::cerr<<"returning"<<std::endl;
    stream<<"j "<<context.local.back().returnLabel<<std::endl;

}



int ContinueStatement::getSize(Context &context)const{
    return 0;
}

void ContinueStatement::Print(std::ostream &stream) const
{
    stream<<"continue ";
    stream<<" \n";
}
void ContinueStatement:: EmitRISC(std::ostream &stream, Context &context, int destReg) const{
    std::cerr<<"returning"<<std::endl;
    stream<<"j "<<context.local.back().startLabel<<std::endl;
}


int BreakStatement::getSize(Context &context)const{
    return 0;
}

void BreakStatement::Print(std::ostream &stream) const
{
    stream<<"break ";
    stream<<" \n";
}
void BreakStatement:: EmitRISC(std::ostream &stream, Context &context, int destReg) const{
    std::cerr<<"returning"<<std::endl;
    stream<<"j "<<context.local.back().endLabel<<std::endl;
}
