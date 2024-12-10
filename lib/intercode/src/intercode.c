#include "intercode_private.h"

Quad ic_translate_ast(Arena arena, AST program, uint64_t s_buckets, float load_threshold_factor) {
  error_assert(error_intercode, arena != NULL);
  error_assert(error_intercode, program != NULL);

  SymbolTable table = symboltable_create(s_buckets, load_threshold_factor);
  error_assert(error_intercode, table != NULL);
  SymbolStack stack = symbolstack_create();
  error_assert(error_intercode, stack != NULL);

  uint32_t temp_counter = 0, label_counter = 0;
  Quad head = NULL, tail = NULL;

  for (
    ASTN_Obj node = program->objects;
    node != NULL;
    node = node->next
  ) {
    if (node->type != ASTN_FUN)
      error_panic(error_intercode, "Only implemented functions in intercode generation");

    Quad fquad = ic_translate_func(
      arena, &table, &stack, node, &temp_counter, &label_counter
    );

    if (head == NULL) {
      head = tail = fquad;
    } else {
      tail->next = fquad;
    }
    tail = ic_get_tail(tail);
  }

  error_assert(error_intercode, symboltable_free(table));
  error_assert(error_intercode, symbolstack_free(&stack));

  return head;
}

Quad ic_translate_func(Arena arena, SymbolTable* table, SymbolStack* stack, ASTN_Obj node, uint32_t* temp_counter, uint32_t* label_counter) {
  error_assert(error_intercode, arena != NULL);
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, node != NULL && node->type == ASTN_FUN);

  error_assert(
    error_intercode,
    symboltable_insert_ident(table, node->obj._fun.ident, -1)
  );
  error_assert(
    error_intercode,
    symbolstack_push(stack, node->obj._fun.ident)
  );

  Address faddr = ic_create_address(
    arena, AT_Label, (void*)node->obj._fun.ident->value.ident
  );
  Quad func_label = ic_create_quad(
    arena, ICI_Label, faddr, NULL, NULL, NULL
  );

  Quad head = func_label,
       tail = func_label;

  symbolstack_push_frame(stack);
  ASTN_FunArg arg = node->obj._fun.args;
  for (; arg != NULL; arg = arg->next) {
    ASTN_Token token = arg->arg;
    error_assert(
      error_intercode,
      symboltable_insert_ident(table, token, -1)
    );
    error_assert(
      error_intercode,
      symbolstack_push(stack, token)
    );

    uint32_t temp = ic_get_temp(table, token, temp_counter);
    Address addr1 = ic_create_address(
      arena, AT_Temp, (void*)&temp
    ),      addr2 = ic_create_address(
      arena, AT_Label, (void*)token->value.ident
    );
    Quad func_param = ic_create_quad(
      arena, ICI_DT_LoadWord, addr1, addr2, NULL, NULL
    );

    tail->next = func_param;
    tail = func_param;
  }

  Quad body = NULL;
  ASTN_Stmt stmt = node->obj._fun.body;
  for (; stmt != NULL; stmt = stmt->next) {
    Quad quad = ic_translate_stmt(
      arena, table, stack, stmt, temp_counter, label_counter
    );
    if (body == NULL) {
      body = quad;
      continue;
    }
    body->next = quad;
    body = quad;
  } 

  if (body != NULL) {
    tail->next = body;
  }
  tail = ic_get_tail(tail);

  Quad func_return = ic_create_quad(
    arena, ICI_UJ_JumpRegister, NULL, NULL, NULL, NULL
  );
  tail->next = func_return;

  symbolstack_pop_frame(stack, *table);

  return head;
}

