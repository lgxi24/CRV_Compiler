// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

// TODO: you can either continue adding to this grammar file or
// rename parser_full.y to parser.y once you're happy with
// how this example works.

%code requires{
    #include "ast.hpp"

    extern Node *g_root;
    extern FILE *yyin;
    int yylex(void);
    void yyerror(const char *);
    int yylex_destroy(void);
}

// Represents the value associated with any kind of AST node.
%union{
  Node         *node;
  NodeList     *nodes;
  int          number_int;
  double       number_float;
  std::string  *string;
  yytokentype  token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL CHAR_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> external_declaration function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression declaration declaration_specifiers constant_expression
%type <node> init_declarator type_specifier struct_specifier struct_declaration
%type <node> struct_declarator enum_specifier enumerator declarator direct_declarator pointer parameter_declaration
%type <node> type_name abstract_declarator direct_abstract_declarator initializer statement labeled_statement
%type <node> compound_statement expression_statement selection_statement iteration_statement jump_statement

%type <nodes> declarationStatement_list identifier_list initializer_list parameter_list init_declarator_list translation_unit argument_expression_list
%type <nodes> declaration_list parameter_type_list struct_declaration_list specifier_qualifier_list enumerator_list struct_declarator_list

%type <string> unary_operator assignment_operator storage_class_specifier CHAR_LITERAL STRING_LITERAL IDENTIFIER

%type <number_int> INT_CONSTANT
%type <number_float> FLOAT_CONSTANT


%start ROOT
%%

ROOT
    : translation_unit { g_root = $1; }
	;

translation_unit
	: external_declaration 					{ $$ = new NodeList($1); }
	| translation_unit external_declaration {$1->PushBack($2); $$ = $1;}
	;

external_declaration
	: function_definition 	{ $$ = $1; }
	| declaration 			{$$ =$1;}
	;

function_definition
	: declaration_specifiers declarator compound_statement {$$ = new FunctionDefinition($1, $2, $3);}
	| declarator compound_statement
	;

declaration
	: declaration_specifiers ';' 						{$$ = new declaration($1, NULL);}
	| declaration_specifiers init_declarator_list ';'	{$$ = new declaration($1, $2);}
    ;

declaration_specifiers
	: type_specifier 	{ $$ = $1; }
	| type_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator 							{ $$ = new NodeList($1); }
	| init_declarator_list ',' init_declarator 	{ $1->PushBack($3); $$ = $1;}
	;

init_declarator
	: declarator 					{$$ =$1;}
	| declarator '=' initializer 	{ $$ = new initDeclarator ($1,$3); }
    ;

type_specifier
	: INT 		{$$ = new TypeSpecifier("int");}
    | UNSIGNED 	{$$ = new TypeSpecifier("unsigned");}
	| CHAR 		{$$ = new TypeSpecifier("char");}
	| FLOAT 	{$$ = new TypeSpecifier("float");}
	| DOUBLE 	{$$ = new TypeSpecifier("double");}
	| VOID 		{$$ = new TypeSpecifier("void");}
	;

declarator
	: direct_declarator 		{ $$ = $1; }
	| pointer direct_declarator {$$ = new PointerDeclarator($2);}
	;

pointer
	: '*'
	| '*' pointer
	;

direct_declarator
	: IDENTIFIER 									{$$ = new variableDeclarator(*$1); delete $1;}
	| direct_declarator '(' ')' 					{$$ = new FunctionDeclarator($1, NULL);}
	| direct_declarator '(' parameter_list ')'		{$$ = new FunctionDeclarator($1, $3);}
	| direct_declarator '[' constant_expression ']' {$$ = new ArrayDeclarator($1,new NodeList($3));}
	;

parameter_list
	: parameter_declaration						{$$= new NodeList($1);}
	| parameter_list ',' parameter_declaration 	{$1->PushBack($3); $$=$1;}
	;

parameter_declaration
	: declaration_specifiers declarator		{$$ = new declaration($1,  new NodeList($2)); } //similar to variable declaration
	;

identifier_list
	: IDENTIFIER  						{$$ = new NodeList(new Identifier(*$1));}
	| identifier_list ',' IDENTIFIER	{ $1->PushBack(new Identifier(*$3)); $$ = $1;}
	;

initializer
	: assignment_expression	{$$ = $1;}
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: jump_statement 		{ $$ = $1; }
    | expression_statement	{$$ = $1;}
	| compound_statement 	{$$= $1;}
	| selection_statement 	{$$ = $1;}
	| iteration_statement 	{$$ = $1;}
	| labeled_statement 	{$$ = $1;}
	;

labeled_statement
	: CASE constant_expression ':' statement 			{$$ = new CaseStatement($2, $4);}
	| CASE constant_expression ':' statement BREAK ';' 	{$$ = new CaseBreakStatement($2, $4);}
	| DEFAULT ':' statement 							{$$ = new CaseStatement(NULL, $3);}
	;

compound_statement
	: '{' '}'         					{$$ = new compoundStatement(NULL);}
    | '{' declarationStatement_list '}' {$$ = new compoundStatement($2);}
	;

expression_statement
	: ';'				{$$ = NULL;}//do nothing
	| expression ';'	{$$ = $1;}
	;

selection_statement
	: IF '(' expression ')' statement 					{$$ = new IfStatement($3, $5);}
	| IF '(' expression ')' statement ELSE statement 	{$$ = new IfElseStatement($3, $5, $7);}
	| SWITCH '(' expression ')' statement 				{$$ = new SwitchStatement($3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement 											{$$ = new WhileStatement($3, $5);}
	| DO statement WHILE '(' expression ')' ';' 									{$$ = new DoWhileStatement($5, $2);}
	| FOR '(' expression_statement expression_statement ')' statement 				{$$ = new ForStatement($3, $4, NULL, $6);}
	| FOR '(' expression_statement expression_statement expression ')' statement 	{$$ = new ForStatement($3, $4, $5, $7);}
	;

declarationStatement_list
	: statement 							{ $$ = new NodeList($1); }
	| declaration 							{ $$ = new NodeList($1); }
	| declarationStatement_list statement 	{ $1->PushBack($2); $$=$1; }
	| declarationStatement_list declaration { $1->PushBack($2); $$=$1; }
	;

jump_statement
	: RETURN ';' 			{$$ = new ReturnStatement(nullptr);}
	| RETURN expression ';' {$$ = new ReturnStatement($2);}
	| CONTINUE ';' 			{$$ = new ContinueStatement();}
	| BREAK ';' 			{$$ = new BreakStatement();}
	;

primary_expression
	: INT_CONSTANT 							{$$ = new IntConstant($1);}
	| FLOAT_CONSTANT 						{$$ = new FloatConstant($1);}
	| IDENTIFIER  							{$$ = new Identifier(*$1); delete $1;}
	| '(' expression ')' 					{$$ = $2;}
	| STRING_LITERAL						{$$ = new stringConstant(*$1); delete $1;}
	| CHAR_LITERAL							{$$ = new charConstant(*$1); delete $1;}
	;

postfix_expression
	: primary_expression									{$$ = $1;}
	| postfix_expression '(' ')'							{$$ = new functionCall($1, NULL);}
	| postfix_expression INC_OP								{$$ = new postincOperator($1);}
	| postfix_expression DEC_OP								{$$ = new postdecOperator($1);}
	| postfix_expression '(' argument_expression_list ')' 	{$$ = new functionCall($1, $3);}
	| postfix_expression '[' expression ']' 				{ $$ = new arrayIndex($1, new NodeList($3)); }
	;

argument_expression_list
	: assignment_expression {$$ = new NodeList($1);}
	| argument_expression_list ',' assignment_expression {$1->PushBack($3); $$=$1;}
	;

unary_expression
	: postfix_expression				{$$ = $1;}
	| INC_OP unary_expression			{$$ = new preincOperator($2);}
	| DEC_OP unary_expression			{$$ = new predecOperator($2);}
	| '+' cast_expression				{$$ = $2;}
	| '-' cast_expression				{$$ = new negOperator($2);}
	| '!' cast_expression				{$$ = new notOperator($2);}
	| '~' cast_expression				{$$ = new bitwiseNotOperator($2);}
	| SIZEOF unary_expression			{$$ = new sizeofOperator($2);}
	| SIZEOF '(' type_specifier ')'		{$$ = new sizeofTypeOperator($3);}
	| '&' cast_expression				{$$ = new addressOperator($2);}
	| '*' cast_expression				{$$ = new dereferenceOperator($2);}
	;

cast_expression
	: unary_expression{$$ = $1;}
	;

multiplicative_expression
	: cast_expression 								{$$ = $1;}
	| multiplicative_expression '*' cast_expression	{$$ = new mulOperator($1, $3);}
	| multiplicative_expression '/' cast_expression	{$$ = new divOperator($1, $3);}
	| multiplicative_expression '%' cast_expression	{$$ = new modOperator($1, $3);}
	;

additive_expression
	: multiplicative_expression 						{$$ = $1;}
    | additive_expression '+' multiplicative_expression	{$$ = new addOperator($1, $3);}
    | additive_expression '-' multiplicative_expression	{$$ = new subOperator($1, $3);}
	;

shift_expression
	: additive_expression							{$$ = $1;}
    | shift_expression LEFT_OP additive_expression	{$$ = new leftShiftOperator($1, $3);}
    | shift_expression RIGHT_OP additive_expression	{$$ = new rightShiftOperator($1, $3);}
	;

relational_expression
	: shift_expression								{$$ = $1;}
    | relational_expression '<' shift_expression	{$$ = new lessThanOperator($1, $3);}
    | relational_expression '>' shift_expression	{$$ = new greaterThanOperator($1, $3);}
    | relational_expression LE_OP shift_expression	{$$ = new lessEqualOperator($1, $3);}
    | relational_expression GE_OP shift_expression	{$$ = new greaterEqualOperator($1, $3);}
	;

equality_expression
	: relational_expression{$$ = $1;}
    | equality_expression EQ_OP relational_expression{$$ = new equalOperator($1, $3);}
    | equality_expression NE_OP relational_expression{$$ = new notEqualOperator($1, $3);}
	;

and_expression
	: equality_expression{$$ = $1;}
    | and_expression '&' equality_expression{$$ = new andOperator($1, $3);}
	;

exclusive_or_expression
	: and_expression{$$ = $1;}
    | exclusive_or_expression '^' and_expression{$$ = new xorOperator($1, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression{$$ = $1;}
    | inclusive_or_expression '|' exclusive_or_expression{$$ = new orOperator($1, $3);}
	;

logical_and_expression
	: inclusive_or_expression{$$ = $1;}
    | logical_and_expression AND_OP inclusive_or_expression{$$ = new logicalAndOperator($1, $3);}
	;

logical_or_expression
	: logical_and_expression{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression{$$ = new logicalOrOperator($1, $3);}
	;

conditional_expression
	: logical_or_expression{$$ = $1;}
	| logical_or_expression '?' expression ':' conditional_expression {$$ = new ternaryOperator($1, $3,$5);}
	;

assignment_expression
	: conditional_expression								{$$ = $1;}
    | unary_expression '=' assignment_expression 			{$$ = new assignmentOperator($1,$3);}
    | unary_expression MUL_ASSIGN assignment_expression 	{$$ = new mulAssignmentOperator($1, $3);}
    | unary_expression DIV_ASSIGN assignment_expression 	{$$ = new divAssignmentOperator($1, $3);}
    | unary_expression MOD_ASSIGN assignment_expression 	{$$ = new modAssignmentOperator($1, $3);}
    | unary_expression ADD_ASSIGN assignment_expression 	{$$ = new addAssignmentOperator($1, $3);}
    | unary_expression SUB_ASSIGN assignment_expression 	{$$ = new subAssignmentOperator($1, $3);}
    | unary_expression LEFT_ASSIGN assignment_expression 	{$$ = new leftAssignmentOperator($1,$3);}
    | unary_expression RIGHT_ASSIGN assignment_expression 	{$$ = new rightAssignmentOperator($1,$3);}
    | unary_expression AND_ASSIGN assignment_expression 	{$$ = new andAssignmentOperator($1,$3);}
    | unary_expression XOR_ASSIGN assignment_expression 	{$$ = new xorAssignmentOperator($1,$3);}
    | unary_expression OR_ASSIGN assignment_expression 		{$$ = new orAssignmentOperator($1,$3);}
	;

expression
	: assignment_expression {$$ = $1;}
	;

constant_expression
	: conditional_expression	{$$ = $1;}
	;


%%

Node *g_root;

Node *ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  fclose(yyin);
  yylex_destroy();
  return g_root;
}
