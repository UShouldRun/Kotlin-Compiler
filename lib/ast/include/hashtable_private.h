#ifndef HASH_TABLE_PRIVATE_H
#define HASH_TABLE_PRIVATE_H

#include "ast_private.h"
#include "hashtable.h"

// ==================================================# PRIVATE #===========================================================

typedef struct hashtable_value {
  ASTN_Type type;
  void* node;
} *HT_Value;

struct stack_table {
  bool frame;
  ASTN_Token token;
  Stack next;
};

void hashtable_free_ktype(void* ktype);

#endif // HASH_TABLE_PRIVATE_H