Quad ic_translate_stmt(Arena arena, SymbolTable* table, SymbolStack* stack, ASTN_Stmt node, uint32_t* temp_counter, uint32_t* label_counter) {
  switch (node->type) {
    case STMT_WHILE: {
      char* label_start = ic_get_label(arena, STMT_DO, label_counter);
      char* label_end = ic_get_label(arena, STMT_DO, label_counter);

      symbolstack_push_frame(stack);

      Address addr_start = ic_create_address(
        arena, AT_Label, (void*)label_start
      ),      addr_end = ic_create_address(
        arena, AT_Label, (void*)label_end
      );
      Quad loop_start = ic_create_quad(
        arena, ICI_Label, addr_start, NULL, NULL, NULL
      ),   cond = ic_translate_expr(
        arena, table, node->stmt._while.cond, temp_counter
      ),   jump_end = ic_create_quad(
        arena, ICI_Cond_Equal, cond->addr1, addr_end, NULL, NULL
      ),   block = ic_translate_stmt(
        arena, table, stack, node->stmt._while.block, temp_counter, label_counter
      ),   loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      loop_start->next = cond;
      cond->next = jump_end;
      jump_end->next = block;
      Quad tail = ic_get_tail(block);
      tail->next = loop_end;

      symbolstack_pop_frame(stack, *table);

      return loop_start;
    }
    case STMT_DO: {
      char* label_start = ic_get_label(arena, STMT_DO, label_counter);
      char* label_end = ic_get_label(arena, STMT_DO, label_counter);

      symbolstack_push_frame(stack);

      Address addr_start = ic_create_address(
        arena, AT_Label, (void*)label_start
      ),      addr_end = ic_create_address(
        arena, AT_Label, (void*)label_end
      );
      Quad loop_start = ic_create_quad(
        arena, ICI_Label, addr_start, NULL, NULL, NULL
      ),   block = ic_translate_stmt(
        arena, table, stack, node->stmt._while.block, temp_counter, label_counter
      ),   cond = ic_translate_expr(
        arena, table, node->stmt._while.cond, temp_counter
      ),   jump_back = ic_create_quad(
        arena, ICI_Cond_Equal, cond->addr1, addr_start, NULL, NULL
      ),   loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      loop_start->next = block;
      Quad tail = ic_get_tail(block);
      tail->next = cond;
      cond->next = jump_back;
      jump_back->next = loop_end;

      symbolstack_pop_frame(stack, *table);

      return loop_start;
    }
    case STMT_FOR: {
      char* label_start = ic_get_label(arena, STMT_FOR, label_counter);
      char* label_end = ic_get_label(arena, STMT_FOR, label_counter);

      symbolstack_push_frame(stack);

      Address addr_start = ic_create_address(
        arena, AT_Label, (void*)label_start
      ),      addr_end = ic_create_address(
        arena, AT_Label, (void*)label_end
      );
      Quad init = ic_translate_stmt(
        arena, table, stack, node->stmt._for.init, temp_counter, label_counter
      ),   loop_start = ic_create_quad(
        arena, AT_Label, addr_start, NULL, NULL, NULL
      ),   cond = ic_translate_expr(
        arena, table, node->stmt._for.cond, temp_counter
      ),   jump_end = ic_create_quad(
        arena, ICI_Cond_Equal, cond->addr1, addr_end, NULL, NULL
      ),   block = ic_translate_stmt(
        arena, table, stack, node->stmt._for.block, temp_counter, label_counter
      ),   incr = ic_translate_stmt(
        arena, table, stack, node->stmt._for.incr, temp_counter, label_counter
      ),   jump_back = ic_create_quad(
        arena, ICI_UJ_Jump, addr_start, NULL, NULL, NULL
      ),   loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      init->next = loop_start;
      loop_start->next = cond;
      cond->next = jump_end;
      jump_end->next = block;
      Quad tail = ic_get_tail(block);
      tail->next = incr;
      incr->next = jump_back;
      jump_back->next = loop_end;

      symbolstack_pop_frame(stack, *table);
      
      return init;
    }
    case STMT_IF: {
      char* label_false = ic_get_label(arena, STMT_IF, label_counter),
          * label_end = ic_get_label(arena, STMT_IF, label_counter);

      symbolstack_push_frame(stack);

      Address addr_false = ic_create_address(
        arena, AT_Label, (void*)label_false
      ),      addr_end = ic_create_address(
        arena, AT_Label, (void*)label_end
      );

      Quad cond = ic_translate_expr(
        arena, table, node->stmt._if.cond, temp_counter
      ),   jump_false = ic_create_quad(
        arena, ICI_Cond_NEqual, cond->addr1, addr_false, NULL, NULL
      ),   block = ic_translate_stmt(
        arena, table, stack, node->stmt._if.block, temp_counter, label_counter
      ),   jump_end = ic_create_quad(
        arena, ICI_UJ_Jump, addr_end, NULL, NULL, NULL
      ),   quad_false = ic_create_quad(
        arena, ICI_Label, addr_false, NULL, NULL, NULL
      );

      symbolstack_pop_frame(stack, *table);

      Quad tail = quad_false;

      cond->next = jump_false;
      jump_false->next = block;
      tail = ic_get_tail(block);
      tail->next = jump_end;
      jump_end->next = quad_false;
      
      ASTN_Stmt else_if = node->stmt._if.next;
      for (; else_if != NULL; else_if = else_if->stmt._if.next) {
        symbolstack_push_frame(stack);

        Address else_if_addr_false = ic_create_address(
          arena, AT_Label, ic_get_label(arena, STMT_IF, label_counter)
        );
        Quad else_if_cond = else_if->type == STMT_ELSE ? NULL : ic_translate_expr(
          arena, table, else_if->stmt._if.cond, temp_counter
        ),   else_if_jump_false = else_if_cond == NULL ? NULL : ic_create_quad(
          arena, ICI_Cond_NEqual, else_if_cond->addr1, else_if_addr_false, NULL, NULL
        ),   else_if_block = ic_translate_stmt(
          arena, table, stack, else_if, temp_counter, label_counter
        ),   else_if_jump_end = ic_create_quad(
          arena, ICI_UJ_Jump, addr_end, NULL, NULL, NULL
        ),   else_if_false = else_if_cond == NULL ? NULL : ic_create_quad(
          arena, AT_Label, else_if_addr_false, NULL, NULL, NULL
        );

        symbolstack_pop_frame(stack, *table);

        if (else_if_cond == NULL) {
          tail->next = else_if_block;
          tail = ic_get_tail(else_if_block);
          tail->next = else_if_jump_end;
          tail = else_if_jump_end;
        }
        tail->next = else_if_cond;
        else_if_cond->next = else_if_jump_false;
        else_if_jump_false->next = else_if_block;
        tail = ic_get_tail(else_if_block);
        tail->next = else_if_jump_end;
        else_if_jump_end->next = else_if_false;
        tail = else_if_false;
      }

      Quad end_label = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );
      tail->next = end_label;

      return cond;
    }
    case STMT_ELSEIF: {
      return ic_translate_stmt(arena, table, stack, node->stmt._if.block, temp_counter, label_counter);
    }
    case STMT_ELSE: {
      return ic_translate_stmt(arena, table, stack, node->stmt._if.block, temp_counter, label_counter);
    }
    case STMT_WHEN: {
      Quad switch_cond = ic_translate_expr(
        arena, table, node->stmt._when.cond, temp_counter
      );

      char* label_end = ic_get_label(arena, STMT_CASE, label_counter);

      Quad case_head = switch_cond,
           case_tail = switch_cond;

      Address jump_addr = ic_create_address(
        arena, AT_Label, (void*)label_end
      );

      ASTN_Stmt stmt = node->stmt._when.cases;
      for (; stmt != NULL; stmt = stmt->next) {
        error_assert(error_intercode, stmt->type == STMT_CASE);

        symbolstack_push_frame(stack);

        Address case_addr = ic_create_address(
          arena, AT_Label, (void*)ic_get_label(arena, STMT_CASE, label_counter)
        );

        Quad cond = ic_translate_expr(
          arena, table, stmt->stmt._if.cond, temp_counter
        ),   jump_case = ic_create_quad(
          arena, ICI_Cond_NEqual, switch_cond->addr1, cond->addr1, case_addr, NULL
        ),   block = ic_translate_stmt(
          arena, table, stack, stmt->stmt._if.block, temp_counter, label_counter
        ),   jump_end = ic_create_quad(
          arena, ICI_UJ_Jump, jump_addr, NULL, NULL, NULL
        ),   quad_case = ic_create_quad(
          arena, ICI_Label, case_addr, NULL, NULL, NULL
        );

        symbolstack_pop_frame(stack, *table);

        cond->next = jump_case;
        jump_case->next = block;
        case_tail = ic_get_tail(block);
        case_tail->next = jump_end;
        jump_end->next = quad_case;
        case_tail = quad_case;
      }

      Quad end_label = ic_create_quad(
        arena, ICI_Label, jump_addr, NULL, NULL, NULL
      );
      case_tail->next = end_label;

      return case_head;
    }
    case STMT_RETURN: {
      ASTN_ExprList value = node->stmt._ret.value;
      Quad head = NULL,
           tail = NULL;

      for (; value != NULL; value = value->next) {
        Quad expr = ic_translate_expr(
          arena, table, value->expr, temp_counter
        );
        Quad return_quad = ic_create_quad(
          arena, ICI_DT_StoreWord, expr->addr1, NULL, NULL, NULL
        );

        if (head == NULL) {
          head = expr;
        } else {
          tail->next = expr;
        }
        expr->next = tail = return_quad;
      }

      return head;
    }
    case STMT_FUN_CALL: {
      symbolstack_push_frame(stack);

      ASTN_ExprList arg = node->stmt._fun_call.args;
      Quad head = NULL,
           tail = NULL;

      for (; arg != NULL; arg = arg->next) {
        Quad expr = ic_translate_expr(
          arena, table, arg->expr, temp_counter
        );
        Quad store_arg = ic_create_quad(
          arena, ICI_DT_StoreWord, expr->addr1, NULL, NULL, NULL
        );

        if (!head) {
          head = expr;
        } else {
          tail->next = expr;
        }
        expr->next = tail = store_arg;
      }

      Address faddr = ic_create_address(
        arena, AT_Label, (void*)node->stmt._fun_call.fun->value.ident
      );
      Quad call_func = ic_create_quad(
        arena, ICI_UJ_JumpAndLink, faddr, NULL, NULL, NULL
      );

      if (!head) {
        head = call_func;
      } else {
        tail->next = call_func;
      }

      symbolstack_pop_frame(stack, *table);

      return head;

    }
    case STMT_BLOCK: {
      Quad head = NULL,
           tail = NULL;

      ASTN_Stmt stmt = node->stmt.block;
      for (; stmt; stmt = stmt->next) {
        symbolstack_push_frame(stack);
        Quad quad = ic_translate_stmt(
          arena, table, stack, stmt, temp_counter, label_counter
        );
        symbolstack_pop_frame(stack, *table);

        if (head == NULL) {
          head = quad;
        } else {
          tail->next = quad;
        }
        tail = quad;
      }

      return head;
    }
    case STMT_VAR_INCR_BEFORE: case STMT_VAR_INCR_AFTER: {
      ASTN_Token token = node->stmt._assign.var;

      uint32_t temp = ic_get_temp(table, token, temp_counter), const_value = 1;
      Address addr1 = ic_create_address(
        arena, AT_Temp, (void*)&temp
      ),      addr2 = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      ),      addr3 = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, addr1, addr2, NULL, NULL
      ),   incr = ic_create_quad(
        arena, ICI_Arit_AddI, addr1, addr1, addr3, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, addr2, addr1, NULL, NULL
      );

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }
    case STMT_VAR_DECR_BEFORE: case STMT_VAR_DECR_AFTER: {
      ASTN_Token token = node->stmt._assign.var;

      uint32_t temp = ic_get_temp(table, token, temp_counter), const_value = 1;
      Address addr1 = ic_create_address(
        arena, AT_Temp, (void*)&temp
      ),      addr2 = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      ),      addr3 = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, addr1, addr2, NULL, NULL
      ),   decr = ic_create_quad(
        arena, ICI_Arit_SubI, addr1, addr1, addr3, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, addr2, addr1, NULL, NULL
      );

      load_var->next = decr;
      decr->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_PLUS: {
      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      uint32_t temp1 = ic_get_temp(table, token, temp_counter);
      Address load_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, load_addr, var, NULL, NULL
      );
      
      uint32_t temp2 = ic_get_temp(NULL, NULL, temp_counter);
      Address add_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );

      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      Quad add_quad = ic_create_quad(
        arena, ICI_Arit_Add, add_addr, add_addr, expr->addr1, NULL
      );
      
      Quad store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, add_addr, NULL, NULL
      );

      load_var->next = expr;
      expr->next     = add_quad;
      add_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_MINUS: {
      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      uint32_t temp1 = ic_get_temp(table, token, temp_counter);
      Address load_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, load_addr, var, NULL, NULL
      );
      
      uint32_t temp2 = ic_get_temp(NULL, NULL, temp_counter);
      Address sub_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );

      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      Quad sub_quad = ic_create_quad(
        arena, ICI_Arit_Sub, sub_addr, sub_addr, expr->addr1, NULL
      );
      
      Quad store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, sub_addr, NULL, NULL
      );

      load_var->next = expr;
      expr->next     = sub_quad;
      sub_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_MUL: {
      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      uint32_t temp1 = ic_get_temp(table, token, temp_counter);
      Address load_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, load_addr, var, NULL, NULL
      );
      
      uint32_t temp2 = ic_get_temp(NULL, NULL, temp_counter);
      Address mul_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );

      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      Quad mul_quad = ic_create_quad(
        arena, ICI_Arit_Mul, mul_addr, mul_addr, expr->addr1, NULL
      );
      
      Quad store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, mul_addr, NULL, NULL
      );

      load_var->next = expr;
      expr->next     = mul_quad;
      mul_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_DIV: {
      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      uint32_t temp1 = ic_get_temp(table, token, temp_counter);
      Address load_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad load_var = ic_create_quad(
        arena, ICI_DT_LoadWord, load_addr, var, NULL, NULL
      );

      uint32_t temp2 = ic_get_temp(NULL, NULL, temp_counter);
      Address div_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );

      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      Quad div_quad = ic_create_quad(
        arena, ICI_Arit_Div, div_addr, div_addr, expr->addr1, NULL
      );
      Quad store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, div_addr, NULL, NULL
      );

      load_var->next = expr;
      expr->next     = div_quad;
      div_quad->next = store;

      return load_var;
    }
    case STMT_VAR_DECL: {
      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_insert_ident(table, token, -1)
      );
      error_assert(
        error_intercode,
        symbolstack_push(stack, token)
      );
      return NULL;
    }
    case STMT_VAR_DECL_ASSIGN: {
      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_insert_ident(table, token, -1)
      );
      error_assert(
        error_intercode,
        symbolstack_push(stack, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );
      Quad store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, expr->addr1, NULL, NULL
      );
      expr->next = store;

      return expr;       
    }
    case STMT_VAR_DIRECT_ASSIGN: {
      Quad expr = ic_translate_expr(
        arena,
        table,
        node->stmt._assign.value,
        temp_counter
      );

      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );
      Quad stmt = ic_create_quad(
        arena, ICI_DT_StoreWord, var, expr->addr1, NULL, NULL
      );
      expr->next = stmt;

      return expr;
    }
    case STMT_CASE: default: {
      error_panic(error_intercode, ERROR_INVALID_STMT);
      return NULL;
    }
  }
}

