#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "arena.h"

int32_t main(int32_t argc, char* argv[]) {
  const uint64_t s_arena = 1 << 16, m_nodes = 5, s_block = 1 << 6;
  FILE* file = stdout;

  {
    fprintf(file, "Test Arena Create\n");
    Arena arena = arena_create(s_arena, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);
    arena_destroy(arena);
  }

  {
    fprintf(file, "Test Arena Create Aligned\n");
    Arena arena = arena_create_aligned(s_arena, s_block, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);
    arena_destroy(arena);
  }

  {
    fprintf(file, "Test Arena Alloc and Arena Free (not aligned)\n");
    Arena arena = arena_create(s_arena, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);

    int32_t* ptr = arena_alloc(arena, sizeof(int32_t));
    assert(ptr != NULL);
    arena_print(arena, file);
    fprintf(file, "%p\n", (void*)ptr);
    fprintf(file, "%zu == %zu\n", arena_get_size_used(arena), sizeof(uint64_t) + sizeof(int32_t));
    assert(arena_get_size_used(arena) == sizeof(uint64_t) + sizeof(int32_t));

    assert(arena_free(arena, ptr));;
    arena_print(arena, file);
    assert(arena_get_size_used(arena) == 0);

    arena_destroy(arena);
  }

  return 0;
}
