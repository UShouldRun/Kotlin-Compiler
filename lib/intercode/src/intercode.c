#include "intercode_private.h"

// ==================================================# PUBLIC #=================================================================

void ic_print_translation(Quad program) {
  Quad node = program;
  fprintf(stdout, "=====================\n");
  for (; node != NULL; node = node->next) {
    fprintf(
      stdout,
      "%s%s%s%s: ",
      node->inst != ICI_Label ? "\t" : "",
      colors[RED],
      match_instruction_to_string(node->inst),
      colors[GREEN]
    );

    ic_print_addr(node->addr1);
    if (node->inst != ICI_Label
      && node->inst != ICI_UJ_JumpRegister
      && node->inst != ICI_UJ_JumpAndLink) {
      fprintf(stdout, ", ");
      ic_print_addr(node->addr2);
      fprintf(stdout, ", ");
      ic_print_addr(node->addr3);
    } 

    fprintf(stdout, ";%s\n", colors[RESET]);
  }
  fprintf(stdout, "=====================\n");
}

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
      head = fquad;
    } else {
      tail->next = fquad;
    }
    tail = ic_get_tail(fquad);
  }

  error_assert(error_intercode, symboltable_free(table));
  error_assert(error_intercode, symbolstack_free(&stack));

  return head;
}

// ==================================================# PRIVATE #=================================================================

