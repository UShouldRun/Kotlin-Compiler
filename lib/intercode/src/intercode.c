#include "hashtable_private.h"

#include "ast.h"
#include "ast_private.h"

Quad ic_translate_func(Arena arena, HashTable hashtable, ASTN_Obj node) {
  if(!node || node -> type != ASTN_FUN) return NULL;

  Quad head = NULL, tail = NULL;

  Quad func_label = (Quad)arena_alloc(arena,sizeof(struct quad));
  func_label -> inst = ICI_DT_LoadWord;
  func_label -> add1.type = AT_String;
  func_label -> add1.value.label = arena_strdup(arena, node -> obj._fun.ident -> value.ident);
  func_label -> add2 = func_label -> add3 = func_label -> add4 = NULL;
  func_label -> next = NULL;

  head = func_label;
  tail = func_label;


  ASTN_FunArg params = node->obj._fun.args;
  while(params){
    Quad func_param = (Quad)arena_alloc(arena,sizeof(struct quad));
    func_param->inst              = ICI_DT_LoadWord;
    func_param->add1.type         = AT_String;
    func_param->add1.value.label  = arena_strdup(arena, params -> arg -> value.ident);
    func_param->next              = NULL;

    tail -> next = func_param;
    tail = func_param;

    params = params -> next;
  }

  Quad body = ic_translate_stmt(arena , hashtable , node -> obj._fun.body, &hashtable->temp_counter , &hashtable->label_counter); 

  if(body){
    tail -> next = body;
  }

  while(tail -> next){
    tail -> next = tail;
  }

  Quad func_return = (Quad)arena_alloc(arena,sizeof(struct quad));
  func_return -> inst = ICI_UJ_JumpRegister;
  func_return -> add1 = func_return -> add2 = func_return -> add3 = func_return -> add4 = NULL;
  func_return -> next = NULL;

  tail -> next = func_return;
  
  return head;
}

