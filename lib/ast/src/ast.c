#include "hashtable_private.h"

// =======================================# PUBLIC #==========================================

// AST Type Check

bool ast_type_check(FILE* file, AST program, uint64_t s_buckets, float load_threshold_factor) {
  error_assert(error_type_checker, file != NULL);
  error_assert(error_type_checker, program != NULL);

  bool type_check = true;
  HashTable table = hashtable_create(s_buckets, load_threshold_factor);
  error_assert(error_type_checker, table != NULL);

  for (ASTN_Obj node = program->objects; node != NULL; node = node->next)
    if (node->type != ASTN_FUN)
      type_check = type_check && ast_type_check_obj(file, table, node);
  for (ASTN_Obj node = program->objects; node != NULL; node = node->next)
    if (node->type == ASTN_FUN)
      type_check = type_check && ast_type_check_obj(file, table, node);

  error_assert(error_type_checker, hashtable_free(table));
  return type_check;
}

bool ast_type_check_obj(FILE* file, HashTable table, ASTN_Obj node) {
  error_assert(error_type_checker, file != NULL);
  error_assert(error_type_checker, node != NULL);

  bool type_check = true;
  switch (node->type) {
    case ASTN_FUN: {
      error_assert(error_type_checker, hashtable_insert_obj(table, node->obj._fun.ident, node));

      for (ASTN_FunArg node_arg = node->obj._fun.args; node_arg != NULL; node_arg = node_arg->next) {
        type_check = type_check && ast_type_check_ktype(file, table, node_arg->type);
        error_assert(error_type_checker, hashtable_insert_var_ktype(table, node_arg->arg, node_arg->type));
      }
      for (ASTN_FunRet node_ret = node->obj._fun.ret; node_ret != NULL; node_ret = node_ret->next)
        type_check = type_check && ast_type_check_ktype(file, table, node_ret->type);

      for (ASTN_Stmt node_stmt = node->obj._fun.body; node_stmt != NULL; node_stmt = node_stmt->next)
        type_check = type_check && ast_type_check_stmt(file, table, node_stmt, node->obj._fun.ret);

      for (ASTN_FunArg node_arg = node->obj._fun.args; node_arg != NULL; node_arg = node_arg->next)
        (void)hashtable_remove_var_ktype(table, node_arg->arg);

      break;
    }
    case ASTN_ENUM: {
      error_assert(error_type_checker, hashtable_insert_obj(table, node->obj._enum.ident, node));
      int32_t i = 0;
      for (ASTN_EnumVal node_value = node->obj._enum.values; node_value != NULL; node_value = node_value->next, i++) {
        if (!node_value->is_atributed) {
          node_value->atribute->type = TT_LIT_NUMBER;
          node_value->atribute->value.lit_number = i;
          node_value->is_atributed = true;
        }
        error_assert(error_type_checker, hashtable_insert_global(table, node_value->value, node_value->atribute))
      }
      break;
    }
    default: {
      error_panic(error_parser, ERROR_INVALID_OBJ);
    }
  }

  return type_check;
}

