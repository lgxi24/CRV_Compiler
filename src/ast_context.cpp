#include "ast_context.hpp"


void Registers::useReg(int index)
{
    intRegs[index].isInUse=true;
}


void Registers::freeReg(int index) {
    if(type == "float" || type == "double"){
        floatRegs[index].isInUse = false;
        std::cerr<<"free float register index: "<<index<<std::endl;
        return;
    }
    else{
        intRegs[index].isInUse = false;
        std::cerr<<"free register index: "<<index<<std::endl;
    }
}

int Registers::allocate()
{
    if (type == "float" || type == "double") {
        for (int i = 5; i < floatRegSize; i++) { //first 5 regiser not allocatable
            if (floatRegs.find(i) == floatRegs.end() || !floatRegs[i].isInUse) {
                floatRegs[i].isInUse = true;
                std::cerr << "Allocated float register index: " << i << std::endl;
                return i;
            }
        }
    } else {
        for (int i = 5; i < intRegSize; i++) {
            if (intRegs.find(i) == intRegs.end() || !intRegs[i].isInUse) {
                intRegs[i].isInUse = true;
                std::cerr << "Allocated register index: " << i << std::endl;
                return i;
            }
        }
    }
    std::cerr << "Error: no register available" << std::endl;
    return -1; // No registers available.
}


void Context::enterSymbolTable(){
    local.push_back(local.back());
}

void Context::exitSymbolTable(){
    int layer = local.back().layer;
    for (int i = 0; i < layer; i++){
        local.pop_back();
    }
}

std::string Context::Labeling(std::string id){

    if (label.find(id) != label.end()){ //if the label already exist
        label[id] ++;
        int index = label[id];
       std::cerr<<"make up "<<id<< " label_"<<index<<std::endl; //get the index of that label
        return id+"_"+"L"+std::to_string(index); //returen label
    }
    else{  //if the id label does not exist
        label[id] = 0;
        std::cerr<<"make up new "<<id<< " label_0"<<std::endl;  //insert that label into existed label
        return id+"_"+"L"+"0";
    }
}

int Context::FloatToInt(float f){
    union FloatIntUnion {
        int i;
        float f;
    };
    FloatIntUnion u;
    u.f = f;
    return u.i;
}

int Context::DoubleToInt(double d){
    union DoubleIntUnion {
        int64_t i;
        double d;
    };
    DoubleIntUnion u;
    u.d = d;
    return u.i;
}
