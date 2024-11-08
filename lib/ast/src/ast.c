#include "ast_private.h"

// =======================================# PUBLIC #==========================================

void ast_print(AST program) {
  fprintf(stdout, "%p\n", (void*)program);
}

uint64_t astn_max_size() {
  uint64_t max = astn_sizes[0];
  for (uint32_t i = 1; i < sizeof(astn_sizes)/sizeof(uint64_t); i++)
    if (max < astn_sizes[i])
      max = astn_sizes[i];
  return max;
}

AST ast_create(Arena arena, const char* name, ASTN_Obj objects, ASTN_Obj main) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, main != NULL);
  AST program = (AST)arena_alloc(arena, sizeof(struct astn_program));
  if (program == NULL)
    return NULL;
  program->name    = name;
  program->objects = objects;
  program->main    = main;
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
  error_assert(error_nullptr, args != NULL);
  error_assert(error_nullptr, ret != NULL);
  ASTN_Obj node = (ASTN_Obj)arena_alloc(arena, sizeof(struct astn_obj));
  error_assert(error_mem, node != NULL);
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
  node->type             = do_while ? STMT_DO : STMT_WHILE;
  node->stmt._while.cond  = cond;
  node->stmt._while.block = block;
  node->next             = next;
  return node;
}

ASTN_Stmt astn_create_stmt_for(Arena arena, ASTN_Stmt init, ASTN_Expr cond, ASTN_Stmt incr, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = STMT_FOR;
  node->stmt._for.init  = init;
  node->stmt._for.cond  = cond;
  node->stmt._for.incr  = incr;
  node->stmt._for.block = block;
  node->next           = next;
  return node;
}

ASTN_Stmt astn_create_stmt_if(Arena arena, ASTN_StmtType type, ASTN_Expr cond, ASTN_Stmt block, ASTN_Stmt elseif, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  error_assert(error_unexp, type == STMT_IF || type == STMT_ELSEIF || type == STMT_ELSE || type == STMT_CASE);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type          = type;
  node->stmt._if.cond  = type == STMT_ELSE ? NULL : cond;
  node->stmt._if.block = block;
  node->stmt._if.next  = type == STMT_ELSE ? NULL : elseif;
  node->next          = next;
  return node;
}

ASTN_Stmt astn_create_stmt_when(Arena arena, ASTN_Expr cond, ASTN_Stmt cases, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_WHEN;
  node->stmt._when.cond  = cond;
  node->stmt._when.cases = cases;
  node->next            = next;
  return node;
}

ASTN_Stmt astn_create_stmt_ret(Arena arena, ASTN_ExprList value) {
  error_assert(error_nullptr, arena != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = STMT_RETURN;
  node->stmt._ret.value = value;
  node->next           = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_fcall(Arena arena, ASTN_Token fun, ASTN_ExprList args, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, var != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type                = STMT_FUN_CALL;
  node->next                = next;
  node->stmt._fun_call.args = args;
  node->stmt._fun_call.fun  = fun;
  return node;
}

ASTN_Stmt astn_create_stmt_assign(Arena arena, ASTN_Type type, ASTN_Token var, ASTN_KType ktype, ASTN_Expr value, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, var != NULL);
  error_assert(
    error_unexp,
    type == STMT_VAR_INCR_BEFORE || type == STMT_VAR_INCR_AFTER || type == STMT_VAR_DECR_BEFORE || type == STMT_VAR_DECR_AFTER ||
    type == STMT_VAR_EQUALS_PLUS || type == STMT_VAR_EQUALS_MINUS || type == STMT_VAT_EQUALS_MUL ||  type == STMT_VAR_EQUALS_DIV ||
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

ASTN_ExprList astn_create_expr_list(Arena arena, ASTN_Expr expr, ASTN_Expr next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, arg != NULL);
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
    case TT_LIT_NUMBER: node->value.lit_number = *(int64_t*)value;
    case TT_LIT_REAL:   node->value.lit_real   = *(double*)value; 
    case TT_LIT_TRUE:   node->value.lit_bool   = true;
    case TT_LIT_FALSE:  node->value.lit_bool   = false;
    case TT_LIT_NULL:   node->value.lit_null   = true;
    case TT_LIT_STRING: node->value.lit_str    = (const char*)value;
    case TT_IDENT:      node->value.ident      = (const char*)value;
    default:            error_panic(error_unexp, ERROR_INVALID_TT);
  }
  return node;
}

ASTN_KType astn_create_ktype(Arena arena, bool is_default, ASTN_KTypeDefault _default, ASTN_Token _defined) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, !is_default && defined == NULL); 
  ASTN_KType node = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
  error_assert(error_mem, node != NULL);
  node->is_default = is_default;
  if (is_default) node->type._default = _default;
  else            node->type._defined = _defined;
  return node;
}

// =======================================# PRIVATE #==========================================
