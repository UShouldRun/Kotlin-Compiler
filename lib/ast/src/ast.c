#include "ast_private.h"

static const uint64_t astn_sizes[] = {
  sizeof(struct astn_program),
  sizeof(struct astn_obj),
  sizeof(struct astn_enum_val),
  sizeof(struct astn_fun_ret),
  sizeof(struct astn_fun_arg),
  sizeof(struct astn_stmt),
  sizeof(struct astn_expr),
  sizeof(struct astn_ktype),
  sizeof(struct astn_token)
};

// =======================================# PUBLIC #==========================================

// AST Type Check

bool ast_type_check(Arena arena, AST program, const char* file, uint64_t s_buckets, float load_threshold_factor) {
  error_assert(error_type_checker, file != NULL);
  error_assert(error_type_checker, program != NULL);

  bool type_check = true;
  HashTable table = hashtable_create(s_buckets, load_threshold_factor);
  error_assert(error_type_checker, table != NULL);

  ASTN_Obj readln = astn_create_fun(
    arena,
    astn_create_token(arena, TT_IDENT, (void*)DEFAULT_READLN, file, 0, 0, 0),
    NULL,
    astn_create_fun_ret(
      arena,
      astn_create_ktype(arena, true, KOTLIN_INT, NULL, 0, 0, 0, 0),
      NULL
    ),
    NULL,
    NULL
  ),
  println = astn_create_fun(
    arena,
    astn_create_token(arena, TT_IDENT, (void*)DEFAULT_PRINTLN, file, 0, 0, 0),
    astn_create_fun_args(
      arena,
      astn_create_ktype(arena, true, KOTLIN_INT, NULL, 0, 0, 0, 0),
      astn_create_token(arena, TT_IDENT, (void*)DEFAULT_INPUT, file, 0, 0, 0),
      NULL
    ),
    NULL,
    NULL,
    NULL
  );

  ast_type_check_obj(file, arena, table, readln);
  ast_type_check_obj(file, arena, table, println);

  for (ASTN_Obj node = program->objects; node != NULL; node = node->next)
    if (node->type != ASTN_FUN)
      type_check = type_check && ast_type_check_obj(file, arena, table, node);
  for (ASTN_Obj node = program->objects; node != NULL; node = node->next)
    if (node->type == ASTN_FUN)
      type_check = type_check && ast_type_check_obj(file, arena, table, node);
  for (ASTN_Obj node = program->objects; node != NULL; node = node->next)
    if (node->type == ASTN_FUN) {
      Stack stack = stack_create();
      type_check = type_check && ast_type_check_stmt(
        file, arena, table, &stack, node->obj._fun.body, node->obj._fun.ret
      );
      error_assert(error_type_checker, stack_free(&stack) && stack == NULL);
    }

  error_assert(error_type_checker, hashtable_free(table));
  return type_check;
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

// AST Node Get Position

uint32_t astn_get_pos_first_line(void* ptr, ASTN_Type type) {
  if (ptr == NULL)
    return 0;

  switch (type) {
    case ASTN_TOKEN:
    case ASTN_VAR:       { return ((ASTN_Token)ptr)->line; }
    case ASTN_KTYPE:     { return ((ASTN_KType)ptr)->first_line; }
    case ASTN_EXPR:      { return ((ASTN_Expr)ptr)->first_line; }
    case ASTN_EXPR_LIST: { return ((ASTN_ExprList)ptr)->first_line; }
    case ASTN_STMT:      { return ((ASTN_Stmt)ptr)->first_line; }
    case ASTN_FUN_ARG:   { return ((ASTN_FunArg)ptr)->first_line; }
    case ASTN_FUN_RET:   { return ((ASTN_FunRet)ptr)->first_line; }
    case ASTN_ENUM_VAL:  { return ((ASTN_EnumVal)ptr)->first_line;}
    case ASTN_FUN:
    case ASTN_ENUM:      { return ((ASTN_Obj)ptr)->first_line; }
    default:             { return 0; }
  }
}

uint32_t astn_get_pos_last_line(void* ptr, ASTN_Type type) {
  if (ptr == NULL)
    return 0;

  switch (type) {
    case ASTN_TOKEN:
    case ASTN_VAR:       { return ((ASTN_Token)ptr)->line; }
    case ASTN_KTYPE:     { return ((ASTN_KType)ptr)->last_line; }
    case ASTN_EXPR:      { return ((ASTN_Expr)ptr)->last_line; }
    case ASTN_EXPR_LIST: { return ((ASTN_ExprList)ptr)->last_line; }
    case ASTN_STMT:      { return ((ASTN_Stmt)ptr)->last_line; }
    case ASTN_FUN_ARG:   { return ((ASTN_FunArg)ptr)->last_line; }
    case ASTN_FUN_RET:   { return ((ASTN_FunRet)ptr)->last_line; }
    case ASTN_ENUM_VAL:  { return ((ASTN_EnumVal)ptr)->last_line;}
    case ASTN_FUN:
    case ASTN_ENUM:      { return ((ASTN_Obj)ptr)->last_line; }
    default:             { return 0; }
  }
}

uint32_t astn_get_pos_first_col(void* ptr, ASTN_Type type) {
  if (ptr == NULL)
    return 0;

  switch (type) {
    case ASTN_TOKEN:
    case ASTN_VAR:       { return ((ASTN_Token)ptr)->start; }
    case ASTN_KTYPE:     { return ((ASTN_KType)ptr)->first_column; }
    case ASTN_EXPR:      { return ((ASTN_Expr)ptr)->first_column; }
    case ASTN_EXPR_LIST: { return ((ASTN_ExprList)ptr)->first_column; }
    case ASTN_STMT:      { return ((ASTN_Stmt)ptr)->first_column; }
    case ASTN_FUN_ARG:   { return ((ASTN_FunArg)ptr)->first_column; }
    case ASTN_FUN_RET:   { return ((ASTN_FunRet)ptr)->first_column; }
    case ASTN_ENUM_VAL:  { return ((ASTN_EnumVal)ptr)->first_column;}
    case ASTN_FUN:
    case ASTN_ENUM:      { return ((ASTN_Obj)ptr)->first_column; }
    default:             { return 0; }
  }
}

uint32_t astn_get_pos_last_col(void* ptr, ASTN_Type type)  {
  if (ptr == NULL)
    return 0;

  switch (type) {
    case ASTN_TOKEN:
    case ASTN_VAR:       { return ((ASTN_Token)ptr)->end; }
    case ASTN_KTYPE:     { return ((ASTN_KType)ptr)->last_column; }
    case ASTN_EXPR:      { return ((ASTN_Expr)ptr)->last_column; }
    case ASTN_EXPR_LIST: { return ((ASTN_ExprList)ptr)->last_column; }
    case ASTN_STMT:      { return ((ASTN_Stmt)ptr)->last_column; }
    case ASTN_FUN_ARG:   { return ((ASTN_FunArg)ptr)->last_column; }
    case ASTN_FUN_RET:   { return ((ASTN_FunRet)ptr)->last_column; }
    case ASTN_ENUM_VAL:  { return ((ASTN_EnumVal)ptr)->last_column;}
    case ASTN_FUN:
    case ASTN_ENUM:      { return ((ASTN_Obj)ptr)->last_column; }
    default:             { return 0; }
  }
}

// AST Node Set Position

void astn_set_pos_obj(ASTN_Obj node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;
}

void astn_set_pos_enum_val(ASTN_EnumVal node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;
}

void astn_set_pos_fun_arg(ASTN_FunArg node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;

}

void astn_set_pos_fun_ret(ASTN_FunRet node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;

}

void astn_set_pos_stmt(ASTN_Stmt node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;
}

void astn_set_pos_expr(ASTN_Expr node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;
}

void astn_set_pos_expr_list(ASTN_ExprList node, uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column) {
  if (node == NULL)
    return;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;
}

// AST Node Creation

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

  astn_set_pos_obj(node, ident->line, ident->line, ident->start, ident->end);

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

  ASTN_EnumVal last = node;
  for (; last != NULL && last->next != NULL; last = last->next);
  astn_set_pos_enum_val(
    node,
    value->line,
    last ? last->last_line : (atribute ? atribute->line : value->line),
    value->start,
    last ? last->last_column : (atribute ? atribute->end : value->end)
  );

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

  astn_set_pos_obj(node, ident->line, ident->line, ident->start, ident->end);

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

  ASTN_FunArg last = node;
  for (; last != NULL && last->next != NULL; last = last->next);
  astn_set_pos_fun_arg(
    node,
    type->first_line,
    last ? last->last_line : arg->line,
    type->first_column,
    last ? last->last_column : arg->end
  );

  return node;
}