Quad ic_translate_expr(Arena arena, SymbolTable* table, ASTN_Expr node, uint32_t* temp_counter) {
  if (node == NULL)
    return NULL;

  switch(node->type) {
    case EXPR_TOKEN: {
      Address addr1 = ic_create_address(arena, AT_Empty, NULL),
              addr2 = ic_create_address(arena, AT_Empty, NULL);
      Quad expr = ic_create_quad(
        arena, ICI_None, NULL, NULL, NULL, NULL
      );

      if (node->expr.token->type != TT_IDENT) {
        switch (node->expr.token->type) {
          case TT_LIT_NUMBER: {
            addr2->type = AT_IntConst;
            addr2->value.val_int = node->expr.token->value.lit_number;
            break;
          }
          case TT_LIT_REAL: {
            error_panic(error_intercode, "LONG FLOAT DOUBLE inter code not implemented");
            break;
          }
          case TT_LIT_TRUE: case TT_LIT_FALSE: {
            addr2->type = AT_IntConst;
            addr2->value.val_int = node->expr.token->value.lit_bool ? 1 : 0;
            break;
          }
          case TT_LIT_NULL: {
            addr2->type = AT_IntConst;
            addr2->value.val_int = 0;
            break;
          }
          case TT_LIT_STRING: {
            addr2->type = AT_String;
            error_assert(error_intercode, node->expr.token->value.lit_str != NULL);
            addr2->value.label = arena_strdup(arena, (char*)node->expr.token->value.lit_str);
            error_assert(error_mem, addr2->value.label != NULL);
            break;
          }
          case TT_IDENT: {
            error_panic(error_intercode, ERROR_INVALID_TT);
          }
        }

        addr1->type = AT_Temp;
        addr1->value.temp = ic_get_temp(NULL, NULL, temp_counter);

        expr->inst = ICI_DT_LoadImmediate;
        expr->addr1 = addr1;
        expr->addr2 = addr2;
        expr->addr3 = NULL;
      } else {
        addr1->type = AT_Temp;
        addr1->value.temp = ic_get_temp(table, node->expr.token, temp_counter);

        addr2->type = AT_Label;
        error_assert(
          error_intercode,
          symboltable_exists_ident(*table, node->expr.token)
        );
        addr2->value.label = arena_strdup(arena, (char*)node->expr.token->value.ident);
        error_assert(error_mem, addr2->value.label != NULL);
   
        expr->inst = ICI_DT_LoadWord;
        expr->addr1 = addr1;
        expr->addr2 = addr2;
        expr->addr3 = NULL;
      }

      return expr;
    }
    case EXPR_UN: {
      Quad sub_expr = ic_translate_expr(
        arena,
        table,
        node->expr.unary.operand, 
        temp_counter
      );

      uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
      Address result = ic_create_address(
        arena, AT_Temp, (void*)&temp
      );

      Quad expr = ic_create_quad(
        arena, ICI_None, NULL, NULL, NULL, NULL
      );

      switch (node->expr.binary.op) {
        case OP_UN_ARIT_PLUS: {
          ast_print_expr(stderr, node);
          error_panic(error_intercode, "Not implemented in this version of the compiler");
          break;
        }
        case OP_UN_ARIT_MINUS: {
          ast_print_expr(stderr, node);
          error_panic(error_intercode, "Not implemented in this version of the compiler");
          break;
        }
        case OP_UN_LOG_NOT: {
          expr->inst = ICI_Logic_BitNorI;
          expr->addr1 = result;
          expr->addr2 = sub_expr->addr1;

          uint32_t const_value = 0;
          Address immediate = ic_create_address(
            arena, AT_IntConst, (void*)&const_value
          );
          expr->addr3 = immediate;

          break;
        }
        default: {
          error_panic(error_intercode, ERROR_INVALID_EXPR);
          break;
        }
      }

      return expr;
    }
    case EXPR_BIN: {
      Quad leftSide = ic_translate_expr(
        arena,
        table,
        node->expr.binary.left,
        temp_counter
      ), rightSide = ic_translate_expr(
        arena,
        table,
        node->expr.binary.right,
        temp_counter
      );

      uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
      Address result = ic_create_address(
        arena, AT_Temp, (void*)&temp
      );
      
      ICI op;
      switch (node->expr.binary.op) {
        case OP_BIN_ARIT_PLUS:
          op = ICI_Arit_Add; 
          break;
        case OP_BIN_ARIT_MINUS:
          op = ICI_Arit_Sub;
          break;
        case OP_BIN_ARIT_MUL:
          op = ICI_Arit_MulI;  
          break;
        case OP_BIN_ARIT_DIV:
          op = ICI_Arit_Div;
          break;
        case OP_BIN_COMP_EQUAL:
          op = ICI_Cond_Equal;
          break;
        case OP_BIN_COMP_NEQUAL:
          op = ICI_Cond_NEqual;
          break;
        case OP_BIN_COMP_LTHAN:
          op = ICI_Cond_LThan;
          break;
        case OP_BIN_COMP_GTHAN:
          op = ICI_Cond_GThan;
          break;
        case OP_BIN_COMP_LEQUAL:
          op = ICI_Cond_LThanEqual;
          break;
        case OP_BIN_COMP_GEQUAL:
          op = ICI_Cond_GThanEqual;
          break;
        case OP_BIN_LOG_AND:
          op = ICI_Logic_BitAnd;
          break;
        case OP_BIN_LOG_OR:
          op = ICI_Logic_BitOr;
          break;
        case OP_NONE: default:
          error_assert(error_intercode, ERROR_INVALID_EXPR);
      }

      Quad expr = ic_create_quad(
        arena, op, result, leftSide->addr1, rightSide->addr2, NULL
      );
      
      return expr;
    }
    case EXPR_FUN_CALL: {
      Quad head = NULL,
           tail = NULL;

      ASTN_ExprList arg = node->expr.fun_call.args;
      for (; arg; arg = arg->next) {
        Quad trans_arg = ic_translate_expr(arena, table, arg->expr, temp_counter);
        Quad fun_arg = ic_create_quad(
          arena, ICI_DT_StoreWord, trans_arg->addr1, NULL, NULL, NULL
        );

        if (head == NULL) {
          head = fun_arg;
        } else {
          tail->next = fun_arg;
        }
        tail = fun_arg;
      }

      ASTN_Token token = node->expr.fun_call.fun;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address fun_label = ic_create_address(arena, AT_Label, (void*)token);

      Quad call_func = ic_create_quad(
        arena, ICI_UJ_JumpAndLink, fun_label, NULL, NULL, NULL
      );

      if (head == NULL) {
        head = call_func;
      } else {
        tail->next = call_func;
      }

      uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
      Address return_add = ic_create_address(
        arena, AT_Temp, (void*)&temp
      );
      Quad func_return = ic_create_quad(
        arena, ICI_DT_LoadWord, return_add, NULL, NULL, NULL
      );

      call_func->next = func_return;

      return head != NULL ? head : call_func;
    }
  }
  return NULL;
}

