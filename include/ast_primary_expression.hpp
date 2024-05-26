#ifndef AST_PRIMARY_EXPRESSION_HPP
#define AST_PRIMARY_EXPRESSION_HPP

#include "ast_node.hpp"
#include <iostream>


class Identifier : public Node
{
private:
    std::string identifier_;

public:
    Identifier(std::string identifier) : identifier_(identifier){};
    ~Identifier(){};
    void EmitRISC(std::ostream &stream, Context &context,int destRegister) const override;
    void Print(std::ostream &stream) const override;
    std::string getIdentifier()const override{return identifier_;}
    void leftCompile(std::ostream &stream, Context &context,int destRegister) const override;
    int getSize(Context &context) const override
    {
        return 0;
    }
    virtual bool isPointer(Context &context) override;

};

class IntConstant : public Node
{
private:
protected:
public:
    int value;

    IntConstant(int value) : value(value) {std::cerr<<"int constant"<<std::endl;}

    void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    void Print(std::ostream &stream) const override;
    int getSize(Context &context) const {return 0;}
    std::string getIdentifier()const override{
        std::cerr<<"Error: Getting Id, of int immediate";
        exit(1);
    }
    int getValue(Context &context)override {
        return value;
    }
};

class FloatConstant : public Node
{
private:
    float value_;
public:
    FloatConstant(float value) : value_(value) {}

    void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    void Print(std::ostream &stream) const override;
    int getSize(Context &context) const {return 0;}
    std::string getIdentifier()const override{
        std::cerr<<"Error: Getting Id, of float immediate";
        exit(1);
    }
};

// class DoubleConstant : public Node
// {
// private:
//     double value_;
// public:
//     DoubleConstant(double value) : value_(value) {}

//     void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
//     void Print(std::ostream &stream) const override;
//     int getSize(Context &context) const {return 0;}
//     std::string getIdentifier()const override{
//         std::cerr<<"Error: Getting Id, of double immediate";
//         exit(1);
//     }
// };

class stringConstant
    : public Node
{
private:
protected:
public:
    std::string val;
    stringConstant(std::string _val)
        :val(_val)
    {
        std::cerr<<"string constant"<<std::endl;
        val = val.substr(1, val.size()-2);
    }
    virtual std::string getIdentifier()const override;
    virtual int getSize(Context &context)const override
    {
        return 0;
    }
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister)const override;
    virtual void Print(std::ostream &stream)const override;
    virtual int getValue(Context &context) override;

};

class charConstant
    : public Node
{
private:
protected:
public:
    std::string val;
    charConstant(std::string _val)
        :val(_val)
    {
        std::cerr<<"char constant"<<std::endl;
        val = val.substr(1, val.size()-2);
    }
    virtual std::string getIdentifier()const override;
    int getSize(Context &context)const override{
        return 0;
    }
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister)const override;
    virtual void Print(std::ostream &stream)const override;
    virtual int getValue(Context &context) override;

};

#endif
