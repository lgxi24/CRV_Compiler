#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <string>
#include <vector>

// #include "ast_direct_declarator.hpp"
#include "ast_function_definition.hpp"
#include "ast_primary_expression.hpp"
#include "ast_jump_statement.hpp"
#include "ast_node.hpp"
#include "ast_type_specifier.hpp"
#include "ast_context.hpp"
#include "ast_binary_operation.hpp"
#include "ast_declaration.hpp"
#include "ast_compound_statement.hpp"
// #include "ast_variable_declarator.hpp"
#include "ast_function_call.hpp"
#include "ast_selection_statement.hpp"
#include "ast_iteration_statement.hpp"
#include "ast_unary_operation.hpp"
#include "ast_array.hpp"
#include "ast_pointer.hpp"
#include "ast_switch.hpp"
#include "ast_ternary_operation.hpp"
extern Node *ParseAST(std::string file_name);

#endif
