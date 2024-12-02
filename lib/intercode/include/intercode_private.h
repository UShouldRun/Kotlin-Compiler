#ifndef INTERCODE_PRIVATE_H
#define INTERCODE_PRIVATE_H

#include "intercode.h"

struct address {
  AddressType type;
  union {
    int64_t  val_int;
    uint64_t val_uint;
    char     val_char;
    uint32_t temp;
    char*    label;
  } value;
};

struct quad {
  ICI inst;
  Address add1, add2, add3, add4;
  Quad next;
};

#endif // !INTERCODE_PRIVATE_H
