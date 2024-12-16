#ifndef INTERCODE_PRIVATE_H
#define INTERCODE_PRIVATE_H

#include "intercode.h"
#include "symboltable.h"

// ==================================================# PRIVATE #=================================================================

#define SIZEOFLABEL 20

#define LABEL_LOOP   "loop"
#define LABEL_COND   "cond"
#define LABEL_RETURN "return"
#define LABEL_JUMP   "jump"

struct address {
  AddressType type;
  union {
    int64_t  val_int;
    uint64_t val_uint;
    char     val_char;
    int64_t  offset;
    uint32_t temp;
    char*    label;
  } value;
};

struct quad {
  bool fun_label;
  ICI inst;
  Address addr1, addr2, addr3;
  Quad next;
};

// Print Translation
void ic_print_addr(Address addr);

// Translate Program
Quad     ic_translate_func    (Arena, SymbolTable*, SymbolStack*, ASTN_Obj, uint32_t*, uint32_t*);
Quad     ic_translate_stmt    (Arena, SymbolTable*, SymbolStack*, ASTN_Stmt, uint32_t*, uint32_t*, bool);
Quad     ic_translate_expr    (Arena, SymbolTable*, ASTN_Expr, Address, uint32_t*);

Quad     ic_exit_main         (Arena);

Quad     ic_translate_println (Arena, Address, ASTN_KTypeDefault);
Quad     ic_translate_readln  (Arena, Address, ASTN_KTypeDefault);

void     ic_set_token         (SymbolTable*, ASTN_Token, Address);
void     ic_pop_temp          (uint32_t*, uint32_t);

uint32_t ic_get_temp          (uint32_t*);
char*    ic_get_label         (Arena, ASTN_StmtType, uint32_t*);
Quad     ic_get_tail          (Quad);

Quad     ic_stack_pop         (Arena, SymbolStack*, SymbolTable);

bool     ic_inst_syscall      (ICI);

Address ic_create_address     (Arena, AddressType, void*);
Quad    ic_create_quad        (Arena, ICI, Address, Address, Address, Quad);

const char* match_instruction_to_string (ICI);

#endif // !INTERCODE_PRIVATE_H
