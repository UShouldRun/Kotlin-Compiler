%{
#include "arena.h"
#include "ast.h"
#include "parser.tab.h"

extern const char* filename;
void yyerror(YYLTYPE* yylloc, AST* ast, const char* error_msg);
%}

%define api.pure full
%define parse.error verbose
%locations

%parse-param { AST* ast, Arena arena }

%union {
  int         num;
  double      real;
  const char* str;
  AST           program;
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

%type <program>     kotlin_input
%type <obj>         kotlin_program
%type <obj>         kotlin_main
%type <enum_values> kotlin_enum_block
%type <fun_args>    kotlin_fun_params
%type <fun_args>    kotlin_parameter_list
%type <fun_ret>     kotlin_return_type
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

%token TT_IDENTIFIER TT_VAR TT_VAL TT_STRING_LIT TT_NUMBER TT_REAL TT_TRUE TT_FALSE TT_MAIN
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
    kotlin_program kotlin_main
    { *ast = ast_create(arena, filename, $1.obj, $2.obj); }
  | kotlin_main
    { *ast = ast_create(arena, filename, NULL, $1.obj); }
  ;

kotlin_program:
    TT_FUN kotlin_identifier kotlin_fun_params kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, $4.fun_ret, $6.stmt, $8.obj); }
  | TT_FUN kotlin_identifier kotlin_fun_params kotlin_return_type TT_SEMICOLON kotlin_program
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, $4.fun_ret, NULL, $6.obj); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE kotlin_program
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, NULL, $5.stmt, $7.obj); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON kotlin_program
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, NULL, NULL, $5.obj); }
  | TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE kotlin_program
    { $$.obj = astn_create_enum(arena, $2.token, $4.enum_values, $6.obj); }

  | TT_FUN kotlin_identifier kotlin_fun_params kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE 
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, $4.fun_ret, $6.stmt, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params kotlin_return_type TT_SEMICOLON 
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, $4.fun_ret, NULL, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, NULL, $5.stmt, NULL); }
  | TT_FUN kotlin_identifier kotlin_fun_params TT_SEMICOLON
    { $$.obj = astn_create_fun(arena, $2.token, $3.fun_args, NULL, NULL, NULL); }
  | TT_ENUM kotlin_identifier TT_LBRACE kotlin_enum_block TT_RBRACE 
    { $$.obj = astn_create_enum(arena, $2.token, $4.enum_values, NULL); }
  ;

kotlin_main:
    TT_FUN TT_MAIN kotlin_fun_params kotlin_return_type TT_LBRACE kotlin_stmt TT_RBRACE
    { 
      $$.obj = astn_create_fun(
            arena, astn_create_token(arena, TT_IDENT, NULL, "main", file, yylloc.first_line, yylloc.first_column, yylloc.last_column),
            $3.fun_args, $4.fun_ret, $6.stmt, NULL
          ); 
    }
  | TT_FUN TT_MAIN kotlin_fun_params TT_LBRACE kotlin_stmt TT_RBRACE
    { 
      $$.obj = astn_create_fun(
            arena, astn_create_token(arena, TT_IDENT, NULL, "main", file, yylloc.first_line, yylloc.first_column, yylloc.last_column),
            $3.fun_args, NULL, $5.stmt, NULL
          ); 
    }
  ;

kotlin_enum_block:
    kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN TT_COMMA kotlin_enum_block
    { $$.enum_values = astn_create_enum_val(arena, $1.token, $3.token, true, $6.enum_values); }
  | kotlin_identifier TT_COMMA kotlin_enum_block
    { $$.enum_values = astn_create_enum_val(arena, $1.token, 0, false, $3.enum_values); }
  | kotlin_identifier TT_LPAREN kotlin_number TT_RPAREN
    { $$.enum_values = astn_create_enum_val(arena, $1.token, $3.token, true, NULL); }
  | kotlin_identifier
    { $$.enum_values = astn_create_enum_val(arena, $1.token, 0, false, NULL); }
  ;

