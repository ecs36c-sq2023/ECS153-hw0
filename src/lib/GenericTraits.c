
#include "GenericTraits.h"
#include <string.h>

#define MAX_TYPES 256
static char *type_names[MAX_TYPES];
static void *(*prototype_constructors[MAX_TYPES])();
static void (*prototype_destructors[MAX_TYPES])(void *);
static int num_types = 0;

Constructor get_prototype_constructor(char *type_name) {
  /* Your code here to get the constructor of the struct' prototype */
}
Destructor get_prototype_destructor(char *type_name) {
  /* Your code here to get the destructor of the struct' prototype */
}

void add_prototype_ctor_dtor(char *type_name, Constructor ctor,
                             Destructor dtor) {
  /* Your code here to register the struct */
}