Address ic_create_address(Arena arena, AddressType type, void* value) {
  error_assert(error_intercode, value != NULL || type == AT_Empty);
  Address addr = (Address)arena_alloc(arena, sizeof(struct address));
  error_assert(error_mem, addr != NULL);
  addr->type = type;
  switch (type) {
    case AT_Empty: {
      break;
    }
    case AT_IntConst: {
      addr->value.val_int = *(int64_t*)value;
      break;
    }
    case AT_UIntConst: {
      addr->value.val_uint = *(uint64_t*)value;
      break;
    }
    case AT_Char: {
      addr->value.val_char = *(char*)value;
      break;
    }
    case AT_Temp: case AT_Save: {
      addr->value.temp = *(uint32_t*)value;
      break;
    }
    case AT_Label: case AT_String: {
      addr->value.label = arena_strdup(arena, (char*)value);
      error_assert(error_mem, addr->value.label != NULL);
      break;
    }
  }
  return addr;
}

Quad ic_create_quad(Arena arena, ICI inst, Address addr1, Address addr2, Address addr3, Quad next) {
  Quad quad = (Quad)arena_alloc(arena, sizeof(quad));
  error_assert(error_mem, quad != NULL);
  quad->inst  = inst;
  quad->addr1 = addr1;
  quad->addr2 = addr2;
  quad->addr3 = addr3;
  quad->next  = next;
  return quad;
}

