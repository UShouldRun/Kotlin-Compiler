#ifndef AST_H
#define AST_H

// ========================================================# PUBLIC #===========================================================

#include "error.h"
#include "arena.h"

// AST Types
typedef enum {
  ASTN_TOKEN, ASTN_KTYPE,
  ASTN_EXPR, ASTN_EXPR_LIST,
  ASTN_STMT,
  ASTN_VAR, 
  ASTN_FUN, ASTN_FUN_ARG, ASTN_FUN_RET,
  ASTN_ENUM, ASTN_ENUM_VAL,
  ASTN_MAIN,
  ASTN_PROGRAM
} ASTN_Type;

typedef enum astn_stmt_type {
  STMT_WHILE, STMT_FOR, STMT_DO,
  STMT_IF, STMT_ELSEIF, STMT_ELSE, STMT_WHEN, STMT_CASE,
  STMT_RETURN, STMT_FUN_CALL, STMT_BLOCK,
  STMT_VAR_INCR_BEFORE, STMT_VAR_DECR_BEFORE,
  STMT_VAR_INCR_AFTER,  STMT_VAR_DECR_AFTER,
  STMT_VAR_EQUALS_PLUS, STMT_VAR_EQUALS_MINUS,
  STMT_VAR_EQUALS_MUL,  STMT_VAR_EQUALS_DIV,
  STMT_VAR_DIRECT_ASSIGN, STMT_VAR_DECL, STMT_VAR_DECL_ASSIGN
} ASTN_StmtType;

typedef enum astn_expr_type {
  EXPR_BIN, EXPR_UN, EXPR_FUN_CALL, EXPR_TOKEN
} ASTN_ExprType;

typedef enum astn_expr_op {
  OP_NONE = 0,
  OP_UN_ARIT_PLUS, OP_UN_ARIT_MINUS,
  OP_UN_LOG_NOT,
  OP_UN_PAREN,
  OP_BIN_ARIT_PLUS, OP_BIN_ARIT_MINUS, OP_BIN_ARIT_MUL, OP_BIN_ARIT_DIV,
  OP_BIN_COMP_EQUAL, OP_BIN_COMP_NEQUAL,
  OP_BIN_COMP_LTHAN, OP_BIN_COMP_GTHAN,
  OP_BIN_COMP_LEQUAL, OP_BIN_COMP_GEQUAL,
  OP_BIN_LOG_AND, OP_BIN_LOG_OR
} ASTN_ExprOp;

typedef enum astn_ktype_default {
  KOTLIN_NONE = -2,
  KOTLIN_NOT_DEFAULT = -1,
  KOTLIN_DECL = 0,
  KOTLIN_ANY,
  KOTLIN_BYTE, KOTLIN_SHORT, KOTLIN_INT, KOTLIN_LONG, 
  KOTLIN_FLOAT, KOTLIN_DOUBLE,
  KOTLIN_CHAR, KOTLIN_STRING,
  KOTLIN_BOOLEAN
} ASTN_KTypeDefault;

typedef enum astn_token_type {
  TT_IDENT, TT_LIT_NUMBER, TT_LIT_REAL, TT_LIT_STRING, TT_LIT_TRUE, TT_LIT_FALSE, TT_LIT_NULL
} ASTN_TokenType;

// AST Nodes
typedef struct astn_program   *AST;

typedef struct astn_obj       *ASTN_Obj;

typedef struct astn_enum_val  *ASTN_EnumVal;

typedef struct astn_fun_arg   *ASTN_FunArg;
typedef struct astn_fun_ret   *ASTN_FunRet;

typedef struct astn_stmt      *ASTN_Stmt;
typedef struct astn_expr      *ASTN_Expr;
typedef struct astn_expr_list *ASTN_ExprList;

typedef struct astn_ktype     *ASTN_KType;
typedef struct astn_token     *ASTN_Token;

// Functions
bool          ast_type_check          (Arena, AST, const char*, uint64_t, float);
void          ast_print               (FILE*, AST);
void          ast_free_tokens         (AST);
uint64_t      astn_max_size           ();

// AST Node Get Position

uint32_t      astn_get_pos_first_line    (void*, ASTN_Type);
uint32_t      astn_get_pos_last_line     (void*, ASTN_Type);
uint32_t      astn_get_pos_first_col     (void*, ASTN_Type);
uint32_t      astn_get_pos_last_col      (void*, ASTN_Type);

// AST Node Set Position

void          astn_set_pos_obj        (ASTN_Obj, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_enum_val   (ASTN_EnumVal, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_fun_arg    (ASTN_FunArg, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_fun_ret    (ASTN_FunRet, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_stmt       (ASTN_Stmt, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_expr       (ASTN_Expr, uint32_t, uint32_t, uint32_t, uint32_t);
void          astn_set_pos_expr_list  (ASTN_ExprList, uint32_t, uint32_t, uint32_t, uint32_t);

// AST Node Creation
AST           ast_create              (Arena, const char*, ASTN_Obj);

ASTN_Obj      astn_create_enum        (Arena, ASTN_Token, ASTN_EnumVal, ASTN_Obj); 
ASTN_EnumVal  astn_create_enum_val    (Arena, ASTN_Token, ASTN_Token, bool, ASTN_EnumVal);

ASTN_Obj      astn_create_fun         (Arena, ASTN_Token, ASTN_FunArg, ASTN_FunRet, ASTN_Stmt, ASTN_Obj); 
ASTN_FunArg   astn_create_fun_args    (Arena, ASTN_KType, ASTN_Token, ASTN_FunArg);
ASTN_FunRet   astn_create_fun_ret     (Arena, ASTN_KType, ASTN_FunRet);

ASTN_Stmt     astn_create_stmt_while  (Arena, bool, ASTN_Expr, ASTN_Stmt, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_for    (Arena, ASTN_Stmt, ASTN_Expr, ASTN_Stmt, ASTN_Stmt, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_if     (Arena, ASTN_StmtType, ASTN_Expr, ASTN_Stmt, ASTN_Stmt, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_when   (Arena, ASTN_Expr, ASTN_Stmt, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_ret    (Arena, ASTN_ExprList, uint32_t);
ASTN_Stmt     astn_create_stmt_fcall  (Arena, ASTN_Token, ASTN_ExprList, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_assign (Arena, ASTN_StmtType, ASTN_Token, ASTN_KType, ASTN_Expr, ASTN_Stmt);
ASTN_Stmt     astn_create_stmt_block  (Arena, ASTN_Stmt, ASTN_Stmt);

ASTN_Expr     astn_create_expr_bin    (Arena, ASTN_ExprOp, ASTN_Expr, ASTN_Expr);
ASTN_Expr     astn_create_expr_un     (Arena, ASTN_ExprOp, ASTN_Expr);
ASTN_Expr     astn_create_expr_fcall  (Arena, ASTN_Token, ASTN_ExprList);
ASTN_Expr     astn_create_expr_token  (Arena, ASTN_Token);
ASTN_ExprList astn_create_expr_list   (Arena, ASTN_Expr, ASTN_ExprList);

ASTN_Token    astn_create_token       (Arena, ASTN_TokenType, void*, const char*, uint32_t, uint32_t, uint32_t);
ASTN_KType    astn_create_ktype       (Arena, bool, ASTN_KTypeDefault, ASTN_Token, uint32_t, uint32_t, uint32_t, uint32_t);

#endif // !AST_H
