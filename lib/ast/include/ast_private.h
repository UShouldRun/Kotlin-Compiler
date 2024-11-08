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
    ASTN_Token        _defined;
    ASTN_KTypeDefault _default;
  } type;
};

// AST TOKEN
struct astn_token {
  ASTN_TokenType type;
  union {
    uint64_t    lit_number;
    double      lit_real;
    bool        lit_bool;
    bool        lit_null;
    const char* lit_str,
              * ident;
  } value;
  uint32_t pos_abs, pos_line, pos_rel;
  const char* file;
};

// AST EXPRESSIONS
struct astn_expr_list {
  ASTN_Expr expr, next;
};

struct astn_expr {
  ASTN_ExprType type;
  union {
    ASTN_Token token;
    struct {
      ASTN_ExprList args;
      ASTN_Token    fun;
    } fun_call;
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
    } _while;
    struct {
      ASTN_Stmt init;
      ASTN_Expr cond;
      ASTN_Stmt incr;
      ASTN_Stmt block;
    } _for;
    struct {
      ASTN_Expr cond;
      ASTN_Stmt block;
      ASTN_Stmt next;
    } _if;
    struct {
      ASTN_Expr cond;
      ASTN_Stmt cases;
    } _when;
    struct {
      ASTN_ExprList value;
    } _ret;
    struct {
      ASTN_Token var;
      ASTN_KType ktype;
      ASTN_Expr  value;
    } _assign; 
    struct {
      ASTN_ExprList args;
      ASTN_Token    fun;
    } _fun_call;
    ASTN_Stmt block;
  } stmt;
  ASTN_Stmt next;
};

struct astn_fun_arg {
  ASTN_KType   type;
  ASTN_Token   arg;
  ASTN_FunArg next;
};

struct astn_fun_ret {
  ASTN_KType  type;
  ASTN_FunRet next;
};

struct astn_fun {
  ASTN_Token  ident;
  ASTN_FunArg args; 
  ASTN_FunRet ret;
  ASTN_Stmt   body;
};

// AST OBJECTS
struct astn_enum_val {
  bool         is_atributed;
  ASTN_Token   atribute;
  ASTN_Token   value;
  ASTN_EnumVal next;
};

struct astn_enum {
  ASTN_Token   ident;
  ASTN_EnumVal values;
};

struct astn_obj {
  ASTN_Type type;
  union {
    struct astn_fun _fun;
    struct astn_enum _enum;
  } obj;
  ASTN_Obj next;
};

// AST META OBJECTS
struct astn_program {
  const char* name;
  ASTN_Obj    objects;
  ASTN_Obj    main;
};

static uint64_t astn_sizes[] = {
  sizeof(struct astn_program),
  sizeof(struct astn_obj),
  sizeof(struct astn_enum),
  sizeof(struct astn_enum_val),
  sizeof(struct astn_fun),
  sizeof(struct astn_fun_ret),
  sizeof(struct astn_fun_arg),
  sizeof(struct astn_stmt),
  sizeof(struct astn_expr),
  sizeof(struct astn_ktype),
  sizeof(struct astn_token)
};

#endif // !AST_PRIVATE_H
