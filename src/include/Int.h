#ifndef INT_H
#define INT_H

#include "GenericTraits.h"
#include <stdint.h>
#include <stdlib.h>

/// A wrapper of `int32_t`.
///
/// This is the first struct you should implement to get yourself familar with
/// function pointers.
typedef struct Int {
  GenericTraits *impl;

  int i;
} Int;

/// Create a new `Int`
void *new_Int(char *string);
/// Prints `Int` to the file stream. You should print it a hex values with a
/// "0x" prefix.
void dump_Int(void *self, FILE *fp);
/// Compares two `Int`.
int cmp_Int(void *self, void *other);
/// Free this struct.
void drop_Int(void *self);

/// Register `Int` using `add_ctor_dtor`.
/// This function should run before main.
/// You may want to look into attributes and constructor/destructor.
void __attribute__((constructor)) register_Int();

#endif