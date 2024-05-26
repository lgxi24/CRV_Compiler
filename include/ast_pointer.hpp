#ifndef AST_POINTER_HPP
#define AST_POINTER_HPP

#include"ast_node.hpp"
#include <cmath>
#include <string>

class PointerDeclarator
    :public Node
{
    private:
    protected:
        Node* declarator;
    public:
        PointerDeclarator(Node* _declarator): declarator(_declarator){};
        ~PointerDeclarator()
        {
            delete declarator;
        };
        virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual std::string getIdentifier() const override;
        virtual int getSize(Context &context) const override;
        // virtual int getValue(Context &context) override;
        virtual bool isPointer(Context &context) override;
};

#endif
