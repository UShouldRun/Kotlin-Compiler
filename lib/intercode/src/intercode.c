#include "intercode.h"

Quad ic_translate_ast(Arena arena, AST program) {

}

Quad ic_translate_func(Arena arena, HashTable hashtable, ASTN_Obj node) {
  if (node != NULL || node->type != ASTN_FUN)
    return NULL;

  Quad head = NULL,
       tail = NULL;

  Quad func_label = (Quad)arena_alloc(arena, sizeof(struct quad));
  error_assert(error_mem, func_label != NULL);
  func_label->inst = ICI_DT_LoadWord;
  func_label->addr1.type = AT_String;
  func_label->addr1.value.label = arena_strdup(arena, node->obj._fun.ident->value.ident);
  func_label->addr2 = func_label->addr3 = func_label->addr4 = NULL;
  func_label->next = NULL;

  head = func_label;
  tail = func_label;


  ASTN_FunArg params = node->obj._fun.args;
  while(params){
    Quad func_param = (Quad)arena_alloc(arena, sizeof(struct quad));
    func_param->inst              = ICI_DT_LoadWord;
    func_param->addr1.type         = AT_String;
    func_param->addr1.value.label  = arena_strdup(arena, params->arg->value.ident);
    func_param->next              = NULL;

    tail->next = func_param;
    tail = func_param;

    params = params->next;
  }

  Quad body = ic_translate_stmt(arena, hashtable, node->obj._fun.body, &hashtable->temp_counter, &hashtable->label_counter); 

  if(body){
    tail->next = body;
  }

  while(tail->next){
    tail->next = tail;
  }

  Quad func_return = (Quad)arena_alloc(arena, sizeof(struct quad));
  func_return->inst = ICI_UJ_JumpRegister;
  func_return->addr1 = func_return->addr2 = func_return->addr3 = func_return->addr4 = NULL;
  func_return->next = NULL;

  tail->next = func_return;
  
  return head;
}