ASTN_FunRet astn_create_fun_ret(Arena arena, ASTN_KType type, ASTN_FunRet next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, type != NULL);

  ASTN_FunRet node = (ASTN_FunRet)arena_alloc(arena, sizeof(struct astn_fun_ret));
  error_assert(error_mem, node != NULL);
  node->type = type;
  node->next = next;

  ASTN_FunRet last = node;
  for (; last != NULL && last->next != NULL; last = last->next);
  astn_set_pos_fun_ret(
    node,
    type->first_line,
    last ? last->last_line : type->first_line,
    type->first_column,
    last ? last->last_column : type->last_column
  );

  return node;
}

ASTN_Stmt astn_create_stmt_while(Arena arena, bool do_while, ASTN_Expr cond, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);

  if (cond == NULL)
    return astn_create_stmt_block(arena, block, next);

  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type              = do_while ? STMT_DO : STMT_WHILE;
  node->stmt._while.cond  = cond;
  node->stmt._while.block = block;
  node->next              = next;

  ASTN_Stmt last = block;
  for (; last != NULL && last->next != NULL; last = last->next);

  uint32_t block_first_line   = block ? block->first_line : cond->first_line,
           block_last_line    = block ? block->last_line : cond->last_line,
           block_first_column = block ? block->first_column : cond->first_column,
           block_last_column  = block ? block->last_column : cond->last_column;

  astn_set_pos_stmt(
    node,
    do_while ? block_first_line : cond->first_line,
    do_while ? cond->last_line : block_last_line,
    do_while ? block_first_column : cond->first_column,
    do_while ? cond->last_column : block_last_column
  );

  return node;
}

ASTN_Stmt astn_create_stmt_for(Arena arena, ASTN_Stmt init, ASTN_Expr cond, ASTN_Stmt incr, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);

  if (cond == NULL) {
    ASTN_Stmt node = init;
    if (init != NULL) {
      for (; node->next != NULL; node = node->next);
      node->next = block;
    }
    node = block;
    if (block != NULL) {
      for (; node->next != NULL; node = node->next);
      node->next = incr;
    }
    node = init ? init : (block ? block : incr);
    if (node == NULL)
      return next;
    return astn_create_stmt_block(arena, node, next);
  }
  if (incr == NULL) {
    ASTN_Stmt node = init;
    if (init != NULL) {
      for (; node->next != NULL; node = node->next);
      node->next = block;
    }
    return astn_create_stmt_while(arena, false, cond, init, next);
  }

  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_FOR;
  node->stmt._for.init  = init;
  node->stmt._for.cond  = cond;
  node->stmt._for.incr  = incr;
  node->stmt._for.block = block;
  node->next            = next;

  ASTN_Stmt last = block ? block : incr;
  for (; last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    init ? init->first_line : cond->first_line,
    last->last_line,
    init ? init->first_column : cond->first_column,
    last->last_column
  );

  return node;
}

