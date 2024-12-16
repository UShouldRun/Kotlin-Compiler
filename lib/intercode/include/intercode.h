#ifndef INTERCODE_H
#define INTERCODE_H

#include "ast_private.h"
#include "inttypes.h"

// ==================================================# PUBLIC #==================================================================

#define SIZEOFWORD 4

typedef enum ic_instructions {
  ICI_None,

  ICI_StackPtrIncr,
  ICI_StackPtrDecr,

  ICI_Arit_Add, ICI_Arit_AddI, ICI_Arit_AddU, ICI_Arit_AddIU, ICI_Arit_Sub, ICI_Arit_SubI,
  ICI_Arit_Mul, ICI_Arit_MulI, ICI_Arit_Div,

  ICI_Cond_Equal, ICI_Cond_NEqual, ICI_Cond_GThan, ICI_Cond_GThanEqual, ICI_Cond_LThan, ICI_Cond_LThanEqual,
  ICI_Branch_NEqual, ICI_Branch_Equal,

  ICI_DT_LoadWord, ICI_DT_StoreWord, ICI_DT_LoadAdress, ICI_DT_LoadImmediate, ICI_DT_Move,

  ICI_Label,
  
  ICI_Syscall_1,  ICI_Syscall_2,  ICI_Syscall_3,  ICI_Syscall_4,  ICI_Syscall_5,  
  ICI_Syscall_6,  ICI_Syscall_7,  ICI_Syscall_8,  ICI_Syscall_9,  ICI_Syscall_10,  
  ICI_Syscall_11, ICI_Syscall_12, ICI_Syscall_13, ICI_Syscall_14, ICI_Syscall_15,  
  ICI_Syscall_16, ICI_Syscall_17, ICI_Syscall_18, ICI_Syscall_19, ICI_Syscall_20,  
  ICI_Syscall_21, ICI_Syscall_22, ICI_Syscall_23,

  ICI_Comp_Equal,
  ICI_Comp_NEqual,
  ICI_Comp_LThan,
  ICI_Comp_GThan,

  ICI_Logic_BitAnd, ICI_Logic_BitAndI,
  ICI_Logic_BitNAnd, ICI_Logic_BitNAndI,
  ICI_Logic_BitOr, ICI_Logic_BitOrI,
  ICI_Logic_BitNor, ICI_Logic_BitNorI,
  ICI_Logic_ShiftLeft, ICI_Logic_ShiftRight,
  ICI_Logic_XorI,

  ICI_UJ_Jump, ICI_UJ_JumpRegister, ICI_UJ_JumpAndLink
} ICI;

typedef enum address_type {
  AT_Empty,
  AT_IntConst, AT_UIntConst, AT_Char, AT_String,
  AT_Temp, AT_Label,
  AT_Stack, AT_Frame, AT_Ret,
  AT_v0, AT_a0
} AddressType;

typedef struct address *Address;
typedef struct quad    *Quad;

void ic_print_translation (Quad);
Quad ic_translate_ast     (Arena, AST, uint64_t, float);

#endif

/*
| Syscall Code | Name            | Description                        | Arguments                   | Result                |
|--------------|-----------------|------------------------------------|-----------------------------|-----------------------|
| 1            | Print Integer   | Prints an integer to stdout        | $a0 = integer               | None                  |
| 2            | Print Float     | Prints a float to stdout           | $f12 = float                | None                  |
| 3            | Print Double    | Prints a double to stdout          | $f12 = double               | None                  |
| 4            | Print String    | Prints a string to stdout          | $a0 = address of string     | None                  |
| 5            | Read Integer    | Reads an integer from stdin        | None                        | $v0 = integer         |
| 6            | Read Float      | Reads a float from stdin           | None                        | $f0 = float           |
| 7            | Read Double     | Reads a double from stdin          | None                        | $f0 = double          |
| 8            | Read String     | Reads a string from stdin          | $a0 = address, $a1 = length | None                  |
| 9            | Allocate Memory | Allocates memory dynamically       | $a0 = size                  | $v0 = address         |
| 10           | Exit            | Terminates the program             | None                        | Program terminates    |
| 11           | Print Char      | Prints a single character          | $a0 = character             | None                  |
| 12           | Read Char       | Reads a single character from stdin| None                        | $v0 = character       |
| 13           | Open File       | Opens a file                       | $a0 = filename,             | $v0 = file descriptor |
|              |                 |                                    | $a1 = flags,                |                       |
|              |                 |                                    | $a2 = mode                  |                       |
| 14           | Read File       | Reads from a file                  | $a0 = file descriptor,      | $v0 = bytes read      |  
|              |                 |                                    | $a1 = buffer,               |                       |
|              |                 |                                    | $a2 = size                  |                       |
| 15           | Write File      | Writes to a file                   | $a0 = file descriptor,      | $v0 = bytes written   |
|              |                 |                                    | $a1 = buffer,               |                       |
|              |                 |                                    | $a2 = size                  |                       |
| 16           | Close File      | Closes a file                      | $a0 = file descriptor       | None                  |
| 17           | Exit2           | Terminates the program with status | $a0 = exit code             | Program terminates    |
*/



/*
typedef enum register {
  RZero,
  Rv0, Rv1,
  Ra0, Ra1, Ra2, Ra3,
  Rt0, Rt1, Rt2, Rt3, Rt4, Rt5, Rt6, Rt7,
  Rs0, Rs1, Rs2, Rs3, Rs4, Rs5, Rs6, Rs7,
  Rt8, Rt9,
  Rk0, Rk1,
  Rgp,
  Rsp,
  Rfp,
  Rra
} Register;
*/
