#ifndef GENERIC_TRAITS_H
#define GENERIC_TRAITS_H

#include <stdio.h>

/// Some generic traits that all structs should have.
///
/// In order for all structs to have it, a `GenericTraits*` should be placed at
/// the head of all structs.
/// This struct demostrates how to do OOP in C, which is similar to v-table in
/// C++.
typedef struct GenericTraits {

  void *(*new)(char *self);

  /// Prints the details of the struct to a file stream.
  void (*dump)(void *self, FILE *fp);

  /// Compares two instances, returns positive number if larger, negative number
  /// is smaller, 0 if equal.
  int (*cmp)(void *self, void *other);

  void (*drop)(void *self);

} GenericTraits;

/// Ask for the object constructor based on the given type name.
typedef void *(*Constructor)(char *string);
Constructor get_constructor(char *type_name);

/// Ask for the object destructor based on the given type name.
typedef void (*Destructor)(void *);
Destructor get_destructor(char *type_name);

/// Register a new type, its name, constructor and destructor.
/// This function runs before main.
void add_ctor_dtor(char *type_name, Constructor ctor, Destructor dtor);

#define DECLARE_STRUCT(Object, Internal)                                       \
  typedef struct Object Internal Object;                                       \
  void *new_##Object(char *);                                                  \
  void dump_##Object(void *, FILE *fp);                                        \
  int cmp_##Object(void *, void *);                                            \
  void drop_##Object(void *);                                                  \
                                                                               \
  void __attribute__((constructor)) register_##Object();

#define DEFINE_STRUCT(Object)                                                  \
  void drop_##Object(void *this) { /* Your code here to free the instance. */  \
  }                                                                            \
  void __attribute__((constructor)) register_##Object() {                      \
    /* Your code here to register an object. */                                \
  }

#endif