bool ast_type_check_stmt(FILE* file, HashTable table, ASTN_Stmt node, ASTN_FunRet ret) {
  error_assert(error_type_checker, file != NULL); 
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, node != NULL);
  
  bool type_check = true;
  while (node != NULL) {
    error_assert(error_type_checker, node != node->next);

    switch (node->type) {
      case STMT_WHILE: case STMT_DO: {
        bool check_cond  = ast_type_check_expr(file, table, node->stmt._while.cond),
             check_block = ast_type_check_stmt(file, table, node->stmt._while.block, ret);
        type_check = type_check && check_cond && check_block;
        break;
      }
      case STMT_FOR: {
        bool check_init  = ast_type_check_stmt(file, table, node->stmt._for.init, NULL),
             check_cond  = ast_type_check_expr(file, table, node->stmt._for.cond),
             check_incr  = ast_type_check_stmt(file, table, node->stmt._for.incr, NULL),
             check_block = ast_type_check_stmt(file, table, node->stmt._for.block, ret);
        type_check = type_check && check_init && check_cond && check_incr && check_block;
        break;
      }
      case STMT_IF: {
        bool check_cond  = ast_type_check_expr(file, table, node->stmt._if.cond),
             check_block = ast_type_check_stmt(file, table, node->stmt._if.block);
        type_check = type_check && check_cond && check_block;
        for (ASTN_Stmt node_stmt = node->stmt._if.next; node_stmt != NULL; node_stmt = node_stmt->stmt._if.next) {
          error_assert(error_type_checker, node_stmt != node_stmt->stmt._if.next);
          error_assert(error_type_checker, node_stmt->type == STMT_ELSEIF || node_stmt->type == STMT_ELSE);
          check_cond  = (node->type == STMT_ELSE || ast_type_check_expr(file, table, node->stmt._if.cond));
          check_block = ast_type_check_stmt(file, table, node->stmt._if.block, ret);
          type_check  = type_check && check_cond && check_block;
        } 
        break;
      }
      case STMT_WHEN: {
        bool check_cond  = ast_type_check_expr(file, table, node->stmt._when.cond),
             check_cases = true;
        type_check = type_check && check_cond;
        for (ASTN_Stmt node_stmt = node->stmt._when.cases; node_stmt != NULL; node_stmt = node_stmt->stmt._if.next) {
          error_assert(error_type_checker, node_stmt != node_stmt->stmt._if.next);
          error_assert(error_type_checker, node_stmt->type == STMT_CASE || node_stmt->type == STMT_ELSE);
          check_cond  = ast_type_check_expr(file, table, node_stmt->stmt._if.cond); 
          check_cases = check_cases && ast_type_check_stmt(file, table, node_stmt->stmt._if.block);
        }
        break;
      }
      case STMT_BLOCK: {
        break;
      }
      case STMT_FUN_CALL: {
        break;
      }
      case STMT_RETURN: {
        break;
      }
      case STMT_VAR_DECL: {
        break;
      }
      case STMT_VAR_DIRECT_ASSIGN: {
        break;
      }
      case STMT_VAR_DECL_ASSIGN: {
        break;
      }
      case STMT_VAR_INCR_BEFORE: {
        break;
      }
      case STMT_VAR_DECR_BEFORE: {
        break;
      }
      case STMT_VAR_INCR_AFTER: {
        break;
      }
      case STMT_VAR_DECR_AFTER: {
        break;
      }
      case STMT_VAR_EQUALS_PLUS: {
        break;
      }
      case STMT_VAR_EQUALS_MINUS: {
        break;
      }
      case STMT_VAR_EQUALS_MUL: {
        break;
      }
      case STMT_VAR_EQUALS_DIV: {
        break;
      }
      case STMT_ELSEIF: case STMT_ELSE: {
        ast_error(file, ERROR_SYNTAX_ELSEIF_ELSE);
        break;
      }
      case STMT_CASE: {
        ast_error(file, ERROR_SYNTAX_CASE);
        break;
      }
      default: {
        error_panic(error_type_checker, ERROR_INVALID_STMT);
        break;
      }
    }

    node = node->next;
  }

  return type_check;
}

bool ast_type_check_ktype(FILE* file, HashTable table, ASTN_KType ktype) {
  error_assert(error_type_checker, file != NULL); 
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, ktype != NULL);
  return ktype->is_default || hashtable_lookup_global(table, ktype->type._defined) != NULL;
}

// AST Print 
void ast_print(FILE* file, AST program) {
  if (file == NULL)
    return;
  if (program == NULL)
    return;
  fprintf(file, "Program: %s\n", program->name);
  ASTN_Obj node = program->objects;
  while (node) {
    ast_print_obj(file, node, 0);
    node = node->next;
  }
}

uint64_t astn_max_size() {
  uint64_t max = astn_sizes[0];
  for (uint32_t i = 1; i < sizeof(astn_sizes)/sizeof(uint64_t); i++)
    if (max < astn_sizes[i])
      max = astn_sizes[i];
  return max;
}

AST ast_create(Arena arena, const char* name, ASTN_Obj objects) {
  error_assert(error_nullptr, arena != NULL);
  AST program = (AST)arena_alloc(arena, sizeof(struct astn_program));
  if (program == NULL)
    return NULL;
  program->name    = name;
  program->objects = objects;
  return program;
}

ASTN_Obj astn_create_enum(Arena arena, ASTN_Token ident, ASTN_EnumVal values, ASTN_Obj next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, ident != NULL);
  ASTN_Obj node = (ASTN_Obj)arena_alloc(arena, sizeof(struct astn_obj));
  error_assert(error_mem, node != NULL);
  node->type             = ASTN_ENUM;
  node->obj._enum.ident  = ident;
  node->obj._enum.values = values;
  node->next             = next;
  return node;
}

