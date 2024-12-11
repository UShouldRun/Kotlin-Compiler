#include "gen_assembly.h"
#include "symboltable.h"
#include "intercode.h"




void Print_MIPS (FILE *output , Quad head){

    for(Quad q = head ; q != NULL ; q = q -> next){
        switch (q->inst) {

            // Instruções de Aritmética
            case ICI_Arit_Add:
                emit_instruction("add", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_AddI:
                emit_instruction("addi", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_AddU:
                emit_instruction("addu", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_AddIU:
                emit_instruction("addiu", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_Sub:
                emit_instruction("sub", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_SubI:
                emit_instruction("subi", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_Mul:
                emit_instruction("mul", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_MulI:
                emit_instruction("muli", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Arit_Div:
                emit_instruction("div", q->addr1, q->addr2, q->addr3, output);
                break;

            case ICI_Cond_Equal:
                emit_instruction("beq", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Cond_NEqual:
                emit_instruction("bne", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Cond_GThan:
                emit_instruction("bgt", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Cond_GThanEqual:
                emit_instruction("bge", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Cond_LThan:
                emit_instruction("blt", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Cond_LThanEqual:
                emit_instruction("ble", q->addr1, q->addr2, q->addr3, output);
                break;

            case ICI_DT_LoadWord:
                emit_instruction("lw", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_DT_StoreWord:
                emit_instruction("sw", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_DT_LoadAdress:
                emit_instruction("la", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_DT_LoadImmediate:
                emit_instruction("li", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_DT_Move:
                emit_instruction("move", q->addr1, q->addr2, q->addr3, output);
                break;

            case ICI_Label:
                emit_label(q->addr1->value.label, output);
                break;

            case ICI_UJ_Jump:
                emit_instruction("j", q->addr1, q->addr2, q->addr3, output);
                break;

            case ICI_UJ_JumpRegister:
                emit_instruction("jr", q->addr1, q->addr2, q->addr3, output);
                break;

            case ICI_UJ_JumpAndLink:
                emit_instruction("jal", q->addr1, q->addr2, q->addr3, output);
                break;

            // Instruções Lógicas
            case ICI_Logic_BitAnd:
                emit_instruction("and", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_BitAndI:
                emit_instruction("andi", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_BitOr:
                emit_instruction("or", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_BitOrI:
                emit_instruction("ori", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_BitNor:
                emit_instruction("nor", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_BitNorI:
                emit_instruction("nori", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_ShiftLeft:
                emit_instruction("sll", q->addr1, q->addr2, q->addr3, output);
                break;
            case ICI_Logic_ShiftRight:
                emit_instruction("srl", q->addr1, q->addr2, q->addr3, output);
                break;
        }
    }
}


void translate_op(Address addr , char* reg , FILE* output){
    switch(addr -> type){
        case AT_Empty: {
            break;
        }
        case AT_IntConst: case AT_UIntConst:{
            fprintf(output, "    li %s, %llu\n", reg, addr->value.val_uint);
            break;
        }
        case AT_Char: {
            fprintf(output, "    li %s, %llu\n", reg, addr->value.val_char);
            break;
        }
        case AT_Temp: case AT_Save: {
            fprintf(output, "    li %s, %llu\n", reg, addr->value.temp);
            break;
        }
        case AT_String: {
            fprintf(output, "    li %s, %llu\n", reg, addr->value.label);
            break;
        } 
        case AT_Label:{
            break;
        }
    }
}

void emit_label(const char* label , FILE* output){
    fprintf(output , "%s:\n" ,label);
}

void emit_instruction(const char* instruction, Address arg1, Address arg2, Address arg3, FILE* output){
    char reg1[10] = "$t0", reg2[10] = "$t1", reg3[10] = "$t2";
    
    if(arg1 != AT_None) translate_op(arg1 , reg1 , output);
    if(arg1 != AT_None) translate_op(arg1 , reg2 , output);
    if(arg1 != AT_None) translate_op(arg1 , reg3 , output);

    fprintf("   %s %s %s %s\n" , instruction ,arg1 ,arg2 ,arg3 ,output);
}