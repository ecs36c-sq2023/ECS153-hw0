#ifndef HUMAN_H
#define HUMAN_H

#include "GenericTraits.h"
#include <stdint.h>
#include <stdlib.h>

/// Human only have a name.
typedef struct Human {
  /* Your code here to declare the struct */
} Human;

void *new_Human(char *);
void dump_Human(void *self, FILE *fp);
int cmp_Human(void *self, void *other);
void drop_Human(void *self);

void __attribute__((constructor)) register_Human();

#endif