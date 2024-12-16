#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "parser.tab.h"
#include "error.h"
#include "intercode.h"
#include "gen_assembly.h"

const char* filename;
extern FILE* yyin;
extern int yylex_destroy(void);

Arena arena = NULL;
AST   ast   = NULL;

#define KOTLIN_PASSED_PARSING    "AST built\n"
#define KOTLIN_PASSED_TYPE_CHECK "Type Check passed\n"
#define KOTLIN_PASSED_IT_GEN     "Intermediate Code generated\n"
#define KOTLIN_PASSED_ASSEMBLY   "Generated assembly file\n"

#define PRINT_OFF                "--print-off"

void init_ast_arena(Arena* arena) {
  const uint64_t s_ast_arena = 1 << 20;
  const uint64_t s_ast_arena_nodes = 5;
  *arena = arena_create_aligned(s_ast_arena, astn_max_size(), s_ast_arena_nodes);
}

int32_t main(int32_t argc, char* argv[]) {
  error_assert(error_inval_arg, argc > 1);
  filename = argv[1];
  if (strlen(filename) <= 3) {
    fprintf(stderr, "File name to short (must be greater than 3)\n");
    return 1;
  }

  bool print_execution = true;
  if (argc == 3 && strcmp(argv[2], PRINT_OFF) == 0)
    print_execution = false;

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
  if (print_execution)
    ast_print(stdout, ast);
  fclose(yyin);
  fprintf(stdout, KOTLIN_PASSED_PARSING);

  const uint64_t s_buckets = 256;
  const float load_threshold_factor = 0.75;
  if (!ast_type_check(arena, ast, filename, s_buckets, load_threshold_factor)) {
    error_assert(error_unexp, arena_destroy(arena));
    yylex_destroy();
    return 1;
  }
  fprintf(stdout, KOTLIN_PASSED_TYPE_CHECK);

  Quad quad_tree = ic_translate_ast(arena, ast, s_buckets, load_threshold_factor);
  error_assert(error_intercode, quad_tree != NULL);
  fprintf(stdout, KOTLIN_PASSED_IT_GEN);
  if (print_execution)
    ic_print_translation(quad_tree);

  // Unsafe
  uint64_t len = strlen(filename);
  char output_name[256];
  strncpy(output_name, filename, len - 3);
  output_name[len - 3] = '.';
  output_name[len - 2] = 's';
  output_name[len - 1] = '\0';

  FILE* output = fopen(output_name, "w");
  print_mips(output, quad_tree);

  fclose(output);

  error_assert(error_unexp, arena_destroy(arena));
  yylex_destroy();

  return 0;
}
