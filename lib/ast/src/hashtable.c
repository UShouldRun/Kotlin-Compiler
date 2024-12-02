#include "hashtable_private.h"

// ==================================================# PUBLIC #=================================================================

HashTable hashtable_create(uint64_t s_buckets, float load_threshold_factor) {
  return (HashTable)hashmap_create(s_buckets, load_threshold_factor);
}

uint64_t hashtable_size(HashTable table) {
  return hashmap_size(table);
}

ASTN_KType hashtable_lookup_var_ktype(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident);
  error_assert(error_type_checker, value->type != ASTN_TOKEN);
  ASTN_KType node = (ASTN_KType)value->node;
  return node;
}

ASTN_KType hashtable_remove_var_ktype(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident); 
  error_assert(error_type_checker, value->type != ASTN_TOKEN);
  ASTN_KType node = (ASTN_KType)value->node;
  error_assert(error_type_checker, hashmap_remove(table, value, NULL));
  return node;
}

ASTN_Obj hashtable_lookup_obj(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident); 
  error_assert(error_type_checker, value->type != ASTN_OBJ);
  ASTN_Obj node = (ASTN_Obj)value->node;
  return node;
}

ASTN_Obj hashtable_remove_obj(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident); 
  error_assert(error_type_checker, value->type != ASTN_OBJ);
  ASTN_Obj node = (ASTN_Obj)value->node;
  error_assert(error_type_checker, hashmap_remove(table, value, NULL));
  return node;
}

ASTN_Token hashtable_lookup_global(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident); 
  error_assert(error_type_checker, value->type != ASTN_VAR);
  ASTN_Token node = (ASTN_Token)value->node;
  return node;
}

ASTN_Token hashtable_remove_global(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, token->value.ident); 
  error_assert(error_type_checker, value->type != ASTN_VAR);
  ASTN_Token node = (ASTN_Token)value->node;
  error_assert(error_type_checker, hashmap_remove(table, value, NULL));
  return node;
}

bool hashtable_insert_var_ktype(HashTable* table, ASTN_Token token, ASTN_KType ktype) {
  if (!table) return false;
  if (!token) return false;
  if (!ktype) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_type_checker, value != NULL);
  value->type = ASTN_TOKEN;
  value->node = (void*)ktype;
  return hashmap_insert(table, token->value.ident, (void*)value, NULL);
}

bool hashtable_insert_obj(HashTable* table, ASTN_Token token, ASTN_Obj obj) {
  if (!table) return false;
  if (!token) return false;
  if (!ktype) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_type_checker, value != NULL);
  value->type = ASTN_OBJ;
  value->node = (void*)obj;
  return hashmap_insert(table, token->value.ident, (void*)value, NULL);
}

bool hashtable_insert_global(HashTable* table, ASTN_Token token, ASTN_Token global) {
  if (!table) return false;
  if (!token) return false;
  if (!ktype) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_type_checker, value != NULL);
  value->type = ASTN_VAR;
  value->node = (void*)global;
  return hashmap_insert(table, token->value.ident, (void*)value, NULL);
}

bool hashtable_exists_token(HashTable table, ASTN_Token token) {
  return hashmap_exists(table, token->value.ident);
}

bool hashtable_free(HashTable table) {
  if (!table) return false;
  return hashmap_free(table);
}

// ==================================================# PRIVATE #==========================================================

void hashtable_free_ktype(void* ktype) { return; }
