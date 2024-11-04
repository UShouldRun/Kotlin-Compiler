#ifndef AST_PRIVATE_H
#define AST_PRIVATE_H

// ========================================================# PRIVATE #===========================================================

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ast.h"
#include "error.h"

// AST KOTLIN TYPES
struct astn_ktype {
  bool              is_default;
  union {
    ASTN_Token        defined;
    ASTN_KTypeDefault default;
  } type;
};

// AST TOKEN
struct astn_token {
  ASTN_TokenType type;
  union {
    uint64_t    lit_number;
    double      lit_real;
    const char* lit_str,
              * ident;
  } value;
  uint32_t pos_abs, pos_line, pos_rel;
  const char* file;
};

// AST EXPRESSIONS
struct astn_expr {
  ASTN_ExprType type;
  union {
    ASTN_Token token;
    struct {
      ASTN_Expr  arg;
      ASTN_Expr  next;
      ASTN_Token func;
    } func_call;
    struct {
      ASTN_ExprOp op;
      ASTN_Expr   operand;
    } unary; 
    struct {
      ASTN_ExprOp op;
      ASTN_Expr   left, right;
    } binary;
  } expr;
};

// AST STATEMENTS
struct astn_stmt {
  ASTN_StmtType type;
  union {
    struct {
      ASTN_Expr cond;
      ASTN_Stmt block;
    } while;
    struct {
      ASTN_Stmt init;
      ASTN_Expr cond;
      ASTN_Stmt incr;
      ASTN_Stmt block;
    } for;
    struct {
      ASTN_Expr cond;
      ASTN_Stmt block;
      ASTN_Stmt next;
    } if;
    struct {
      ASTN_Expr cond;
      ASTN_Stmt cases;
    } when;
    struct {
      ASTN_Expr value;
      ASTN_Stmt next;
    } ret;
    struct {
      ASTN_Token var;
      ASTN_KType ktype;
      ASTN_Expr  value;
    } assign; 
  } stmt;
  ASTN_Stmt next;
};

struct astn_func_arg {
  ASTN_KType   type;
  ASTN_Token   arg;
  ASTN_FuncArg next;
};

struct astn_func_return {
  ASTN_KType   type;
  ASTN_FuncRet next;
};

struct astn_func {
  uint32_t s_args, s_body, s_return;
  ASTN_Stmt    body;
  ASTN_Token   ident;
  ASTN_FuncArg args; 
  ASTN_FuncRet ret;
};

// AST OBJECTS
struct astn_enum_val {
  int64_t      atribute;
  ASTN_Token   value;
  ASTN_EnumVal next;
};

struct astn_enum {
  ASTN_Token   ident;
  ASTN_EnumVal  value;
};

struct astn_obj {
  ASTN_Type type;
  union {
    struct astn_func func;
    struct astn_enum enum;
  } obj;
  ASTN_Obj next;
};

// AST META OBJECTS
struct astn_program {
  const char* name;
  ASTN_Obj    objects;
  ASTN_Func   main;
};

static uint64_t astn_sizes[] = {
  sizeof(struct astn_program),
  sizeof(struct astn_obj),
  sizeof(struct astn_enum),
  sizeof(struct astn_enum_value),
  sizeof(struct astn_func),
  sizeof(struct astn_func_return),
  sizeof(struct astn_func_args),
  sizeof(struct astn_stmt),
  sizeof(struct astn_expr),
  sizeof(struct astn_ktype),
  sizeof(struct astn_token)
};

#endif // !AST_PRIVATE_H