<<<<<<< Updated upstream
Quad ic_translate_stmt(Arena arena, HashTable hashtable, ASTN_Stmt node, uint32_t*  temp_counter, uint32_t* label_counter) {
  if(!node) return NULL;

  switch (node->type){
    case STMT_WHILE:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->addr1.type = AT_String;
      loop_start->addr1.value.label = strdup(label_start);
      loop_start->addr2 = loop_start->addr3 = loop_start->addr4 = NULL;
      loop_start->next = NULL;

      Quad while_cond = ic_translate_expr(arena, hashtable, node->stmt._while.cond, temp_counter, label_counter);
      
      
      Quad jump_exit = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_exit->inst = ICI_Cond_NEqual;
      jump_exit->addr1 = while_cond->addr1;
      jump_exit->addr2 = NULL;
      jump_exit->addr3.type = AT_String;
      jump_exit->addr3.value.label = strdup(label_end);
      jump_exit->addr4 = NULL;
      jump_exit->next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._while.block, temp_counter, label_counter);

      Quad jump_back = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->addr1 = NULL;
      jump_back->addr2 = NULL;
      jump_back->addr3.type = AT_String;
      jump_back->addr3.value.label = strdup(label_start);
      jump_back->addr4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->addr1.type = AT_String;
      loop_end->addr1.value.label = strdup(label_end);
      loop_end->addr2 = loop_end->addr3 = loop_end->addr4 = NULL;
      loop_end->next = NULL;
      
      loop_start-> next = while_cond;
      while_cond-> next = jump_exit;
      jump_exit-> next = block;
      block-> next = jump_back;
      jump_back-> next = loop_end;

      return loop_start;
    }
    case STMT_DO:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->addr1.type = AT_String;
      loop_start->addr1.value.label = strdup(label_start);
      loop_start->addr2 = loop_start->addr3 = loop_start->addr4 = NULL;
      loop_start->next = NULL;
      
      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._while.block, temp_counter, label_counter);

      Quad cond = ic_translate_expr(arena, hashtable, node->stmt._while.cond, temp_counter, label_counter);

      Quad jump_back = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->addr1 = NULL;
      jump_back->addr2 = NULL;
      jump_back->addr3.type = AT_String;
      jump_back->addr3.value.label = strdup(label_start);
      jump_back->addr4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->addr1.type = AT_String;
      loop_end->addr1.value.label = strdup(label_end);
      loop_end->addr2 = loop_end->addr3 = loop_end->addr4 = NULL;
      loop_end->next = NULL;

      loop_start-> next  = block;
      block-> next  = cond;
      cond-> next  = jump_back;
      jump_back-> next  = loop_end;

      return loop_start;
    }
    case STMT_FOR:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad init = ic_translate_stmt(arena, hashtable, node->stmt._for.init, temp_counter, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->addr1.type = AT_String;
      loop_start->addr1.value.label = strdup(label_start);
      loop_start->addr2 = loop_start->addr3 = loop_start->addr4 = NULL;
      loop_start->next = NULL;

      Quad cond = ic_translate_expr(arena, hashtable, node->stmt._for.cond, temp_counter, label_counter);

      Quad jump_end = (Quad) arena_alloc(arena ,sizeof(struct quad));
      jump_end-> inst = ICI_Cond_NEqual;
      jump_end-> addr1 = cond->addr1;
      jump_end-> addr2 = NULL;
      jump_end-> addr3.type = AT_String;
      jump_end-> addr3.value.label = strdup(label_end);
      jump_end-> addr4 = NULL;
      jump_end-> next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._for.block, temp_counter, label_counter);

      Quad incr = ic_translate_expr(arena, hashtable, node->stmt._for.incr ,temp_counter, label_counter);

      Quad jump_back = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->addr1 = NULL;
      jump_back->addr2 = NULL;
      jump_back->addr3.type = AT_String;
      jump_back->addr3.value.label = strdup(label_start);
      jump_back->addr4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->addr1.type = AT_String;
      loop_end->addr1.value.label = strdup(label_end);
      loop_end->addr2 = loop_end->addr3 = loop_end->addr4 = NULL;
      loop_end->next = NULL;

      init-> next  = loop_start;
      loop_start-> next  = cond;
      cond-> next  = jump_end;
      jump_end-> next  = block;
      block-> next  = incr;
      incr-> next  = jump_back;
      jump_back-> next  = loop_end
      
      return init;
    }
    case STMT_IF:{
      Quad cond = ic_translate_expr(arena, hashtable,  node->stmt._if.cond, temp_counter, label_counter);

      char* label_true = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_false = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad jump_false = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_false->inst = ICI_COND_NEQUAL;
      jump_false->addr1 = cond->addr1;
      jump_false->addr2 = NULL;
      jump_false->addr3.type = AT_String;
      jump_false->addr3.value.label = strdup(label_true);
      jump_false->addr4 = NULL;
      jump_false->next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._if.block, temp_counter, label_counter);

      Quad jump_end = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_end->inst = ICI_UJ_JUMP;
      jump_end->addr1 = NULL;
      jump_end->addr2 = NULL;
      jump_end->addr3.type = AT_String;
      jump_end->addr3.value.label = strdup(label_false);
      jump_end->addr4 = NULL;
      jump_end->next = NULL;

      Quad else_block = NULL;

      if(node->stmt._if.next){
          else_block = ic_translate_stmt(arena, hashtable, node->stmt._if.next, temp_counter, label_counter);
      }

      Quad end_label = (Quad)malloc(sizeof(struct quad));
      end_label->inst = ICI_Label;
      end_label->addr1.type = AT_String;
      end_label->addr1.value.label = strdup(label_end);
      end_label->addr2 = end_label->addr3 = end_label->addr4 = NULL;
      end_label->next = NULL;

      cond->next = jump_false;
      jump_false->next = block;
      block->next = jump_end;
      jump_end->next = else_block;

      if(else_block){
        Quad last = else_block;
        while(last->next ) last = last->next;
        last->next = end_label;
      }
      else{
        last->next = end_label;
      }

      return cond;
    }

    case STMT_ELSEIF:{
      return ic_translate_stmt(arena, hashtable, node ,temp_counter ,label_counter);
    }

    case STMT_ELSE:{
      return ic_translate_stmt(arena ,hashtable, node->stmt._if.block, temp_counter, label_counter);
    }

    case STMT_CASE:{
      Quad switch_cond = ic_translate_expr(arena, hashtable, node->stmt._when.cond, temp_counter ,label_counter);

      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad case_head = switch_cond, case_tail = switch_cond;

      ASTN_STMT cases = node->stmt._when.cases;

      while(cases){
        if(cases->type == STMT_WHEN){
        char* case_label = ic_get_label(arena, ASTN_STMT, label_counter);

        Quad cond = ic_translate_stmt(arena, hashtable, cases->stmt._when.cond, temp_counter ,label_counter);

        Quad jump_case = (Quad)arena_alloc(arena, sizeof(struct quad));
        jump_case->inst = ICI_Cond_Equal;
        jump_case->addr1 = switch_cond->addr1;
        jump_case->addr2 = cond->addr1;
        jump_case->addr3.type = AT_String;
        jump_case->addr3.value.label = strdup(case_label);
        jump_case->addr4 = NULL;
        jump_case->next = NULL;

        Quad block = ic_translate_stmt(arena, hashtable, cases->stmt._when.block, temp_counter ,label_counter);

        case_tail->next = jump_case;
        case_tail = jump_case;


        Quad case = (Quad)arena_alloc(arena, sizeof(struct quad));
        case->inst = ICI_Label;
        case->addr1.type = AT_String;
        case->addr1.value.label = strdup(label_case);
        case->addr2 = case->addr3 = case->addr4 = NULL;
        case->next = block;

        case_tail->next = case ;
        case_tail = block;

        Quad jump_end = (Quad)arena_alloc(arena, sizeof(struct quad));
        jump_end->inst = ICI_UJ_Jump;
        jump_end->addr1 = NULL;
        jump_end->addr2 = NULL;
        jump_end->addr3.type = AT_String;
        jump_end->addr3.value.label = strdup(label_end);
        jump_end->addr4 = NULL;
        jump_end->next = NULL;

        case_tail->next = jump_end;
        case_tail = jump_next;

          
      }
      cases = cases->next;
      }

      Quad end_label = (Quad)arena_alloc(arena, sizeof(struct quad));
      end_label->inst = ICI_Label;
      end_label->addr1.type = AT_String;
      end_label->addr1.value.label = strdup(label_end);
      end_label->addr2 = end_label->addr3 = end_label->addr4 = NULL;
      end_label->next = NULL;


      case_tail->next = end_label;

      return case_head;
    }
    case STMT_RETURN:{
      ASTN_ExprList values = node->stmt._ret.value ;
      Quad head = NULL, tail = NULL;
      while (values){
        Quad expr = ic_translate_expr(arena, hashtable, values->expr, temp_counter ,label_counter);

        Quad return_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
        return_quad->inst = ICI_UJ_Return;
        return_quad->addr1 = expr->addr1;
        return_quad->addr2 = return_quad->addr3 = return_quad->addr4 = NULL;
        return_quad->next = NULL;

        if (!head) {
          head = expr;
        } else {
          tail->next = expr;
        }
        tail = expr;
        expr->next = return_quad;
        tail = return_quad;
        values = values->next;
      }

      return head;
    }

    case STMT_FUN_CALL:{
      ASTN_ExprList args = node->stmt._fun_call.args;
      Quad head = NULL, tail = NULL;

      while(args){
        Quad expr = ic_translate_expr(arena, hashtable, args->expr, temp_counter ,label_counter);

        Quad pass_args = (Quad)arena_alloc(arena, sizeof(struct quad));
        pass_args->inst = ICI_DT_Storeword;
        pass_args->addr1 = expr->addr1;
        pass_args->addr2 = pass_args->addr3 = pass_args->addr4 = NULL;
        pass_args->next = NULL;

        if (!head) {
          head = expr;
        } else {
          tail->next = expr;
        }
        tail = expr;
        expr->next = pass_args;
        tail = pass_args;

        args = args->next;
      }

      Quad call_func = (Quad)arena_alloc(arena, sizeof(struct quad));
      call_func->inst = ICI_UJ_JumpAndLink;
      call_func->addr1.type = AT_String;
      call_func->addr1.value.label = strdup(node->stmt._fun_call.fun->value.ident);
      call_func->addr2 = call_func->addr3 = call_func->addr4 = NULL;
      call_func->next = NULL;


      if (!head) {
        head = call_func;
      } else {
        tail->next = call_func;
      }
      tail = call_func;

      return head;

    }

    case STMT_BLOCK:{
      Quad head = NULL, tail = NULL;

      ASTN_Stmt stmt_block = node->stmt.block;
      while (stmt_block){
        Quad stmt = ic_translate_stmt(arena ,hashtable, stmt_block, temp_counter, label_counter);

        if (!head) {
          head = stmt;
        } else {
          tail->next = stmt;
        }

        while (stmt && stmt->next) {
          stmt = stmt->next;
        }
        tail = stmt;

        stmt_block = stmt_block->next;


      }

      return head;
    }

    case STMT_VAR_INCR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena, sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->addr1.type = AT_Temp;
      incr->addr1.value.temp = temp;
      incr->addr2.type = AT_UIntConst;
      incr->addr2.value.val_uint = 1; 
      incr->addr3.type = AT_Temp;
      incr->addr3.value.temp = temp; 
      incr->addr4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }

    case STMT_VAR_DECR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->addr1.type = AT_Temp;
      decr->addr1.value.temp = temp;
      decr->addr2.type = AT_UIntConst;
      decr->addr2.value.val_uint = 1; 
      decr->addr3.type = AT_Temp;
      decr->addr3.value.temp = temp; 
      decr->addr4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = decr;
      decr->next = store;

      return load_var;
    }
    case STMT_VAR_INCR_AFTER:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena, sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->addr1.type = AT_Temp;
      incr->addr1.value.temp = temp;
      incr->addr2.type = AT_UIntConst;
      incr->addr2.value.val_uint = 1; 
      incr->addr3.type = AT_Temp;
      incr->addr3.value.temp = temp; 
      incr->addr4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }

    case STMT_VAR_DECR_AFTER:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena, sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->addr1.type = AT_Temp;
      decr->addr1.value.temp = temp;
      decr->addr2.type = AT_UIntConst;
      decr->addr2.value.val_uint = 1; 
      decr->addr3.type = AT_Temp;
      decr->addr3.value.temp = temp; 
      decr->addr4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = decr;
      decr->next = store;

      return load_var;
    }

    case STMT_VAR_EQUALS_PLUS:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena, hashtable, node._assign.value, temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad add = (Quad)arena_alloc(arena, sizeof(struct quad));
      add->inst = ICI_Arit_Add;
      add->addr1.type = AT_Temp;
      add->addr1.value.temp = temp;
      add->addr2.type = expr->addr1.type;
      add->addr2.value = expr->addr1.value; 
      add->addr3.type = AT_Temp;
      add->addr3.value.temp = result; 
      add->addr4 = NULL;
      add->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next = add;
      add->next = store;

      return load_var;
    }

    case STMT_VAR_EQUALS_MINUS:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena, hashtable, node._assign.value, temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad sub = (Quad)arena_alloc(arena, sizeof(struct quad));
      sub->inst = ICI_Arit_Sub;
      sub->addr1.type = AT_Temp;
      sub->addr1.value.temp = temp;
      sub->addr2.type = expr->addr1.type;
      sub->addr2.value = expr->addr1.value; 
      sub->addr3.type = AT_Temp;
      sub->addr3.value.temp = result; 
      sub->addr4 = NULL;
      sub->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next = sub;
      sub->next = store;

      return load_var;
    }

    case STMT_VAR_EQUALS_MUL:{
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena, hashtable, node._assign.value, temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad mult = (Quad)arena_alloc(arena, sizeof(struct quad));
      mult->inst = ICI_Arit_Mul;
      mult->addr1.type = AT_Temp;
      mult->addr1.value.temp = temp;
      mult->addr2.type = expr->addr1.type;
      mult->addr2.value = expr->addr1.value; 
      mult->addr3.type = AT_Temp;
      mult->addr3.value.temp = result; 
      mult->addr4 = NULL;
      mult->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next = mult;
      mult->next = store;

      return load_var;
    }

    case STMT_VAR_EQUALS_DIV: {
      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = strdup(node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena, hashtable, node._assign.value, temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad div_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
      div_quad->inst = ICI_Arit_Div;
      div_quad->addr1.type = AT_Temp;
      div_quad->addr1.value.temp = temp;
      div_quad->addr2.type = expr->addr1.type;
      div_quad->addr2.value = expr->addr1.value; 
      div_quad->addr3.type = AT_Temp;
      div_quad->addr3.value.temp = result; 
      div_quad->addr4 = NULL;
      div_quad->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      load_var-> next = expr;
      expr-> next = div_quad;
      div_quad->next = store;

      return load_var;
    }

    case STMT_VAR_DECL:{

      Quad expr = ic_translate_expr(arena, hashtable, node->stmt._assign.value, temp_counter ,label_counter);

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1 = expr->addr1;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      expr->next = store;
      
      symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

      return NULL;
    }

    case STMT_VAR_DECL_ASSIGN:{
    

      Quad expr = ic_translate_expr(arena, hashtable, node->stmt._assign.value, temp_counter ,label_counter);

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1 = expr->addr1;
      store->addr2.type = AT_String;
      store->addr2.value.label = strdup(node->stmt._assign.var->value.ident);
      store->addr3 = NULL;
      store->addr4 = NULL;
      store->next = NULL;

      expr->next = store;

      symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

      return expr;       
    }

    case STMT_VAR_DIRECT_ASSIGN:{
      Quad expr = ic_translate_expr(arena, hashtable, node->stmt._assign.value, temp_counter, label_counter);

      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      var.type = AT_Temp;
      var.value.temp = node->stmt._assign.var->value.ident;

      Quad stmt = (Quad)arena_alloc(arena, sizeof(struct quad));
      stmt->inst = ICI_DT_StoreWord;
      stmt->addr1 = expr->addr1;
      stmt->addr2 = var;
      stmt->addr3 = NULL;
      stmt->addr4 = NULL;
      stmt->next = NULL;

      expr->next = stmt;

      return expr;
    }

    case STMT_DO:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->addr1.type = AT_String;
      loop_start->addr1.value.label = arena_strdup(arena, label_start);
      loop_start->addr2 = loop_start->addr3 = loop_start->addr4 = NULL;
      loop_start->next = NULL;
      
      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._while.block, temp_counter, label_counter);

      Quad cond = ic_translate_expr(arena, hashtable, node->stmt._while.cond, temp_counter,label_counter);

      Quad jump_back = (Quad)arena_alloc(arena, sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->addr1 = NULL;
      jump_back->addr2 = NULL;
      jump_back->addr3.type = AT_String;
      jump_back->addr3.value.label = arena_strdup(arena,label_start);
      jump_back->addr4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena, sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->addr1.type = AT_String;
      loop_end->addr1.value.label = arena_strdup(arena,label_end);
      loop_end->addr2 = loop_end->addr3 = loop_end->addr4 = NULL;
      loop_end->next = NULL;

      loop_start-> next  = block;
      block-> next  = cond;
      cond-> next  = jump_back;
      jump_back-> next  = loop_end;

      return loop_start;
    }

    case STMT_FOR:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad init = ic_translate_stmt(arena, hashtable, node->stmt._for.init, temp_counter, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->addr1.type = AT_String;
      loop_start->addr1.value.label = arena_strdup(arena,label_start);
      loop_start->addr2 = loop_start->addr3 = loop_start->addr4 = NULL;
      loop_start->next = NULL;

      Quad cond = ic_translate_expr(arena, hashtable, node->stmt._for.cond, temp_counter, label_counter);

      Quad jump_end = (Quad) arena_alloc(arena ,sizeof(struct quad));
      jump_end-> inst = ICI_Cond_NEqual;
      jump_end-> addr1 = cond->addr1;
      jump_end-> addr2 = NULL;
      jump_end-> addr3.type = AT_String;
      jump_end-> addr3.value.label = arena_strdup(arena,label_end);
      jump_end-> addr4 = NULL;
      jump_end-> next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._for.block, temp_counter, label_counter);

      Quad incr = ic_translate_expr(arena, hashtable, node->stmt._for.incr ,temp_counter, label_counter);

      Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->addr1 = NULL;
      jump_back->addr2 = NULL;
      jump_back->addr3.type = AT_String;
      jump_back->addr3.value.label = arena_strdup(arena,label_start);
      jump_back->addr4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->addr1.type = AT_String;
      loop_end->addr1.value.label = arena_strdup(arena,label_end);
      loop_end->addr2 = loop_end->addr3 = loop_end->addr4 = NULL;
      loop_end->next = NULL;

      init-> next  = loop_start;
      loop_start-> next  = cond;
      cond-> next  = jump_end;
      jump_end-> next  = block;
      block-> next  = incr;
      incr-> next  = jump_back;
      jump_back-> next  = loop_end
      
      return init;
    }

    case STMT_IF:{
      Quad cond = ic_translate_expr(arena, hashtable, node->stmt._if.cond, temp_counter, label_counter);

      char* label_true = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_false = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad jump_false = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_false->inst = ICI_COND_NEQUAL;
      jump_false->addr1 = cond->addr1;
      jump_false->addr2 = NULL;
      jump_false->addr3.type = AT_String;
      jump_false->addr3.value.label = arena_strdup(arena,label_true);
      jump_false->addr4 = NULL;
      jump_false->next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node->stmt._if.block,temp_counter,label_counter);

      Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_end->inst = ICI_UJ_JUMP;
      jump_end->addr1 = NULL;
      jump_end->addr2 = NULL;
      jump_end->addr3.type = AT_String;
      jump_end->addr3.value.label = arena_strdup(arena,label_false);
      jump_end->addr4 = NULL;
      jump_end->next = NULL;

      Quad else_block = NULL;

      if(node->stmt._if.next){
          else_block = ic_translate_stmt(arena, hashtable, node->stmt._if.next, temp_counter,label_counter);
      }

      Quad end_label = (Quad)malloc(sizeof(struct quad));
      end_label->inst = ICI_Label;
      end_label->addr1.type = AT_String;
      end_label->addr1.value.label = arena_strdup(arena,label_end);
      end_label->addr2 = end_label->addr3 = end_label->addr4 = NULL;
      end_label->next = NULL;

      cond->next = jump_false;
      jump_false->next = block;
      block->next = jump_end;
      jump_end->next = else_block;

      if(else_block){
        Quad last = else_block;
        while(last->next ) last = last->next;
        last->next = end_label;
      }
      else{
        last->next = end_label;
      }

      return cond;
    }

    case STMT_ELSEIF:{
      return ic_translate_stmt(arena, hashtable, node ,temp_counter ,label_counter);
    }

    case STMT_ELSE:{
      return ic_translate_stmt(arena ,hashtable, node->stmt._if.block, temp_counter, label_counter);
    }

    case STMT_CASE:{
      Quad switch_cond = ic_translate_expr(arena, hashtable, node->stmt._when.cond, temp_counter ,label_counter);

      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad case_head = switch_cond, case_tail = switch_cond;

      ASTN_STMT cases = node->stmt._when.cases;

      while(cases){
        if(cases->type == STMT_WHEN){
          char* case_label = ic_get_label(arena, ASTN_STMT, label_counter);

          Quad cond = ic_translate_stmt(arena, hashtable, cases->stmt._when.cond, temp_counter ,label_counter);

          Quad jump_case = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_case->inst = ICI_Cond_Equal;
          jump_case->addr1 = switch_cond->addr1;
          jump_case->addr2 = cond->addr1;
          jump_case->addr3.type = AT_String;
          jump_case->addr3.value.label = arena_strdup(arena,case_label);
          jump_case->addr4 = NULL;
          jump_case->next = NULL;

          Quad block = ic_translate_stmt(arena, hashtable, cases->stmt._when.block, temp_counter ,label_counter);

          case_tail->next = jump_case;
          case_tail = jump_case;


          Quad case = (Quad)arena_alloc(arena,sizeof(struct quad));
          case->inst = ICI_Label;
          case->addr1.type = AT_String;
          case->addr1.value.label = arena_strdup(arena,label_case);
          case->addr2 = case->addr3 = case->addr4 = NULL;
          case->next = block;

          case_tail->next = case ;
          case_tail = block;

          Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_end->inst = ICI_UJ_Jump;
          jump_end->addr1 = NULL;
          jump_end->addr2 = NULL;
          jump_end->addr3.type = AT_String;
          jump_end->addr3.value.label = arena_strdup(arena,label_end);
          jump_end->addr4 = NULL;
          jump_end->next = NULL;

          case_tail->next = jump_end;
          case_tail = jump_next;
        }

        cases = cases->next;
      }

      Quad end_label = (Quad)arena_alloc(arena,sizeof(struct quad));
      end_label->inst = ICI_Label;
      end_label->addr1.type = AT_String;
      end_label->addr1.value.label = arena_strdup(arena,label_end);
      end_label->addr2 = end_label->addr3 = end_label->addr4 = NULL;
      end_label->next = NULL;


      case_tail->next = end_label;

      return case_head;
    }

    case STMT_RETURN:{
      ASTN_ExprList values = node->stmt._ret.value ;
      Quad head = NULL, tail = NULL;
      while (values){
        Quad expr = ic_translate_expr(arena, hashtable, values->expr, temp_counter ,label_counter);

        Quad return_quad = (Quad)arena_alloc(arena,sizeof(struct quad));
        return_quad->inst = ICI_UJ_Return;
        return_quad->addr1 = expr->addr1;
        return_quad->addr2 = return_quad->addr3 = return_quad->addr4 = NULL;
        return_quad->next = NULL;

        if (!head) {
          head = expr;
        } else {
          tail->next = expr;
        }
        tail = expr;
        expr->next = return_quad;
        tail = return_quad;
        values = values->next;
      }

      return head;
    }
    case STMT_FUN_CALL:{
      ASTN_ExprList args = node->stmt._fun_call.args;
      Quad head = NULL, tail = NULL;

      while(args){
        Quad expr = ic_translate_expr(arena, hashtable, args->expr, temp_counter ,label_counter);

        Quad pass_args = (Quad)arena_alloc(arena,sizeof(struct quad));
        pass_args->inst = ICI_DT_Storeword;
        pass_args->addr1 = expr->addr1;
        pass_args->addr2 = pass_args->addr3 = pass_args->addr4 = NULL;
        pass_args->next = NULL;

        if (!head) {
          head = expr;
        } else {
          tail->next = expr;
        }
        tail = expr;
        expr->next = pass_args;
        tail = pass_args;

        args = args->next;
      }

      Quad call_func = (Quad)arena_alloc(arena,sizeof(struct quad));
      call_func->inst = ICI_UJ_JumpAndLink;
      call_func->addr1.type = AT_String;
      call_func->addr1.value.label = arena_strdup(arena,node->stmt._fun_call.fun->value.ident);
      call_func->addr2 = call_func->addr3 = call_func->addr4 = NULL;
      call_func->next = NULL;


      if (!head) {
        head = call_func;
      } else {
        tail->next = call_func;
      }
      tail = call_func;

      return head;

    }

    case STMT_BLOCK:{
      Quad head = NULL, tail = NULL;

      ASTN_Stmt stmt_block = node->stmt.block;
      while (stmt_block){
        Quad stmt = ic_translate_stmt(arena ,hashtable, stmt_block, temp_counter, label_counter);

        if (!head) {
          head = stmt;
        } else {
          tail->next = stmt;
        }

        while (stmt && stmt->next) {
          stmt = stmt->next;
        }
        tail = stmt;

        stmt_block = stmt_block->next;


      }

      return head;
    }

    case STMT_VAR_INCR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->addr1.type = AT_Temp;
      incr->addr1.value.temp = temp;
      incr->addr2.type = AT_UIntConst;
      incr->addr2.value.val_uint = 1; 
      incr->addr3.type = AT_Temp;
      incr->addr3.value.temp = temp; 
      incr->addr4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }

    case STMT_VAR_DECR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->addr1.type = AT_Temp;
      decr->addr1.value.temp = temp;
      decr->addr2.type = AT_UIntConst;
      decr->addr2.value.val_uint = 1; 
      decr->addr3.type = AT_Temp;
      decr->addr3.value.temp = temp; 
      decr->addr4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = decr;
      decr->next = store;

      return load_var;
    }

    case STMT_VAR_INCR_AFTER:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->addr1.type = AT_Temp;
      incr->addr1.value.temp = temp;
      incr->addr2.type = AT_UIntConst;
      incr->addr2.value.val_uint = 1; 
      incr->addr3.type = At_Temp;
      incr->addr3.value.temp = temp; 
      incr->addr4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_Temp;
      store->addr1.value.temp = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = incr;
      incr->next = store;

      return load_var;
    }

    case STMT_VAR_DECR_AFTER: {
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1.type = AT_String;
      load_var->addr1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var->addr2 = load_var->addr3 = load_var->addr4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->addr3.type = AT_Temp;
      load_var->addr3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->addr1.type = AT_Temp;
      decr->addr1.value.temp = temp;
      decr->addr2.type = AT_UIntConst;
      decr->addr2.value.val_uint = 1; 
      decr->addr3.type = AT_Temp;
      decr->addr3.value.temp = temp; 
      decr->addr4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1.type = AT_UIntConst;
      store->addr1.value.val_uint = temp;
      store->addr2 = NULL;
      store->addr3.type = AT_String;
      store->addr3.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      store->addr4 = NULL;
      store->next = NULL;

      load_var->next = decr;
      decr->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_PLUS: {
      ASTN_Token token = node->stmt._assign.var;

      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, token)
      );
      var->value.label = arena_strdup(arena, token->value.ident);
      error_assert(error_mem, var->value.label != NULL);

      Address load_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, load_addr != NULL);
      load_addr->type = AT_Temp;
      load_addr->value.temp = ic_get_temp(table, token, temp_counter);

      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, load_var != NULL);
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1 = load_addr;
      load_var->addr2 = var;
      load_var->addr3 = load_var->addr4 = NULL;
      load_var->next = NULL;

      Address add_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, add_addr != NULL);
      add_addr->type = AT_Temp;
      add_addr->value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad expr = ic_translate_expr(
        arena,
        table,
        node._assign.value,
        temp_counter
      );

      Quad add_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, add_quad != NULL);
      add_quad->inst = ICI_Arit_Add;
      add_quad->addr1 = add_addr;
      add_quad->addr2 = add_addr;
      add_quad->addr3 = expr->addr1; 
      add_quad->addr4 = NULL;
      add_quad->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, store != NULL);
      store->inst = ICI_DT_StoreWord;
      store->addr1 = var;
      store->addr2 = add_quad;
      store->addr3 = store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next     = add_quad;
      add_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_MINUS: {
      ASTN_Token token = node->stmt._assign.var;

      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, token)
      );
      var->value.label = arena_strdup(arena, token->value.ident);
      error_assert(error_mem, var->value.label != NULL);

      Address load_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, load_addr != NULL);
      load_addr->type = AT_Temp;
      load_addr->value.temp = ic_get_temp(table, token, temp_counter);

      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, load_var != NULL);
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1 = load_addr;
      load_var->addr2 = var;
      load_var->addr3 = load_var->addr4 = NULL;
      load_var->next = NULL;

      Address sub_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, sub_addr != NULL);
      sub_addr->type = AT_Temp;
      sub_addr->value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad expr = ic_translate_expr(
        arena,
        table,
        node._assign.value,
        temp_counter
      );

      Quad sub_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, sub_quad != NULL);
      sub_quad->inst = ICI_Arit_Sub;
      sub_quad->addr1 = sub_addr;
      sub_quad->addr2 = sub_addr;
      sub_quad->addr3 = expr->addr1; 
      sub_quad->addr4 = NULL;
      sub_quad->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, store != NULL);
      store->inst = ICI_DT_StoreWord;
      store->addr1 = var;
      store->addr2 = sub_quad;
      store->addr3 = store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next     = sub_quad;
      sub_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_MUL: {
      ASTN_Token token = node->stmt._assign.var;

      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, token)
      );
      var->value.label = arena_strdup(arena, token->value.ident);
      error_assert(error_mem, var->value.label != NULL);

      Address load_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, load_addr != NULL);
      load_addr->type = AT_Temp;
      load_addr->value.temp = ic_get_temp(table, token, temp_counter);

      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, load_var != NULL);
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1 = load_addr;
      load_var->addr2 = var;
      load_var->addr3 = load_var->addr4 = NULL;
      load_var->next = NULL;

      Address mul_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, mul_addr != NULL);
      mul_add->type = AT_Temp;
      mul_addr->value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad expr = ic_translate_expr(
        arena,
        table,
        node._assign.value,
        temp_counter
      );

      Quad mul_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, mul_quad != NULL);
      mul_quad->inst = ICI_Arit_Mul;
      mul_quad->addr1 = mul_addr;
      mul_quad->addr2 = mul_addr;
      mul_quad->addr3 = expr->addr1; 
      mul_quad->addr4 = NULL;
      mul_quad->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, store != NULL);
      store->inst = ICI_DT_StoreWord;
      store->addr1 = var;
      store->addr2 = mul_quad;
      store->addr3 = store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next     = mul_quad;
      mul_quad->next = store;

      return load_var;
    }
    case STMT_VAR_EQUALS_DIV: {
      ASTN_Token token = node->stmt._assign.var;

      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, token)
      );
      var->value.label = arena_strdup(arena, token->value.ident);
      error_assert(error_mem, var->value.label != NULL);

      Address load_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, load_addr != NULL);
      load_addr->type = AT_Temp;
      load_addr->value.temp = ic_get_temp(table, token, temp_counter);

      Quad load_var = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, load_var != NULL);
      load_var->inst = ICI_DT_LoadWord;
      load_var->addr1 = load_addr;
      load_var->addr2 = var;
      load_var->addr3 = load_var->addr4 = NULL;
      load_var->next = NULL;

      Address div_addr = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, div_addr != NULL);
      div_addr->type = AT_Temp;
      div_addr->value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad expr = ic_translate_expr(
        arena,
        table,
        node._assign.value,
        temp_counter
      );

      Quad div_quad = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, div_quad != NULL);
      div_quad->inst = ICI_Arit_Div;
      div_quad->addr1 = div_addr;
      div_quad->addr2 = div_addr;
      div_quad->addr3 = expr->addr1; 
      div_quad->addr4 = NULL;
      div_quad->next = NULL;

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, store != NULL);
      store->inst = ICI_DT_StoreWord;
      store->addr1 = var;
      store->addr2 = div_quad;
      store->addr3 = store->addr4 = NULL;
      store->next = NULL;

      load_var->next = expr;
      expr->next     = div_quad;
      div_quad->next = store;

      return load_var;
    }
    case STMT_VAR_DECL: {
      error_assert(
        error_intercode,
        symboltable_insert_ident(table, node->stmt._assign.var, -1)
      );
      error_assert(
        error_intercode,
        symbolstack_push(stack, node->stmt._assign.var);
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
      Address var = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_insert_ident(table, token, -1)
      );
      error_assert(
        error_intercode,
        symbolstack_push(stack, token)
      );
      var->value.label = arena_strdup(arena, token);
      error_assert(error_mem, var->value.label != NULL);

      Quad store = (Quad)arena_alloc(arena, sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->addr1 = var;
      store->addr2 = expr->addr1;
      store->addr3 = store->addr4 = NULL;
      store->next = NULL;

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

      Address var = (Address)arena_alloc(arena, sizeof(struct address));;
      error_assert(error_mem, var != NULL);
      var->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, node->stmt._assign.var)
      );
      var->value.label = arena_strdup(arena, node->stmt._assign.var);
      error_assert(error_mem, var->value.label != NULL);

      Quad stmt = (Quad)arena_alloc(arena, sizeof(struct quad));
      stmt->inst = ICI_DT_StoreWord;
      stmt->addr1 = var;
      stmt->addr2 = expr->addr1;
      stmt->addr3 = stmt->addr4 = NULL;
      stmt->next = NULL;

      expr->next = stmt;

      return expr;
    }
  }
}