void ic_print_addr(Address addr) {
  if (addr == NULL) {
    fprintf(stdout, "None");
    return;
  }
  switch (addr->type) {
    case AT_Empty: default:
      error_panic(error_intercode, ERROR_INVALID_ADDR_T);
      break;
    case AT_IntConst:
      fprintf(stdout, "%ld", addr->value.val_int);
      break;
    case AT_UIntConst:
      fprintf(stdout, "%lu", addr->value.val_uint);
      break;
    case AT_Char:
      fprintf(stdout, "%c", addr->value.val_char);
      break;
    case AT_String: case AT_Label:
      fprintf(stdout, "%s", addr->value.label);
      break;
    case AT_Temp:
      fprintf(stdout, "t%d", addr->value.temp);
      break;
  }
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
    ic_reset_token(table, token);
    error_assert(
      error_intercode,
      symbolstack_push(stack, token)
    );
  }

  Quad body = NULL;
  ASTN_Stmt stmt = node->obj._fun.body;
  for (; stmt != NULL; stmt = stmt->next) {
    Quad quad = ic_translate_stmt(
      arena, table, stack, stmt, temp_counter, label_counter
    );
    if (quad == NULL)
      continue;
    if (body == NULL) {
      body = quad;
      head->next = body;
    } else {
      tail->next = quad;
    }
    tail = ic_get_tail(quad);
  } 

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

      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );

      uint64_t const_value = 1;
      Address one = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad loop_start = ic_create_quad(
        arena, ICI_Label, addr_start, NULL, NULL, NULL
      ),   cond = ic_translate_expr(
        arena, table, node->stmt._while.cond, dest1, temp_counter
      ),   jump_end = ic_create_quad(
        arena, ICI_Branch_Equal, dest1, one, addr_end, NULL
      );

      Quad block = NULL, tail = NULL;
      ASTN_Stmt stmt = node->stmt._while.block;
      for (; stmt != NULL; stmt = stmt->next) {
        Quad quad = ic_translate_stmt(
          arena, table, stack, stmt, temp_counter, label_counter
        );
        if (quad == NULL)
          continue;
        if (block == NULL) {
          block = quad;
        } else {
          tail->next = quad;
        }
        tail = ic_get_tail(quad);
      }

      Quad jump_back = ic_create_quad(
        arena, ICI_UJ_Jump, addr_start, NULL, NULL, NULL
      );
      Quad loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      loop_start->next = cond;
      tail = ic_get_tail(cond);
      tail->next = jump_end;
      jump_end->next = block;
      tail = ic_get_tail(block);
      tail->next = jump_back;
      jump_back->next = loop_end;

      ic_pop_temp(temp_counter, 1);
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

      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );

      uint64_t const_value = 1;
      Address one = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad loop_start = ic_create_quad(
        arena, ICI_Label, addr_start, NULL, NULL, NULL
      );

      Quad block = NULL, tail = NULL;
      ASTN_Stmt stmt = node->stmt._while.block;
      for (; stmt != NULL; stmt = stmt->next) {
        Quad quad = ic_translate_stmt(
          arena, table, stack, stmt, temp_counter, label_counter
        );
        if (quad == NULL)
          continue;
        if (block == NULL) {
          block = quad;
        } else {
          tail->next = quad;
        }
        tail = ic_get_tail(quad);
      }

      Quad cond = ic_translate_expr(
        arena, table, node->stmt._while.cond, dest1, temp_counter
      ),   jump_back = ic_create_quad(
        arena, ICI_Branch_Equal, dest1, one, addr_start, NULL
      ),   loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      loop_start->next = block;
      tail->next = cond;
      tail = ic_get_tail(cond);
      tail->next = jump_back;
      jump_back->next = loop_end;

      ic_pop_temp(temp_counter, 1);
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

      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );

      uint64_t const_value = 1;
      Address one = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad init = ic_translate_stmt(
        arena, table, stack, node->stmt._for.init, temp_counter, label_counter
      ),   loop_start = ic_create_quad(
        arena, AT_Label, addr_start, NULL, NULL, NULL
      ),   cond = ic_translate_expr(
        arena, table, node->stmt._for.cond, dest1, temp_counter
      ),   jump_end = ic_create_quad(
        arena, ICI_Branch_Equal, ic_get_tail(cond)->addr1, one, addr_end, NULL
      );   

      Quad block = NULL, tail = NULL;
      ASTN_Stmt stmt = node->stmt._for.block;
      for (; stmt != NULL; stmt = stmt->next) {
        Quad quad = ic_translate_stmt(
          arena, table, stack, stmt, temp_counter, label_counter
        );
        if (quad == NULL)
          continue;
        if (block == NULL) {
          block = quad;
        } else {
          tail->next = quad;
        }
        tail = ic_get_tail(quad);
      }

      Quad incr = ic_translate_stmt(
        arena, table, stack, node->stmt._for.incr, temp_counter, label_counter
      ),   jump_back = ic_create_quad(
        arena, ICI_UJ_Jump, addr_start, NULL, NULL, NULL
      ),   loop_end = ic_create_quad(
        arena, ICI_Label, addr_end, NULL, NULL, NULL
      );

      tail = ic_get_tail(init);
      tail->next = loop_start;
      loop_start->next = cond;
      tail = ic_get_tail(cond);
      tail->next = jump_end;
      jump_end->next = block;
      tail = ic_get_tail(block);
      tail->next = incr;
      tail = ic_get_tail(incr);
      tail->next = jump_back;
      jump_back->next = loop_end;

      ic_pop_temp(temp_counter, 1);
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

      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );

      Quad cond = ic_translate_expr(
        arena, table, node->stmt._if.cond, dest1, temp_counter
      ),   end_cond = ic_get_tail(cond);

      uint64_t const_value = 1;
      Address one = ic_create_address(
        arena, AT_UIntConst, (void*)&const_value
      );

      Quad jump_false = ic_create_quad(
        arena, ICI_Branch_NEqual, end_cond->addr1, one, addr_false, NULL
      );   

      Quad block = NULL, tail = NULL;
      ASTN_Stmt stmt = node->stmt._if.block;
      for (; stmt != NULL; stmt = stmt->next) {
        Quad quad = ic_translate_stmt(
          arena, table, stack, stmt, temp_counter, label_counter
        );
        if (quad == NULL)
          continue;
        if (block == NULL) {
          block = quad;
        } else {
          tail->next = quad;
        }
        tail = ic_get_tail(quad);
      }

      Quad jump_end = ic_create_quad(
        arena, ICI_UJ_Jump, addr_end, NULL, NULL, NULL
      ),   quad_false = ic_create_quad(
        arena, ICI_Label, addr_false, NULL, NULL, NULL
      );

      ic_pop_temp(temp_counter, 1);
      symbolstack_pop_frame(stack, *table);

      end_cond->next = jump_false;
      jump_false->next = block;
      tail->next = jump_end;
      jump_end->next = quad_false;

      tail = quad_false;
      
      ASTN_Stmt else_if = node->stmt._if.next;
      for (; else_if != NULL; else_if = else_if->stmt._if.next) {
        symbolstack_push_frame(stack);

        Address else_if_addr_false = ic_create_address(
          arena, AT_Label, ic_get_label(arena, STMT_IF, label_counter)
        );

        uint32_t temp2 = else_if->type == STMT_ELSE ? 0 : ic_get_temp(NULL, NULL, temp_counter);
        Address dest2 = else_if->type == STMT_ELSE ? NULL : ic_create_address(
          arena, AT_Temp, (void*)&temp2
        );

        Quad else_if_cond = else_if->type == STMT_ELSE ? NULL : ic_translate_expr(
          arena, table, else_if->stmt._if.cond, dest2, temp_counter
        ),   end_else_if_cond = ic_get_tail(else_if_cond);

        uint64_t const_value = 1;
        Address one = else_if->type == STMT_ELSE ? NULL : ic_create_address(
          arena, AT_UIntConst, (void*)&const_value
        );

        Quad else_if_jump_false = else_if_cond == NULL ? NULL : ic_create_quad(
          arena, ICI_Branch_NEqual, end_else_if_cond->addr1, one, else_if_addr_false, NULL
        );         

        Quad else_if_block = NULL;
        ASTN_Stmt stmt = else_if->stmt._if.block;
        for (; stmt != NULL; stmt = stmt->next) {
          Quad quad = ic_translate_stmt(
            arena, table, stack, stmt, temp_counter, label_counter
          );
          if (quad == NULL)
            continue;
          if (else_if_block == NULL) {
            else_if_block = quad;
          } else {
            tail->next = quad;
          }
          tail = ic_get_tail(quad);
        }

        Quad else_if_jump_end = ic_create_quad(
          arena, ICI_UJ_Jump, addr_end, NULL, NULL, NULL
        ),   else_if_false = else_if_cond == NULL ? NULL : ic_create_quad(
          arena, AT_Label, else_if_addr_false, NULL, NULL, NULL
        );

        if (else_if->type != STMT_ELSE)
          ic_pop_temp(temp_counter, 1);
        symbolstack_pop_frame(stack, *table);

        if (else_if_cond == NULL) {
          tail->next = else_if_block;
          tail = ic_get_tail(else_if_block);
          tail->next = else_if_jump_end;
          tail = else_if_jump_end;
          continue;
        }
        tail->next = else_if_cond;
        end_else_if_cond->next = else_if_jump_false;
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
      return ic_translate_stmt(
        arena, table, stack, node->stmt._if.block, temp_counter, label_counter
      );
    }
    case STMT_ELSE: {
      return ic_translate_stmt(
        arena, table, stack, node->stmt._if.block, temp_counter, label_counter
      );
    }
    case STMT_WHEN: {
      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad switch_cond = ic_translate_expr(
        arena, table, node->stmt._when.cond, dest1, temp_counter
      );

      char* label_end = ic_get_label(arena, STMT_CASE, label_counter);

      Quad case_head = switch_cond,
           case_tail = ic_get_tail(switch_cond);

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

        uint32_t temp2 = stmt->type == STMT_ELSE ? 0 : ic_get_temp(NULL, NULL, temp_counter);
        Address dest2 = stmt->type == STMT_ELSE ? NULL : ic_create_address(
          arena, AT_Temp, (void*)&temp2
        );

        Quad cond = stmt->type == STMT_ELSE ? NULL : ic_translate_expr(
          arena, table, stmt->stmt._if.cond, dest2, temp_counter
        ),   end_cond = ic_get_tail(cond);

        Quad jump_case = stmt->type == STMT_ELSE ? NULL : ic_create_quad(
          arena, ICI_Branch_NEqual, switch_cond->addr1, end_cond->addr1, case_addr, NULL
        );

        Quad block = NULL;
        ASTN_Stmt stmt = stmt->stmt._if.block;
        for (; stmt != NULL; stmt = stmt->next) {
          Quad quad = ic_translate_stmt(
            arena, table, stack, stmt, temp_counter, label_counter
          );
          if (quad == NULL)
            continue;
          if (block == NULL) {
            block = quad;
          } else {
            case_tail->next = quad;
          }
          case_tail = ic_get_tail(quad);
        }

        Quad jump_end = ic_create_quad(
          arena, ICI_UJ_Jump, jump_addr, NULL, NULL, NULL
        ),   quad_case = ic_create_quad(
          arena, ICI_Label, case_addr, NULL, NULL, NULL
        );

        ic_pop_temp(temp_counter, 1);
        symbolstack_pop_frame(stack, *table);

        if (cond == NULL) {
          case_tail->next = block;
          case_tail = ic_get_tail(block);
          case_tail->next = jump_end;
          case_tail = jump_end;
          continue;
        }
        case_tail->next = cond;
        end_cond->next = jump_case;
        jump_case->next = block;
        case_tail = ic_get_tail(block);
        case_tail->next = jump_end;
        jump_end->next = quad_case;
        case_tail = quad_case;
      }

      ic_pop_temp(temp_counter, 1);

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
        uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
        Address dest1 = ic_create_address(
          arena, AT_Temp, (void*)&temp1
        );
        Quad expr = ic_translate_expr(
          arena, table, value->expr, dest1, temp_counter
        );
        Quad end_expr = ic_get_tail(expr);
        Quad return_quad = ic_create_quad(
          arena, ICI_DT_StoreWord, dest1, NULL, NULL, NULL
        );
        ic_pop_temp(temp_counter, 1);

        if (head == NULL) {
          head = expr;
        } else {
          tail->next = expr;
        }

        end_expr->next = return_quad;
        tail = return_quad;
      }

      Quad jump_reg = ic_create_quad(
        arena, ICI_UJ_JumpRegister, NULL, NULL, NULL, NULL
      );
      if (head != NULL) {
        tail->next = jump_reg;
      } else {
        head = jump_reg;
      }

      return head;
    }
    case STMT_FUN_CALL: {
      ASTN_Token token = node->stmt._fun_call.fun;

      if (strcmp(token->value.ident, DEFAULT_PRINTLN_INT) == 0) {
        uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
        Address dest1 = ic_create_address(
          arena, AT_Temp, (void*)&temp1
        );
        Quad expr = ic_translate_expr(
          arena, table, node->stmt._fun_call.args->expr, dest1, temp_counter
        );
        ic_pop_temp(temp_counter, 1);
        Quad print = ic_translate_println(
          arena, dest1, KOTLIN_INT
        );
        Quad tail = ic_get_tail(expr);
        tail->next = print;
        return expr;
      } else if (strcmp(token->value.ident, DEFAULT_READLN_INT) == 0) {
        uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
        Address addr = ic_create_address(
          arena, AT_Temp, (void*)&temp
        );
        return ic_translate_readln(
          arena, addr, KOTLIN_INT
        );
      } else if (strcmp(token->value.ident, DEFAULT_PRINTLN_STR) == 0) {
        uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
        Address dest1 = ic_create_address(
          arena, AT_Temp, (void*)&temp1
        );
        Quad expr = ic_translate_expr(
          arena, table, node->stmt._fun_call.args->expr, dest1, temp_counter
        );
        ic_pop_temp(temp_counter, 1);
        Quad print = ic_translate_println(
          arena, dest1, KOTLIN_STRING
        );
        Quad tail = ic_get_tail(expr);
        tail->next = print;
        return expr;
      } else if (strcmp(token->value.ident, DEFAULT_READLN_STR) == 0) {
        uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
        Address addr = ic_create_address(
          arena, AT_Temp, (void*)&temp
        );
        return ic_translate_readln(
          arena, addr, KOTLIN_STRING
        );
      }

      symbolstack_push_frame(stack);

      ASTN_ExprList arg = node->stmt._fun_call.args;
      Quad head = NULL,
           tail = NULL;

      for (; arg != NULL; arg = arg->next) {
        uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
        Address dest1 = ic_create_address(
          arena, AT_Temp, (void*)&temp1
        );
        Quad expr = ic_translate_expr(
          arena, table, arg->expr, dest1, temp_counter
        );
        Quad end_expr = ic_get_tail(expr);
        Quad store_arg = ic_create_quad(
          arena, ICI_DT_StoreWord, dest1, NULL, NULL, NULL
        );
        ic_pop_temp(temp_counter, 1);

        if (head == NULL) {
          head = expr;
        } else {
          tail->next = expr;
        }

        end_expr->next = store_arg;
        tail = store_arg;
      }

      Address faddr = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
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
        tail = ic_get_tail(quad);
      }

      return head;
    }
    case STMT_VAR_INCR_BEFORE: case STMT_VAR_INCR_AFTER: {
      ASTN_Token token = node->stmt._assign.var;

      uint32_t temp = ic_get_temp(table, token, temp_counter);
      uint64_t const_value = 1;
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
      ic_pop_temp(temp_counter, 1);
      ic_reset_token(table, token);

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }
    case STMT_VAR_DECR_BEFORE: case STMT_VAR_DECR_AFTER: {
      ASTN_Token token = node->stmt._assign.var;

      uint32_t temp = ic_get_temp(table, token, temp_counter);
      uint64_t const_value = 1;
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
      ic_pop_temp(temp_counter, 1);
      ic_reset_token(table, token);
      
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
      Address expr_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, expr_addr, temp_counter
      ), tail = ic_get_tail(expr);

      Quad add_quad = ic_create_quad(
        arena, ICI_Arit_Add, load_addr, load_addr, expr_addr, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, load_addr, NULL, NULL
      );
      ic_pop_temp(temp_counter, 2);
      ic_reset_token(table, token);

      load_var->next = expr;
      tail->next = add_quad;
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
      Address expr_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, expr_addr, temp_counter
      ), tail = ic_get_tail(expr);

      Quad sub_quad = ic_create_quad(
        arena, ICI_Arit_Sub, load_addr, load_addr, expr_addr, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, load_addr, NULL, NULL
      );
      ic_pop_temp(temp_counter, 2);
      ic_reset_token(table, token);

      load_var->next = expr;
      tail->next = sub_quad;
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
      Address expr_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, expr_addr, temp_counter
      ), tail = ic_get_tail(expr);

      Quad mul_quad = ic_create_quad(
        arena, ICI_Arit_Mul, load_addr, load_addr, expr_addr, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, load_addr, NULL, NULL
      );
      ic_pop_temp(temp_counter, 2);
      ic_reset_token(table, token);

      load_var->next = expr;
      tail->next = mul_quad;
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
      Address expr_addr = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, expr_addr, temp_counter
      ), tail = ic_get_tail(expr);

      Quad div_quad = ic_create_quad(
        arena, ICI_Arit_Div, load_addr, load_addr, expr_addr, NULL
      ),   store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, load_addr, NULL, NULL
      );
      ic_pop_temp(temp_counter, 2);
      ic_reset_token(table, token);

      load_var->next = expr;
      tail->next = div_quad;
      div_quad->next = store;

      return load_var;
    }
    case STMT_VAR_DECL: {
      ASTN_Token token = node->stmt._assign.var;
      ic_reset_token(table, token);
      error_assert(
        error_intercode,
        symbolstack_push(stack, token)
      );
      return NULL;
    }
    case STMT_VAR_DECL_ASSIGN: {
      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, dest1, temp_counter
      );

      ASTN_Token token = node->stmt._assign.var;
      ic_reset_token(table, token);
      error_assert(
        error_intercode,
        symbolstack_push(stack, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      Quad tail = ic_get_tail(expr),
           store = ic_create_quad(
        arena, ICI_DT_StoreWord, var, dest1, NULL, NULL
      );
      tail->next = store;
      ic_pop_temp(temp_counter, 1);

      return expr;       
    }
    case STMT_VAR_DIRECT_ASSIGN: {
      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      Quad expr = ic_translate_expr(
        arena, table, node->stmt._assign.value, dest1, temp_counter
      );

      ASTN_Token token = node->stmt._assign.var;
      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address var = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      Quad tail = ic_get_tail(expr),
           stmt = ic_create_quad(
        arena, ICI_DT_StoreWord, var, dest1, NULL, NULL
      );
      tail->next = stmt;
      ic_pop_temp(temp_counter, 1);

      return expr;
    }
    case STMT_CASE: default: {
      error_panic(error_intercode, ERROR_INVALID_STMT);
      return NULL;
    }
  }
}

