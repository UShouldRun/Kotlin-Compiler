#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parser.tab.h"
#include "error.h"

const char* filename;
extern FILE* yyin;

Arena arena = NULL;
AST   ast   = NULL;

void init_ast_arena(Arena* arena) {
  const uint64_t s_ast_arena = 1 << 20;
  const uint64_t s_ast_arena_nodes = 5;
  *arena = arena_create_aligned(s_ast_arena, astn_max_size(), s_ast_arena_nodes);
}

int32_t main(int32_t argc, char* argv[]) {
  error_assert(error_inval_arg, argc > 1);
  filename = argv[1];

  yyin = fopen(filename, "r");
  if (yyin == NULL)
    error_panic(error_io, strerror(errno));

  init_ast_arena(&arena);
  error_assert(error_nullptr, arena != NULL);

  yyparse();
  // ast_print(stdout, ast);
  const uint64_t s_buckets = 256;
  const float load_threshold_factor = 0.75;
  (void)ast_type_check(filename, ast, s_buckets, load_threshold_factor);

  error_assert(error_unexp, arena_destroy(arena));
  fclose(yyin);

  return 0;
}
