%{
#include <stdio.h>
#include "error.h"
#include "ast.h"
#include "parser.tab.h"

extern const char* filename;
extern YYLTYPE* yylloc;

int yylex(YYSTYPE* yylval, YYLTYPE* yylloc);
void yyerror(YYLTYPE* yylloc, AST* ast, const char* error_msg);

#define YY_DECL int yylex(YYSTYPE* yylval, YYLTYPE* yylloc, AST* ast)
%}

%define api.pure full
%define parse.error verbose
%locations

%parse-param { AST* ast, Arena arena }

%token TT_IDENTIFIER TT_VAR TT_VAL TT_STRING_LIT TT_NUMBER TT_REAL TT_TRUE TT_FALSE TT_MAIN
%token TT_BYTE TT_SHORT TT_INT TT_LONG TT_FLOAT TT_DOUBLE TT_BOOLEAN TT_CHAR TT_STRING TT_ANY
%token TT_INCR TT_DECR TT_EQUALS_PLUS TT_EQUALS_MINUS TT_EQUALS_MUL TT_EQUALS_DIV
%token TT_LPAREN TT_RPAREN TT_LBRACE TT_RBRACE TT_LPARENRECT TT_RPARENRECT TT_SEMICOLON TT_COLON TT_COMMA TT_ASSIGN TT_ARROW TT_DOT
%token TT_IF TT_ELSE TT_ELSEIF TT_WHEN TT_WHILE TT_FOR TT_IN TT_DO TT_FUN TT_$$ =  TT_NULL TT_ENUM

%left TT_EQUALS TT_NOT_EQUALS TT_LTHAN TT_GTHAN TT_LEQUALS TT_GEQUALS TT_AND TT_OR
%left TT_PLUS TT_MINUS
%left TT_STAR TT_SLASH
%right TT_BANG

%%

kotlin_input:
      kotlin_program kotlin_main
      { $$ =  ast_create(arena, filename, $1, $2); }
    ;

kotlin_program:
      TT_FUN TT_IDENTIFIER kotlin_fun_params kotlin_$$ = _type kotlin_stmt_block kotlin_program
      { $$ =  astn_create_func(arena, $2, $3, $4, $5, $6); }
    | TT_FUN TT_IDENTIFIER kotlin_fun_params kotlin_$$ = _type kotlin_stmt_block                
      { $$ =  astn_create_func(arena, $2, $3, $4, $5, NULL); }
    | TT_FUN TT_IDENTIFIER kotlin_fun_params kotlin_$$ = _type                   kotlin_program
      { $$ =  astn_create_func(arena, $2, $3, $4, NULL, NULL); }
    | TT_FUN TT_IDENTIFIER kotlin_fun_params kotlin_$$ = _type                   
      { $$ =  astn_create_func(arena, $2, $3, $4, NULL, NULL); }

    | TT_ENUM TT_IDENTIFIER TT_LBRACE kotlin_enum_block TT_RBRACE                 kotlin_program
      { $$ =  astn_create_enum($2, $4, $6); }
    | TT_ENUM TT_IDENTIFIER TT_LBRACE kotlin_enum_block TT_RBRACE                  
      { $$ =  astn_create_enum(arena, $2, $4, NULL); }
    ;

kotlin_main: // Kotlin Main Function Rule
      TT_FUN TT_MAIN kotlin_fun_params kotlin_$$ = _type kotlin_stmt_block
      { $$ =  astn_create_func(arena, $2, $3, $4, $5, NULL); }
    ;

kotlin_enum_block:
      TT_IDENTIFIER TT_LPAREN TT_NUMBER TT_RPAREN TT_COMMA kotlin_enum_block
      { $$ =  astn_create_enum_val(arena, $1, $3, true, $6); }
    | TT_IDENTIFIER TT_COMMA kotlin_enum_block
      { $$ =  astn_create_enum_val(arena, $1, 0, false, $3); }
    | TT_IDENTIFIER TT_LPAREN TT_NUMBER TT_RPAREN
      { $$ =  astn_create_enum_val(arena, $1, $3, true, NULL); }
    | TT_IDENTIFIER
      { $$ =  astn_create_enum_val(arena, $1, 0, false, NULL); }
    ;

