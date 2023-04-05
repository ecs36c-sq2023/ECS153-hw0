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
  /* Your code here to declare the struct */
} Int;

/// Create a new `Int`
void *new_Int(char *string);
/// Prints `Int` to the file stream. You should print it a hex values with a
/// "0x" prefix.
void dump_Int(void *this, FILE *fp);
/// Compares two `Int`.
int cmp_Int(void *this, void *that);
/// Free this struct. Don't forget to free `GenericTraits` too.
void drop_Int(void *this);

/// Create an `Int` prototype, which only has methods without actual data.
void *new_Int_prototype();
/// Free the prototype.
void drop_Int_prototype(void *this);

/// Register `Int` using `add_prototype_constructor`.
/// This function should run before main.
/// You may want to look into attributes and constructor/destructor.
void __attribute__((constructor)) register_Int();

#endif