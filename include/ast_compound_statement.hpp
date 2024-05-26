#ifndef ast_compound_statement_hpp
#define ast_compound_statement_hpp
#include "ast_node.hpp"

#include <cmath>
#include <string>

class compoundStatement
    : public Node
{
private:
protected:
    NodeList* list;
public:
    compoundStatement(
        NodeList* _statement_list)
        :list(_statement_list)
    {}
    virtual ~compoundStatement()
    {
        if (list != NULL){
            delete list;
        }
    }
    virtual int getSize(Context &context)const override;
    // virtual std::string getIdentifier() const override;
    virtual void Print(std::ostream &stream) const override;
    virtual void EmitRISC(std::ostream &stream, Context &context, int destRegister) const override;
    virtual std::string  getIdentifier()const override;

};


#endif
