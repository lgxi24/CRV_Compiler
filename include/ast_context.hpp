#ifndef AST_CONTEXT_HPP
#define AST_CONTEXT_HPP

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <cassert>
#include <utility>
#include <unordered_map>

struct RegStatus {
    bool isInUse;
};

class Registers
{
private:
    std::unordered_map<int, RegStatus> intRegs;
    std::unordered_map<int, RegStatus> floatRegs;
    int intRegSize;
    int floatRegSize;

public:
    Registers(int intRegSize = 32, int floatRegSize = 32) : intRegSize(intRegSize), floatRegSize(floatRegSize)
    {
        // integer register
        intRegs[0] = {true}; // x0 (zero)
        intRegs[1] = {true}; // ra (return address)
        intRegs[2] = {true}; // sp (stack pointer)
        intRegs[3] = {true}; // gp (global pointer)
        intRegs[4] = {true}; // tp (thread pointer)
        intRegs[5] = {true}; // t0 (temporary registers)
        for (int i = 6; i < 8; i++) { // t1-t2 (temporary registers)
            intRegs[i] = {true};
        }

        intRegs[8] = {true}; // s0/fp (callee-saved registers/ frame pointer)
        intRegs[9] = {true};// s1 (callee-saved registers)

        for (int i = 10; i < 18; i++) { // a0-a7 (argument registers)
            intRegs[i] = {true};
        }

        for (int i = 18; i < 28; i++) { // s2-s11 (callee-saved registers)
            intRegs[i] = {false};
        }

        for (int i = 29; i < 32; i++) { // t3-t6 (temporary registers)
            intRegs[i] = {true};
        }

        // floating-point register
        for (int i=0; i<5; i++) { // ft0-ft4 (temporary registers)
            floatRegs[i]={true};
        }
        floatRegs[5] = {false}; // ft5 (temporary registers)
        floatRegs[6] = {false}; // ft6 (temporary registers)
        floatRegs[7] = {false}; // ft7 (temporary registers)
        floatRegs[8] = {false}; // fs0 (callee-saved registers)
        floatRegs[9] = {false}; // fs1 (callee-saved registers)

        for (int i=10; i<18; i++) { // fa0-fa7 (argument registers)
            floatRegs[i]={true};
        }

        for (int i=18; i<28; i++) { // fs2-fs11 (callee-saved registers)
            floatRegs[i]={false};
        }

        for (int i=28; i<32; i++) { // ft8-ft11 (temporary registers)
            floatRegs[i]={true};
        }

    }

    virtual void useReg(int index);
    std::string type = "int";
    virtual void freeReg(int index);
    virtual int allocate();
};

struct variable{
    int size; // total size of mem needed
    int offset; // offset in memory
    int arraySize; // give size if its an array
    int pointer; // 0 for not pointer, 1 for pointer
};
struct function{
    int size; //store the size of the parameter that is larger than argument register number.
    std::vector<int> parameterOffset; // stores offset of the more than 8 params(positive offset)
};

struct symbolTable{
    std::map<std::string, variable> variableBindings; // available variables in symbolTable
    int offset = -52; // next last declared from fp/s0 -s11.
    // 12* -4 for s11, -4 for ra
    int layer = 0;    //used for repeated definition in sub-symbolTable, how many layer to recover when exiting symbolTable
    std::string returnLabel = "undefined"; // return label
    std::string startLabel = "undefined";  // continue label
    std::string endLabel = "undefined";    // break label
};

class Context
{
public:
    std::vector<symbolTable> local; //stores local variables

    symbolTable global;  //global declarations

    std::map<std::string, function> functions;

    Registers RegisterFile;

    std::map<std::string, int> label; // id and its corresponding labels, may more than 1

    virtual void enterSymbolTable();
    virtual void exitSymbolTable();

    virtual std::string Labeling(std::string id);

    int FloatToInt(float f);
    int DoubleToInt(double d);

};

#endif
