#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "hashmap.h"
#include "ast_private.h"
#include "intercode.h"

// ==================================================# PUBLIC #=================================================================

typedef HashMap SymbolTable;
typedef Stack   SymbolStack;

// SymbolTable
SymbolTable symboltable_create            (uint64_t s_buckets, float load_threshold_factor);

uint64_t    symboltable_size              (SymbolTable table);

Address     symboltable_lookup_ident_addr (SymbolTable table, ASTN_Token token);
Address     symboltable_remove_ident      (SymbolTable table, ASTN_Token token);
bool        symboltable_insert_ident      (SymbolTable* table, ASTN_Token token, Address addr);
bool        symboltable_exists_ident      (SymbolTable table, ASTN_Token token);
bool        symboltable_free              (SymbolTable table);

SymbolStack symbolstack_create            ();
uint64_t    symbolstack_size              (SymbolStack stack);
ASTN_Token  symbolstack_pop               (SymbolStack* stack);
int64_t     symbolstack_pop_frame         (SymbolStack* stack, SymbolTable table);
bool        symbolstack_push              (SymbolStack* stack, ASTN_Token token);
bool        symbolstack_push_frame        (SymbolStack* stack);
bool        symbolstack_is_frame          (SymbolStack stack);
bool        symbolstack_free              (SymbolStack* stack);

#endif // !SYMBOL_TABLE_H