Quad ic_translate_expr(Arena arena, SymbolTable* table, ASTN_Expr node, Address dest, uint32_t* temp_counter) {
  error_assert(error_intercode, arena != NULL);
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, node != NULL);
  error_assert(error_intercode, temp_counter != NULL);

  switch (node->type) {
    case EXPR_TOKEN: {
      Address addr2 = ic_create_address(arena, AT_Empty, NULL);
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

        expr->inst = ICI_DT_LoadImmediate;
        expr->addr1 = dest;
        expr->addr2 = addr2;
        expr->addr3 = NULL;
      } else {
        addr2->type = AT_Label;
        error_assert(
          error_intercode,
          symboltable_exists_ident(*table, node->expr.token)
        );
        addr2->value.label = arena_strdup(arena, (char*)node->expr.token->value.ident);
        error_assert(error_mem, addr2->value.label != NULL);
   
        expr->inst = ICI_DT_LoadWord;
        expr->addr1 = dest;
        expr->addr2 = addr2;
        expr->addr3 = NULL;
      }

      return expr;
    }
    case EXPR_UN: {
      uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
      Address result = ic_create_address(
        arena, AT_Temp, (void*)&temp
      );
      Quad sub_expr = ic_translate_expr(
        arena, table, node->expr.unary.operand, result, temp_counter
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
          expr->addr1 = dest;
          expr->addr2 = result;
          ic_pop_temp(temp_counter, 1);

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

      sub_expr->next = expr;
      return sub_expr;
    }
    case EXPR_BIN: {
      uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest1 = ic_create_address(
        arena, AT_Temp, (void*)&temp1
      );
      uint32_t temp2 = ic_get_temp(NULL, NULL, temp_counter);
      Address dest2 = ic_create_address(
        arena, AT_Temp, (void*)&temp2
      );
      Quad leftSide = ic_translate_expr(
        arena, table, node->expr.binary.left, dest1, temp_counter
      ), rightSide = ic_translate_expr(
        arena, table, node->expr.binary.right, dest2, temp_counter
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
        arena, op, dest, dest1, dest2, NULL
      );
      ic_pop_temp(temp_counter, 2);
      
      Quad tail = ic_get_tail(leftSide);
      tail->next = rightSide;
      tail = ic_get_tail(rightSide);
      tail->next = expr;
      return leftSide;
    }
    case EXPR_FUN_CALL: {
      ASTN_Token token = node->expr.fun_call.fun;

      if (strcmp(token->value.ident, DEFAULT_PRINTLN_INT) == 0) {
        error_panic(error_intercode, ERROR_INVALID_PRINTLN_USE);
      } else if (strcmp(token->value.ident, DEFAULT_READLN_INT) == 0) {
        uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
        Address addr = ic_create_address(
          arena, AT_Temp, (void*)&temp
        );
        return ic_translate_readln(
          arena, addr, KOTLIN_INT
        );
      } else if (strcmp(token->value.ident, DEFAULT_PRINTLN_STR) == 0) {
        error_panic(error_intercode, ERROR_INVALID_PRINTLN_USE);
      } else if (strcmp(token->value.ident, DEFAULT_READLN_STR) == 0) {
        uint32_t temp = ic_get_temp(NULL, NULL, temp_counter);
        Address addr = ic_create_address(
          arena, AT_Temp, (void*)&temp
        );
        return ic_translate_readln(
          arena, addr, KOTLIN_STRING
        );
      }

      Quad head = NULL,
           tail = NULL;

      ASTN_ExprList arg = node->expr.fun_call.args;
      for (; arg; arg = arg->next) {
        uint32_t temp1 = ic_get_temp(NULL, NULL, temp_counter);
        Address dest1 = ic_create_address(
          arena, AT_Temp, (void*)&temp1
        );
        Quad trans_arg = ic_translate_expr(
          arena, table, arg->expr, dest1, temp_counter
        ),   fun_arg = ic_create_quad(
          arena, ICI_DT_StoreWord, dest1, NULL, NULL, NULL
        );
        ic_pop_temp(temp_counter, 1);
 
        if (head == NULL) {
          head = trans_arg;
        } else {
          tail->next = trans_arg;
        }
        tail = ic_get_tail(trans_arg);
        tail->next = fun_arg;
        tail = fun_arg;
      }

      error_assert(
        error_intercode,
        symboltable_exists_ident(*table, token)
      );
      Address fun_label = ic_create_address(
        arena, AT_Label, (void*)token->value.ident
      );

      Quad call_func = ic_create_quad(
        arena, ICI_UJ_JumpAndLink, fun_label, NULL, NULL, NULL
      );

      if (head == NULL) {
        head = call_func;
      } else {
        tail->next = call_func;
      }

      Quad func_return = ic_create_quad(
        arena, ICI_DT_LoadWord, dest, NULL, NULL, NULL
      );
      call_func->next = func_return;

      return head != NULL ? head : call_func;
    }
  }
  return NULL;
}

