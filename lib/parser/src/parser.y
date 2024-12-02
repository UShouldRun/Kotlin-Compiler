%{
#include "arena.h"
#include "ast.h"
#include "parser.tab.h"

extern const char* filename;

extern AST   ast;
extern Arena arena;

extern int yylex(YYSTYPE* yylval, YYLTYPE* yylloc);
void yyerror(YYLTYPE* yylloc, const char* error_msg);
%}

%define api.pure full
%define parse.error verbose
%locations

%code requires {
  #include "ast.h"
}

%union {
  int64_t       num;
  double        real;
  const char*   str;
  AST           root;
  ASTN_Obj      obj;
  ASTN_EnumVal  enum_values;
  ASTN_FunArg   fun_args;
  ASTN_FunRet   fun_ret;
  ASTN_Stmt     stmt;
  ASTN_Expr     expr;
  ASTN_ExprList expr_list;
  ASTN_Token    token;
  ASTN_KType    ktype;
  ASTN_KTypeDefault ktype_default;
}

%type <root>        kotlin_input
%type <obj>         kotlin_program
%type <enum_values> kotlin_enum_block
%type <fun_args>    kotlin_fun_params
%type <fun_args>    kotlin_parameter_list
%type <fun_ret>     kotlin_return_type
%type <fun_ret>     kotlin_return_type_list 
%type <stmt>        kotlin_stmt
%type <stmt>        kotlin_stmt_var
%type <stmt>        kotlin_while
%type <stmt>        kotlin_do
%type <stmt>        kotlin_for
%type <stmt>        kotlin_for_init
%type <stmt>        kotlin_for_incr
%type <stmt>        kotlin_if
%type <stmt>        kotlin_elseif_else
%type <stmt>        kotlin_when
%type <stmt>        kotlin_when_branch
%type <stmt>        kotlin_return
%type <expr>        kotlin_expression
%type <expr>        kotlin_fun_call
%type <expr_list>   kotlin_expression_list
%type <token>       kotlin_token
%type <token>       kotlin_identifier
%type <token>       kotlin_number
%type <ktype>       kotlin_type
%type <ktype_default> kotlin_type_default

%token TT_IDENTIFIER TT_VAR TT_VAL TT_STRING_LIT TT_NUMBER TT_REAL TT_TRUE TT_FALSE
%token TT_BYTE TT_SHORT TT_INT TT_LONG TT_FLOAT TT_DOUBLE TT_BOOLEAN TT_CHAR TT_STRING TT_ANY
%token TT_INCR TT_DECR TT_EQUALS_PLUS TT_EQUALS_MINUS TT_EQUALS_MUL TT_EQUALS_DIV
%token TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE TT_LPARENRECT TT_RPARENRECT TT_SEMICOLON TT_COLON TT_COMMA TT_ASSIGN TT_ARROW TT_DOT
%token TT_IF TT_ELSE TT_ELSEIF TT_WHEN TT_WHILE TT_FOR TT_IN TT_DO TT_FUN TT_RETURN  TT_NULL TT_ENUM

%left TT_EQUALS TT_NOT_EQUALS TT_LTHAN TT_GTHAN TT_LEQUALS TT_GEQUALS TT_AND TT_OR
%left TT_PLUS TT_MINUS
%left TT_STAR TT_SLASH
%right TT_BANG

/*    
    | TT_FOR TT_LPAREN kotlin_type kotlin_identifier TT_IN kotlin_identifier TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_for(arena, $3, $5, $7, $10, $12); }
  ;

    | TT_IF TT_LPAREN kotlin_expression TT_RPAREN kotlin_stmt kotlin_elseif_else kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, $6, $8, $9); }
    | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN kotlin_stmt kotlin_elseif_else
    | TT_ELSE kotlin_stmt

    | kotlin_expression TT_ARROW kotlin_stmt TT_SEMICOLON
    | TT_ELSE TT_ARROW kotlin_stmt TT_SEMICOLON
*/

%%

kotlin_input:
    kotlin_program
    { ast = ast_create(arena, filename, $1); }
  ;

