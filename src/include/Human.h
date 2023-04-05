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
void dump_Human(void *, FILE *fp);
int cmp_Human(void *, void *);
void drop_Human(void *);

void *new_Human_prototype();
void drop_Human_prototype(void *);
void __attribute__((constructor)) register_Human();

#endif