Quad ic_translate_println(Arena arena, Address value, ASTN_KTypeDefault type) {
  error_assert(error_intercode, arena != NULL);
  error_assert(error_intercode, value != NULL);

  if (type != KOTLIN_INT && type != KOTLIN_STRING) {
    error_panic(
      error_intercode,
      "Only implemented KOTLIN_INT and KOTLIN_STRING in this version of the compiler"
    );
  }

  Quad load_quad = ic_create_quad(
    arena, ICI_DT_Move, NULL, value, NULL, NULL
  );

  ICI syscall_code;
  switch (type) {
    case KOTLIN_INT:
      syscall_code = ICI_Syscall_1;
      break;
    case KOTLIN_STRING:
      syscall_code = ICI_Syscall_4;
      break;
    default:
      error_assert(error_intercode, ERROR_INVALID_KTYPE);
      break;
  }

  Quad syscall_quad = ic_create_quad(
    arena, syscall_code, NULL, NULL, NULL, NULL
  );
  load_quad->next = syscall_quad;

  return load_quad;
}

Quad ic_translate_readln(Arena arena, Address dest, ASTN_KTypeDefault type) {
  error_assert(error_intercode, arena != NULL);
  error_assert(error_intercode, dest != NULL);

  if (type != KOTLIN_INT && type != KOTLIN_STRING) {
    error_panic(
      error_intercode,
      "Only implemented KOTLIN_INT and KOTLIN_STRING in this version of the compiler"
    );
  }

  ICI syscall_code;
  switch (type) {
    case KOTLIN_INT:
      syscall_code = ICI_Syscall_5;
      break;
    case KOTLIN_STRING:
      syscall_code = ICI_Syscall_8;
      break;
    default:
      error_assert(error_intercode, ERROR_INVALID_KTYPE);
      break;
  }

  Quad syscall_quad = ic_create_quad(
    arena, syscall_code, NULL, NULL, NULL, NULL
  ),   move_quad = ic_create_quad(
    arena, ICI_DT_Move, dest, NULL, NULL, NULL
  );
  syscall_quad->next = move_quad;

  return syscall_quad;
}

