#ifndef AST_TERNARY_OPERATION
#define AST_TERNARY_OPERATION

#include "ast_node.hpp"
#include <cmath>
#include <string>

class ternaryOperator
    :public Node
{
    private:
    protected:
        Node* condition;
        Node* conditionTrue;
        Node* conditionFalse;
    public:
        ternaryOperator(Node* condition, Node* conditionTrue, Node* conditionFlase) : condition(condition),conditionTrue(conditionTrue),conditionFalse{conditionFalse}
        {}
        virtual ~ternaryOperator();

        virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
        // virtual const std::string getOpcode() const =0;

        virtual void Print(std::ostream &stream) const override;
        // virtual int doCondition(std::ostream &stream, Context &context,int destRegister)const;
        // virtual int doConditionTrue(std::ostream &stream, Context &context, int destRegister)const;
        // virtual int doConditionFalse(std::ostream &stream, Context &context, int destRegister)const;
        virtual int getSize(Context &context) const override
        {
            return 0; //only declarations have memory declared
        };
        virtual std::string getIdentifier() const override;
};

#endif