kotlin_fun_params:
    TT_LPAREN kotlin_parameter_list TT_RPAREN
    { $$.fun_args = $2.fun_args; }
  | TT_LPAREN TT_RPAREN
    { $$.fun_args = NULL; }
  ;

kotlin_parameter_list:
    kotlin_identifier TT_COLON kotlin_type TT_COMMA kotlin_parameter_list
    { $$.fun_args = astn_create_fun_args(arena, $1.token, $3.ktype, $5.fun_args); }
  | kotlin_identifier TT_COLON kotlin_type
    { $$.fun_args = astn_create_fun_args(arena, $1.token, $3.ktype, NULL); }
  ;

kotlin_return_type:
    kotlin_type TT_COMMA kotlin_return_type
    { $$.fun_ret = astn_create_fun_ret(arena, $1.ktype, $3.fun_ret); }
  | kotlin_type
    { $$.fun_ret = astn_create_fun_ret(arena, $1.ktype, NULL); }
  ;

kotlin_type:
    kotlin_type_default
    { $$.ktype = astn_create_ktype(arena, true, $1, NULL); }
  | kotlin_identifier
    { $$.ktype = astn_create_ktype(arena, true, NULL, $1); }
  ;

kotlin_type_default:
    TT_BYTE     { $$.ktype_default = KOTLIN_BYTE; }
  | TT_SHORT    { $$.ktype_default = KOTLIN_SHORT; }
  | TT_INT      { $$.ktype_default = KOTLIN_INT; }
  | TT_LONG     { $$.ktype_default = KOTLIN_LONG; }
  | TT_FLOAT    { $$.ktype_default = KOTLIN_FLOAT; }
  | TT_DOUBLE   { $$.ktype_default = KOTLIN_DOUBLE; }
  | TT_BOOLEAN  { $$.ktype_default = KOTLIN_BOOLEAN; }
  | TT_CHAR     { $$.ktype_default = KOTLIN_CHAR; }
  | TT_STRING   { $$.ktype_default = KOTLIN_STRING; }
  | TT_ANY      { $$.ktype_default = KOTLIN_ANY; }
  ;

kotlin_stmt:
    kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON kotlin_stmt 
    { $$.stmt = astn_create_stmt_fcall(arena, $1.token, $3.expr_list, $6.stmt); }
  | kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_fcall(arena, $1.token, $3.expr_list, NULL); }
  | kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt 
    { $$.stmt = astn_create_stmt_fcall(arena, $1.token, NULL, $5.stmt); }
  | kotlin_identifier TT_LPAREN TT_RPAREN TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_fcall(arena, $1.token, NULL, NULL); }
  | TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_block(arena, $2.stmt, $4.stmt); }
  | TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_block(arena, $2.stmt, NULL); }
  | kotlin_stmt_var
    { $$.stmt = $1.stmt; }
  | kotlin_while
    { $$.stmt = $1.stmt; }
  | kotlin_for
    { $$.stmt = $1.stmt; }
  | kotlin_do
    { $$.stmt = $1.stmt; }
  | kotlin_if
    { $$.stmt = $1.stmt; }
  | kotlin_when
    { $$.stmt = $1.stmt; }
  | kotlin_return
    { $$.stmt = $1.stmt; } 
  ;