kotlin_program:
    TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program
    { $$ = astn_create_fun(arena, $2, $3, $5, $7, $9); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_SEMICOLON kotlin_program
    { $$ = astn_create_fun(arena, $2, $3, $5, NULL, $7); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program
    { $$ = astn_create_fun(arena, $2, $3, NULL, $5, $7); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON kotlin_program
    { $$ = astn_create_fun(arena, $2, $3, NULL, NULL, $5); }
  | TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE kotlin_program
    { $$ = astn_create_enum(arena, $2, $4, $6); }

  | TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE 
    { $$ = astn_create_fun(arena, $2, $3, $5, $7, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_COLON kotlin_return_type TT_SEMICOLON 
    { $$ = astn_create_fun(arena, $2, $3, $5, NULL, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_fun(arena, $2, $3, NULL, $5, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON
    { $$ = astn_create_fun(arena, $2, $3, NULL, NULL, NULL); }
  | TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE 
    { $$ = astn_create_enum(arena, $2, $4, NULL); }
  ;

kotlin_enum_block:
    kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN TT_COMMA kotlin_enum_block
    { $$ = astn_create_enum_val(arena, $1, $3, true, $6); }
  | kotlin_identifier TT_COMMA kotlin_enum_block
    { $$ = astn_create_enum_val(arena, $1, 0, false, $3); }
  | kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN
    { $$ = astn_create_enum_val(arena, $1, $3, true, NULL); }
  | kotlin_identifier
    { $$ = astn_create_enum_val(arena, $1, 0, false, NULL); }
  ;

kotlin_fun_params:
    TT_LPAREN kotlin_parameter_list TT_RPAREN
    { $$ = $2; }
  | TT_LPAREN TT_RPAREN
    { $$ = NULL; }
  ;

kotlin_parameter_list:
    kotlin_identifier TT_COLON kotlin_type TT_COMMA kotlin_parameter_list
    { $$ = astn_create_fun_args(arena, $3, $1, $5); }
  | kotlin_identifier TT_COLON kotlin_type
    { $$ = astn_create_fun_args(arena, $3, $1, NULL); }
  ;

kotlin_return_type:
    TT_LPAREN kotlin_return_type_list TT_RPAREN 
    { $$ = $2; }
  | TT_LPAREN TT_RPAREN
    { $$ = NULL; }
  | kotlin_type
    { $$ = astn_create_fun_ret(arena, $1, NULL); }
  ;

kotlin_return_type_list:
    kotlin_type TT_COMMA kotlin_return_type_list
    { $$ = astn_create_fun_ret(arena, $1, $3); }
  | kotlin_type
    { $$ = astn_create_fun_ret(arena, $1, NULL); }
  ;

kotlin_type:
    kotlin_type_default
    { $$ = astn_create_ktype(arena, true, $1, NULL); }
  | kotlin_identifier
    { $$ = astn_create_ktype(arena, false, KOTLIN_NOT_DEFAULT, $1); }
  ;

kotlin_type_default:
    TT_BYTE     { $$ = KOTLIN_BYTE; }
  | TT_SHORT    { $$ = KOTLIN_SHORT; }
  | TT_INT      { $$ = KOTLIN_INT; }
  | TT_LONG     { $$ = KOTLIN_LONG; }
  | TT_FLOAT    { $$ = KOTLIN_FLOAT; }
  | TT_DOUBLE   { $$ = KOTLIN_DOUBLE; }
  | TT_BOOLEAN  { $$ = KOTLIN_BOOLEAN; }
  | TT_CHAR     { $$ = KOTLIN_CHAR; }
  | TT_STRING   { $$ = KOTLIN_STRING; }
  | TT_ANY      { $$ = KOTLIN_ANY; }
  ;

kotlin_stmt:
    kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON kotlin_stmt 
    { $$ = astn_create_stmt_fcall(arena, $1, $3, $6); }
  | kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON 
    { $$ = astn_create_stmt_fcall(arena, $1, $3, NULL); }
  | kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt 
    { $$ = astn_create_stmt_fcall(arena, $1, NULL, $5); }
  | kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON 
    { $$ = astn_create_stmt_fcall(arena, $1, NULL, NULL); }
  | TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_block(arena, $2, $4); }
  | TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_block(arena, $2, NULL); }
  | kotlin_stmt_var
    { $$ = $1; }
  | kotlin_while
    { $$ = $1; }
  | kotlin_for
    { $$ = $1; }
  | kotlin_do
    { $$ = $1; }
  | kotlin_if
    { $$ = $1; }
  | kotlin_when
    { $$ = $1; }
  | kotlin_return
    { $$ = $1; } 
  ;

kotlin_stmt_var:
    TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, $8); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, $6); }
  | kotlin_identifier TT_ASSIGN       kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_INCR                                                 TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, NULL, $4); }
  | kotlin_identifier TT_DECR                                                 TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, NULL, $4); }
  | TT_INCR kotlin_identifier                                                 TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $2, KOTLIN_DECL, NULL, $4); }
  | TT_DECR kotlin_identifier                                                 TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $2, KOTLIN_DECL, NULL, $4); }

  | TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, NULL); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, NULL); }
  | kotlin_identifier TT_ASSIGN       kotlin_expression                       TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_INCR                                                 TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, NULL, NULL); }
  | kotlin_identifier TT_DECR                                                 TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, NULL, NULL); }
  | TT_INCR kotlin_identifier                                                 TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $2, KOTLIN_DECL, NULL, NULL); }
  | TT_DECR kotlin_identifier                                                 TT_SEMICOLON 
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $2, KOTLIN_DECL, NULL, NULL); }
  ;