ASTN_EnumVal astn_create_enum_val(Arena arena, ASTN_Token value, ASTN_Token atribute, bool is_atributed, ASTN_EnumVal next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, value != NULL);
  ASTN_EnumVal node = (ASTN_EnumVal)arena_alloc(arena, sizeof(struct astn_enum_val));
  error_assert(error_mem, node != NULL);
  node->is_atributed = is_atributed;
  node->atribute     = atribute;
  node->value        = value;
  node->next         = next;
  return node;
}

ASTN_Obj astn_create_fun(Arena arena, ASTN_Token ident, ASTN_FunArg args, ASTN_FunRet ret, ASTN_Stmt body, ASTN_Obj next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, ident != NULL);
  ASTN_Obj node = (ASTN_Obj)arena_alloc(arena, sizeof(struct astn_obj));
  error_assert(error_mem, node != NULL);
  node->type           = ASTN_FUN;
  node->obj._fun.ident = ident;
  node->obj._fun.args  = args;
  node->obj._fun.ret   = ret;
  node->obj._fun.body  = body;
  node->next           = next;
  return node;
}

ASTN_FunArg astn_create_fun_args(Arena arena, ASTN_KType type, ASTN_Token arg, ASTN_FunArg next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, type != NULL);
  error_assert(error_nullptr, arg != NULL);
  ASTN_FunArg node = (ASTN_FunArg)arena_alloc(arena, sizeof(struct astn_fun_arg));
  error_assert(error_mem, node != NULL);
  node->type = type;
  node->arg  = arg;
  node->next = next;
  return node;
}

ASTN_FunRet astn_create_fun_ret(Arena arena, ASTN_KType type, ASTN_FunRet next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, type != NULL);
  ASTN_FunRet node = (ASTN_FunRet)arena_alloc(arena, sizeof(struct astn_fun_ret));
  error_assert(error_mem, node != NULL);
  node->type = type;
  node->next = next;
  return node;
}

ASTN_Stmt astn_create_stmt_while(Arena arena, bool do_while, ASTN_Expr cond, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type              = do_while ? STMT_DO : STMT_WHILE;
  node->stmt._while.cond  = cond;
  node->stmt._while.block = block;
  node->next              = next;
  return node;
}

ASTN_Stmt astn_create_stmt_for(Arena arena, ASTN_Stmt init, ASTN_Expr cond, ASTN_Stmt incr, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_FOR;
  node->stmt._for.init  = init;
  node->stmt._for.cond  = cond;
  node->stmt._for.incr  = incr;
  node->stmt._for.block = block;
  node->next            = next;
  return node;
}

ASTN_Stmt astn_create_stmt_if(Arena arena, ASTN_StmtType type, ASTN_Expr cond, ASTN_Stmt block, ASTN_Stmt elseif, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, type == STMT_IF || type == STMT_ELSEIF || type == STMT_ELSE || type == STMT_CASE);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = type;
  node->stmt._if.cond  = type == STMT_ELSE ? NULL : cond;
  node->stmt._if.block = block;
  node->stmt._if.next  = type == STMT_ELSE ? NULL : elseif;
  node->next           = next;
  return node;
}

ASTN_Stmt astn_create_stmt_when(Arena arena, ASTN_Expr cond, ASTN_Stmt cases, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type             = STMT_WHEN;
  node->stmt._when.cond  = cond;
  node->stmt._when.cases = cases;
  node->next             = next;
  return node;
}

