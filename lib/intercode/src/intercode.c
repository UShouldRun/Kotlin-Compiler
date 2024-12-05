#include "hashtable_private.h"

#include "ast.h"
#include "ast_private.h"

Quad ic_translate_func (Arena arena, HashTable hashtable, ASTN_Obj obj){

}

Quad ic_translate_stmt (Arena arena, HashTable hashtable, ASTN_Stmt stmt, uint32_t*  temp_counter, uint32_t* label_counter){

}

Quad ic_translate_expr (Arena arena, HashTable hashtable, ASTN_Expr expr, uint32_t* temp_counter, uint32_t* label_counter){
    if (!expr) return NULL;

    switch(expr -> type){
        case EXPR_UN:{
            Quad expr = ic_translate_expr(arena,hashtable,expr -> expr.un.operand, temp_counter, label_counter);
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