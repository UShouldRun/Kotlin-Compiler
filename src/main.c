#include <stdio.h>
#include <stdlib.h>

#include "parser.tab.h"
#include "error.h"

void init_ast_arena(Arena* arena) {
  const uint64_t s_ast_arena = 1 << 20;
  const uint64_t s_ast_arena_nodes = 5;
  *arena = arena_create_aligned(s_ast_arena, ast_max_size(), s_ast_arena_nodes);
}

void init_ast(AST* ast, Arena arena, const char* filename) { 
  *ast = ast_create(arena, filename, 0, NULL, NULL, NULL);
}

int32_t main(int32_t argc, char* argv[]) {
  error_assert(error_inval_arg, argc > 1);
  const char* filename = argv[1];

  FILE* file = fopen(filename, "r");
  if (file == NULL)
    error_panic(error_io, strerror(errno));

  Arena arena = NULL;
  AST ast = NULL;

  init_ast_arena(&arena);
  error_assert(error_nullptr, arena != NULL);

  init_ast(&ast, arena);
  error_assert(error_nullptr, ast != NULL);

  yyparse(&ast);
  ast_print(ast);

  error_assert(error_unexp, ast_destroy(ast));
  error_assert(error_unexp, arena_destroy(arena));

  return 0;
}
