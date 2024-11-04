#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef enum {
  error_start = 0,
  error_nullptr,
  error_mem,
  error_inval_arg,
  error_unexp,
  error_io,
  error_parser,
  error_end
} ErrorType;

#define ERROR_SYNTAX     "Syntax Error"
#define ERROR_INVALID_TT "Invalid Token Type"

// ======================================# PRIVATE #==========================================

void _error_assert(ErrorType, const char*, const char*, uint32_t);

// ======================================# PUBLIC #==========================================

#define error_assert(error, condition) _error_assert(error, #condition, __FILE__, __LINE__)
#define error_panic(error, msg)        _error_assert(error, msg, __FILE__, __LINE__)

#endif // !ERROR_H
