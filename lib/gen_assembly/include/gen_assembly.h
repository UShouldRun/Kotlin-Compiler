#ifndef GENASSEMBLY_H
#define GENASSEMBLY_H

#include "intercode_private.h"

void print_mips   (FILE *output, Quad head);

void translate_op (Address addr, char* reg, FILE* output);
void gen_inst     (const char* instruction, Address arg1, Address arg2, Address arg3, FILE* output);
void emit_instruction(const char* instruction, Address arg1, Address arg2, Address arg3, FILE* output);
void emit_label   (const char* label, FILE* output);
void emit_syscall (int syscall_num, FILE *output);

#endif