<<<<<<< HEAD
Quad ic_translate_stmt (Arena arena, HashTable hashtable, ASTN_Stmt node, uint32_t*  temp_counter, uint32_t* label_counter){
  if(!node) return NULL;

  switch (node -> type){
    case STMT_WHILE:{

      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->add1.type = AT_String;
      loop_start->add1.value.label = arena_strdup(arena , label_start);
      loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
      loop_start->next = NULL;

      Quad while_cond = ic_translate_expr(arena, hashtable, node->stmt._while.cond , temp_counter,label_counter);
      
      
      Quad jump_exit = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_exit->inst = ICI_Cond_NEqual;
      jump_exit->add1 = while_cond->add1;
      jump_exit->add2 = NULL;
      jump_exit->add3.type = AT_String;
      jump_exit->add3.value.label = arena_strdup(arena , label_end);
      jump_exit->add4 = NULL;
      jump_exit->next = NULL;

      Quad block = ic_translate_stmt(arena , hashtable, node -> stmt._while.block,temp_counter,label_counter);

      Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->add1 = NULL;
      jump_back->add2 = NULL;
      jump_back->add3.type = AT_String;
      jump_back->add3.value.label = arena_strdup(arena ,label_start);
      jump_back->add4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->add1.type = AT_String;
      loop_end->add1.value.label = arena_strdup(arena ,label_end);
      loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
      loop_end->next = NULL;
      
      loop_start  ->  next = while_cond;
      while_cond  ->  next = jump_exit;
      jump_exit   ->  next = block;
      block       ->  next = jump_back;
      jump_back   ->  next = loop_end;

      return loop_start;
=======
Quad ic_translate_stmt(Arena arena, HashTable hashtable, ASTN_Stmt node, uint32_t*  temp_counter, uint32_t* label_counter) {
     if(!node) return NULL;

    switch (node -> type){
        case STMT_WHILE:{
            char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
            char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

            Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
            loop_start->inst = ICI_Label;
            loop_start->add1.type = AT_String;
            loop_start->add1.value.label = strdup(label_start);
            loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
            loop_start->next = NULL;

            Quad while_cond = ic_translate_expr(arena, hashtable, node->stmt._while.cond , temp_counter,label_counter);
            
            
            Quad jump_exit = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_exit->inst = ICI_Cond_NEqual;
            jump_exit->add1 = while_cond->add1;
            jump_exit->add2 = NULL;
            jump_exit->add3.type = AT_String;
            jump_exit->add3.value.label = strdup(label_end);
            jump_exit->add4 = NULL;
            jump_exit->next = NULL;

            Quad block = ic_translate_stmt(arena , hashtable, node -> stmt._while.block,temp_counter,label_counter);

            Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_back->inst = ICI_UJ_Jump;
            jump_back->add1 = NULL;
            jump_back->add2 = NULL;
            jump_back->add3.type = AT_String;
            jump_back->add3.value.label = strdup(label_start);
            jump_back->add4 = NULL;
            jump_back->next = NULL;

            Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
            loop_end->inst = ICI_Label;
            loop_end->add1.type = AT_String;
            loop_end->add1.value.label = strdup(label_end);
            loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
            loop_end->next = NULL;
            
            loop_start  ->  next = while_cond;
            while_cond  ->  next = jump_exit;
            jump_exit   ->  next = block;
            block       ->  next = jump_back;
            jump_back   ->  next = loop_end;

            return loop_start;
        }
        case STMT_DO:{
          char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
          char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

          Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
          loop_start->inst = ICI_Label;
          loop_start->add1.type = AT_String;
          loop_start->add1.value.label = strdup(label_start);
          loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
          loop_start->next = NULL;
          
          Quad block = ic_translate_stmt(arena, hashtable, node -> stmt._while.block, temp_counter , label_counter);

          Quad cond = ic_translate_expr(arena , hashtable , node -> stmt._while.cond, temp_counter,label_counter);

          Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_back->inst = ICI_UJ_Jump;
          jump_back->add1 = NULL;
          jump_back->add2 = NULL;
          jump_back->add3.type = AT_String;
          jump_back->add3.value.label = strdup(label_start);
          jump_back->add4 = NULL;
          jump_back->next = NULL;

          Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
          loop_end->inst = ICI_Label;
          loop_end->add1.type = AT_String;
          loop_end->add1.value.label = strdup(label_end);
          loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
          loop_end->next = NULL;

          loop_start  ->  next  = block;
          block       ->  next  = cond;
          cond        ->  next  = jump_back;
          jump_back   ->  next  = loop_end;

          return loop_start;
        }
        case STMT_FOR:{
          char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
          char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

          Quad init = ic_translate_stmt(arena , hashtable , node -> stmt._for.init , temp_counter , label_counter);

          Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
          loop_start->inst = ICI_Label;
          loop_start->add1.type = AT_String;
          loop_start->add1.value.label = strdup(label_start);
          loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
          loop_start->next = NULL;

          Quad cond = ic_translate_expr(arena , hashtable , node -> stmt._for.cond , temp_counter, label_counter);

          Quad jump_end = (Quad) arena_alloc(arena ,sizeof(struct quad));
          jump_end-> inst = ICI_Cond_NEqual;
          jump_end-> add1 = cond -> add1;
          jump_end-> add2 = NULL;
          jump_end-> add3.type = AT_String;
          jump_end-> add3.value.label = strdup(label_end);
          jump_end-> add4 = NULL;
          jump_end-> next = NULL;

          Quad block = ic_translate_stmt(arena , hashtable , node -> stmt._for.block , temp_counter , label_counter);

          Quad incr = ic_translate_expr(arena , hashtable , node -> stmt._for.incr ,temp_counter , label_counter);

          Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_back->inst = ICI_UJ_Jump;
          jump_back->add1 = NULL;
          jump_back->add2 = NULL;
          jump_back->add3.type = AT_String;
          jump_back->add3.value.label = strdup(label_start);
          jump_back->add4 = NULL;
          jump_back->next = NULL;

          Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
          loop_end->inst = ICI_Label;
          loop_end->add1.type = AT_String;
          loop_end->add1.value.label = strdup(label_end);
          loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
          loop_end->next = NULL;

          init        ->  next  = loop_start;
          loop_start  ->  next  = cond;
          cond        ->  next  = jump_end;
          jump_end    ->  next  = block;
          block       ->  next  = incr;
          incr        ->  next  = jump_back;
          jump_back   ->  next  = loop_end
          
          return init;
        }
        case STMT_IF:{
            Quad cond = ic_translate_expr(arena, hashtable, node -> stmt._if.cond , temp_counter, label_counter);

            char* label_true = ic_get_label(arena , ASTN_STMT , label_counter);
            char* label_false = ic_get_label(arena , ASTN_STMT , label_counter);

            Quad jump_false = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_false -> inst = ICI_COND_NEQUAL;
            jump_false -> add1 = cond -> add1;
            jump_false -> add2 = NULL;
            jump_false -> add3.type = AT_String;
            jump_false -> add3.value.label = strdup(label_true);
            jump_false -> add4 = NULL;
            jump_false -> next = NULL;

            Quad block = ic_translate_stmt(arena, hashtable, node -> stmt._if.block,temp_counter,label_counter);

            Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_end -> inst = ICI_UJ_JUMP;
            jump_end -> add1 = NULL;
            jump_end -> add2 = NULL;
            jump_end -> add3.type = AT_String;
            jump_end -> add3.value.label = strdup(label_false);
            jump_end -> add4 = NULL;
            jump_end -> next = NULL;

            Quad else_block = NULL;

            if(node -> stmt._if.next){
                else_block = ic_translate_stmt(arena , hashtable , node -> stmt._if.next , temp_counter,label_counter);
            }

            Quad end_label = (Quad)malloc(sizeof(struct quad));
            end_label->inst = ICI_Label;
            end_label->add1.type = AT_String;
            end_label->add1.value.label = strdup(label_end);
            end_label->add2 = end_label->add3 = end_label->add4 = NULL;
            end_label->next = NULL;

            cond        -> next = jump_false;
            jump_false  -> next = block;
            block       -> next = jump_end;
            jump_end    -> next = else_block;

            if(else_block){
              Quad last = else_block;
              while(last -> next ) last = last -> next;
              last -> next = end_label;
            }
            else{
              last -> next = end_label;
            }

            return cond;
        }

        case STMT_ELSEIF:{
          return ic_translate_stmt(arena , hashtable , node ,temp_counter ,label_counter);
        }

        case STMT_ELSE:{
          return ic_translate_stmt(arena ,hashtable, node -> stmt._if.block , temp_counter, label_counter);
        }

        case STMT_CASE:{
          Quad switch_cond = ic_translate_expr(arena , hashtable, node -> stmt._when.cond , temp_counter ,label_counter);

          char* label_end = ic_get_label(arena , ASTN_STMT , label_counter);

          Quad case_head = switch_cond, case_tail = switch_cond;

          ASTN_STMT cases = node -> stmt._when.cases;

          while(cases){
            if(cases -> type == STMT_WHEN){
            char* case_label = ic_get_label(arena , ASTN_STMT , label_counter);

            Quad cond = ic_translate_stmt(arena , hashtable , cases -> stmt._when.cond , temp_counter ,label_counter);

            Quad jump_case = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_case -> inst = ICI_Cond_Equal;
            jump_case -> add1 = switch_cond -> add1;
            jump_case -> add2 = cond -> add1;
            jump_case -> add3.type = AT_String;
            jump_case -> add3.value.label = strdup(case_label);
            jump_case -> add4 = NULL;
            jump_case -> next = NULL;

            Quad block = ic_translate_stmt(arena , hashtable , cases -> stmt._when.block , temp_counter ,label_counter);

            case_tail->next = jump_case;
            case_tail = jump_case;


            Quad case = (Quad)arena_alloc(arena,sizeof(struct quad));
            case -> inst = ICI_Label;
            case -> add1.type = AT_String;
            case -> add1.value.label = strdup(label_case);
            case -> add2 = case -> add3 = case -> add4 = NULL;
            case -> next = block;

            case_tail -> next = case ;
            case_tail = block;

            Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_end -> inst = ICI_UJ_Jump;
            jump_end -> add1 = NULL;
            jump_end->add2 = NULL;
            jump_end->add3.type = AT_String;
            jump_end->add3.value.label = strdup(label_end);
            jump_end->add4 = NULL;
            jump_end->next = NULL;

            case_tail -> next = jump_end;
            case_tail = jump_next;

             
          }
          cases = cases -> next;
          }

          Quad end_label = (Quad)arena_alloc(arena,sizeof(struct quad));
          end_label -> inst = ICI_Label;
          end_label->add1.type = AT_String;
          end_label->add1.value.label = strdup(label_end);
          end_label->add2 = end_label->add3 = end_label->add4 = NULL;
          end_label->next = NULL;


          case_tail -> next = end_label;

          return case_head;
        }
        case STMT_RETURN:{
          ASTN_ExprList values = node -> stmt._ret.value ;
          Quad head = NULL, tail = NULL;
          while (values){
            Quad expr = ic_translate_expr(arena , hashtable, values -> expr , temp_counter ,label_counter);

            Quad return_quad = (Quad)arena_alloc(arena,sizeof(struct quad));
            return_quad -> inst = ICI_UJ_Return;
            return_quad -> add1 = expr -> add1;
            return_quad -> add2 = return_quad -> add3 = return_quad -> add4 = NULL;
            return_quad -> next = NULL;

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
          ASTN_ExprList args = node -> stmt._fun_call.args;
          Quad head = NULL, tail = NULL;

          while(args){
            Quad expr = ic_translate_expr(arena , hashtable, args -> expr , temp_counter ,label_counter);

            Quad pass_args = (Quad)arena_alloc(arena,sizeof(struct quad));
            pass_args -> inst = ICI_DT_Storeword;
            pass_args -> add1 = expr -> add1;
            pass_args -> add2 = pass_args -> add3 = pass_args -> add4 = NULL;
            pass_args -> next = NULL;

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
          call_func -> inst = ICI_UJ_JumpAndLink;
          call_func -> add1.type = AT_String;
          call_func->add1.value.label = strdup(node->stmt._fun_call.fun->value.ident);
          call_func->add2 = call_func->add3 = call_func->add4 = NULL;
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
          Quad head = NULL , tail = NULL;

          ASTN_Stmt stmt_block = node -> stmt.block;
          while (stmt_block){
            Quad stmt = ic_translate_stmt(arena ,hashtable , stmt_block, temp_counter, label_counter);

            if (!head) {
              head = stmt;
            } else {
              tail->next = stmt;
            }

            while (stmt && stmt->next) {
              stmt = stmt->next;
            }
            tail = stmt;

            stmt_block = stmt_block -> next;


          }

          return head;
        }

        case STMT_VAR_INCR_BEFORE:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
          incr->inst = ICI_Arit_Add;
          incr->add1.type = AT_UIntConst;
          incr->add1.value.val_uint = temp;
          incr->add2.type = AT_UIntConst;
          incr->add2.value.val_uint = 1; 
          incr->add3.type = AT_UIntConst;
          incr->add3.value.val_uint = temp; 
          incr->add4 = NULL;
          incr->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = incr;
          incr -> next = store;

          return load_var;
        }

        case STMT_VAR_DECR_BEFORE:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
          decr->inst = ICI_Arit_Sub;
          decr->add1.type = AT_UIntConst;
          decr->add1.value.val_uint = temp;
          decr->add2.type = AT_UIntConst;
          decr->add2.value.val_uint = 1; 
          decr->add3.type = AT_UIntConst;
          decr->add3.value.val_uint = temp; 
          decr->add4 = NULL;
          decr->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = decr;
          decr -> next = store;

          return load_var;
        }
        case STMT_VAR_INCR_AFTER:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
          incr->inst = ICI_Arit_Add;
          incr->add1.type = AT_UIntConst;
          incr->add1.value.val_uint = temp;
          incr->add2.type = AT_UIntConst;
          incr->add2.value.val_uint = 1; 
          incr->add3.type = AT_UIntConst;
          incr->add3.value.val_uint = temp; 
          incr->add4 = NULL;
          incr->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = incr;
          incr -> next = store;

          return load_var;
        }

        case STMT_VAR_DECR_AFTER:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
          decr->inst = ICI_Arit_Sub;
          decr->add1.type = AT_UIntConst;
          decr->add1.value.val_uint = temp;
          decr->add2.type = AT_UIntConst;
          decr->add2.value.val_uint = 1; 
          decr->add3.type = AT_UIntConst;
          decr->add3.value.val_uint = temp; 
          decr->add4 = NULL;
          decr->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = decr;
          decr -> next = store;

          return load_var;
        }

        case STMT_VAR_EQUALS_PLUS:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

          uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

          Quad add = (Quad)arena_alloc(arena,sizeof(struct quad));
          add->inst = ICI_Arit_Add;
          add->add1.type = AT_UIntConst;
          add->add1.value.val_uint = temp;
          add->add2.type = expr -> add1.type;
          add->add2.value = expr -> add1.value; 
          add->add3.type = AT_UIntConst;
          add->add3.value.val_uint = result; 
          add->add4 = NULL;
          add->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = expr;
          expr     -> next = add;
          add      -> store;

          return load_var;
        }

        case STMT_VAR_EQUALS_MINUS:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

          uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

          Quad sub = (Quad)arena_alloc(arena,sizeof(struct quad));
          sub->inst = ICI_Arit_Sub;
          sub->add1.type = AT_UIntConst;
          sub->add1.value.val_uint = temp;
          sub->add2.type = expr -> add1.type;
          sub->add2.value = expr -> add1.value; 
          sub->add3.type = AT_UIntConst;
          sub->add3.value.val_uint = result; 
          sub->add4 = NULL;
          sub->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = expr;
          expr     -> next = sub;
          sub      -> store;

          return load_var;
        }

        case STMT_VAR_EQUALS_MUL:{
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

          uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

          Quad mult = (Quad)arena_alloc(arena,sizeof(struct quad));
          mult->inst = ICI_Arit_Mul;
          mult->add1.type = AT_UIntConst;
          mult->add1.value.val_uint = temp;
          mult->add2.type = expr -> add1.type;
          mult->add2.value = expr -> add1.value; 
          mult->add3.type = AT_UIntConst;
          mult->add3.value.val_uint = result; 
          mult->add4 = NULL;
          mult->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = expr;
          expr     -> next = mult;
          mult      -> store;

          return load_var;
        }

        case STMT_VAR_EQUALS_DIV: {
          Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
          load_var -> inst = ICI_DT_LoadWord;
          load_var -> add1.type = AT_String;
          load_var -> add1.value.label = strdup(node->stmt._assign.var->value.ident);
          load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          load_var->add3.type = AT_UIntConst;
          load_var->add3.value.val_uint = temp;
          load_var->next = NULL;

          Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

          uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

          Quad div_quad = (Quad)arena_alloc(arena,sizeof(struct quad));
          div_quad ->inst = ICI_Arit_Div;
          div_quad ->add1.type = AT_UIntConst;
          div_quad ->add1.value.val_uint = temp;
          div_quad ->add2.type = expr -> add1.type;
          div_quad ->add2.value = expr -> add1.value; 
          div_quad ->add3.type = AT_UIntConst;
          div_quad ->add3.value.val_uint = result; 
          div_quad ->add4 = NULL;
          div_quad ->next = NULL;

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1.type = AT_UIntConst;
          store->add1.value.val_uint = temp;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(node ->stmt._assign.var->value.ident);
          store->add4 = NULL;
          store->next = NULL;

          load_var -> next = expr;
          expr     -> next = div_quad;
          div_quad      -> store;

          return load_var;
        }

        case STMT_VAR_DECL:{
          char* var_name = node->stmt._assign.var->value.ident;

          
          symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

          return NULL;
        }

        case STMT_VAR_DECL_ASSIGN:{
          char* var_name = node->stmt._assign.var->value.ident;

          Quad expr = ic_translate_expr(arena , hashtable , node -> stmt._assign.value, temp_counter ,label_counter);

          Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
          store->inst = ICI_DT_StoreWord;
          store->add1 = expr -> add1;
          store->add2 = NULL;
          store->add3.type = AT_String;
          store->add3.value.label = strdup(var_name);
          store->add4 = NULL;
          store->next = NULL;

          expr -> next = store;

          symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

          return expr;       
        }

        case STMT_VAR_DIRECT_ASSIGN:{
            Quad expr = ic_translate_expr(arena , hashtable, node -> stmt._assign.value, temp_counter, label_counter);

            Address var;
            var.type = AT_UIntConst;
            var.value.val_uint = node -> stmt._assign.var -> value.ident;

            Quad stmt = (Quad)arena_alloc(arena,sizeof(struct quad));
            stmt -> inst = ICI_DT_StoreWord;
            stmt -> add1 = expr -> add1;
            stmt -> add2 = NULL;
            stmt -> add3 = var;
            stmt -> add4 = NULL;
            stmt -> next = NULL;

            expr -> next = stmt;

            return expr;
        }
>>>>>>> 6f16e0986fe88e2f75140dcc8ac14878c5f8b606
    }

    case STMT_DO:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->add1.type = AT_String;
      loop_start->add1.value.label = arena_strdup(arena, label_start);
      loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
      loop_start->next = NULL;
      
      Quad block = ic_translate_stmt(arena, hashtable, node -> stmt._while.block, temp_counter , label_counter);

      Quad cond = ic_translate_expr(arena , hashtable , node -> stmt._while.cond, temp_counter,label_counter);

      Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->add1 = NULL;
      jump_back->add2 = NULL;
      jump_back->add3.type = AT_String;
      jump_back->add3.value.label = arena_strdup(arena,label_start);
      jump_back->add4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->add1.type = AT_String;
      loop_end->add1.value.label = arena_strdup(arena,label_end);
      loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
      loop_end->next = NULL;

      loop_start  ->  next  = block;
      block       ->  next  = cond;
      cond        ->  next  = jump_back;
      jump_back   ->  next  = loop_end;

      return loop_start;
    }
    case STMT_FOR:{
      char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
      char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

      Quad init = ic_translate_stmt(arena , hashtable , node -> stmt._for.init , temp_counter , label_counter);

      Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_start->inst = ICI_Label;
      loop_start->add1.type = AT_String;
      loop_start->add1.value.label = arena_strdup(arena,label_start);
      loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
      loop_start->next = NULL;

      Quad cond = ic_translate_expr(arena , hashtable , node -> stmt._for.cond , temp_counter, label_counter);

      Quad jump_end = (Quad) arena_alloc(arena ,sizeof(struct quad));
      jump_end-> inst = ICI_Cond_NEqual;
      jump_end-> add1 = cond -> add1;
      jump_end-> add2 = NULL;
      jump_end-> add3.type = AT_String;
      jump_end-> add3.value.label = arena_strdup(arena,label_end);
      jump_end-> add4 = NULL;
      jump_end-> next = NULL;

      Quad block = ic_translate_stmt(arena , hashtable , node -> stmt._for.block , temp_counter , label_counter);

      Quad incr = ic_translate_expr(arena , hashtable , node -> stmt._for.incr ,temp_counter , label_counter);

      Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_back->inst = ICI_UJ_Jump;
      jump_back->add1 = NULL;
      jump_back->add2 = NULL;
      jump_back->add3.type = AT_String;
      jump_back->add3.value.label = arena_strdup(arena,label_start);
      jump_back->add4 = NULL;
      jump_back->next = NULL;

      Quad loop_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      loop_end->inst = ICI_Label;
      loop_end->add1.type = AT_String;
      loop_end->add1.value.label = arena_strdup(arena,label_end);
      loop_end->add2 = loop_end->add3 = loop_end->add4 = NULL;
      loop_end->next = NULL;

      init        ->  next  = loop_start;
      loop_start  ->  next  = cond;
      cond        ->  next  = jump_end;
      jump_end    ->  next  = block;
      block       ->  next  = incr;
      incr        ->  next  = jump_back;
      jump_back   ->  next  = loop_end
      
      return init;
    }
    case STMT_IF:{
      Quad cond = ic_translate_expr(arena, hashtable, node -> stmt._if.cond , temp_counter, label_counter);

      char* label_true = ic_get_label(arena , ASTN_STMT , label_counter);
      char* label_false = ic_get_label(arena , ASTN_STMT , label_counter);

      Quad jump_false = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_false -> inst = ICI_COND_NEQUAL;
      jump_false -> add1 = cond -> add1;
      jump_false -> add2 = NULL;
      jump_false -> add3.type = AT_String;
      jump_false -> add3.value.label = arena_strdup(arena,label_true);
      jump_false -> add4 = NULL;
      jump_false -> next = NULL;

      Quad block = ic_translate_stmt(arena, hashtable, node -> stmt._if.block,temp_counter,label_counter);

      Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
      jump_end -> inst = ICI_UJ_JUMP;
      jump_end -> add1 = NULL;
      jump_end -> add2 = NULL;
      jump_end -> add3.type = AT_String;
      jump_end -> add3.value.label = arena_strdup(arena,label_false);
      jump_end -> add4 = NULL;
      jump_end -> next = NULL;

      Quad else_block = NULL;

      if(node -> stmt._if.next){
          else_block = ic_translate_stmt(arena , hashtable , node -> stmt._if.next , temp_counter,label_counter);
      }

      Quad end_label = (Quad)malloc(sizeof(struct quad));
      end_label->inst = ICI_Label;
      end_label->add1.type = AT_String;
      end_label->add1.value.label = arena_strdup(arena,label_end);
      end_label->add2 = end_label->add3 = end_label->add4 = NULL;
      end_label->next = NULL;

      cond        -> next = jump_false;
      jump_false  -> next = block;
      block       -> next = jump_end;
      jump_end    -> next = else_block;

      if(else_block){
        Quad last = else_block;
        while(last -> next ) last = last -> next;
        last -> next = end_label;
      }
      else{
        last -> next = end_label;
      }

      return cond;
    }

    case STMT_ELSEIF:{
      return ic_translate_stmt(arena , hashtable , node ,temp_counter ,label_counter);
    }

    case STMT_ELSE:{
      return ic_translate_stmt(arena ,hashtable, node -> stmt._if.block , temp_counter, label_counter);
    }

    case STMT_CASE:{
      Quad switch_cond = ic_translate_expr(arena , hashtable, node -> stmt._when.cond , temp_counter ,label_counter);

      char* label_end = ic_get_label(arena , ASTN_STMT , label_counter);

      Quad case_head = switch_cond, case_tail = switch_cond;

      ASTN_STMT cases = node -> stmt._when.cases;

      while(cases){
        if(cases -> type == STMT_WHEN){
          char* case_label = ic_get_label(arena , ASTN_STMT , label_counter);

          Quad cond = ic_translate_stmt(arena , hashtable , cases -> stmt._when.cond , temp_counter ,label_counter);

          Quad jump_case = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_case -> inst = ICI_Cond_Equal;
          jump_case -> add1 = switch_cond -> add1;
          jump_case -> add2 = cond -> add1;
          jump_case -> add3.type = AT_String;
          jump_case -> add3.value.label = arena_strdup(arena,case_label);
          jump_case -> add4 = NULL;
          jump_case -> next = NULL;

          Quad block = ic_translate_stmt(arena , hashtable , cases -> stmt._when.block , temp_counter ,label_counter);

          case_tail->next = jump_case;
          case_tail = jump_case;


          Quad case = (Quad)arena_alloc(arena,sizeof(struct quad));
          case -> inst = ICI_Label;
          case -> add1.type = AT_String;
          case -> add1.value.label = arena_strdup(arena,label_case);
          case -> add2 = case -> add3 = case -> add4 = NULL;
          case -> next = block;

          case_tail -> next = case ;
          case_tail = block;

          Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
          jump_end -> inst = ICI_UJ_Jump;
          jump_end -> add1 = NULL;
          jump_end->add2 = NULL;
          jump_end->add3.type = AT_String;
          jump_end->add3.value.label = arena_strdup(arena,label_end);
          jump_end->add4 = NULL;
          jump_end->next = NULL;

          case_tail -> next = jump_end;
          case_tail = jump_next;
        }

        cases = cases -> next;
      }

      Quad end_label = (Quad)arena_alloc(arena,sizeof(struct quad));
      end_label -> inst = ICI_Label;
      end_label->add1.type = AT_String;
      end_label->add1.value.label = arena_strdup(arena,label_end);
      end_label->add2 = end_label->add3 = end_label->add4 = NULL;
      end_label->next = NULL;


      case_tail -> next = end_label;

      return case_head;
    }
    case STMT_RETURN:{
      ASTN_ExprList values = node -> stmt._ret.value ;
      Quad head = NULL, tail = NULL;
      while (values){
        Quad expr = ic_translate_expr(arena , hashtable, values -> expr , temp_counter ,label_counter);

        Quad return_quad = (Quad)arena_alloc(arena,sizeof(struct quad));
        return_quad -> inst = ICI_UJ_Return;
        return_quad -> add1 = expr -> add1;
        return_quad -> add2 = return_quad -> add3 = return_quad -> add4 = NULL;
        return_quad -> next = NULL;

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
      ASTN_ExprList args = node -> stmt._fun_call.args;
      Quad head = NULL, tail = NULL;

      while(args){
        Quad expr = ic_translate_expr(arena , hashtable, args -> expr , temp_counter ,label_counter);

        Quad pass_args = (Quad)arena_alloc(arena,sizeof(struct quad));
        pass_args -> inst = ICI_DT_Storeword;
        pass_args -> add1 = expr -> add1;
        pass_args -> add2 = pass_args -> add3 = pass_args -> add4 = NULL;
        pass_args -> next = NULL;

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
      call_func -> inst = ICI_UJ_JumpAndLink;
      call_func -> add1.type = AT_String;
      call_func->add1.value.label = arena_strdup(arena,node->stmt._fun_call.fun->value.ident);
      call_func->add2 = call_func->add3 = call_func->add4 = NULL;
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
      Quad head = NULL , tail = NULL;

      ASTN_Stmt stmt_block = node -> stmt.block;
      while (stmt_block){
        Quad stmt = ic_translate_stmt(arena ,hashtable , stmt_block, temp_counter, label_counter);

        if (!head) {
          head = stmt;
        } else {
          tail->next = stmt;
        }

        while (stmt && stmt->next) {
          stmt = stmt->next;
        }
        tail = stmt;

        stmt_block = stmt_block -> next;


      }

      return head;
    }

    case STMT_VAR_INCR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_Temp;
      load_var->add3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->add1.type = AT_Temp;
      incr->add1.value.temp = temp;
      incr->add2.type = AT_UIntConst;
      incr->add2.value.val_uint = 1; 
      incr->add3.type = AT_Temp;
      incr->add3.value.temp = temp; 
      incr->add4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_Temp;
      store->add1.value.temp = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = incr;
      incr -> next = store;

      return load_var;
    }

    case STMT_VAR_DECR_BEFORE:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_Temp;
      load_var->add3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->add1.type = AT_Temp;
      decr->add1.value.temp = temp;
      decr->add2.type = AT_UIntConst;
      decr->add2.value.val_uint = 1; 
      decr->add3.type = AT_Temp;
      decr->add3.value.temp = temp; 
      decr->add4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_Temp;
      store->add1.value.temp = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = decr;
      decr -> next = store;

      return load_var;
    }

    case STMT_VAR_INCR_AFTER:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_Temp;
      load_var->add3.value.temp = temp;
      load_var->next = NULL;

      Quad incr = (Quad)arena_alloc(arena,sizeof(struct quad));
      incr->inst = ICI_Arit_Add;
      incr->add1.type = AT_Temp;
      incr->add1.value.temp = temp;
      incr->add2.type = AT_UIntConst;
      incr->add2.value.val_uint = 1; 
      incr->add3.type = At_Temp;
      incr->add3.value.temp = temp; 
      incr->add4 = NULL;
      incr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_Temp;
      store->add1.value.temp = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = incr;
      incr -> next = store;

      return load_var;
    }

    case STMT_VAR_DECR_AFTER:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;


      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_Temp;
      load_var->add3.value.temp = temp;
      load_var->next = NULL;

      Quad decr = (Quad)arena_alloc(arena,sizeof(struct quad));
      decr->inst = ICI_Arit_Sub;
      decr->add1.type = AT_Temp;
      decr->add1.value.temp = temp;
      decr->add2.type = AT_UIntConst;
      decr->add2.value.val_uint = 1; 
      decr->add3.type = AT_Temp;
      decr->add3.value.temp = temp; 
      decr->add4 = NULL;
      decr->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_UIntConst;
      store->add1.value.val_uint = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = decr;
      decr -> next = store;

      return load_var;
    }

    case STMT_VAR_EQUALS_PLUS:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_UIntConst;
      load_var->add3.value.val_uint = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad add = (Quad)arena_alloc(arena,sizeof(struct quad));
      add->inst = ICI_Arit_Add;
      add->add1.type = AT_UIntConst;
      add->add1.value.val_uint = temp;
      add->add2.type = expr -> add1.type;
      add->add2.value = expr -> add1.value; 
      add->add3.type = AT_UIntConst;
      add->add3.value.val_uint = result; 
      add->add4 = NULL;
      add->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_UIntConst;
      store->add1.value.val_uint = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = expr;
      expr     -> next = add;
      add      -> store;

      return load_var;
    }

    case STMT_VAR_EQUALS_MINUS:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_UIntConst;
      load_var->add3.value.val_uint = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad sub = (Quad)arena_alloc(arena,sizeof(struct quad));
      sub->inst = ICI_Arit_Sub;
      sub->add1.type = AT_UIntConst;
      sub->add1.value.val_uint = temp;
      sub->add2.type = expr -> add1.type;
      sub->add2.value = expr -> add1.value; 
      sub->add3.type = AT_UIntConst;
      sub->add3.value.val_uint = result; 
      sub->add4 = NULL;
      sub->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_UIntConst;
      store->add1.value.val_uint = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = expr;
      expr     -> next = sub;
      sub      -> store;

      return load_var;
    }

    case STMT_VAR_EQUALS_MUL:{
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_UIntConst;
      load_var->add3.value.val_uint = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad mult = (Quad)arena_alloc(arena,sizeof(struct quad));
      mult->inst = ICI_Arit_Mul;
      mult->add1.type = AT_UIntConst;
      mult->add1.value.val_uint = temp;
      mult->add2.type = expr -> add1.type;
      mult->add2.value = expr -> add1.value; 
      mult->add3.type = AT_UIntConst;
      mult->add3.value.val_uint = result; 
      mult->add4 = NULL;
      mult->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_UIntConst;
      store->add1.value.val_uint = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = expr;
      expr     -> next = mult;
      mult      -> store;

      return load_var;
    }

    case STMT_VAR_EQUALS_DIV: {
      Quad load_var = (Quad)arena_alloc(arena,sizeof(struct quad));
      load_var -> inst = ICI_DT_LoadWord;
      load_var -> add1.type = AT_String;
      load_var -> add1.value.label = arena_strdup(arena,node->stmt._assign.var->value.ident);
      load_var -> add2 = load_var -> add3 = load_var -> add4 = NULL;

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      load_var->add3.type = AT_UIntConst;
      load_var->add3.value.val_uint = temp;
      load_var->next = NULL;

      Quad expr = ic_translate_expr(arena , hashtable , node._assign.value , temp_counter ,label_counter);

      uint32_t result = ic_get_temp(hashtable, NULL, temp_counter);

      Quad div_quad = (Quad)arena_alloc(arena,sizeof(struct quad));
      div_quad ->inst = ICI_Arit_Div;
      div_quad ->add1.type = AT_UIntConst;
      div_quad ->add1.value.val_uint = temp;
      div_quad ->add2.type = expr -> add1.type;
      div_quad ->add2.value = expr -> add1.value; 
      div_quad ->add3.type = AT_UIntConst;
      div_quad ->add3.value.val_uint = result; 
      div_quad ->add4 = NULL;
      div_quad ->next = NULL;

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1.type = AT_UIntConst;
      store->add1.value.val_uint = temp;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,node ->stmt._assign.var->value.ident);
      store->add4 = NULL;
      store->next = NULL;

      load_var -> next = expr;
      expr     -> next = div_quad;
      div_quad      -> store;

      return load_var;
    }

    case STMT_VAR_DECL:{
      char* var_name = node->stmt._assign.var->value.ident;

      
      symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

      return NULL;
    }

    case STMT_VAR_DECL_ASSIGN:{
      char* var_name = node->stmt._assign.var->value.ident;

      Quad expr = ic_translate_expr(arena , hashtable , node -> stmt._assign.value, temp_counter ,label_counter);

      Quad store = (Quad)arena_alloc(arena,sizeof(struct quad));
      store->inst = ICI_DT_StoreWord;
      store->add1 = expr -> add1;
      store->add2 = NULL;
      store->add3.type = AT_String;
      store->add3.value.label = arena_strdup(arena,var_name);
      store->add4 = NULL;
      store->next = NULL;

      expr -> next = store;

      symbol_table_add(hashtable, var_name, UNINITIALIZED_VALUE);

      return expr;       
    }

    case STMT_VAR_DIRECT_ASSIGN:{
      Quad expr = ic_translate_expr(arena , hashtable, node -> stmt._assign.value, temp_counter, label_counter);

      Address var (Address)arena_alloc(arena,sizeof(struct address));;
      var.type = AT_Temp;
      var.value.temp = node -> stmt._assign.var -> value.ident;

      Quad stmt = (Quad)arena_alloc(arena,sizeof(struct quad));
      stmt -> inst = ICI_DT_StoreWord;
      stmt -> add1 = expr -> add1;
      stmt -> add2 = NULL;
      stmt -> add3 = var;
      stmt -> add4 = NULL;
      stmt -> next = NULL;

      expr -> next = stmt;

      return expr;
    }
  }
}

