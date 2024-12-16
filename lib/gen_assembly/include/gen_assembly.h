#ifndef GENASSEMBLY_H
#define GENASSEMBLY_H

#include "intercode_private.h"

void print_mips       (FILE*, Quad);

void translate_op     (Address, char*, FILE*, int32_t, const char*);
void gen_inst         (const char*, Address, Address, Address, FILE*);
void emit_instruction (const char*, Address, Address, Address, FILE*);
void emit_label       (const char*, FILE*);
void emit_syscall     (int, FILE*);

#endif