ASTN_Stmt astn_create_stmt_ret(Arena arena, ASTN_ExprList value) {
  error_assert(error_nullptr, arena != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_RETURN;
  node->stmt._ret.value = value;
  node->next            = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_fcall(Arena arena, ASTN_Token fun, ASTN_ExprList args, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, fun != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type                = STMT_FUN_CALL;
  node->next                = next;
  node->stmt._fun_call.args = args;
  node->stmt._fun_call.fun  = fun;
  return node;
}

ASTN_Stmt astn_create_stmt_assign(Arena arena, ASTN_StmtType type, ASTN_Token var, ASTN_KType ktype, ASTN_Expr value, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, var != NULL);
  error_assert(
    error_unexp,
    type == STMT_VAR_INCR_BEFORE || type == STMT_VAR_INCR_AFTER || type == STMT_VAR_DECR_BEFORE || type == STMT_VAR_DECR_AFTER ||
    type == STMT_VAR_EQUALS_PLUS || type == STMT_VAR_EQUALS_MINUS || type == STMT_VAR_EQUALS_MUL ||  type == STMT_VAR_EQUALS_DIV ||
    type == STMT_VAR_DIRECT_ASSIGN || type == STMT_VAR_DECL || type == STMT_VAR_DECL_ASSIGN
  );
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type              = type;
  node->next              = next;
  node->stmt._assign.var   = var;
  node->stmt._assign.ktype = ktype; 
  node->stmt._assign.value = value;
  return node;
}

ASTN_Stmt astn_create_stmt_block(Arena arena, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type       = STMT_BLOCK;
  node->stmt.block = block;
  node->next       = next;
  return node;
}

ASTN_Expr astn_create_expr_bin(Arena arena, ASTN_ExprOp op, ASTN_Expr left, ASTN_Expr right) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, op >= OP_BIN_ARIT_PLUS);
  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type              = EXPR_BIN;
  node->expr.binary.op    = op; 
  node->expr.binary.left  = left;
  node->expr.binary.right = right;
  return node;
}

ASTN_Expr astn_create_expr_un(Arena arena, ASTN_ExprOp op, ASTN_Expr operand) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, op > OP_NONE && op <= OP_UN_PAREN);
  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type               = EXPR_UN;
  node->expr.unary.op      = op; 
  node->expr.unary.operand = operand;
  return node;
}

ASTN_Expr astn_create_expr_fcall(Arena arena, ASTN_Token fun, ASTN_ExprList args) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, fun != NULL);
  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type = EXPR_FUN_CALL;
  node->expr.fun_call.fun  = fun;
  node->expr.fun_call.args = args;
  return node;
}

ASTN_Expr astn_create_expr_token(Arena arena, ASTN_Token token) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, token != NULL);
  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type       = EXPR_TOKEN;
  node->expr.token = token;
  return node;
}

ASTN_ExprList astn_create_expr_list(Arena arena, ASTN_Expr expr, ASTN_ExprList next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, expr != NULL);
  ASTN_ExprList node = (ASTN_ExprList)arena_alloc(arena, sizeof(struct astn_expr_list));
  error_assert(error_mem, node != NULL);
  node->expr = expr;
  node->next = next;
  return node;
}

ASTN_Token astn_create_token(Arena arena, ASTN_TokenType type, void* value, const char* file, uint32_t abs, uint32_t line, uint32_t rel) {
  error_assert(error_nullptr, arena != NULL);
  ASTN_Token node = (ASTN_Token)arena_alloc(arena, sizeof(struct astn_token));
  error_assert(error_mem, node != NULL);
  node->type     = type;
  node->file     = file;
  node->pos_abs  = abs;
  node->pos_line = line;
  node->pos_rel  = rel;
  switch (type) { 
    case TT_IDENT:      node->value.ident      = (const char*)value; break;
    case TT_LIT_STRING: node->value.lit_str    = (const char*)value; break;
    case TT_LIT_NUMBER: node->value.lit_number = *(int64_t*)value;   break;
    case TT_LIT_REAL:   node->value.lit_real   = *(double*)value;    break;
    case TT_LIT_TRUE:   node->value.lit_bool   = true;               break;
    case TT_LIT_FALSE:  node->value.lit_bool   = false;              break;
    case TT_LIT_NULL:   node->value.lit_null   = true;               break;
    default:            error_panic(error_unexp, ERROR_INVALID_TT);
  }
  return node;
}

ASTN_KType astn_create_ktype(Arena arena, bool is_default, ASTN_KTypeDefault _default, ASTN_Token _defined) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, is_default || _defined != NULL);
  ASTN_KType node = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
  error_assert(error_mem, node != NULL);
  node->is_default = is_default;
  if (is_default) node->type._default = _default;
  else            node->type._defined = _defined;
  return node;
}

// =======================================# PRIVATE #==========================================