uint32_t ic_get_temp(SymbolTable* table, ASTN_Token token, uint32_t* temp_counter) {
  if (table == NULL || token == NULL)
    return (*temp_counter)++;
  int32_t temp = symboltable_lookup_ident(*table, token);
  if (temp > -1)
    return (uint32_t)temp;
  symboltable_insert_ident(table, token, *temp_counter);
  return (*temp_counter)++;
}

char* ic_get_label(Arena arena, ASTN_StmtType type, uint32_t* label_counter) {
  char* label = arena_alloc(arena, SIZEOFLABEL);  

  const char* keyword = NULL;
  switch (type) {
    case STMT_WHILE: case STMT_DO:
    case STMT_FOR: {
      keyword = LABEL_LOOP;
      break;
    }
    case STMT_IF: case STMT_ELSEIF:
    case STMT_ELSE: case STMT_CASE: {
      keyword = LABEL_COND;
      break;
    }
    case STMT_RETURN: {
      keyword = LABEL_RETURN;
      break;
    }
    case STMT_FUN_CALL: {
      keyword = LABEL_JUMP;
      break;
    }                                
    default: {
      error_panic(error_intercode, ERROR_INVALID_STMT);
      break;
    }
  }

  sprintf(label, "%s%d", keyword, (*label_counter)++); 
  return label;
}


Quad ic_get_tail(Quad quad) {
  if (quad == NULL) return NULL;
  for (; quad->next != NULL; quad = quad->next);
  return quad;
}