Quad ic_translate_expr(Arena arena, SymbolTable table, ASTN_Expr node, uint32_t* temp_counter) {
  if (node == NULL)
    return NULL;

  switch(node->type) {
    case EXPR_TOKEN: {
      Address addr1 = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, address != NULL);

      Address addr2 = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, address != NULL);

      Quad expr = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, expr != NULL);

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
          case TT_LIT_CHAR: {
            addr2->type = AT_Char;
            error_assert(error_intercode, node->expr.token->value.str != NULL);
            addr2->value.val_char = node->expr.token->value.str[0];
            break;
          }
          case TT_LIT_STRING: {
            addr2->type = AT_String;
            error_assert(error_intercode, node->expr.token->value.str != NULL);
            addr2->value.label = arena_strdup(arena, node->expr.token->value.str);
            error_assert(error_mem, addr2->value.label != NULL);
            break;
          }
        }

        addr1->type = AT_Temp;
        addr1->value.temp = ic_get_temp(NULL, NULL, temp_counter);

        expr->inst = ICI_DT_LoadImmediate;
        expr->addr1 = addr1;
        expr->addr2 = addr2;
        expr->addr3 = expr->addr4 = NULL;
      }

      addr1->type = AT_Temp;
      addr1->value.temp = ic_get_temp(table, node->expr.token, temp_counter);

      addr2->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, node->expr.token)
      );
      addr2->value.label = arena_strdup(arena, node->expr.token->value.ident);
      error_assert(error_mem, addr2->value.label != NULL);
 
      expr->inst = ICI_DT_LoadWord;
      expr->addr1 = addr1;
      expr->addr2 = addr2;
      expr->addr3 = expr->addr4 = NULL;
      
      return expr;
    }
    case EXPR_UN: {
      Quad sub_expr = ic_translate_expr(
        arena,
        table,
        node->expr.unary.operand, 
        temp_counter
      );

      Address result = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, result != NULL);
      result->type = AT_Temp;
      result->value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad expr = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, expr != NULL);

      ICI op;
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
          expr->op = ICI_Logic_BitNorI;
          expr->addr1 = result;
          expr->addr2 = result;

          Address immediate = (Address)arena_alloc(arena, sizeof(struct address));
          error_assert(error_mem, immediate != NULL);
          immediate->type = AT_IntConst;
          immediate->value.val_int = 0;

          expr->addr3 = immediate;
          expr->addr4 = NULL;

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

      Address result = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, result != NULL);
      result->type = AT_Temp;
      result->value.temp = ic_get_temp(NULL, NULL, temp_counter);

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
      }

      Quad expr = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, expr != NULL);
      expr->inst = op;
      expr->addr1 = result;
      expr->addr2 = leftSide->addr1;
      expr->addr3 = rightSide->addr2;
      expr->addr4 = NULL;

      return expr;
    }
    case EXPR_FUN_CALL: {
      Quad head = NULL,
           tail = NULL;

      ASTN_ExprList arg = node->expr.fun_call.args;
      for (; arg; arg = arg->next) {
        Quad fun_arg = (Quad)arena_alloc(arena, sizeof(struct quad));
        error_assert(error_mem, fun_arg != NULL);
        fun_arg->inst = ICI_DT_StoreWord;
        fun_arg->addr1 = ic_translate_expr(arena, table, arg, temp_counter);
        fun_arg->addr2 = fun_arg->addr3 = fun_arg->addr4 = NULL;
        fun_arg->next = NULL;

        if (head == NULL) {
          head = tail = fun_arg;
        } else {
          tail->next = fun_arg;
          tail = tail->next;
        }
      }

      Address fun_label = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, fun_label != NULL);
      fun_label->type = AT_Label;
      error_assert(
        error_intercode,
        symboltable_exists_ident(table, node->stmt._assign.var)
      );
      fun_label->value.label = arena_strdup(arena, node->expr.fun_call.fun->value.ident);

      Quad call_func = (Quad)arena_alloc(arena, sizeof(struct quad));
      call_func->inst = ICI_UJ_JumpAndLink;
      call_func->addr1 = fun_label;
      call_func->addr2 = call_func->addr3 = call_func->addr4 = NULL;
      call_func->next = NULL;

      if (head == NULL) {
        head = call_func;
      } else {
        tail->next = call_func;
      }

      Address return_add = (Address)arena_alloc(arena, sizeof(struct address));
      error_assert(error_mem, return_add != NULL);
      return_add.type = AT_Temp;
      return_add.value.temp = ic_get_temp(NULL, NULL, temp_counter);

      Quad func_return = (Quad)arena_alloc(arena, sizeof(struct quad));
      func_return->inst = ICI_DT_LoadWord;
      func_return->addr1 = return_add;
      func_return->addr2 = func_return->addr3 = func_return->addr4 = NULL;
      func_return->next = NULL;

      call_func->next = func_return;

      return head != NULL ? head : call_func;
    }
  }
}

uint32_t ic_get_temp(SymbolTable table, ASTN_Token token, uint32_t* temp_counter) {
  if (table == NULL || token == NULL)
    return (*temp_counter)++;
  int32_t temp = symboltable_lookup_ident(table, token);
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