ASTN_Stmt astn_create_stmt_if(Arena arena, ASTN_StmtType type, ASTN_Expr cond, ASTN_Stmt block, ASTN_Stmt elseif, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, type == STMT_IF || type == STMT_ELSEIF || type == STMT_ELSE || type == STMT_CASE);
  error_assert(error_unexp, type == STMT_ELSE || cond != NULL);
  if (cond == NULL && block == NULL)
    return NULL;

  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type           = type;
  node->stmt._if.cond  = type == STMT_ELSE ? NULL : cond;
  node->stmt._if.block = block;
  node->stmt._if.next  = type == STMT_ELSE ? NULL : elseif;
  node->next           = next;

  ASTN_Stmt last = block;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    cond ? cond->first_line : block->first_line,
    last ? last->last_line : cond->last_line,
    cond ? cond->first_column : block->first_column,
    last ? last->last_column : cond->last_column
  );

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

  ASTN_Stmt last = cases;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    cond->first_line,
    last ? last->last_line : cond->last_line,
    cond->first_column,
    last ? last->last_column : cond->last_column
  );

  return node;
}

ASTN_Stmt astn_create_stmt_ret(Arena arena, ASTN_ExprList value, uint32_t first_line) {
  error_assert(error_nullptr, arena != NULL);

  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type            = STMT_RETURN;
  node->stmt._ret.value = value;
  node->next            = NULL;

  ASTN_ExprList last = value;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    first_line,
    last ? last->last_line : first_line,
    value ? value->first_column : 0,
    last ? last->last_column : 0
  );

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

  ASTN_ExprList last = args;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    fun->line,
    last ? last->last_line : fun->line,
    fun->start,
    last ? last->last_column : fun->end
  );

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

  astn_set_pos_stmt(
    node,
    var->line,
    value ? value->last_line : var->line,
    var->start,
    value ? value->last_column : var->end
  );

  return node;
}

ASTN_Stmt astn_create_stmt_block(Arena arena, ASTN_Stmt block, ASTN_Stmt next) {
  error_assert(error_nullptr, arena != NULL);
  if (block == NULL)
    return next;

  ASTN_Stmt node = (ASTN_Stmt)arena_alloc(arena, sizeof(struct astn_stmt));
  error_assert(error_mem, node != NULL);
  node->type       = STMT_BLOCK;
  node->stmt.block = block;
  node->next       = next;

  ASTN_Stmt last = block;
  for (; last->next != NULL; last = last->next);

  astn_set_pos_stmt(
    node,
    block->first_line,
    last->last_line,
    block->first_column,
    last->last_column
  );

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

  astn_set_pos_expr(
    node,
    left->first_line,
    right->last_line,
    left->first_column,
    right->last_column
  );

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

  astn_set_pos_expr(
    node,
    operand->first_line,
    operand->last_line,
    operand->first_column,
    operand->last_column
  );

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

  ASTN_ExprList last = args;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_expr(
    node,
    fun->line,
    last ? last->last_line : fun->line,
    fun->start,
    last ? last->last_column : fun->end
  );

  return node;
}

ASTN_Expr astn_create_expr_token(Arena arena, ASTN_Token token) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, token != NULL);

  ASTN_Expr node = (ASTN_Expr)arena_alloc(arena, sizeof(struct astn_expr));
  error_assert(error_mem, node != NULL);
  node->type       = EXPR_TOKEN;
  node->expr.token = token;

  astn_set_pos_expr(
    node,
    token->line,
    token->line,
    token->start,
    token->end
  );

  return node;
}

ASTN_ExprList astn_create_expr_list(Arena arena, ASTN_Expr expr, ASTN_ExprList next) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_nullptr, expr != NULL);

  ASTN_ExprList node = (ASTN_ExprList)arena_alloc(arena, sizeof(struct astn_expr_list));
  error_assert(error_mem, node != NULL);
  node->expr = expr;
  node->next = next;

  ASTN_ExprList last = next;
  for (; last != NULL && last->next != NULL; last = last->next);

  astn_set_pos_expr_list(
    node,
    expr->first_line,
    last ? last->last_line : expr->last_line,
    expr->first_column,
    last ? last->last_column : expr->last_column
  );

  return node;
}

ASTN_Token astn_create_token(
  Arena arena, ASTN_TokenType type, void* value,
  const char* file, uint32_t line, uint32_t start, uint32_t end
) {
  error_assert(error_nullptr, arena != NULL);

  ASTN_Token node = (ASTN_Token)arena_alloc(arena, sizeof(struct astn_token));
  error_assert(error_mem, node != NULL);
  node->type  = type;
  node->file  = file;
  node->line  = line;
  node->start = start;
  node->end   = end;

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

ASTN_KType astn_create_ktype(
  Arena arena, bool is_default, ASTN_KTypeDefault _default, ASTN_Token _defined,
  uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column
) {
  error_assert(error_nullptr, arena != NULL);
  error_assert(error_unexp, is_default || _defined != NULL);

  ASTN_KType node = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
  error_assert(error_mem, node != NULL);
  node->is_default = is_default;
  if (is_default) node->type._default = _default;
  else            node->type._defined = _defined;
  node->first_line   = first_line;
  node->last_line    = last_line;
  node->first_column = first_column;
  node->last_column  = last_column;

  return node;
}

// =======================================# PRIVATE #==========================================

// AST Type Check
bool ast_type_check_obj(const char* file, Arena arena, HashTable table, ASTN_Obj node) {
  error_assert(error_type_checker, file != NULL);
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, node != NULL);

  bool type_check = true;
  switch (node->type) {
    case ASTN_FUN: {
      error_assert(
        error_type_checker,
        hashtable_insert_obj(&table, node->obj._fun.ident, node)
      );

      for (
        ASTN_FunArg node_arg = node->obj._fun.args;
        node_arg != NULL;
        node_arg = node_arg->next
      ) {
        type_check = type_check && ast_type_check_ktype(file, table, node_arg->type);
        error_assert(
          error_type_checker,
          hashtable_insert_var_ktype(&table, node_arg->arg, node_arg->type)
        );
      }

      for (
        ASTN_FunRet node_ret = node->obj._fun.ret;
        node_ret != NULL;
        type_check = type_check && ast_type_check_ktype(file, table, node_ret->type),
        node_ret = node_ret->next
      );

      break;
    }
    case ASTN_ENUM: {
      error_assert(
        error_type_checker,
        hashtable_insert_obj(&table, node->obj._enum.ident, node)
      );

      ASTN_KType ktype_enum = astn_create_ktype(
        arena, false, KOTLIN_NOT_DEFAULT, node->obj._enum.ident,
        node->first_line, node->last_line, node->first_column, node->last_column
      );
      error_assert(error_mem, ktype_enum != NULL);

      int32_t i = 0;
      for (
        ASTN_EnumVal node_value = node->obj._enum.values;
        node_value != NULL;
        node_value = node_value->next,
        i++
      ) {
        if (!node_value->is_atributed) {
          node_value->atribute->type = TT_LIT_NUMBER;
          node_value->atribute->value.lit_number = i;
          node_value->is_atributed = true;
        }
        error_assert(
          error_type_checker,
          hashtable_insert_var_ktype(&table, node_value->value, ktype_enum)
        );
      }

      break;
    }
    default: {
      error_panic(error_parser, ERROR_INVALID_OBJ);
    }
  }

  return type_check;
}

