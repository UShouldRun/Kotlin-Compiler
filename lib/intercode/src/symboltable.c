#include "symboltable.h"
#include "hashtable_private.h"

SymbolTable symboltable_create(uint64_t s_buckets, float load_threshold_factor) {
  return (SymbolTable)hashmap_create(s_buckets, load_threshold_factor);
}

uint64_t symboltable_size(SymbolTable table) {
  return hashmap_size(table);
}

int32_t symboltable_lookup_ident(SymbolTable table, ASTN_Token token) {
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, token != NULL);
  int32_t* temp = (int32_t*)hashmap_get(table, (char*)token->value.ident);
  error_assert(error_intercode, temp != NULL);
  return *temp;
}

int32_t symboltable_remove_ident(SymbolTable table, ASTN_Token token) {
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, token != NULL);
  int32_t* _temp = (int32_t*)hashmap_get(table, (char*)token->value.ident);
  error_assert(error_intercode, _temp != NULL);
  int32_t temp = *_temp;
  error_assert(
    error_type_checker,
    hashmap_remove(table, (char*)(token->value.ident), NULL)
  );
  return temp;
}

bool symboltable_insert_ident(SymbolTable* table, ASTN_Token token, int32_t temp) {
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, token != NULL);
  int32_t* _temp = (int32_t*)malloc(sizeof(int32_t));
  error_assert(error_mem, _temp != NULL);
  *_temp = temp;
  return hashmap_insert(table, (char*)(token->value.ident), (void*)_temp, NULL);
}

bool symboltable_exists_ident(SymbolTable table, ASTN_Token token) {
  error_assert(error_intercode, table != NULL);
  error_assert(error_intercode, token != NULL);
  return hashmap_exists(table, (char*)token->value.ident);
}

bool symboltable_free(SymbolTable table) {
  if (!table) return false;
  return hashmap_free(table, NULL);
}

SymbolStack symbolstack_create() {
  SymbolStack root = (SymbolStack)malloc(sizeof(struct stack_hashtable));
  error_assert(error_mem, root != NULL);
  root->frame = true;
  root->token = NULL;
  root->next  = NULL;
  return root;
}

uint64_t symbolstack_size(SymbolStack stack) {
  uint64_t s_stack = 0;
  for (SymbolStack node = stack; node != NULL; node = node->next)
    if (!node->frame)
      s_stack++;
  return s_stack;
}

bool symbolstack_push(SymbolStack* stack, ASTN_Token token) {
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

bool symbolstack_push_frame(SymbolStack* stack) {
  return stack_push(stack, NULL);
}

ASTN_Token symbolstack_pop(SymbolStack* stack) {
  if (stack == NULL)
    return NULL;
  SymbolStack top = *stack;
  ASTN_Token token = top->token;
  *stack = top->next;
  free(top);
  return token;
}

bool symbolstack_pop_frame(SymbolStack* stack, SymbolTable table) {
  if (stack == NULL)
    return false;
  while (!(*stack)->frame)
    (void)symboltable_remove_ident(table, stack_pop(stack));
  SymbolStack node = *stack;
  error_assert(error_unexp, node != NULL);
  *stack = node->next;
  free(node);
  return true;
}

bool symbolstack_is_frame(SymbolStack stack) {
  return stack ? stack->frame : false;
}

bool symbolstack_free(SymbolStack* stack) {
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
