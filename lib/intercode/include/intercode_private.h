#ifndef INTERCODE_PRIVATE_H
#define INTERCODE_PRIVATE_H

#include "intercode.h"
#include "symboltable.h"

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
  Address addr1, addr2, addr3;
  Quad next;
};

// Translate Program
Quad     ic_translate_func    (Arena, SymbolTable*, SymbolStack*, ASTN_Obj, uint32_t*, uint32_t*);
Quad     ic_translate_stmt    (Arena, SymbolTable*, SymbolStack*, ASTN_Stmt, uint32_t*, uint32_t*);
Quad     ic_translate_expr    (Arena, SymbolTable*, ASTN_Expr, uint32_t*);

uint32_t ic_get_temp          (SymbolTable*, ASTN_Token, uint32_t*);
char*    ic_get_label         (Arena, ASTN_StmtType, uint32_t*);
Quad     ic_get_tail          (Quad);

Address ic_create_address     (Arena, AddressType, void*);
Quad    ic_create_quad        (Arena, ICI, Address, Address, Address, Quad);

#endif // !INTERCODE_PRIVATE_H