// Print AST Objects
void ast_print_obj(FILE* file, ASTN_Obj node, int indent) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);

  ast_print_indent(file, indent, "");
  if (node->type == ASTN_FUN) {
    fprintf(file, "fun ");
    ast_print_token(file, node->obj._fun.ident);

    fprintf(file, "(");
    ASTN_FunArg node_arg = node->obj._fun.args;
    while (node_arg) {
      ast_print_token(file, node_arg->arg);
      fprintf(file, " ktype: ");
      ast_print_ktype(file, node_arg->type);
      node_arg = node_arg->next;
      fprintf(file, "%s", node_arg ? ", " : "");
    }

    fprintf(file, ") Ret(");
    ASTN_FunRet node_ret = node->obj._fun.ret;
    while (node_ret) {
      fprintf(file, "ktype: ");
      ast_print_ktype(file, node_ret->type);
      node_ret = node_ret->next;
      fprintf(file, "%s", node_ret ? ", " : "");
    }

    fprintf(file, ") Body { \n");
    ast_print_stmt(file, node->obj._fun.body, indent + 1);
    ast_print_indent(file, indent, "}\n");
  } else if (node->type == ASTN_ENUM) {
    fprintf(file, "enum ");
    ast_print_token(file, node->obj._enum.ident);
    fprintf(file, " {\n");
    ASTN_EnumVal node_val = node->obj._enum.values;
    while (node_val) {
      ast_print_indent(file, indent + 1, "");
      ast_print_token(file, node_val->value);
      fprintf(file, ", atribute: ");
      if (node_val->is_atributed)
        ast_print_token(file, node_val->atribute);
      else
        fprintf(file, "none");
      fprintf(file, "\n");
      node_val = node_val->next;
    }
    ast_print_indent(file, indent, "}\n");
  }
}

