
#include "GenericTraits.h"
#include <string.h>

#define MAX_TYPES 256
static char *type_names[MAX_TYPES];
static void *(*constructors[MAX_TYPES])(char *);
static void (*destructors[MAX_TYPES])(void *);
static int num_types = 0;

Constructor get_constructor(char *type_name) {
  /* Your code here to get the constructor of the struct' */
}
Destructor get_destructor(char *type_name) {
  /* Your code here to get the destructor of the struct' */
}

void add_ctor_dtor(char *type_name, Constructor ctor, Destructor dtor) {
  /* Your code here to register the struct */
}
