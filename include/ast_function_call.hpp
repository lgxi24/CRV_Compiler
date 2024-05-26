#ifndef ast_functioncall_hpp
#define ast_functioncall_hpp

#include "ast_node.hpp"

#include <cmath>
#include <string>


class functionCall
    : public Node
{
    private:

    protected:
        Node * identifier;
        NodeList* arguments;

    public:
        functionCall(Node *identifier,NodeList* arguments ): identifier(identifier), arguments(arguments) {}
        virtual ~functionCall()
        {
            delete identifier;
            delete arguments;
        }
        virtual std::string getIdentifier() const override;
        virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;

        virtual void Print(std::ostream &stream) const override;

        int getSize(Context &context) const override
        {
            std::cerr<<"function Call size 0 ";
            return 0;
        }
};


#endif

