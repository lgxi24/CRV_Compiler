#ifndef ast_array_hpp
#define ast_array_hpp

#include "ast_node.hpp"

class ArrayDeclarator
  : public Node
{

private:
protected:
    Node* declarator;
public:
    NodeList* size;

    ArrayDeclarator(Node* declarator, NodeList* size):declarator(declarator), size(size){}
    virtual ~ArrayDeclarator(){
        if(declarator!=NULL){
            delete declarator;
        }
        if(size!=NULL){
            delete size;
        }
    };

  virtual std::string getIdentifier() const override;
  virtual int getSize(Context &context) const override;
  virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
  virtual void Print(std::ostream &stream) const override;

};

class arrayIndex
  : public Node
{
private:
protected:
    Node*  identifier;
public:
    NodeList* index;
    // Constructors
    arrayIndex(Node* identifier, NodeList* index): identifier(identifier),index(index){}

    // Destructor
    virtual ~arrayIndex(){
        if(identifier !=NULL){
            delete identifier;
        }
        if(index !=NULL){
            delete index;
        }
    };

    // Visualising
    virtual std::string getIdentifier() const override;
    virtual int getSize(Context& context) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual void leftCompile(std::ostream &stream, Context &context, int destRegister) const override;
    virtual void Print(std::ostream &stream) const override;
};
#endif