// Print AST Statements
void ast_print_stmt(FILE* file, ASTN_Stmt node, int indent) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);

  while (node) {
    ast_print_indent(file, indent, "");
    switch (node->type) {
      case STMT_WHILE: {
        fprintf(file, "while (");
        ast_print_expr(file, node->stmt._while.cond);
        fprintf(file, ") {\n"); 
        ast_print_stmt(file, node->stmt._while.block, indent + 1);
        ast_print_indent(file, indent, "}\n");
        break;
      } 
      case STMT_FOR: {
        fprintf(file, "for (\n");
        ast_print_indent(file, indent + 1, "  init {\n");
        ast_print_stmt(file, node->stmt._for.init, indent + 2);
        ast_print_indent(file, indent + 1, "} cond {\n");
        ast_print_indent(file, indent + 2, "");
        ast_print_expr(file, node->stmt._for.cond);
        fprintf(file, "\n");
        ast_print_indent(file, indent + 1, "} incr {\n");
        ast_print_stmt(file, node->stmt._for.incr, indent + 2);
        ast_print_indent(file, indent + 1, "})\n");
        ast_print_indent(file, indent + 1, "  block {\n");
        ast_print_stmt(file, node->stmt._for.block, indent + 2);
        ast_print_indent(file, indent, "}");
        break;
      }
      case STMT_DO: {
        fprintf(file, "do {\n");
        ast_print_stmt(file, node->stmt._while.block, indent + 1);
        fprintf(file, "}\n");
        fprintf(file, "while (");
        ast_print_expr(file, node->stmt._while.cond);
        fprintf(file, ")\n");
        break;
      } 
      case STMT_IF: {
        fprintf(file, "if (");
        ast_print_expr(file, node->stmt._if.cond);
        fprintf(file, ") {\n");
        ast_print_stmt(file, node->stmt._if.block, indent + 1);
        ast_print_indent(file, indent, "}\n");
        ASTN_Stmt next = node->stmt._if.next;
        while (next) {
          ast_print_indent(file, indent, "");
          fprintf(file, "else ");
          if (next->type == STMT_ELSEIF) {   
            fprintf(file, "if (");
            ast_print_expr(file, next->stmt._if.cond);
            fprintf(file, ")");
          }
          fprintf(file, " {\n");
          ast_print_stmt(file, next->stmt._if.block, indent + 1);
          ast_print_indent(file, indent, "}\n");
          next = next->stmt._if.next;
        }
        break;
      }
      case STMT_WHEN: {
        fprintf(file, "when (");
        ast_print_expr(file, node->stmt._when.cond);
        fprintf(file, ") {\n");
        ASTN_Stmt cases = node->stmt._when.cases;
        while (cases) {
          ast_print_indent(file, indent + 1, "");
          if (cases->type == STMT_CASE) {
            fprintf(file, "(");
            ast_print_expr(file, cases->stmt._if.cond);
            fprintf(file, ")");
          }
          else {
            fprintf(file, "else");
          }
          fprintf(file, " {\n");
          ast_print_stmt(file, cases->stmt._if.block, indent + 2);
          ast_print_indent(file, indent + 1, "}\n");
          cases = cases->stmt._if.next;
        }
        ast_print_indent(file, indent, "}\n");
        break;
      }
      case STMT_FUN_CALL: {
        ast_print_fun_call(file, node->stmt._fun_call.fun, node->stmt._fun_call.args);
        fprintf(file, "\n");
        break;
      }
      case STMT_RETURN: {
        fprintf(file, "return ");
        ast_print_expr_list(file, node->stmt._ret.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_BLOCK: {
        fprintf(file, "block {\n");
        ast_print_stmt(file, node->stmt.block, indent + 1);
        ast_print_indent(file, indent, "}\n");
        break;
      }
      case STMT_VAR_INCR_BEFORE: {
        fprintf(file, "++");
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_DECR_BEFORE: {
        fprintf(file, "--");
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_INCR_AFTER: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, "++");
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_DECR_AFTER: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, "--");
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_EQUALS_PLUS: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " += ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_EQUALS_MINUS: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " -= ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_EQUALS_MUL: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " *= ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_EQUALS_DIV: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " /= ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_DIRECT_ASSIGN: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " = ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_VAR_DECL: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " ktype(");
        ast_print_ktype(file, node->stmt._assign.ktype);
        fprintf(file, ")\n");
        break;
      }
      case STMT_VAR_DECL_ASSIGN: {
        ast_print_token(file, node->stmt._assign.var);
        fprintf(file, " ktype(");
        ast_print_ktype(file, node->stmt._assign.ktype);
        fprintf(file, ")");
        fprintf(file, " = ");
        ast_print_expr(file, node->stmt._assign.value);
        fprintf(file, "\n");
        break;
      }
      case STMT_ELSEIF: case STMT_ELSE: {
        error_panic(error_parser, ERROR_SYNTAX_ELSEIF_ELSE);
      }
      case STMT_CASE: {
        error_panic(error_parser, ERROR_SYNTAX_CASE);
      }
      default: {
        error_panic(error_parser, ERROR_INVALID_STMT);
      }
    }
    node = node->next;
  }
}

// Print AST Expressions
void ast_print_expr(FILE* file, ASTN_Expr node) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);

  fprintf(file, "%s[%s", colors[BRIGHT_CYAN], colors[RESET]);
  switch (node->type) {
    case EXPR_BIN: {
      ast_print_expr(file, node->expr.binary.left);
      fprintf(file, " %s%s%s ", colors[MAGENTA], ast_match_expr_op(node->expr.binary.op), colors[RESET]);
      ast_print_expr(file, node->expr.binary.right);
      break;
    } 
    case EXPR_UN: {
      fprintf(file, " %s%s%s ", colors[MAGENTA], ast_match_expr_op(node->expr.unary.op), colors[RESET]);
      ast_print_expr(file, node->expr.unary.operand);
      if (node->expr.unary.op == OP_UN_PAREN)
        fprintf(file, "%s )%s ", colors[MAGENTA], colors[RESET]);
      break;
    } 
    case EXPR_FUN_CALL: {
      ast_print_fun_call(file, node->expr.fun_call.fun, node->expr.fun_call.args);
      break;
    }
    case EXPR_TOKEN: {
      ast_print_token(file, node->expr.token);
      break;
    } 
    default:
      error_panic(error_parser, ERROR_INVALID_EXPR);
  }
  fprintf(file, "%s]%s", colors[BRIGHT_CYAN], colors[RESET]);
}

void ast_print_fun_call(FILE* file, ASTN_Token fun, ASTN_ExprList args) {
  fprintf(file, "fun_call[");
  ast_print_token(file, fun);
  ast_print_expr_list(file, args);
  fprintf(file, "]");
}

void ast_print_expr_list(FILE* file, ASTN_ExprList node) {
  error_assert(error_nullptr, file != NULL);
  fprintf(file, "(");
  while (node) {
    ast_print_expr(file, node->expr);
    node = node->next;
    if (node)
      fprintf(file, ", ");
  }
  fprintf(file, ")");
}

void ast_print_ktype(FILE* file, ASTN_KType node) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);
  fprintf(file, "%s", colors[YELLOW]);
  if (node->is_default) {
    fprintf(file, "%s", ast_match_ktype_default(node->type._default));
  } else {
    ast_print_token(file, node->type._defined);
  }
  fprintf(file, "%s", colors[RESET]);
}