Quad ic_translate_expr (Arena arena, HashTable hashtable, ASTN_Expr node, uint32_t* temp_counter, uint32_t* label_counter) {
  if (node == NULL)
    return NULL;

  switch(node -> type){
    case EXPR_UN:{
          Quad expr = ic_translate_expr(arena,hashtable,node -> expr.unary.operand, temp_counter, label_counter);
          uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
          Address result = (Address)arena_alloc(arena,sizeof(struct address));;
          result -> type = AT_Temp;
          result -> value.temp = temp;

    ICI op;
    switch (node->expr.binary.op) {
      case OP_UN_ARIT_PLUS:
        op = ICI_DT_Move;
        break;
      case OP_UN_ARIT_MINUS:
        op = ICI_DT_Sub;
        break;
      case OP_UN_LOG_NOT:
        op = ICI_Logic_BitOrI;
        break;
    }

    return expr;
    }

    case EXPR_BIN: {
      Quad leftSide  = ic_translate_expr(arena, hashtable, node->expr.binary.left, temp_counter, label_counter),
          rightSide = ic_translate_expr(arena, hashtable, node->expr.binary.right, temp_counter, label_counter);

      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
      Address result = (Address)arena_alloc(arena,sizeof(struct address));;
      result->type = AT_Temp;
      result->value.temp = temp;

      ICI op;
      switch (node->expr.binary.op) {
        case OP_BIN_ARIT_PLUS:
          op = ICI_Arit_AddI; 
          break;
        case OP_BIN_ARIT_MINUS:
          op = ICI_Arit_SubI;
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

      Quad expr = (Quad)arena_alloc(arena,sizeof(struct quad));
      error_assert(error_mem, expr != NULL);
      expr->inst = op;
      expr->add1 = leftSide->add1;
      expr->add2 = rightSide->add2;
      expr->add3 = result;
      expr->add4 = NULL;

      return expr;
    }

    case EXPR_TOKEN: {
      uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);

      Address address = (Address)arena_alloc(arena,sizeof(struct address));
      address->type = AT_Temp;
      address->value.temp = temp;

      Quad expr = (Quad)arena_alloc(arena, sizeof(struct quad));
      error_assert(error_mem, expr != NULL);
      expr->inst = ICI_DT_LoadImmediate;
      expr->add1.type = AT_String;
      expr->add1.value.label = arena_arena_strdup(arena,arena,node->expr.token->value.ident);
      expr->add2 = NULL;
      expr->add3 = address;
      expr->add4 = NULL; 
      
      return expr;
    }

    case EXPR_FUN_CALL:{
      Quad head = NULL; tail = NULL;

      ASTN_ExprList args = node->expr.fun_call.args;
      while(args){

        Quad fun_arg = (Quad)arena_alloc(arena, sizeof(struct quad));
        fun_arg->inst = ICI_BT_StoreWord;
        fun_args->add1 = args -> add1;
        fun_args->add2 = fun_args->add3 = fun_args->add4 = NULL;
        fun_args->next = NULL;

        if(!head){
          head = fun_args;
        }
        else{
          tail = fun_args;
        }

        tail = fun_args;

        args = args->next;
      }

      Quad call_func = (Quad)arena_alloc(arena, sizeof(struct quad));
      call_func->inst = ICI_UJ_JumpAndLink;
      call_func->add1.type = AT_String;
      call_func->add1.value.label = arena_strdup(arena, node -> expr.fun_call.fun -> value.ident);
      call_func->add2 = call_func->add3 = call_func->add4 = NULL;
      call_func->next = NULL;

      if(tail){
        tail = call_func;
      }

      uint32_t temp = ic_get_temp(hashtable, NULL , temp_counter);
      Address return_add;
      return_add.type = AT_UIntConst;
      return_add.value.val_uint = temp;

      Quad func_return = (Quad)arena_alloc(arena, sizeof(struct quad));
      func_return->inst = ICI_DT_LoadWord;
      func_return->add1 = NULL;
      func_return->add2 = NULL;
      func_return->add3 = return_add;
      func_return->add4 = NULL;
      func_return->next = NULL;

      call_func->next = func_return;

      return head ? head : call_func;
    }
  }
}

uint32_t ic_get_temp(HashTable hashtable, ASTN_Token token, uint32_t* temp_counter) {
  return (*temp_counter)++;
}

char* ic_get_label(Arena arena, ASTN_Type type, uint32_t* label_counter) {
  char* label = arena_alloc(arena, 20);  
  sprintf(label, "L%d", (*label_counter)++); 
  return label;
}
