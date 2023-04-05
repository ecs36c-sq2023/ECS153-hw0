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

  /// Generate a new struct based on a string.
  void *(*new)(char *this);

  /// Prints the details of the struct to a file stream.
  void (*dump)(void *this, FILE *fp);

  /// Compares two instances, returns positive number if larger, negative number
  /// is smaller, 0 if equal.
  int (*cmp)(void *this, void *that);

  /// Free the memory allocated to this instance.
  void (*drop)(void *this);

} GenericTraits;

/// Ask for a new prototype constructor based on the given type name.
typedef void *(*Constructor)();
Constructor get_prototype_constructor(char *type_name);

/// Ask for a new prototype destructor based on the given type name.
typedef void (*Destructor)(void *);
Destructor get_prototype_destructor(char *type_name);

/// Register a new type, its name and prototype constructor and destructor.
/// This function runs before main.
void add_prototype_ctor_dtor(char *type_name, Constructor ctor,
                             Destructor dtor);

#define DECLARE_STRUCT(Name, Internal)                                         \
  typedef struct Name Internal Name;                                           \
  void *new_##Name(char *);                                                    \
  void dump_##Name(void *, FILE *fp);                                          \
  int cmp_##Name(void *, void *);                                              \
  void drop_##Name(void *);                                                    \
                                                                               \
  void *new_##Name##_prototype();                                              \
  void drop_##Name##_prototype(void *);                                        \
                                                                               \
  void __attribute__((constructor)) register_##Name();

#define DEFINE_STRUCT(Name)                                                    \
  void drop_ #Name(void *this) { /* Your code here to free the instance */     \
  }                                                                            \
  void new_##Name##_prototype() {                                              \
    /* Your code here to create a new prototype */                             \
  }                                                                            \
  void *drop_##Name##_prototype(void *this) {                                  \
    /* Your code here to free the prototype */                                 \
  }                                                                            \
  void __attribute__((constructor)) register_##Name() {                        \
    /* Your code here to register ctor and  dtor */                            \
  }

#endif
