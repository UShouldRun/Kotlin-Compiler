#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "arena.h"

int32_t main(int32_t argc, char* argv[]) {
  const uint64_t s_arena = 1 << 16, m_nodes = 5, s_block = 1 << 6, s_word = 8;
  FILE* file = stdout;

  srand(time(NULL));

  {
    fprintf(file, "Test Arena Create\n");
    Arena arena = arena_create(s_arena, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);
    assert(arena_destroy(arena));
  }

  {
    fprintf(file, "Test Arena Create Aligned\n");
    Arena arena = arena_create_aligned(s_arena, s_block, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);
    assert(arena_destroy(arena));
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

    assert(arena_destroy(arena));
  }

  {
    fprintf(file, "Test Arena Alloc and Arena Free (aligned)\n");
    Arena arena = arena_create_aligned(s_arena, s_block, m_nodes);
    assert(arena != NULL);
    arena_print(arena, file);

    int32_t* ptr = arena_alloc(arena, sizeof(int32_t));
    assert(ptr != NULL);
    arena_print(arena, file);
    fprintf(file, "%p\n", (void*)ptr);
    fprintf(file, "%zu == %zu\n", arena_get_size_used(arena), (uint64_t)64);
    assert(arena_get_size_used(arena) == 64);

    assert(arena_free(arena, ptr));;
    arena_print(arena, file);
    assert(arena_get_size_used(arena) == 0);

    assert(arena_destroy(arena));
  }

  {
    fprintf(file, "Test Arena Alloc and Arena Free for an array (not aligned)\n");
    Arena arena = arena_create(s_arena, m_nodes);
    assert(arena != NULL);

    uint32_t s_vector = rand() % 30;
    int32_t* vector = arena_alloc(arena, s_vector * sizeof(int32_t));
    assert(vector != NULL);
    fprintf(file, "%zu == %zu\n", arena_get_size_used(arena), sizeof(uint64_t) + s_vector * sizeof(int32_t));
    assert(arena_get_size_used(arena) == sizeof(uint64_t) + s_vector * sizeof(int32_t));

    assert(arena_free(arena, vector));
    arena_print(arena, file);
    assert(arena_get_size_used(arena) == 0);

    assert(arena_destroy(arena));
  }

  {
    fprintf(file, "Test Arena Alloc Array, Arena Realloc and Arena Free for arrays (not aligned)\n");
    Arena arena = arena_create(s_arena, m_nodes);
    assert(arena != NULL);

    uint32_t s_vector1 = rand() % 30;
    int32_t* vector1 = arena_alloc_array(arena, sizeof(int32_t), s_vector1);
    assert(vector1 != NULL);

    for (uint32_t i = 0; i < s_vector1; i++)
      vector1[i] = i + 1;

    uint32_t s_vector2 = rand() % 40;
    double* vector2 = arena_alloc_array(arena, sizeof(double), s_vector2);
    assert(vector2 != NULL);

    for (uint32_t i = 0; i < s_vector2; i++)
      vector2[i] = 1 + 1/(i+1);

    uint64_t expected = 2 * s_word + s_vector1 * sizeof(int32_t) + s_vector2 * sizeof(double);
    fprintf(
      file,
      "expected: 2 * %zu + %u * %zu + %u * %zu == %zu\n",
      s_word, s_vector1, sizeof(int32_t), s_vector2, sizeof(double), expected
    );

    arena_print(arena, file);
    assert(arena_get_size_used(arena) == expected);

    int32_t* temp = vector1;

    s_vector1++;
    vector1 = arena_realloc(arena, vector1, s_vector1 * sizeof(int32_t));
    assert(vector1 != temp);

    for (uint32_t i = 0; i < s_vector1 - 1; i++)
      assert(vector1[i] == i + 1);

    for (uint32_t i = 0; i < s_vector2; i++)
      assert(vector2[i] == 1 + 1/(i+1));

    expected = 2 * s_word + s_vector1 * sizeof(int32_t) + s_vector2 * sizeof(double);
    fprintf(
      file,
      "expected: 2 * %zu + %u * %zu + %u * %zu == %zu\n",
      s_word, s_vector1, sizeof(int32_t), s_vector2, sizeof(double), expected
    );

    arena_print(arena, file);
    assert(arena_get_size_used(arena) == expected);

    assert(arena_free(arena, vector1));
    assert(arena_free(arena, vector2));
    arena_print(arena, file);
    assert(arena_get_size_used(arena) == 0);

    assert(arena_destroy(arena));
  }

  return 0;
}