kotlin_fun_params:
      TT_LPAREN kotlin_parameter_list TT_RPAREN
      { $$ =  $2; }
    | TT_LPAREN TT_RPAREN
      { $$ =  NULL; }
    ;

kotlin_fun_call:
      TT_IDENTIFIER TT_LPAREN kotlin_fun_call_args TT_RPAREN
      { $$ =  astn_create_expr_fcall(arena, $1, $3); }
    | TT_IDENTIFIER TT_LPAREN TT_RPAREN
      { $$ =  astn_create_expr_fcall(arena, $1, NULL); }
    ;

kotlin_fun_call_args:
      kotlin_expression TT_COMMA kotlin_fun_call_args
      { $$ =  astn_create_expr_list(arena, $1, $3); }
    | kotlin_expression
      { $$ =  astn_create_expr_list(arena, $1, NULL); }
    ;

kotlin_parameter_list:
      TT_IDENTIFIER TT_COLON kotlin_type TT_COMMA kotlin_parameter_list
      { $$ =  astn_create_func_args(arena, $3, $1, $5); }
    | TT_IDENTIFIER TT_COLON kotlin_type
      { $$ =  astn_create_func_args(arena, $3, $1, NULL); }
    ;

kotlin_type:
      TT_BYTE | TT_SHORT | TT_INT | TT_LONG
    | TT_FLOAT | TT_DOUBLE
    | TT_BOOLEAN
    | TT_CHAR | TT_STRING
    | TT_IDENTIFIER
    | TT_ANY
    ;

kotlin_while:
      TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt_block TT_RBRACE
    ;

kotlin_do:
      TT_DO TT_LBRACE kotlin_stmt_block TT_RBRACE TT_WHILE TT_LPAREN kotlin_expression TT_RPAREN TT_SEMICOLON
    ;

kotlin_for:
      TT_FOR TT_LPAREN kotlin_for_init TT_SEMICOLON kotlin_expression TT_SEMICOLON kotlin_for_incr TT_RPAREN TT_LBRACE kotlin_stmt_block TT_RBRACE
    | TT_FOR TT_LPAREN kotlin_type TT_IDENTIFIER TT_IN TT_IDENTIFIER TT_RPAREN TT_LBRACE kotlin_stmt_block TT_RBRACE
    ;

kotlin_for_init:
        kotlin_for_init_no_null
      |
      ;

kotlin_for_incr:
        kotlin_for_incr_no_null
      |
      ; 

kotlin_for_init_no_null:
        kotlin_type TT_IDENTIFIER TT_ASSIGN kotlin_expression TT_COMMA kotlin_for_init_no_null
      | kotlin_type TT_IDENTIFIER TT_ASSIGN kotlin_expression
      | TT_IDENTIFIER TT_ASSIGN kotlin_expression
      ;

kotlin_for_incr_no_null:
        kotlin_stmt TT_COMMA kotlin_for_incr_no_null
      | kotlin_stmt
      ;
        
kotlin_if:
      TT_IF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt_block TT_RBRACE kotlin_elseif_else
    | TT_IF TT_LPAREN kotlin_expression TT_RPAREN kotlin_stmt kotlin_elseif_else
    ;

kotlin_elseif_else:
      TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_stmt_block TT_RBRACE kotlin_elseif_else
      TT_ELSEIF TT_LPAREN kotlin_expression TT_RPAREN kotlin_stmt kotlin_elseif_else
    | TT_ELSE TT_LBRACE kotlin_stmt_block TT_RBRACE
    | TT_ELSE kotlin_stmt
    |
    ;

kotlin_when:
      TT_WHEN TT_LPAREN kotlin_expression TT_RPAREN TT_LBRACE kotlin_when_block TT_RBRACE
    ;

kotlin_when_block:
      kotlin_when_branch kotlin_when_block
    | kotlin_when_branch
    ;

