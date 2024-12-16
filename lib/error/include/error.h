#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifndef COLORS
#define COLORS

extern const char* colors[];

#define RESET 0
#define BLACK 1
#define RED 2
#define GREEN 3
#define YELLOW 4
#define BLUE 5
#define MAGENTA 6
#define CYAN 7
#define WHITE 8
#define BOLD 9
#define UNDERLINE 10
#define REVERSED 11
#define BRIGHT_BLACK 12
#define BRIGHT_RED 13
#define BRIGHT_GREEN 14
#define BRIGHT_YELLOW 15
#define BRIGHT_BLUE 16
#define BRIGHT_MAGENTA 17
#define BRIGHT_CYAN 18
#define BRIGHT_WHITE 19
#define BG_BLACK 20
#define BG_RED 21
#define BG_GREEN 22
#define BG_YELLOW 23
#define BG_BLUE 24
#define BG_MAGENTA 25
#define BG_CYAN 26
#define BG_WHITE 27
#endif

typedef enum {
  error_start = 0,
  error_nullptr,
  error_mem,
  error_inval_arg,
  error_unexp,
  error_io,
  error_parser,
  error_type_checker,
  error_intercode,
  error_genassembly,
  error_end
} ErrorType;

#define ERROR_SYNTAX              "Syntax Error"
#define ERROR_SYNTAX_ELSEIF_ELSE  "<else if> or <else> block with no parent <if>"
#define ERROR_SYNTAX_CASE         "<case> block with no parent <when>"

#define ERROR_INVALID_EXPR_OP     "Invalid Expr Op"
#define ERROR_INVALID_TT          "Invalid Token Type"
#define ERROR_INVALID_EXPR        "Invalid Expression"
#define ERROR_INVALID_STMT        "Invalid Statement"
#define ERROR_INVALID_OBJ         "Invalid Object"
#define ERROR_INVALID_KTYPE       "Invalid KType Default"
#define ERROR_INVALID_ASTNT       "Invalid ASTN Type"

#define ERROR_INVALID_COND_BOOL   "Invalid KType - conditional expressions must be Boolean"
#define ERROR_INVALID_PRINTLN_USE "Invalid call of println functions - should've been handled by the TC"
#define ERROR_INVALID_READLN_USE "Invalid call of readln functions - should've been handled by the TC"

#define ERROR_INCOMPATIBLE_KTYPES "Type conflict - evaluated expressions and/or statements have different tyes"

#define ERROR_INVALID_ADDR_T      "Invalid address type"
#define ERROR_INVALID_ADDRESS     "Invalid Address Type"

#define ERROR_MAIN_NOT_FOUND      "main was not found"
#define ERROR_MULT_DEF_MAIN       "main is defined more than once"

#define ERROR_UNDEFINED_FUN       "Undefined function"
#define ERROR_UNDEFINED_IDENT     "Undefined identifier"
#define ERROR_UNDEFINED_KTYPE     "Undefined type"

#define ERROR_TYPE_CONFLICT_BOOL  "Type conflict (type must be bool)"
#define ERROR_TYPE_CONFLICT_NUM   "Type conflict (type must be number)"
#define ERROR_TYPE_CONFLICT       "Type conflict"
#define ERROR_TYPE_FEW_ARGS       "Too few arguments passed into function"
#define ERROR_TYPE_MANY_ARGS      "Too many arguments passed into function"
#define ERROR_TYPE_FEW_RET        "Too few values returned by the current function"
#define ERROR_TYPE_MANY_RET       "Too many values returned by the current function"

#define ERROR_NOT_IMPLEMENT_RET   "Not implemented multiple return values in this version of the compiler"
#define ERROR_NOT_IMPLEMENT_NFUN  "Only implemented functions in intercode generation"
#define ERROR_NOT_IMPLEMENT_REAL  "LONG FLOAT DOUBLE inter code not implemented"

#define ERROR_IO_SOURCE_FILE      "[ERROR]: Could not open file %s for error display.\n"

// ======================================# PRIVATE #==========================================

void _error_print(ErrorType error, const char* msg, const char* file, uint32_t line, int32_t column);
void _error_assert(ErrorType, const char*, const char*, uint32_t);

void error_print_kotlin(ErrorType error, const char* msg, const char* file, uint32_t line, int32_t column);

// ======================================# PUBLIC #==========================================

#define error_assert(error, condition) condition ? (void)0 : _error_assert(error, #condition, __FILE__, __LINE__)
#define error_panic(error, msg)        _error_assert(error, msg, __FILE__, __LINE__)

#endif // !ERROR_H
