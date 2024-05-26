#ifndef AST_DECLATION
#define AST_DECLATION

#include "ast_node.hpp"
#include <cmath>
#include <string>


class declaration
    : public Node
{
    private:
    protected:
        Node* declaration_specifier;
    public:
        NodeList* list;
        declaration (Node* declaration_specifier, NodeList* list):  declaration_specifier(declaration_specifier), list(list){}
        virtual ~declaration(){
            if (declaration_specifier !=nullptr){
                delete declaration_specifier;
            }
            if(list !=nullptr){
                delete list;
            }

        };

        virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
        virtual void Print(std::ostream &stream) const override;
        virtual int getSize(Context &context) const override;

};

class initDeclarator: public Node{
    public:
        Node* declarator;
        Node* initializer;
        initDeclarator (Node* declarator, Node* initializer):  declarator(declarator), initializer(initializer){}
        virtual ~initDeclarator(){
            if (declarator !=nullptr){
                delete declarator;
            }
            if(initializer !=nullptr){
                delete initializer;
            }


        };
        virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
        std::string getIdentifier() const override{ return declarator->getIdentifier(); }
        virtual void Print(std::ostream &stream) const override;
        int getSize(Context &context) const {return declarator->getSize(context);}
        virtual bool isPointer(Context &context) override;

};

class variableDeclarator
    : public Node
{
private:
protected:
public:
    std::string identifier;
    variableDeclarator(std::string identifier):identifier(identifier){}

    virtual void Print(std::ostream &stream)const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const;
    virtual std::string getIdentifier()const override;
    virtual int getSize(Context &context)const override;
};



#endif