kotlin_stmt_var:
    TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2.token, $4.ktype, $6.expr, $8.stmt); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2.token, $4.ktype, NULL, $6.stmt); }
  | kotlin_identifier TT_ASSIGN       kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1.token, KOTLIN_DECL, $3.expr, $5.stmt); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1.token, KOTLIN_DECL, $3.expr, $5.stmt); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1.token, KOTLIN_DECL, $3.expr, $5.stmt); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1.token, KOTLIN_DECL, $3.expr, $5.stmt); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1.token, KOTLIN_DECL, $3.expr, $5.stmt); }
  | kotlin_identifier TT_INCR                                                 TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1.token, KOTLIN_DECL, 1, $4.stmt); }
  | kotlin_identifier TT_DECR                                                 TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1.token, KOTLIN_DECL, 1, $4.stmt); }
  | TT_INCR kotlin_identifier                                                 TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1.token, KOTLIN_DECL, 1, $4.stmt); }
  | TT_DECR kotlin_identifier                                                 TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1.token, KOTLIN_DECL, 1, $4.stmt); }

  | TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2.token, $4.ktype, $6.expr, NULL); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2.token, $4.ktype, NULL, NULL); }
  | kotlin_identifier TT_ASSIGN       kotlin_expression                       TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1.token, KOTLIN_DECL, $3.expr, NULL); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1.token, KOTLIN_DECL, $3.expr, NULL); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1.token, KOTLIN_DECL, $3.expr, NULL $5.stmt); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1.token, KOTLIN_DECL, $3.expr, NULL $5.stmt); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1.token, KOTLIN_DECL, $3.expr, NULL $5.stmt); }
  | kotlin_identifier TT_INCR                                                 TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1.token, KOTLIN_DECL, 1, NULL $4.stmt); }
  | kotlin_identifier TT_DECR                                                 TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1.token, KOTLIN_DECL, 1, NULL $4.stmt); }
  | TT_INCR kotlin_identifier                                                 TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1.token, KOTLIN_DECL, 1, NULL $4.stmt); }
  | TT_DECR kotlin_identifier                                                 TT_SEMICOLON 
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1.token, KOTLIN_DECL, 1, NULL $4.stmt); }
  ;

kotlin_while:
    TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_while(arena, false, $3.expr, $6.stmt, $8.stmt); }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_while(arena, false, NULL, $5.stmt, $7.stmt); }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$.stmt = $7.stmt; }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$.stmt = $6.stmt; }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE 
    { $$.stmt = astn_create_stmt_while(arena, false, $3.expr, $6.stmt, NULL); }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_while(arena, false, NULL, $5.stmt, NULL); }
  | TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  | TT_WHILE TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  ;

kotlin_do:
    TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_while(arena, true, $3.stmt, $7.expr, $10.stmt); }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = $9.stmt; }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = $8.stmt; }
  | TT_DO TT_LBRACE kotlin_stmt TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON
    { $$.stmt = astn_create_stmt_while(arena, true, $3.stmt, $7.expr, NULL); }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON
    { $$.stmt = NULL; }
  | TT_DO TT_LBRACE TT_RBRACE TT_WHILE TT_LPAREN TT_RPAREN TT_SEMICOLON
    { $$.stmt = NULL; }
  ;

kotlin_for:
    TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt 
    TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_for(arena, $3, $5, $7, $10, $12); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, $6, $9, $11); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, NULL, $8, $10); }
  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_for(arena, $3, $5, $7, NULL, $10); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, $6, NULL, $9); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = $8; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$.stmt = $8; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON kotlin_stmt
    { $$.stmt = $7; }

  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_for(arena, $3, $5, $7, $10, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, $6, $9, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, NULL, $8, NULL); }
  | TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON
    { $$.stmt = astn_create_stmt_for(arena, $3, $5, $7, NULL, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_SEMICOLON
    { $$.stmt = astn_create_stmt_for(arena, NULL, $4, $6, NULL, NULL); }
  | TT_FOR TT_LPAREN TT_SEMICOLON kotlin_expression TT_SEMICOLON TT_RPAREN TT_SEMICOLON
    { $$.stmt = NULL; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  | TT_FOR TT_LPAREN TT_SEMICOLON TT_SEMICOLON TT_RPAREN TT_SEMICOLON
    { $$.stmt = NULL; }
  ;

kotlin_for_init:
    TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, $8); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type                             TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, $6); }
  |  kotlin_identifier TT_ASSIGN       kotlin_expression                      TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_INCR                                                 TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, 1, $4); }
  | kotlin_identifier TT_DECR                                                 TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, 1, $4); }
  | TT_INCR kotlin_identifier                                                 TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1, KOTLIN_DECL, 1, $4); }
  | TT_DECR kotlin_identifier                                                 TT_COMMA kotlin_for_init
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1, KOTLIN_DECL, 1, $4); }

  | TT_VAR kotlin_identifier TT_COLON kotlin_type TT_ASSIGN kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL_ASSIGN, $2, $4, $6, NULL); }
  | TT_VAR kotlin_identifier TT_COLON kotlin_type
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECL, $2, $4, NULL, NULL); }
  |  kotlin_identifier TT_ASSIGN      kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_INCR
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, 1, NULL); }
  | kotlin_identifier TT_DECR
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, 1, NULL); }
  | TT_INCR kotlin_identifier
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1, KOTLIN_DECL, 1, NULL); }
  | TT_DECR kotlin_identifier
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1, KOTLIN_DECL, 1, NULL); }
  ;