// Print AST Token
void ast_print_token(FILE* file, ASTN_Token token) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, token != NULL);

  fprintf(file, "%s", colors[GREEN]);;
  switch (token->type) {
    case TT_IDENT:
      fprintf(file, "ID(%s)", token->value.ident);
      break;
    case TT_LIT_STRING:
      fprintf(file, "STRING(%s)", token->value.lit_str);
      break;
    case TT_LIT_NUMBER:
      fprintf(file, "NUMBER(%zu)", token->value.lit_number);
      break;
    case TT_LIT_REAL:
      fprintf(file, "REAL(%.6lf)", token->value.lit_real);
      break;
    case TT_LIT_NULL:
      fprintf(file, "null");
      break;
    case TT_LIT_TRUE:
      fprintf(file, "true");
      break;
    case TT_LIT_FALSE:
      fprintf(file, "false");
      break;
    default:
      error_panic(error_parser, ERROR_INVALID_TT);
  }
  fprintf(file, "%s", colors[RESET]);
}

void ast_print_indent(FILE* file, int indent, const char* str) {
  error_assert(error_nullptr, file != NULL);
  fprintf(file, "%*c%s", 2 * indent, ' ', str);
}

const char* ast_match_expr_op(ASTN_ExprOp op) {
  switch (op) {
    case OP_NONE:
      return "NONE";
    case OP_UN_ARIT_PLUS:
      return "UN PLUS";
    case OP_UN_ARIT_MINUS:
      return "UN MINUS";
    case OP_UN_LOG_NOT:
      return "UN LOG NOT";
    case OP_UN_PAREN:
      return "(";
    case OP_BIN_ARIT_PLUS:
      return "BIN ARIT ADD";
    case OP_BIN_ARIT_MINUS:
      return "BIN ARIT SUB";
    case OP_BIN_ARIT_MUL:
      return "BIN ARIT MUL";
    case OP_BIN_ARIT_DIV:
      return "BIN ARIT DIV";
    case OP_BIN_COMP_EQUAL:
      return "BIN COMP EQUAL";
    case OP_BIN_COMP_NEQUAL:
      return "BIN COMP NOT EQUAL";
    case OP_BIN_COMP_LTHAN:
      return "BIN COMP LESS THAN";
    case OP_BIN_COMP_GTHAN:
      return "BIN COMP GREATER THAN";
    case OP_BIN_COMP_LEQUAL:
      return "BIN COMP LESS THAN EQUAL";
    case OP_BIN_COMP_GEQUAL:
      return "BIN COMP GREATER THAN EQUAL";
    case OP_BIN_LOG_AND:
      return "BIN LOG AND";
    case OP_BIN_LOG_OR:
      return "BIN LOG OR";
    default:
      error_panic(error_parser, ERROR_INVALID_EXPR_OP);
  }
  return NULL;
}

const char* ast_match_ktype_default(ASTN_KTypeDefault ktype) {
  switch (ktype) {
    case KOTLIN_ANY:
      return "Any";
    case KOTLIN_BYTE:
      return "Byte";
    case KOTLIN_SHORT:
      return "Short";
    case KOTLIN_INT:
      return "Int";
    case KOTLIN_LONG:
      return "Long";
    case KOTLIN_FLOAT:
      return "Float";
    case KOTLIN_DOUBLE:
      return "Double";
    case KOTLIN_CHAR:
      return "Char";
    case KOTLIN_STRING:
      return "String";
    case KOTLIN_BOOLEAN:
      return "Boolean";
    case KOTLIN_DECL: case KOTLIN_NOT_DEFAULT:
      error_panic(error_unexp, ERROR_INVALID_KTYPE);
  }
  return NULL;
}

void ast_error(ASTN_Token token, const char* error_msg) {
  error_assert(error_unexp, token != NULL);

  _error_print(error_parser, error_msg, filename, token->pos_line, token->pos_rel);
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, ERROR_IO_SOURCE_FILE, filename);
    return;
  }
  char line[1024];
  for (
    int current_line = 1;
    fgets(line, sizeof(line), file) && current_line != token->pos_line;
    current_line++
  );
  fclose(file);

  fprintf(stderr, "%s", line);
  for (int i = 1; i < token->pos_rel; i++)
    fprintf(stderr, " ");
  fprintf(stderr, "^\n");
}
