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

AST ast_create(Arena arena, const char* name, ASTN_Obj objects, ASTN_Func main) {
  error_assert(error_nullptr, arena != NULL);
  AST program = (AST)arena_alloc(arena, sizeof(struct astn_program));
  if (program == NULL)
    return NULL;
  program->name    = name;
  program->objects = objects;
  program->main    = main;
  return program;
}

ASTN_Obj astn_create_enum(Arena arena, ASTN_Token ident, ASTN_EnumVal values) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, ident != NULL);
  ASTN_Obj node = (ASTN_Obj)arena_alloc(arena, sizeof(struct astn_obj));
  error_assert(error_mem, node != NULL);
  node->type               = ASTN_ENUM;
  node->obj.enum.ident     = ident;
  node->obj.enum.values    = values;
  return node;
}

ASTN_Obj astn_create_enum_val(Arena arena, ASTN_Token value, int64_t atribute) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, value != NULL);
  ASTN_Obj node = (ASTN_Obj)arena_alloc(arena, sizeof(struct astn_enum_val));
  error_assert(error_mem, node != NULL);
  node->atribute = atribute;
  node->value    = value;
  node->next     = NULL;
  return node;
}

ASTN_Obj astn_create_func(Arena arena, ASTN_Token ident, ASTN_FuncArg args, ASTN_FuncRet ret, ASTN_Stmt body) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, ident != NULL);
  error_assert(error_nullptr, args != NULL);
  error_assert(error_nullptr, ret != NULL);
  ASTN_Func node = (ASTN_Func)arena_alloc(arena, sizeof(struct astn_func));
  error_assert(error_mem, node != NULL);
  node->obj.fun.ident = ident;
  node->obj.fun.args  = args;
  node->obj.fun.ret   = ret;
  node->obj.fun.body  = body;
  return node;
}

ASTN_Obj astn_create_func_args(Arena arena, ASTN_KType type, ASTN_Token arg) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, type != NULL);
  error_assert(error_nullptr, arg != NULL);
  ASTN_Func node = (ASTN_Func)arena_alloc(arena, sizeof(struct astn_func_arg));
  error_assert(error_mem, node != NULL);
  node->type = ident;
  node->arg  = args;
  node->next = NULL;
  return node;
}

ASTN_Obj astn_create_func_ret(Arena arena, ASTN_KType type) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, type != NULL);
  ASTN_Func node = (ASTN_Func)arena_alloc(arena, sizeof(struct astn_func_return));
  error_assert(error_mem, node != NULL);
  node->type = ident;
  node->next = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_while(Arena arena, bool do_while, ASTN_Expr cond, ASTN_Stmt block) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type             = do_while ? STMT_DO : STMT_WHILE;
  node->stmt.while.cond  = cond;
  node->stmt.while.block = block;
  node->next             = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_for(Arena arena, ASTN_Stmt init, ASTN_Expr cond, ASTN_Stmt incr, ASTN_Stmt block) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = STMT_FOR;
  node->stmt.for.init  = init;
  node->stmt.for.cond  = cond;
  node->stmt.for.incr  = incr;
  node->stmt.for.block = block;
  node->next           = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_if(Arena arena, ASTN_StmtType type, ASTN_Expr cond, ASTN_Stmt block) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  error_assert(error_unexp, type == STMT_IF || type == STMT_ELSEIF || type == STMT_ELSE || type == STMT_CASE);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type          = type;
  node->stmt.if.cond  = type == STMT_ELSE ? NULL : cond;
  node->stmt.if.block = block;
  node->stmt.if.next  = NULL;
  node->next          = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_when(Arena arena, ASTN_Expr cond, ASTN_Stmt cases) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, cond != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_WHEN;
  node->stmt.when.cond  = cond;
  node->stmt.when.cases = cases;
  node->next            = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_ret(Arena arena, ASTN_Expr value) {
  error_assert(error_nullptr, arena != NULL);
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = STMT_RETURN;
  node->stmt.ret.value = value;
  node->stmt.ret.net   = NULL;
  node->next           = NULL;
  return node;
}

ASTN_Stmt astn_create_stmt_assign(Arena arena, ASTN_Type type, ASTN_Token var, ASTN_Ktype ktype, ASTN_Expr value) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, var != NULL);
  error_assert(
    error_unexp,
    type == STMT_INCR || type == STMT_DECR || type == STMT_DIRECT_ASSIGN || type == STMT_DECL || type == STMT_DECL_ASSIGN
  );
  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);

  node->type            = type;
  node->next            = NULL;
  node->stmt.assign.var = var;

  if (type == STMT_INCR || type == STMT_DECR)
    return node;

  node->stmt.assign.ktype = type == STMT_DIRECT_ASSIGN ? KOTLIN_DECL : ktype;
  node->stmt.assign.value = value;

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

ASTN_Expr astn_create_expr_fcall(Arena arena, ASTN_Token func, ASTN_Expr arg) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, func != NULL);
  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type = EXPR_FUNC_CALL;
  node->expr.func_call.func = func;
  node->expr.func_call.arg  = arg;
  node->expr.func_call.next = NULL;
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

ASTN_Token astn_create_token(Arena arena, ASTN_TokenType type, void* value, const char* file, uint32_t abs, uint32_t line, uint32_t rel) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, value != NULL);
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
    case TT_LIT_STRING: node->value.lit_str    = (const char*)value;
    case TT_IDENT:      node->value.ident      = (const char*)value;
    default:            error_panic(error_unexp, ERROR_INVALID_TT);
  }
  return node;
}

ASTN_KType astn_create_ktype(Arena arena, bool is_default, ASTN_KTypeDefault default, ASTN_Token defined) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, !is_default && defined == NULL); 
  ASTN_KType node = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
  error_assert(error_mem, node != NULL);
  node->is_default = is_default;
  if (is_default) node->type.default = default;
  else            node->type.defined = defined;
  return node;
}

// =======================================# PRIVATE #==========================================