kotlin_for_incr:
    kotlin_identifier TT_ASSIGN       kotlin_expression                      TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression                       TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, $5); }
  | kotlin_identifier TT_INCR                                                 TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, 1, $4); }
  | kotlin_identifier TT_DECR                                                 TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, 1, $4); }
  | TT_INCR kotlin_identifier                                                 TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1, KOTLIN_DECL, 1, $4); }
  | TT_DECR kotlin_identifier                                                 TT_COMMA kotlin_for_incr
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1, KOTLIN_DECL, 1, $4); }
 
  |  kotlin_identifier TT_ASSIGN      kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DIRECT_ASSIGN, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_PLUS  kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_PLUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MINUS kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MINUS, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_MUL   kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_MUL, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_EQUALS_DIV   kotlin_expression
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_EQUALS_DIV, $1, KOTLIN_DECL, $3, NULL); }
  | kotlin_identifier TT_INCR
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_AFTER, $1, KOTLIN_DECL, 1, NULL); }
  | kotlin_identifier TT_DECR
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_AFTER, $1, KOTLIN_DECL, 1, NULL); }
  | TT_INCR kotlin_identifier
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_INCR_BEFORE, $1, KOTLIN_DECL, 1, NULL); }
  | TT_DECR kotlin_identifier
    { $$.stmt = astn_create_stmt_assign(arena, STMT_VAR_DECR_BEFORE, $1, KOTLIN_DECL, 1, NULL); }
  ;
        
kotlin_if:
    TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, $3, $6, $8, $9); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, $3, $6, NULL, $8); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$.stmt = $7; }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, $5, $7, $8); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, $5, NULL, $7); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else kotlin_stmt
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, NULL, $6, $7); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_stmt
    { $$.stmt = $6; }

  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, $3, $6, $8, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, $3, $6, NULL, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, $3, NULL, $7, NULL); }
  | TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, $5, $7, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, $5, NULL, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_IF, NULL, NULL, $6, NULL); }
  | TT_IF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  ;

kotlin_elseif_else:
    TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, $3, $6, $8, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, NULL, $5, $7, NULL); }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, $3, NULL, $7, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE kotlin_elseif_else
    { $$.stmt = $6; }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, $3, $6, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, NULL, $5, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSEIF, $3, NULL, NULL, NULL); }
  | TT_ELSEIF TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  | TT_ELSE TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSE, NULL, $3, NULL, NULL); }
  | TT_ELSE TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  ;

kotlin_when:
    TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE kotlin_stmt
    { $$.stmt = astn_create_stmt_when(arena, $3, $6, $8); }
  | TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_branch TT_RBRACE
    { $$.stmt = astn_create_stmt_when(arena, $3, $6, NULL); }
  ;

kotlin_when_branch:
    kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch
    { $$.stmt = astn_create_stmt_if(arena, STMT_CASE, $1, $4, $6, NULL); }
  | kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch
    { $$.stmt = $5; }
  | kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_CASE, $1, $4, NULL, NULL); }
  | kotlin_expression TT_ARROW TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  | TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE kotlin_when_branch
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSE, NULL, $4, $6, NULL); }
  | TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt TT_RBRACE
    { $$.stmt = astn_create_stmt_if(arena, STMT_ELSE, NULL, $4, NULL, NULL); }
  | TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE kotlin_when_branch
    { $$.stmt = $5; }
  | TT_ELSE TT_ARROW TT_LBRACE TT_RBRACE
    { $$.stmt = NULL; }
  ;

