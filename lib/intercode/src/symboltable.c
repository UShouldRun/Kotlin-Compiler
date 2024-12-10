#include "symboltable.h"

SymbolTable symboltable_create(uint64_t s_buckets, float load_threshold_factor) {
  return (SymbolTable)hashmap_create(s_buckets, load_threshold_factor);
}

uint64_t symboltable_size(SymbolTable table) {
  return hashmap_size(table);
}

int32_t symboltable_lookup_ident(SymbolTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  int32_t* temp = (int32_t*)hashmap_get(table, token->value.ident);
  error_assert(error_intercode, temp != NULL);
  return *temp;
}

int32_t symboltable_remove_ident(SymbolTable table, ASTN_Token token) {
  if (!table) return NULL;
  if (!token) return NULL;
  int32_t* temp = (int32_t*)hashmap_get(table, token->value.ident);
  error_assert(error_intercode, temp != NULL);
  error_assert(
    error_type_checker,
    hashmap_remove(table, (char*)(token->value.ident), NULL)
  );
  return *temp;
}

bool symboltable_insert_ident(SymbolTable* table, ASTN_Token token, int32_t temp) {
  if (!table) return false;
  if (!token) return false;
  int32_t* _temp = (int32_t*)malloc(sizeof(struct bool));
  error_assert(error_mem, _temp != NULL);
  *_temp = temp;
  return hashmap_insert(table, (char*)(token->value.ident), (void*)_temp, NULL);
}

bool symboltable_exists_ident(SymbolTable table, ASTN_Token token) {
  if (!table) return false;
  if (!token) return false;
  return hashmap_exists(table, (char*)token->value.ident);
}

bool symboltable_free(SymbolTable table) {
  if (!table) return false;
  return hashmap_free(table, NULL);
}

SymbolStack stack_create() {
  SymbolStack root = (SymbolStack)malloc(sizeof(struct stack_symboltable));
  error_assert(error_mem, root != NULL);
  root->frame = true;
  root->token = NULL;
  root->next  = NULL;
  return root;
}

uint64_t stack_size(SymbolStack stack) {
  uint64_t s_stack = 0;
  for (SymbolStack node = stack; node != NULL; node = node->next)
    if (!node->frame)
      s_stack++;
  return s_stack;
}

bool stack_push(SymbolStack* stack, ASTN_Token token) {
  if (stack == NULL)
    return false;
  SymbolStack top = (SymbolStack)malloc(sizeof(struct stack_hashtable));
  error_assert(error_mem, top != NULL);
  top->next  = *stack;
  top->frame = token == NULL;
  top->token = token;
  *stack = top;
  return true;
}

bool stack_push_frame(SymbolStack* stack) {
  return stack_push(stack, NULL);
}

ASTN_Token stack_pop(SymbolStack* stack) {
  if (stack == NULL)
    return NULL;
  SymbolStack top = *stack;
  ASTN_Token token = top->token;
  *stack = top->next;
  free(top);
  return token;
}

bool stack_pop_frame(SymbolStack* stack, HashTable table) {
  if (stack == NULL)
    return false;
  while (!(*stack)->frame)
    (void)hashtable_remove_ident(table, stack_pop(stack));
  SymbolStack node = *stack;
  error_assert(error_unexp, node != NULL);
  *stack = node->next;
  free(node);
  return true;
}

bool stack_is_frame(SymbolStack stack) {
  return stack ? stack->frame : false;
}

bool stack_free(SymbolStack* stack) {
  if (stack == NULL)
    return false;
  while (*stack != NULL) {
    SymbolStack node = *stack;
    *stack = node->next;
    free(node);
  }
  *stack = NULL;
  return true;
}