kotlin_when_branch:
      kotlin_expression TT_ARROW TT_LBRACE kotlin_stmt_block TT_RBRACE
    | kotlin_expression TT_ARROW kotlin_stmt TT_SEMICOLON
    | TT_ELSE TT_ARROW TT_LBRACE kotlin_stmt_block TT_RBRACE
    | TT_ELSE TT_ARROW kotlin_stmt TT_SEMICOLON
    ;

kotlin_return:
      TT_RETURN kotlin_expression TT_SEMICOLON
    | TT_RETURN kotlin_stmt_var TT_SEMICOLON
    | TT_RETURN
    ;

kotlin_return_type:
      kotlin_return_type_repeat
    |
    ;

kotlin_return_type_repeat:
      kotlin_type TT_COMMA kotlin_$$ = _type_repeat
    | kotlin_type
    ;

kotlin_stmt_block:
      kotlin_stmt TT_SEMICOLON kotlin_stmt_block
    | 
    ;

kotlin_stmt:
      kotlin_stmt_list kotlin_stmt
    | kotlin_$$ = 
    ;

kotlin_stmt_list:
      kotlin_stmt_var
    | kotlin_while
    | kotlin_for
    | kotlin_do
    | kotlin_if
    | kotlin_when
    | kotlin_fun_call // Expression
    ;

kotlin_stmt_var:
      TT_VAR TT_COLON kotlin_type TT_IDENTIFIER TT_ASSIGN kotlin_expression TT_SEMICOLON
    | TT_VAR TT_COLON kotlin_type TT_IDENTIFIER TT_SEMICOLON
    | TT_IDENTIFIER TT_INCR TT_SEMICOLON
    | TT_IDENTIFIER TT_DECR TT_SEMICOLON
    | TT_INCR TT_IDENTIFIER TT_SEMICOLON
    | TT_DECR TT_IDENTIFIER TT_SEMICOLON
    | TT_IDENTIFIER TT_EQUALS_PLUS kotlin_expression  TT_SEMICOLON
    | TT_IDENTIFIER TT_EQUALS_MINUS kotlin_expression TT_SEMICOLON
    | TT_IDENTIFIER TT_EQUALS_MUL kotlin_expression   TT_SEMICOLON
    | TT_IDENTIFIER TT_EQUALS_DIV kotlin_expression   TT_SEMICOLON
    ;

kotlin_expression: // Kotlin Expression Rules
      kotlin_expression TT_PLUS       kotlin_expression
    | kotlin_expression TT_MINUS      kotlin_expression
    | kotlin_expression TT_STAR       kotlin_expression
    | kotlin_expression TT_SLASH      kotlin_expression

    | kotlin_expression TT_EQUALS     kotlin_expression
    | kotlin_expression TT_NOT_EQUALS kotlin_expression
    | kotlin_expression TT_LEQUALS    kotlin_expression
    | kotlin_expression TT_GEQUALS    kotlin_expression
    | kotlin_expression TT_LTHAN      kotlin_expression
    | kotlin_expression TT_GTHAN      kotlin_expression

    | kotlin_expression TT_AND        kotlin_expression
    | kotlin_expression TT_OR         kotlin_expression

    | TT_BANG  kotlin_expression

    | TT_PLUS  kotlin_expression
    | TT_MINUS kotlin_expression

    | TT_LPAREN kotlin_expression TT_RPAREN

    | kotlin_fun_call
    // | TT_IDENTIFIER TT_DOT TT_IDENTIFIER
    | TT_TRUE
    | TT_FALSE
    | TT_NULL
    | TT_NUMBER
    | TT_REAL
    | TT_STRING_LIT
    | TT_IDENTIFIER
    ;

%%

void yyerror(YYLTYPE* yylloc, AST* ast, const char* error_msg) {
  fprintf(stderr, "AST instance: %p", (void*)ast);
  _error_assert(error_parser, error_msg, filename, yylloc->first_line);
}

int yylex(YYSTYPE* yylval, YYLTYPE* yylloc) {
  return 0;
}
