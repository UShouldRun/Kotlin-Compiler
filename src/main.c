#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parser.tab.h"
#include "error.h"

const char* filename;
extern FILE* yyin;

// extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern int yylex_destroy(void);

Arena arena = NULL;
AST   ast   = NULL;

#define KOTLIN_PASSED_PARSING    "AST built\n"
#define KOTLIN_PASSED_TYPE_CHECK "Type Check passed\n"
#define KOTLIN_PASSED_IT_GEN     "Intermediate Code generated\n"
#define KOTLIN_PASSED_ASSEMBLY   "Generated assembly file\n"

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
  if (ast == NULL) {
    error_assert(error_unexp, arena_destroy(arena));
    yylex_destroy();
    return 1;
  }
  // ast_print(stdout, ast);
  fclose(yyin);
  fprintf(stdout, KOTLIN_PASSED_PARSING);

  const uint64_t s_buckets = 256;
  const float load_threshold_factor = 0.75;
  (void)ast_type_check(arena, ast, filename, s_buckets, load_threshold_factor);
  fprintf(stdout, KOTLIN_PASSED_TYPE_CHECK);

  error_assert(error_unexp, arena_destroy(arena));
  yylex_destroy();

  return 0;
}