void ic_reset_token(SymbolTable* table, ASTN_Token token) {
  error_assert(
    error_intercode,
    symboltable_insert_ident(table, token, -1)
  );
}

void ic_pop_temp(uint32_t* temp_counter, uint32_t n) {
  error_assert(error_intercode, *temp_counter > 0);
  *temp_counter -= n;
}

uint32_t ic_get_temp(SymbolTable* table, ASTN_Token token, uint32_t* temp_counter) {
  if (table == NULL || token == NULL)
    return (*temp_counter)++;
  error_assert(
    error_intercode,
    symboltable_exists_ident(*table, token)
  );
  return (*temp_counter)++;
  /*
  int32_t temp = symboltable_lookup_ident(*table, token);
  if (temp > -1)
    return (uint32_t)temp;
  symboltable_insert_ident(table, token, *temp_counter);
  return (*temp_counter)++;
  */
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
    case AT_Temp: {
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

const char* match_instruction_to_string(ICI instruction) {
  switch (instruction) {
    case ICI_None: return "None";

    case ICI_Arit_Add: return "Arit_Add";
    case ICI_Arit_AddI: return "Arit_AddI";
    case ICI_Arit_AddU: return "Arit_AddU";
    case ICI_Arit_AddIU: return "Arit_AddIU";
    case ICI_Arit_Sub: return "Arit_Sub";
    case ICI_Arit_SubI: return "Arit_SubI";
    case ICI_Arit_Mul: return "Arit_Mul";
    case ICI_Arit_MulI: return "Arit_MulI";
    case ICI_Arit_Div: return "Arit_Div";

    case ICI_Cond_Equal: return "Cond_Equal";
    case ICI_Cond_NEqual: return "Cond_NEqual";
    case ICI_Cond_GThan: return "Cond_GThan";
    case ICI_Cond_GThanEqual: return "Cond_GThanEqual";
    case ICI_Cond_LThan: return "Cond_LThan";
    case ICI_Cond_LThanEqual: return "Cond_LThanEqual";

    case ICI_Branch_Equal: return "Branch_Equal";
    case ICI_Branch_NEqual: return "Branch_NEqual";

    case ICI_DT_LoadWord: return "DT_LoadWord";
    case ICI_DT_StoreWord: return "DT_StoreWord";
    case ICI_DT_LoadAdress: return "DT_LoadAdress";
    case ICI_DT_LoadImmediate: return "DT_LoadImmediate";
    case ICI_DT_Move: return "DT_Move";

    case ICI_Label: return "Label";

    case ICI_Syscall_1: return "Syscall_1";
    case ICI_Syscall_2: return "Syscall_2";
    case ICI_Syscall_3: return "Syscall_3";
    case ICI_Syscall_4: return "Syscall_4";
    case ICI_Syscall_5: return "Syscall_5";
    case ICI_Syscall_6: return "Syscall_6";
    case ICI_Syscall_7: return "Syscall_7";
    case ICI_Syscall_8: return "Syscall_8";
    case ICI_Syscall_9: return "Syscall_9";
    case ICI_Syscall_10: return "Syscall_10";
    case ICI_Syscall_11: return "Syscall_11";
    case ICI_Syscall_12: return "Syscall_12";
    case ICI_Syscall_13: return "Syscall_13";
    case ICI_Syscall_14: return "Syscall_14";
    case ICI_Syscall_15: return "Syscall_15";
    case ICI_Syscall_16: return "Syscall_16";
    case ICI_Syscall_17: return "Syscall_17";
    case ICI_Syscall_18: return "Syscall_18";
    case ICI_Syscall_19: return "Syscall_19";
    case ICI_Syscall_20: return "Syscall_20";
    case ICI_Syscall_21: return "Syscall_21";
    case ICI_Syscall_22: return "Syscall_22";
    case ICI_Syscall_23: return "Syscall_23";

    case ICI_Logic_BitAnd: return "Logic_BitAnd";
    case ICI_Logic_BitAndI: return "Logic_BitAndI";
    case ICI_Logic_BitOr: return "Logic_BitOr";
    case ICI_Logic_BitOrI: return "Logic_BitOrI";
    case ICI_Logic_BitNor: return "Logic_BitNor";
    case ICI_Logic_BitNorI: return "Logic_BitNorI";
    case ICI_Logic_ShiftLeft: return "Logic_ShiftLeft";
    case ICI_Logic_ShiftRight: return "Logic_ShiftRight";

    case ICI_UJ_Jump: return "UJ_Jump";
    case ICI_UJ_JumpRegister: return "UJ_JumpRegister";
    case ICI_UJ_JumpAndLink: return "UJ_JumpAndLink";

    default: return "Unknown Instruction";
  }
}
