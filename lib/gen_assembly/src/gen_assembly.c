#include "gen_assembly.h"
#include "symboltable.h"
#include "intercode.h"

void print_mips(FILE *output, Quad head) {
  for (Quad q = head ; q != NULL ; q = q->next) {
    switch (q->inst) {
      case ICI_None: {
        error_panic(error_genassembly, "Invalid Inst");
        break;
      }

      case ICI_StackPtrIncr: case ICI_StackPtrDecr: {
        fprintf(output, "    addi $sp %ld\n", q->addr1->value.offset);
        break;
      }

      case ICI_Arit_Add: {
        emit_instruction("add", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_AddI: {
        emit_instruction("addi", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_AddU: {
        emit_instruction("addu", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_AddIU: {
        emit_instruction("addiu", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_Sub: {
        emit_instruction("sub", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_SubI: {
        emit_instruction("subi", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_Mul: {
        emit_instruction("mul", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_MulI: {
        emit_instruction("muli", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Arit_Div: {
        emit_instruction("div", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_Equal: {
        emit_instruction("beq", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_NEqual: {
        emit_instruction("bne", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_GThan: {
        emit_instruction("bgt", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_GThanEqual: {
        emit_instruction("bge", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_LThan: {
        emit_instruction("blt", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Cond_LThanEqual: {
        emit_instruction("ble", q->addr1, q->addr2, q->addr3, output);
        break;
      }

      // Branch Instructions
      case ICI_Branch_Equal: {
        emit_instruction("beq", q->addr1, q->addr2, q->addr3, output);  // Branch if equal
        break;
      }
      case ICI_Branch_NEqual: {
        emit_instruction("bne", q->addr1, q->addr2, q->addr3, output);  // Branch if not equal
        break;
      }

      case ICI_DT_LoadWord: {
        emit_instruction("lw", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_DT_StoreWord: {
        emit_instruction("sw", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_DT_LoadAdress: {
        emit_instruction("la", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_DT_LoadImmediate: {
        emit_instruction("li", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_DT_Move: {
        emit_instruction("mv", q->addr1, q->addr2, q->addr3, output);
        break;
      }

      case ICI_Label: {
        emit_label(q->addr1->value.label, output);
        break;
      }

      case ICI_UJ_Jump: {
        emit_instruction("j", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_UJ_JumpRegister: {
        emit_instruction("jr", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_UJ_JumpAndLink: {
        emit_instruction("jal", q->addr1, q->addr2, q->addr3, output);
        break;
      }

      // Logical Instructions
      case ICI_Logic_BitAnd: {
        emit_instruction("and", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_BitAndI: {
        emit_instruction("andi", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_BitOr: {
        emit_instruction("or", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_BitOrI: {
        emit_instruction("ori", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_BitNor: {
        emit_instruction("nor", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_BitNorI: {
        emit_instruction("nori", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_ShiftLeft: {
        emit_instruction("sll", q->addr1, q->addr2, q->addr3, output);
        break;
      }
      case ICI_Logic_ShiftRight: {
        emit_instruction("srl", q->addr1, q->addr2, q->addr3, output);
        break;
      }

      // Syscalls
      case ICI_Syscall_1: {
        emit_syscall(1, output);
        break;
      }
      case ICI_Syscall_2: {
        emit_syscall(2, output);
        break;
      }
      case ICI_Syscall_3: {
        emit_syscall(3, output);
        break;
      }
      case ICI_Syscall_4: {
        emit_syscall(4, output);
        break;
      }
      case ICI_Syscall_5: {
        emit_syscall(5, output);
        break;
      }
      case ICI_Syscall_6: {
        emit_syscall(6, output);
        break;
      }
      case ICI_Syscall_7: {
        emit_syscall(7, output);
        break;
      }
      case ICI_Syscall_8: {
        emit_syscall(8, output);
        break;
      }
      case ICI_Syscall_9: {
        emit_syscall(9, output);
        break;
      }
      case ICI_Syscall_10: {
        emit_syscall(10, output);
        break;
      }
      case ICI_Syscall_11: {
        emit_syscall(11, output);
        break;
      }
      case ICI_Syscall_12: {
        emit_syscall(12, output);
        break;
      }
      case ICI_Syscall_13: {
        emit_syscall(13, output);
        break;
      }
      case ICI_Syscall_14: {
        emit_syscall(14, output);
        break;
      }
      case ICI_Syscall_15: {
        emit_syscall(15, output);
        break;
      }
      case ICI_Syscall_16: {
        emit_syscall(16, output);
        break;
      }
      case ICI_Syscall_17: {
        emit_syscall(17, output);
        break;
      }
      case ICI_Syscall_18: {
        emit_syscall(18, output);
        break;
      }
      case ICI_Syscall_19: {
        emit_syscall(19, output);
        break;
      }
      case ICI_Syscall_20: {
        emit_syscall(20, output);
        break;
      }
      case ICI_Syscall_21: {
        emit_syscall(21, output);
        break;
      }
      case ICI_Syscall_22: {
        emit_syscall(22, output);
        break;
      }
      case ICI_Syscall_23: {
        emit_syscall(23, output);
        break;
      }
    }
  }
}

void emit_syscall(int syscall_num, FILE *output) {
  fprintf(output, "    li $v0, %d\n", syscall_num);
  fprintf(output, "    syscall\n");
}

void translate_op(Address arg, char* reg, FILE* output) {
  if (arg == NULL)
    return;
  switch (arg->type) { 
    case AT_IntConst: {
      sprintf(reg, "%ld", arg->value.val_int);
      break;
    }
    case AT_UIntConst: {
      sprintf(reg, "%lu", arg->value.val_uint);
      break;
    }
    case AT_Char: {
      sprintf(reg, "%d", arg->value.val_char);
      break;
    }
    case AT_String: {
      fprintf(output, "%s", arg->value.label);
      break;
    }
    case AT_Stack: {
      int64_t offset = arg->value.offset;
      if (offset == 0) {
        sprintf(reg, "$sp");
      } else {
        sprintf(reg, "%" PRId64 "($sp)", offset);
      }
      break;
    }
    case AT_Frame: {
      int64_t offset = arg->value.offset;
      if (offset == 0) {
        sprintf(reg, "$fp");
      } else {
        sprintf(reg, "%" PRId64 "($fp)", offset);
      }
      break;
    }
    case AT_Ret: {
      sprintf(reg, "$ra");
      break;
    }
    case AT_v0: {
      sprintf(reg, "$v0");
      break;
    }
    case AT_a0: {
      sprintf(reg, "$a0");
      break;
    }
    case AT_Temp: {
      sprintf(reg, "$t%d", arg->value.temp);
      break;
    }
    case AT_Label: {
      sprintf(reg, "%s", arg->value.label);
      break;
    }
    default: {
      error_assert(error_genassembly, ERROR_INVALID_ADDRESS);
      break;
    }
  }
}

void emit_label(const char* label , FILE* output) {
  fprintf(output , "%s:\n" ,label);
}

void emit_instruction(const char* inst, Address arg1, Address arg2, Address arg3, FILE* output) {
  char reg1[64] = "",
       reg2[64] = "",
       reg3[64] = "";
  
  translate_op(arg1, reg1, output);
  translate_op(arg2, reg2, output);
  translate_op(arg3, reg3, output);
  fprintf(output, "    %s %s %s %s\n", inst, reg1, reg2, reg3);
}

