#ifndef INTERCODE_H
#define INTERCODE_H

#include "ast_private.h"

// ==================================================# PUBLIC #=================================================================

typedef enum ic_instructions {
  ICI_Arit_Add, ICI_Arit_AddI, ICI_Arit_AddU, ICI_Arit_AddIU, ICI_Arit_Sub, ICI_Arit_SubI,
  ICI_Arit_Mul, ICI_Arit_MulI, ICI_Arit_Div,

  ICI_Cond_Equal, ICI_Cond_NEqual, ICI_Cond_GThan, ICI_Cond_GThanEqual, ICI_Cond_LThan, ICI_Cond_LThanEqual,

  ICI_DT_LoadWord, ICI_DT_StoreWord, ICI_DT_LoadAdress, ICI_DT_LoadImmediate, ICI_DT_Move,

  ICI_Label,

  ICI_Logic_BitAnd, ICI_Logic_BitAndI, ICI_Logic_BitOr, ICI_Logic_BitOrI, ICI_Logic_BitNor, ICI_Logic_BitNorI,
  ICI_Logic_ShiftLeft, ICI_Logic_ShiftRight,

  ICI_UJ_Jump, ICI_UJ_JumpRegister, ICI_UJ_JumpAndLink
} ICI;

typedef enum address_type {
  AT_Empty,
  AT_IntConst, AT_UIntConst, AT_Char, AT_String,
  AT_Temp, AT_Save, AT_Label
} AddressType;

typedef struct address *Address;
typedef struct quad    *Quad;

Quad ic_translate_ast (Arena, AST);

#endif

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
