#ifndef INTERCODE_PRIVATE_H
#define INTERCODE_PRIVATE_H

#include "intercode.h"


// ==================================================# PRIVATE #=================================================================

#define SIZEOFLABEL  20

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
    uint32_t temp;
    char*    label;
  } value;
};

struct quad {
  ICI inst;
  Address addr1, addr2, addr3, addr4;
  Quad next;
};

// Translate Program
Quad     ic_translate_func    (Arena, SymbolTable, ASTN_Obj);
Quad     ic_translate_stmt    (Arena, SymbolTable, SymbolStack, ASTN_Stmt, uint32_t*, uint32_t*);
Quad     ic_translate_expr    (Arena, SymbolTable, ASTN_Expr, uint32_t*);

uint32_t ic_get_temp          (SymbolTable, ASTN_Token, uint32_t*);
char*    ic_get_label         (Arena, ASTN_Type, uint32_t*);

#endif // !INTERCODE_PRIVATE_H