kotlin_while:
    TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_while(arena, false, $3, $6, $8); }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_while(arena, false, NULL, $5, $7); }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$ = $7; }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$ = $6; }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE 
    { $$ = astn_create_stmt_while(arena, false, $3, $6, NULL); }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_while(arena, false, NULL, $5, NULL); }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  ;

kotlin_do:
    TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_while(arena, true, $7, $3, $10); }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = $9; }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = $8; }
  | TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON
    { $$ = astn_create_stmt_while(arena, true, $7, $3, NULL); }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON
    { $$ = NULL; }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON
    { $$ = NULL; }
  ;

kotlin_for:
    TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt 
    TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_for(arena, $3, $5, $7, $10, $12); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_for(arena, NULL, $4, $6, $9, $11); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_for(arena, NULL, $4, NULL, $8, $10); }
  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_for(arena, $3, $5, $7, NULL, $10); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = astn_create_stmt_for(arena, NULL, $4, $6, NULL, $9); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = $8; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$ = $8; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$ = $7; }

  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_for(arena, $3, $5, $7, $10, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_for(arena, NULL, $4, $6, $9, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_for(arena, NULL, $4, NULL, $8, NULL); }
  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON
    { $$ = astn_create_stmt_for(arena, $3, $5, $7, NULL, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON
    { $$ = astn_create_stmt_for(arena, NULL, $4, $6, NULL, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON
    { $$ = NULL; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON
    { $$ = NULL; }
  ;

kotlin_for_init:
    TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_COMMA kotlin_for_init
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, $8); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_COMMA kotlin_for_init
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, $6); }
  | kotlin_for_incr
    { $$ = $1; }
  ;

kotlin_for_incr:
    kotlin_identifier TT_ASSIGN       kotlin_expression                      TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_INCR                                                 TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, NULL, $4); }
  | kotlin_identifier TT_DECR                                                 TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, NULL, $4); }
  | TT_INCR kotlin_identifier                                                 TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $2, KOTLIN_DECL, NULL, $4); }
  | TT_DECR kotlin_identifier                                                 TT_COMMA kotlin_for_incr
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $2, KOTLIN_DECL, NULL, $4); }

  | TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, NULL); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, NULL); }
  |  kotlin_identifier TT_ASSIGN      kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_INCR
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, NULL, NULL); }
  | kotlin_identifier TT_DECR
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, NULL, NULL); }
  | TT_INCR kotlin_identifier
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $2, KOTLIN_DECL, NULL, NULL); }
  | TT_DECR kotlin_identifier
    { $$ = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $2, KOTLIN_DECL, NULL, NULL); }
  ;

kotlin_if:
    TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, $6, $8, $9); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, $6, NULL, $8); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, NULL, $7, $8); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$ = $7; }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, $5, $7, $8); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, $5, NULL, $7); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, NULL, $6, $7); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$ = $6; }

  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, $6, $8, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, $6, NULL, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_IF, $3, NULL, $7, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, $5, $7, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, $5, NULL, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_IF, NULL, NULL, $6, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  ;

kotlin_elseif_else:
    TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, $3, $6, $8, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, NULL, $5, $7, NULL); }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, $3, NULL, $7, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$ = $6; }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, $3, $6, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, NULL, $5, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_ELSEIF, $3, NULL, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  | TT_ELSE TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_ELSE, NULL, $3, NULL, NULL); }
  | TT_ELSE TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  ;

kotlin_when:
    TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE kotlin_stmt
    { $$ = astn_create_stmt_when(arena, $3, $6, $8); }
  | TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE
    { $$ = astn_create_stmt_when(arena, $3, $6, NULL); }
  ;

kotlin_when_branch:
    kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch
    { $$ = astn_create_stmt_if(arena, STMT_CASE, $1, $4, $6, NULL); }
  | kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch
    { $$ = $5; }
  | kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_CASE, $1, $4, NULL, NULL); }
  | kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  | TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch
    { $$ = astn_create_stmt_if(arena, STMT_ELSE, NULL, $4, $6, NULL); }
  | TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE
    { $$ = astn_create_stmt_if(arena, STMT_ELSE, NULL, $4, NULL, NULL); }
  | TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch
    { $$ = $5; }
  | TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE
    { $$ = NULL; }
  ;

