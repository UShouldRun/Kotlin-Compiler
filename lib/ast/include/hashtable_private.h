#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "hashtable.h"

// ==================================================# PRIVATE #===========================================================

typedef struct hashtable_value {
  ASTN_Type type;
  void* node;
} *HT_Value;

void hashtable_free_ktype(void* ktype);

#endif // HASH_TABLE_H