bool ast_type_check_stmt(const char* file, Arena arena, HashTable table, Stack* stack, ASTN_Stmt node, ASTN_FunRet ret) {
  error_assert(error_type_checker, file != NULL); 
  error_assert(error_type_checker, arena != NULL);
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, stack != NULL);
  error_assert(error_type_checker, node != NULL);
  
  bool type_check = true;
  while (node != NULL) {
    error_assert(error_type_checker, node != node->next);

    switch (node->type) {
      case STMT_WHILE: case STMT_DO: {
        stack_push_frame(stack);
        bool check_cond  = ast_type_check_expr_is_bool(file, arena, table, node->stmt._while.cond),
             check_block = ast_type_check_stmt(file, arena, table, stack, node->stmt._while.block, ret);
        type_check = type_check && check_cond && check_block;
        stack_pop_frame(stack, table);
        break;
      }
      case STMT_FOR: {
        stack_push_frame(stack);
        bool check_init  = ast_type_check_stmt(file, arena, table, stack, node->stmt._for.init, NULL),
             check_cond  = ast_type_check_expr_is_bool(file, arena, table, node->stmt._for.cond),
             check_incr  = ast_type_check_stmt(file, arena, table, stack, node->stmt._for.incr, NULL),
             check_block = ast_type_check_stmt(file, arena, table, stack, node->stmt._for.block, ret);
        type_check = type_check && check_init && check_cond && check_incr && check_block;
        stack_pop_frame(stack, table);
        break;
      }
      case STMT_IF: {
        stack_push_frame(stack);
        bool check_cond  = ast_type_check_expr_is_bool(file, arena, table, node->stmt._if.cond),
             check_block = ast_type_check_stmt(file, arena, table, stack, node->stmt._if.block, ret);
        type_check = type_check && check_cond && check_block;
        stack_pop_frame(stack, table);

        for (
          ASTN_Stmt node_stmt = node->stmt._if.next;
          node_stmt != NULL;
          node_stmt = node_stmt->stmt._if.next
        ) {
          stack_push_frame(stack);

          error_assert(
            error_type_checker,
            node_stmt != node_stmt->stmt._if.next
          );
          error_assert(
            error_type_checker,
            node_stmt->type == STMT_ELSEIF || node_stmt->type == STMT_ELSE
          );

          check_cond  = (
            node_stmt->type == STMT_ELSE ||
            ast_type_check_expr_is_bool(file, arena, table, node_stmt->stmt._if.cond)
          );
          check_block = ast_type_check_stmt(file, arena, table, stack, node_stmt->stmt._if.block, ret);
          type_check  = type_check && check_cond && check_block;

          stack_pop_frame(stack, table);
        }

        break;
      }
      case STMT_WHEN: {
        ASTN_KType switch_ktype = ast_type_check_expr(file, arena, table, node->stmt._when.cond);
        bool check_cases = true;
        type_check = type_check && switch_ktype;

        for (
          ASTN_Stmt node_stmt = node->stmt._when.cases;
          node_stmt != NULL;
          node_stmt = node_stmt->stmt._if.next
        ) {
          error_assert(
            error_type_checker,
            node_stmt != node_stmt->stmt._if.next
          );
          error_assert(
            error_type_checker,
            node_stmt->type == STMT_CASE || node_stmt->type == STMT_ELSE
          );

          ASTN_KType case_cond_ktype = ast_type_check_expr(file, arena, table, node_stmt->stmt._if.cond);
          bool check_cond  = ast_type_check_ktype_same(switch_ktype, case_cond_ktype); 

          stack_push_frame(stack);
          bool check_case = ast_type_check_stmt(file, arena, table, stack, node_stmt->stmt._if.block, ret);
          stack_pop_frame(stack, table);

          check_cases = check_cases && check_cond && check_case;
        }

        type_check = type_check && check_cases;
        break;
      }
      case STMT_BLOCK: {
        stack_push_frame(stack);
        bool check_block = ast_type_check_stmt(file, arena, table, stack, node->stmt.block, ret);
        stack_pop_frame(stack, table);

        type_check = type_check && check_block;
        break;
      }
      case STMT_FUN_CALL: {
        ASTN_Obj node_fun = hashtable_lookup_obj(table, node->stmt._fun_call.fun);
        if (node_fun == NULL) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_FUN,
            file,
            astn_get_pos_first_line((void*)node, ASTN_STMT),
            astn_get_pos_last_line((void*)node, ASTN_STMT),
            astn_get_pos_first_col((void*)node, ASTN_STMT),
            astn_get_pos_last_col((void*)node, ASTN_STMT)
          );
          type_check = false;
        } else {
          ASTN_ExprList fc_arg = node->stmt._fun_call.args;
          ASTN_FunArg   f_arg  = node_fun->obj._fun.args;  

          while (f_arg != NULL && fc_arg != NULL) {
            ASTN_KType expr_type = ast_type_check_expr(file, arena, table, fc_arg->expr);

            if (!ast_type_check_ktype_same(f_arg->type, expr_type)) {
              ast_error(
                error_type_checker,
                ERROR_TYPE_CONFLICT,
                file,
                astn_get_pos_first_line((void*)fc_arg->expr, ASTN_EXPR),
                astn_get_pos_last_line((void*)fc_arg->expr, ASTN_EXPR),
                astn_get_pos_first_col((void*)fc_arg->expr, ASTN_EXPR),
                astn_get_pos_last_col((void*)fc_arg->expr, ASTN_EXPR)
              );
              ast_print_fun_decl(stderr, node_fun);
              type_check = false;
            }

            f_arg  = f_arg->next;
            fc_arg = fc_arg->next;
          }

          if (f_arg != NULL && fc_arg == NULL) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_FEW_ARGS,
              file,
              astn_get_pos_first_line((void*)node, ASTN_STMT),
              astn_get_pos_last_line((void*)node, ASTN_STMT),
              astn_get_pos_first_col((void*)node, ASTN_STMT),
              astn_get_pos_last_col((void*)node, ASTN_STMT)
            );
            ast_print_fun_decl(stderr, node_fun);
            type_check = false;
          } else if (f_arg == NULL && fc_arg != NULL) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_MANY_ARGS,
              file,
              astn_get_pos_first_line((void*)fc_arg, ASTN_EXPR_LIST),
              astn_get_pos_last_line((void*)fc_arg, ASTN_EXPR_LIST),
              astn_get_pos_first_col((void*)fc_arg, ASTN_EXPR_LIST),
              astn_get_pos_last_col((void*)fc_arg, ASTN_EXPR_LIST)
            );
            ast_print_fun_decl(stderr, node_fun);
            type_check = false;
          }
        }

        break;
      }
      case STMT_RETURN: {
        ASTN_ExprList node_ret = node->stmt._ret.value;

        while (node_ret != NULL && ret != NULL) {
          ASTN_KType expr_type = ast_type_check_expr(file, arena, table, node_ret->expr);

          if (!ast_type_check_ktype_same(ret->type, expr_type)) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT,
              file,
              astn_get_pos_first_line((void*)node_ret->expr, ASTN_EXPR),
              astn_get_pos_last_line((void*)node_ret->expr, ASTN_EXPR),
              astn_get_pos_first_col((void*)node_ret->expr, ASTN_EXPR),
              astn_get_pos_last_col((void*)node_ret->expr, ASTN_EXPR)
            );
            type_check = false;
          }

          node_ret = node_ret->next;
          ret = ret->next;
        }

        if (ret != NULL && node_ret == NULL) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_FEW_RET,
            file,
            astn_get_pos_first_line((void*)node, ASTN_STMT),
            astn_get_pos_last_line((void*)node, ASTN_STMT),
            astn_get_pos_first_col((void*)node, ASTN_STMT),
            astn_get_pos_last_col((void*)node, ASTN_STMT)
          );
          type_check = false;
        } else if (ret == NULL && node_ret != NULL) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_MANY_RET,
            file,
            astn_get_pos_first_line((void*)node_ret->expr, ASTN_EXPR),
            astn_get_pos_last_line((void*)node_ret->expr, ASTN_EXPR),
            astn_get_pos_first_col((void*)node_ret->expr, ASTN_EXPR),
            astn_get_pos_last_col((void*)node_ret->expr, ASTN_EXPR)
          );
          type_check = false;
        }

        break;
      }
      case STMT_VAR_DECL: {
        if (!ast_type_check_ktype(file, table, node->stmt._assign.ktype)) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_KTYPE,
            file,
            astn_get_pos_first_line((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_last_line((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_first_col((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_last_col((void*)node->stmt._assign.ktype, ASTN_KTYPE)
          );
          type_check = false;
        }

        error_assert(
          error_type_checker,
          hashtable_insert_var_ktype(&table, node->stmt._assign.var, node->stmt._assign.ktype)
        );
        error_assert(
          error_type_checker,
          stack_push(stack, node->stmt._assign.var)
        );
        break;
      } 
      case STMT_VAR_DECL_ASSIGN: {
        if (!ast_type_check_ktype(file, table, node->stmt._assign.ktype)) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_KTYPE,
            file,
            astn_get_pos_first_line((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_last_line((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_first_col((void*)node->stmt._assign.ktype, ASTN_KTYPE),
            astn_get_pos_last_col((void*)node->stmt._assign.ktype, ASTN_KTYPE)
          );
          type_check = false;
        }

        ASTN_KType expr_ktype = ast_type_check_expr(file, arena, table, node->stmt._assign.value);
        bool check_expr = true;
        if (!(node->stmt._assign.ktype->is_default && node->stmt._assign.ktype->type._default == KOTLIN_ANY)) {
          check_expr = ast_type_check_ktype_same(node->stmt._assign.ktype, expr_ktype); 
        } else {
          node->stmt._assign.ktype = expr_ktype;
        }
        if (!check_expr) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_CONFLICT,
            file,
            astn_get_pos_first_line((void*)node, ASTN_STMT),
            astn_get_pos_last_line((void*)node, ASTN_STMT),
            astn_get_pos_first_col((void*)node, ASTN_STMT),
            astn_get_pos_last_col((void*)node, ASTN_STMT)
          );
        }

        error_assert(
          error_type_checker,
          hashtable_insert_var_ktype(&table, node->stmt._assign.var, node->stmt._assign.ktype)
        );
        error_assert(
          error_type_checker,
          stack_push(stack, node->stmt._assign.var)
        );

        type_check = type_check && check_expr;
        break;
      }
      case STMT_VAR_DIRECT_ASSIGN: {
        ASTN_KType var_ktype = hashtable_lookup_var_ktype(table, node->stmt._assign.var);

        if (var_ktype == NULL) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_IDENT,
            file,
            astn_get_pos_first_line((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_last_line((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_first_col((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_last_col((void*)node->stmt._assign.var, ASTN_TOKEN)
          );
        } else {
          ASTN_KType expr_ktype = ast_type_check_expr(file, arena, table, node->stmt._assign.value);

          bool check_expr = true;
          if (!(node->stmt._assign.ktype->is_default && node->stmt._assign.ktype->type._default == KOTLIN_ANY)) {
            check_expr = ast_type_check_ktype_same(node->stmt._assign.ktype, expr_ktype); 
          } else {
            node->stmt._assign.ktype = expr_ktype;
          }
          if (!check_expr) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT,
              file,
              astn_get_pos_first_line((void*)node, ASTN_STMT),
              astn_get_pos_last_line((void*)node, ASTN_STMT),
              astn_get_pos_first_col((void*)node, ASTN_STMT),
              astn_get_pos_last_col((void*)node, ASTN_STMT)
            );
          }

          type_check = type_check && check_expr;
        }
        break;
      }
      case STMT_VAR_INCR_BEFORE: case STMT_VAR_DECR_BEFORE:
      case STMT_VAR_INCR_AFTER:  case STMT_VAR_DECR_AFTER: {
        ASTN_KType var_ktype = hashtable_lookup_var_ktype(table, node->stmt._assign.var);
        if (var_ktype == NULL) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_IDENT,
            file,
            astn_get_pos_first_line((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_last_line((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_first_col((void*)node->stmt._assign.var, ASTN_TOKEN),
            astn_get_pos_last_col((void*)node->stmt._assign.var, ASTN_TOKEN)
          );
        } else {
          bool check_ktype = ast_type_check_ktype_is_number(var_ktype);

          if (!check_ktype) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT_NUM,
              file,
              astn_get_pos_first_line((void*)node, ASTN_STMT),
              astn_get_pos_last_line((void*)node, ASTN_STMT),
              astn_get_pos_first_col((void*)node, ASTN_STMT),
              astn_get_pos_last_col((void*)node, ASTN_STMT)
            );
          }

          type_check = type_check && check_ktype;
        }

        break;
      }
      case STMT_VAR_EQUALS_PLUS: case STMT_VAR_EQUALS_MINUS:
      case STMT_VAR_EQUALS_MUL:  case STMT_VAR_EQUALS_DIV: {
        ASTN_KType var_ktype = hashtable_lookup_var_ktype(table, node->stmt._assign.var);
        if (var_ktype == NULL) {
          ast_error(
            error_type_checker,
            ERROR_UNDEFINED_IDENT,
            file,
            astn_get_pos_first_line((void*)node, ASTN_STMT),
            astn_get_pos_last_line((void*)node, ASTN_STMT),
            astn_get_pos_first_col((void*)node, ASTN_STMT),
            astn_get_pos_last_col((void*)node, ASTN_STMT)
          );
        } else {
          bool check_ktype = ast_type_check_ktype_is_number(var_ktype);

          if (!check_ktype) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT_NUM,
              file,
              astn_get_pos_first_line((void*)node, ASTN_STMT),
              astn_get_pos_last_line((void*)node, ASTN_STMT),
              astn_get_pos_first_col((void*)node, ASTN_STMT),
              astn_get_pos_last_col((void*)node, ASTN_STMT)
            );
          }
          type_check = type_check && check_ktype;

          ASTN_KType expr_ktype = ast_type_check_expr(file, arena, table, node->stmt._assign.value);
          bool check_expr = ast_type_check_ktype_same(var_ktype, expr_ktype);

          if (!check_expr) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT,
              file,
              astn_get_pos_first_line((void*)node, ASTN_STMT),
              astn_get_pos_last_line((void*)node, ASTN_STMT),
              astn_get_pos_first_col((void*)node, ASTN_STMT),
              astn_get_pos_last_col((void*)node, ASTN_STMT)
            );
          }

          type_check = type_check && check_expr;
        }

        break;
      }
      case STMT_ELSEIF: case STMT_ELSE: {
        ast_error(
          error_parser,
          ERROR_SYNTAX_ELSEIF_ELSE,
          file,
          astn_get_pos_first_line((void*)node, ASTN_STMT),
          astn_get_pos_last_line((void*)node, ASTN_STMT),
          astn_get_pos_first_col((void*)node, ASTN_STMT),
          astn_get_pos_last_col((void*)node, ASTN_STMT)
        );
        break;
      }
      case STMT_CASE: {
        ast_error(
          error_parser,
          ERROR_SYNTAX_CASE,
          file,
          astn_get_pos_first_line((void*)node, ASTN_STMT),
          astn_get_pos_last_line((void*)node, ASTN_STMT),
          astn_get_pos_first_col((void*)node, ASTN_STMT),
          astn_get_pos_last_col((void*)node, ASTN_STMT)
        );
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

ASTN_KType ast_type_check_expr(const char* file, Arena arena, HashTable table, ASTN_Expr node) {
  error_assert(error_type_checker, file != NULL); 
  error_assert(error_type_checker, arena != NULL);
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, node != NULL);
  ASTN_KType expr_ktype = NULL;

  switch (node->type) {
    case EXPR_TOKEN: {
      ASTN_Token token = node->expr.token;
      ASTN_KType token_ktype = NULL;

      switch (token->type) {
        case TT_IDENT: {
          token_ktype = hashtable_lookup_var_ktype(table, token);
          break;
        }
        case TT_LIT_REAL: case TT_LIT_NUMBER:
        case TT_LIT_TRUE: case TT_LIT_FALSE:
        case TT_LIT_STRING: case TT_LIT_NULL: {
          token_ktype = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
          error_assert(error_mem, token_ktype != NULL);
          token_ktype->is_default = true;

          switch (token->type) {
            case TT_LIT_REAL: {
              token_ktype->type._default = KOTLIN_DOUBLE;
              break;
            }
            case TT_LIT_NUMBER: case TT_LIT_NULL: {
              token_ktype->type._default = KOTLIN_INT;
              break;
            }
            case TT_LIT_TRUE: case TT_LIT_FALSE: {
              token_ktype->type._default = KOTLIN_BOOLEAN;
              break;
            }
            case TT_LIT_STRING: {
              token_ktype->type._default = KOTLIN_STRING;
              break;
            }
            case TT_IDENT: default: {
              error_panic(error_type_checker, ERROR_INVALID_TT);
            }
          }

          break;
        }
        default: {
          error_panic(error_type_checker, ERROR_INVALID_TT);
        }
      }

      if (token_ktype == NULL) {
        ast_error(
          error_type_checker,
          ERROR_UNDEFINED_IDENT,
          file,
          astn_get_pos_first_line((void*)token, ASTN_TOKEN),
          astn_get_pos_last_line((void*)token, ASTN_TOKEN),
          astn_get_pos_first_col((void*)token, ASTN_TOKEN),
          astn_get_pos_last_col((void*)token, ASTN_TOKEN)
        );
      } else {
        expr_ktype = ast_type_check_ktype_copy(arena, token_ktype);;
        error_assert(error_mem, expr_ktype != NULL);
      }

      break;
    }
    case EXPR_UN: { 
      switch (node->expr.unary.op) {
        case OP_UN_ARIT_PLUS: case OP_UN_ARIT_MINUS: {
          ASTN_KType un_ktype = ast_type_check_expr(file, arena, table, node->expr.unary.operand);
          if (un_ktype == NULL)
            break;

          if (!(un_ktype->is_default && ast_type_check_ktype_is_number(un_ktype))) {
            ast_error(
              error_type_checker,
              file,
              ERROR_TYPE_CONFLICT_NUM,
              astn_get_pos_first_line((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_last_line((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_first_col((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_last_col((void*)node->expr.unary.operand, ASTN_EXPR)
            );
          } else {
            expr_ktype = un_ktype;
          }

          break;
        }
        case OP_UN_LOG_NOT: {
          ASTN_KType un_ktype = ast_type_check_expr(file, arena, table, node->expr.unary.operand);
          if (un_ktype == NULL)
            break;

          if (!(un_ktype->is_default && un_ktype->type._default == KOTLIN_BOOLEAN)) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT_BOOL,
              file,
              astn_get_pos_first_line((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_last_line((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_first_col((void*)node->expr.unary.operand, ASTN_EXPR),
              astn_get_pos_last_col((void*)node->expr.unary.operand, ASTN_EXPR)
            );
          } else {
            expr_ktype = un_ktype;
          }

          break;
        }
        case OP_UN_PAREN: {
          return ast_type_check_expr(file, arena, table, node->expr.unary.operand);
        }
        default: {
          error_panic(error_type_checker, ERROR_INVALID_EXPR_OP);
        }
      }
      break;
    }
    case EXPR_BIN: {
      ASTN_KType left_ktype  = ast_type_check_expr(file, arena, table, node->expr.binary.left),
                 right_ktype = ast_type_check_expr(file, arena, table, node->expr.binary.right);
      if (left_ktype != NULL && right_ktype != NULL) {
        if (!ast_type_check_ktype_same(left_ktype, right_ktype)) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_CONFLICT,
            file,
            astn_get_pos_first_line((void*)node, ASTN_EXPR),
            astn_get_pos_last_line((void*)node, ASTN_EXPR),
            astn_get_pos_first_col((void*)node, ASTN_EXPR),
            astn_get_pos_last_col((void*)node, ASTN_EXPR)
          );
        } else {
          expr_ktype = ast_type_check_ktype_copy(arena, left_ktype);
          error_assert(error_mem, expr_ktype != NULL);
        }
      }
      break;
    }
    case EXPR_FUN_CALL: {
      ASTN_Obj node_fun = hashtable_lookup_obj(table, node->expr.fun_call.fun);
      if (node_fun == NULL) {
        ast_error(
          error_type_checker,
          ERROR_UNDEFINED_FUN,
          file,
          astn_get_pos_first_line((void*)node, ASTN_EXPR),
          astn_get_pos_last_line((void*)node, ASTN_EXPR),
          astn_get_pos_first_col((void*)node, ASTN_EXPR),
          astn_get_pos_last_col((void*)node, ASTN_EXPR)
        );
      } else {
        ASTN_ExprList fc_arg = node->expr.fun_call.args;
        ASTN_FunArg   f_arg  = node_fun->obj._fun.args;  

        while (f_arg != NULL && fc_arg != NULL) {
          ASTN_KType expr_type = ast_type_check_expr(file, arena, table, fc_arg->expr);

          if (!ast_type_check_ktype_same(f_arg->type, expr_type)) {
            ast_error(
              error_type_checker,
              ERROR_TYPE_CONFLICT,
              file,
              astn_get_pos_first_line((void*)fc_arg->expr, ASTN_EXPR),
              astn_get_pos_last_line((void*)fc_arg->expr, ASTN_EXPR),
              astn_get_pos_first_col((void*)fc_arg->expr, ASTN_EXPR),
              astn_get_pos_last_col((void*)fc_arg->expr, ASTN_EXPR)
            );
            ast_print_fun_decl(stderr, node_fun);
          }

          f_arg  = f_arg->next;
          fc_arg = fc_arg->next;
        }

        if (f_arg != NULL && fc_arg == NULL) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_FEW_ARGS,
            file,
            astn_get_pos_first_line((void*)node, ASTN_EXPR),
            astn_get_pos_last_line((void*)node, ASTN_EXPR),
            astn_get_pos_first_col((void*)node, ASTN_EXPR),
            astn_get_pos_last_col((void*)node, ASTN_EXPR)
          );
          ast_print_fun_decl(stderr, node_fun);
        } else if (f_arg == NULL && fc_arg != NULL) {
          ast_error(
            error_type_checker,
            ERROR_TYPE_MANY_ARGS,
            file,
            astn_get_pos_first_line((void*)fc_arg->expr, ASTN_EXPR),
            astn_get_pos_last_line((void*)fc_arg->expr, ASTN_EXPR),
            astn_get_pos_first_col((void*)fc_arg->expr, ASTN_EXPR),
            astn_get_pos_last_col((void*)fc_arg->expr, ASTN_EXPR)
          );
          ast_print_fun_decl(stderr, node_fun);
        }

        uint32_t s_ktypes = 0;
        for (
          ASTN_FunRet node_fret = node_fun->obj._fun.ret;
          node_fret != NULL;
          s_ktypes++,
          node_fret = node_fret->next
        );
        
        if (s_ktypes > 1) {
          ast_error(
            error_type_checker,
            ERROR_NOT_IMPLEMENT_RET,
            file,
            astn_get_pos_first_line((void*)node, ASTN_EXPR),
            astn_get_pos_last_line((void*)node, ASTN_EXPR),
            astn_get_pos_first_col((void*)node, ASTN_EXPR),
            astn_get_pos_last_col((void*)node, ASTN_EXPR)
          );
        }

        expr_ktype = node_fun->obj._fun.ret->type;
      }

      break;
    }
  }

  return expr_ktype;
}

ASTN_KType ast_type_check_ktype_copy(Arena arena, ASTN_KType ktype) {
  error_assert(error_nullptr, arena != NULL);
  if (!ktype) return NULL;

  ASTN_KType cp = (ASTN_KType)arena_alloc(arena, sizeof(struct astn_ktype));
  error_assert(error_mem, cp != NULL);

  cp->is_default = ktype->is_default;
  if (!cp->is_default) {
    cp->type._defined = (ASTN_Token)arena_alloc(arena, sizeof(struct astn_token));
    error_assert(error_mem, cp->type._defined != NULL);

    cp->type._defined->type = ktype->type._defined->type;
    switch (cp->type._defined->type) {
      case TT_IDENT: {
        cp->type._defined->value.ident = arena_strdup(
          arena,
          (char*)ktype->type._defined->value.ident
        );
        break;
      }
      default: {
        error_panic(error_type_checker, ERROR_INVALID_TT);
        break;
      }
    }
  } else {
    cp->type._default = ktype->type._default;
  }

  return cp;
}

bool ast_type_check_expr_is_bool(const char* file, Arena arena, HashTable table, ASTN_Expr node) {
  ASTN_KType expr_ktype = ast_type_check_expr(file, arena, table, node);
  return expr_ktype != NULL && expr_ktype->is_default && expr_ktype->type._default == KOTLIN_BOOLEAN;
}

bool ast_type_check_ktype_same(ASTN_KType a, ASTN_KType b) {
  return a != NULL && b != NULL && (
       (a->is_default && b->is_default && a->type._default == b->type._default) 
    || (!a->is_default && !b->is_default && ast_type_check_token_equals(a->type._defined, b->type._defined))
  );
}

bool ast_type_check_token_equals(ASTN_Token a, ASTN_Token b) {
  if (a == NULL || b == NULL)
    return false;
  if (a->type != b->type)
    return false;
  switch (a->type) {
    case TT_LIT_NULL: case TT_LIT_TRUE: case TT_LIT_FALSE: 
      { return true; }
    case TT_LIT_NUMBER: 
      { return a->value.lit_number == b->value.lit_number; }
    case TT_LIT_REAL:
      { return a->value.lit_real == b->value.lit_real; }
    case TT_LIT_STRING:
      { return strcmp(a->value.lit_str, b->value.lit_str) == 0; }
    case TT_IDENT:
      { return strcmp(a->value.ident, b->value.ident) == 0; }
    default:
      { error_panic(error_type_checker, ERROR_INVALID_TT); }
  }
  return false;
}

bool ast_type_check_ktype_is_number(ASTN_KType node) {
  return node != NULL && node->is_default && (
       node->type._default == KOTLIN_BYTE  || node->type._default == KOTLIN_SHORT
    || node->type._default == KOTLIN_INT   || node->type._default == KOTLIN_LONG
    || node->type._default == KOTLIN_FLOAT || node->type._default == KOTLIN_DOUBLE
  );
}

bool ast_type_check_ktype(const char* file, HashTable table, ASTN_KType ktype) {
  error_assert(error_type_checker, file != NULL); 
  error_assert(error_type_checker, table != NULL);
  error_assert(error_type_checker, ktype != NULL);
  if (ktype->is_default)
    return true;
  ASTN_Obj node = hashtable_lookup_obj(table, ktype->type._defined);
  return node != NULL && node->type != ASTN_FUN;
}

// AST Print
void ast_print_obj(FILE* file, ASTN_Obj node, int32_t indent) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);

  ast_print_indent(file, indent, "");
  if (node->type == ASTN_FUN) {
    ast_print_fun_decl(file, node);
    ast_print_indent(file, indent, "{\n");
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

void ast_print_fun_decl(FILE* file, ASTN_Obj node) {
  error_assert(error_nullptr, file != NULL);
  error_assert(error_nullptr, node != NULL);

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

  fprintf(file, ")\n");
}

// Print AST Statements
void ast_print_stmt(FILE* file, ASTN_Stmt node, int32_t indent) {
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

void ast_print_indent(FILE* file, int32_t indent, const char* str) {
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

void ast_error(
  ErrorType error, const char* error_msg, const char* filename,
  uint32_t first_line, uint32_t last_line, uint32_t first_column, uint32_t last_column
) {
  error_print_kotlin(error, error_msg, filename, first_line, -1);

  if (first_line == 0 && last_line == 0 && first_column == 0 && last_column == 0)
    return;
  
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, ERROR_IO_SOURCE_FILE, filename);
    return;
  }

  char line[1024];
  uint32_t current_line = 1;

  while (fgets(line, sizeof(line), file)) {
    if (current_line >= first_line && current_line <= last_line) {
      fprintf(stderr, "%s", line);

      uint32_t start_column = (current_line == first_line) ? first_column : 1;
      uint32_t end_column = (current_line == last_line) ? last_column : strlen(line);
      
      for (uint32_t i = 1; i < start_column; i++)
        fprintf(stderr, " ");

      fprintf(stderr, "%s", colors[RED]);
      for (uint32_t i = start_column; i <= end_column; i++)
        fprintf(stderr, "^");
      fprintf(stderr, "%s", colors[RESET]);

      fprintf(stderr, "\n");
    }

    if (current_line > last_line)
      break;

    current_line++;
  }

  fclose(file);
}