kotlin_return:
      TT_RETURN kotlin_expression_list TT_SEMICOLON
      { $$ = astn_create_stmt_ret(arena, $2); }
    | TT_RETURN TT_SEMICOLON
      { $$ = astn_create_stmt_ret(arena, NULL); }
    ;

kotlin_expression:
      kotlin_expression TT_PLUS       kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_ARIT_PLUS, $1, $3); }
    | kotlin_expression TT_MINUS      kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_ARIT_MINUS, $1, $3); }
    | kotlin_expression TT_STAR       kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_ARIT_MUL, $1, $3); }
    | kotlin_expression TT_SLASH      kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_ARIT_DIV, $1, $3); }

    | kotlin_expression TT_EQUALS     kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_EQUAL, $1, $3); }
    | kotlin_expression TT_NOT_EQUALS kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_NEQUAL, $1, $3); }
    | kotlin_expression TT_LEQUALS    kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_LEQUAL, $1, $3); }
    | kotlin_expression TT_GEQUALS    kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_GEQUAL, $1, $3); }
    | kotlin_expression TT_LTHAN      kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_LTHAN, $1, $3); }
    | kotlin_expression TT_GTHAN      kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_COMP_GTHAN, $1, $3); }

    | kotlin_expression TT_AND        kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_LOG_AND, $1, $3); }
    | kotlin_expression TT_OR         kotlin_expression
      { $$ = astn_create_expr_bin(arena, OP_BIN_LOG_OR, $1, $3); }

    | TT_BANG  kotlin_expression
      { $$ = astn_create_expr_un(arena, OP_UN_LOG_NOT, $2); }

    | TT_PLUS  kotlin_expression
      { $$ = astn_create_expr_un(arena, OP_UN_ARIT_PLUS, $2); }
    | TT_MINUS kotlin_expression
      { $$ = astn_create_expr_un(arena, OP_UN_ARIT_MINUS, $2); }

    | TT_LPAREN kotlin_expression TT_RPAREN
      { $$ = astn_create_expr_un(arena, OP_UN_PAREN, $2); }

    | kotlin_fun_call
      { $$ = $1; }
    
    | kotlin_token
      { $$ = astn_create_expr_token(arena, $1); }
    ;

kotlin_token:
      TT_TRUE
      { $$ = astn_create_token(arena, TT_LIT_TRUE, NULL, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | TT_FALSE
      { $$ = astn_create_token(arena, TT_LIT_FALSE, NULL, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | TT_NULL
      { $$ = astn_create_token(arena, TT_LIT_NULL, NULL, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); } 
    | TT_STRING_LIT
      { $$ = astn_create_token(arena, TT_LIT_STRING, (void*)yylval.str, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | TT_REAL
      { $$ = astn_create_token(arena, TT_LIT_REAL, (void*)&yylval.real, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | kotlin_number
      { $$ = $1; }
    | kotlin_identifier
      { $$ = $1; }
    ;

kotlin_number:
      TT_NUMBER
      { $$ = astn_create_token(arena, TT_LIT_NUMBER, (void*)&yylval.num, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    ;

kotlin_identifier:
      TT_IDENTIFIER
      { $$ = astn_create_token(arena, TT_IDENT, (void*)yylval.str, filename, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    ;

kotlin_fun_call:
      kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN  
      { $$ = astn_create_expr_fcall(arena, $1, $3); }
    | kotlin_identifier TT_LPAREN TT_RPAREN  
      { $$ = astn_create_expr_fcall(arena, $1, NULL); }
    ;

kotlin_expression_list:
      kotlin_expression TT_COMMA kotlin_expression_list
      { $$ = astn_create_expr_list(arena, $1, $3); }
    | kotlin_expression                               
      { $$ = astn_create_expr_list(arena, $1, NULL); }
    ;

%%

void yyerror(YYLTYPE* yylloc, const char* error_msg) {
  error_assert(error_unexp, yylloc != NULL);

  _error_print(error_parser, error_msg, filename, yylloc->first_line, yylloc->first_column);
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, ERROR_IO_SOURCE_FILE, filename);
    return;
  }
  char line[1024];
  for (
    int current_line = 1;
    fgets(line, sizeof(line), file) && current_line != yylloc->first_line;
    current_line++
  );
  fclose(file);

  fprintf(stderr, "%s", line);
  for (int i = 1; i < yylloc->first_column; i++)
    fprintf(stderr, " ");
  fprintf(stderr, "^\n");
}
