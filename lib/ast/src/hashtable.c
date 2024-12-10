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
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident));
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_KTYPE);
  ASTN_KType node = (ASTN_KType)value->node;
  return node;
}

ASTN_KType hashtable_remove_var_ktype(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident)); 
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_KTYPE);
  ASTN_KType node = (ASTN_KType)value->node;
  error_assert(error_type_checker, hashmap_remove(table, (char*)(token->value.ident), NULL));
  return node;
}

ASTN_Obj hashtable_lookup_obj(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident)); 
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_FUN || value->type == ASTN_ENUM);
  ASTN_Obj node = (ASTN_Obj)value->node;
  return node;
}

ASTN_Obj hashtable_remove_obj(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident)); 
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_FUN || value->type == ASTN_ENUM);
  ASTN_Obj node = (ASTN_Obj)value->node;
  error_assert(error_type_checker, hashmap_remove(table, (char*)(token->value.ident), NULL));
  return node;
}

ASTN_Token hashtable_lookup_global(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident)); 
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_TOKEN);
  ASTN_Token node = (ASTN_Token)value->node;
  return node;
}

ASTN_Token hashtable_remove_global(HashTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  HT_Value value = (HT_Value)hashmap_get(table, (char*)(token->value.ident)); 
  if (value == NULL) return NULL;
  error_assert(error_type_checker, value->type == ASTN_TOKEN);
  ASTN_Token node = (ASTN_Token)value->node;
  error_assert(error_type_checker, hashmap_remove(table, (char*)(token->value.ident), NULL));
  return node;
}

bool hashtable_insert_var_ktype(HashTable* table, ASTN_Token token, ASTN_KType ktype) {
  if (!table) return false;
  if (!token) return false;
  if (!ktype) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_mem, value != NULL);
  value->type = ASTN_KTYPE;
  value->node = (void*)ktype;
  return hashmap_insert(table, (char*)(token->value.ident), (void*)value, NULL);
}

bool hashtable_insert_obj(HashTable* table, ASTN_Token token, ASTN_Obj obj) {
  if (!table) return false;
  if (!token) return false;
  if (!obj) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_mem, value != NULL);
  value->type = obj->type;
  value->node = (void*)obj;
  return hashmap_insert(table, (char*)(token->value.ident), (void*)value, NULL);
}

bool hashtable_insert_global(HashTable* table, ASTN_Token token, ASTN_Token global) {
  if (!table) return false;
  if (!token) return false;
  if (!global) return false;
  HT_Value value = (HT_Value)malloc(sizeof(struct hashtable_value));
  error_assert(error_mem, value != NULL);
  value->type = ASTN_TOKEN;
  value->node = (void*)global;
  return hashmap_insert(table, (char*)(token->value.ident), (void*)value, NULL);
}

bool hashtable_exists_token(HashTable table, ASTN_Token token) {
  return hashmap_exists(table, (char*)(token->value.ident));
}

bool hashtable_free(HashTable table) {
  if (!table) return false;
  return hashmap_free(table, NULL);
}

Stack stack_create() {
  Stack root = (Stack)malloc(sizeof(struct stack_hashtable));
  error_assert(error_mem, root != NULL);
  root->frame = true;
  root->token = NULL;
  root->next  = NULL;
  return root;
}

uint64_t stack_size(Stack stack) {
  uint64_t s_stack = 0;
  for (Stack node = stack; node != NULL; node = node->next)
    if (!node->frame)
      s_stack++;
  return s_stack;
}

bool stack_push(Stack* stack, ASTN_Token token) {
  if (stack == NULL)
    return false;
  Stack top = (Stack)malloc(sizeof(struct stack_hashtable));
  error_assert(error_mem, top != NULL);
  top->next  = *stack;
  top->frame = token == NULL;
  top->token = token;
  *stack = top;
  return true;
}

bool stack_push_frame(Stack* stack) {
  return stack_push(stack, NULL);
}

ASTN_Token stack_pop(Stack* stack) {
  if (stack == NULL)
    return NULL;
  Stack top = *stack;
  ASTN_Token token = top->token;
  *stack = top->next;
  free(top);
  return token;
}

bool stack_pop_frame(Stack* stack, HashTable table) {
  if (stack == NULL)
    return false;
  while (!(*stack)->frame)
    (void)hashtable_remove_var_ktype(table, stack_pop(stack));
  Stack node = *stack;
  error_assert(error_unexp, node != NULL);
  *stack = node->next;
  free(node);
  return true;
}

bool stack_is_frame(Stack stack) {
  return stack ? stack->frame : false;
}

bool stack_free(Stack* stack) {
  if (stack == NULL)
    return false;
  while (*stack != NULL) {
    Stack node = *stack;
    *stack = node->next;
    free(node);
  }
  *stack = NULL;
  return true;
}

// ==================================================# PRIVATE #==========================================================

void hashtable_free_ktype(void* ktype) { return; }