kotlin_return:
      TT_RETURN kotlin_expression_list TT_SEMICOLON
      { $$.stmt = astn_create_stmt_ret(arena, $2); }
    | TT_RETURN TT_SEMICOLON
      { $$.stmt = astn_create_stmt_ret(arena, NULL); }
    ;

kotlin_expression:
      kotlin_expression TT_PLUS       kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_ARIT_PLUS, $1, $3); }
    | kotlin_expression TT_MINUS      kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_ARIT_MINUS, $1, $3); }
    | kotlin_expression TT_STAR       kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_ARIT_MUL, $1, $3); }
    | kotlin_expression TT_SLASH      kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_ARIT_DIV, $1, $3); }

    | kotlin_expression TT_EQUALS     kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_EQUAL, $1, $3); }
    | kotlin_expression TT_NOT_EQUALS kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_NEQUAL, $1, $3); }
    | kotlin_expression TT_LEQUALS    kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_LEQUAL, $1, $3); }
    | kotlin_expression TT_GEQUALS    kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_GEQUAL, $1, $3); }
    | kotlin_expression TT_LTHAN      kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_LTHAN, $1, $3); }
    | kotlin_expression TT_GTHAN      kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_COMP_GTHAN, $1, $3); }

    | kotlin_expression TT_AND        kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_LOG_AND, $1, $3); }
    | kotlin_expression TT_OR         kotlin_expression
      { $$.expr = astn_create_expr_bin(arena, OP_BIN_LOG_OR, $1, $3); }

    | TT_BANG  kotlin_expression
      { $$.expr = astn_create_expr_un(arena, OP_UN_LOG_NOT, $2); }

    | TT_PLUS  kotlin_expression
      { $$.expr = astn_create_expr_un(arena, OP_UN_ARIT_PLUS, $2); }
    | TT_MINUS kotlin_expression
      { $$.expr = astn_create_expr_un(arena, OP_UN_ARIT_MINUS, $2); }

    | TT_LPAREN kotlin_expression TT_RPAREN
      { $$.expr = astn_create_expr_un(arena, OP_UN_PAREN, $2); }

    | kotlin_fun_call
      { $$.expr = $1; }
    
    | kotlin_token
      { $$.expr = astn_create_expr_token(arena, $1.token); }
    ;

kotlin_token:
      TT_TRUE
      { $$.token = astn_create_token(arena, TT_LIT_TRUE, NULL, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | TT_FALSE
      { $$.token = astn_create_token(arena, TT_LIT_FALSE, NULL, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | TT_NULL
      { $$.token = astn_create_token(arena, TT_LIT_NULL, NULL, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); } 
    | TT_STRING_LIT
      { $$.token = astn_create_token(arena, TT_LIT_STRING, yylval.str, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    | kotlin_number
      { $$.token = $1.token; }
    | kotlin_identifier
      { $$.token = $1.token; }
    ;

kotlin_number:
      TT_NUMBER
      { $$.token = astn_create_token(arena, TT_LIT_NUMBER, &yylval.num, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    ;

kotlin_identifier:
      TT_IDENTIFIER
      { $$.token = astn_create_token(arena, TT_IDENT, yylval.str, file, yylloc.first_line, yylloc.first_column, yylloc.last_column); }
    ;

kotlin_fun_call:
      kotlin_identifier TT_LPAREN kotlin_expression_list TT_RPAREN  
      { $$.expr = astn_create_expr_fcall(arena, $1, $3); }
    | kotlin_identifier TT_LPAREN TT_RPAREN  
      { $$.expr = astn_create_expr_fcall(arena, $1, NULL); }
    ;

kotlin_expression_list:
      kotlin_expression TT_COMMA kotlin_expression_list
      { $$.expr_list = astn_create_expr_list(arena, $1, $3); }
    | kotlin_expression                               
      { $$.expr_list = astn_create_expr_list(arena, $1, NULL); }
    ;

%%

void yyerror(YYLTYPE* yylloc, AST* ast, const char* error_msg) {
  fprintf(stderr, "AST instance: %p", (void*)ast);
  _error_assert(error_parser, error_msg, filename, yylloc->first_line);
}


