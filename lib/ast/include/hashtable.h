#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "hashmap.h"
#include "ast.h"

// ==================================================# PUBLIC #=================================================================

typedef HashMap HashTable;
typedef struct stack_hashtable *Stack;

HashTable  hashtable_create           (uint64_t s_buckets, float load_threshold_factor);

uint64_t   hashtable_size             (HashTable table);

ASTN_KType hashtable_lookup_var_ktype (HashTable table, ASTN_Token token);
ASTN_KType hashtable_remove_var_ktype (HashTable table, ASTN_Token token);

ASTN_Obj   hashtable_lookup_obj       (HashTable table, ASTN_Token token);
ASTN_Obj   hashtable_remove_obj       (HashTable table, ASTN_Token token);

ASTN_Token hashtable_lookup_global    (HashTable table, ASTN_Token token);
ASTN_Token hashtable_remove_global    (HashTable table, ASTN_Token token);

bool       hashtable_insert_var_ktype (HashTable* table, ASTN_Token token, ASTN_KType ktype);
bool       hashtable_insert_obj       (HashTable* table, ASTN_Token token, ASTN_Obj obj);
bool       hashtable_insert_global    (HashTable* table, ASTN_Token token, ASTN_Token global);

bool       hashtable_exists_token     (HashTable table, ASTN_Token token);
bool       hashtable_free             (HashTable table);

Stack      stack_create               ();
uint64_t   stack_size                 (Stack stack);
ASTN_Token stack_pop                  (Stack* stack);
bool       stack_pop_frame            (Stack* stack, HashTable table);
bool       stack_push                 (Stack* stack, ASTN_Token token);
bool       stack_push_frame           (Stack* stack);
bool       stack_is_frame             (Stack stack);
bool       stack_free                 (Stack* stack);

#endif // !HASH_TABLE_H
