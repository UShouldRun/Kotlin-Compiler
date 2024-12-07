#include "hashtable_private.h"

#include "ast.h"
#include "ast_private.h"

Quad ic_translate_func (Arena arena, HashTable hashtable, ASTN_Obj obj){

}

Quad ic_translate_stmt (Arena arena, HashTable hashtable, ASTN_Stmt stmt, uint32_t*  temp_counter, uint32_t* label_counter){
    if(!stmt) return NULL;

    switch (stmt -> type){
        case STMT_WHILE:{
            char* label_start = ic_get_label(arena, ASTN_STMT, label_counter);
            char* label_end = ic_get_label(arena, ASTN_STMT, label_counter);

            Quad loop_start = (Quad)arena_alloc(arena,sizeof(struct quad));
            loop_start->inst = ICI_Label;
            loop_start->add1.type = AT_String;
            loop_start->add1.value.label = strdup(label_start);
            loop_start->add2 = loop_start->add3 = loop_start->add4 = NULL;
            loop_start->next = NULL;

            Quad while_cond = ic_translate_expr(arena, hashtable, stmt->stmt._while.cond , temp_counter,label_counter);
            
            
            Quad jump_exit = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_exit->inst = ICI_Cond_NEqual;
            jump_exit->add1 = while_cond->add1;
            jump_exit->add2 = NULL;
            jump_exit->add3.type = AT_String;
            jump_exit->add3.value.label = strdup(label_end);
            jump_exit->add4 = NULL;
            jump_exit->next = NULL;

            Quad block = ic_translate_stmt(arena , hashtable, stmt -> stmt._while.block,temp_counter,label_counter);

            Quad jump_back = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_back->inst = ICI_UJ_Jump;
            jump_back->add1 = NULL;
            jump_back->add2 = NULL;
            jump_back->add3.type = AT_String;
            jump_back->add3.value.label = strdup(label_start);
            jump_back->add4 = NULL;
            jump_back->next = NULL;

            // Quádrupla para o rótulo do final do laço
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
        case STMT_IF:{
            Quad cond = ic_translate_expr(arena, hashtable, stmt -> stmt._if.cond , temp_counter, label_counter);

            char* label_true = ic_get_label(arena , ASTN_STMT , label_counter);
            char* label_false = ic_get_label(arena , ASTN_STMT , label_counter);

            Quad jump_false = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_false -> inst = ICI_COND_NEQUAL;
            jump_false -> add1 = cond -> add1;
            jump_false -> add2 = NULL;
            jump_false -> add3.type = AT_String;
            jump_false -> add3.value.label = strdup(label_false);
            jump_false -> add4 = NULL;
            jump_false -> next = NULL;

            Quad block = ic_translate_stmt(arena, hashtable, stmt -> stmt._if.block,temp_counter,label_counter);

            Quad jump_end = (Quad)arena_alloc(arena,sizeof(struct quad));
            jump_end -> inst = ICI_UJ_JUMP;
            jump_end -> add1 = NULL;
            jump_end -> add2 = NULL;
            jump_end -> add3.type = AT_String;
            jump_end -> add3.value.label = strdup(label_false);
            jump_end -> add4 = NULL;
            jump_end -> next = NULL;

            Quad else_block = NULL;

            if(stmt -> stmt._if.next){
                else_block = ic_translate_stmt(arena , table , stmt -> stmt._if.next , temp_counter,label_counter);
            }

            cond        -> next = jump_false;
            jump_false  -> next = block;
            block       -> next = jump_end;
            jump_end    -> next = else_block;


        }
    }
}

Quad ic_translate_expr (Arena arena, HashTable hashtable, ASTN_Expr expr, uint32_t* temp_counter, uint32_t* label_counter){
    if (!expr) return NULL;

    switch(expr -> type){
        case EXPR_UN:{
            Quad expr = ic_translate_expr(arena,hashtable,expr -> expr.unary.operand, temp_counter, label_counter);
            uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
            Address result;
            result -> type = AT_UIntConst;
            result -> value.val_uint = temp;

            ICI op;
            switch (expr -> expr.binary.op) {
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
            Quad leftSide = ic_translate_expr(arena,hashtable, expr -> expr.binary.left, temp_counter, label_counter);
            Quad rightSide = ic_translate_expr(arena,hashtable, expr -> expr.binary.right, temp_counter, label_counter);

            uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
            Address result;
            result -> type = AT_UIntConst;
            result -> value.val_uint = temp;

            ICI op;
            switch (expr->expr.binary.op) {
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
                 expr -> inst = op;
                 expr -> add1 = leftSide -> add1;
                 expr -> add2 = rightSide -> add2;
                 expr -> add3 = result;
                 expr -> add4 = NULL;

        }
        case EXPR_TOKEN: {
            uint32_t temp = ic_get_temp(hashtable, NULL, temp_counter);
            Address address;
            address -> type = AT_UIntConst;
            address -> value.val_uint = temp;
            Quad expr = (Quad)arena_alloc(arena,sizeof(struct quad));
                expr -> inst = ICI_DT_LoadImmediate;
                expr -> add1.type = AT_String;
                expr -> add1.value.label = strdup(expr -> expr.token -> value.ident);
                expr -> add2 = NULL;
                expr -> add3 = address;
                expr -> add4 = NULL; 
            
            return expr;
        }
    }
}




uint32_t ic_get_temp   (HashTable hashtable, ASTN_Token token, uint32_t* temp_counter){
    return (*temp_counter)++;
}

char*    ic_get_label  (Arena arena, ASTN_Type type, uint32_t* label_counter){
    char* label = arena_alloc(arena, 20);  
    sprintf(label, "L%d", (*label_counter)++); 
    return label;
}