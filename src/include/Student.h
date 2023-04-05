#ifndef STUDENT_H
#define STUDENT_H

#include "GenericTraits.h"
#include "Human.h"
#include <stdint.h>
#include <stdlib.h>

typedef struct Student {
  /* Your code here to declare the struct */
} Student;

void *new_Student(char *);
void dump_Student(void *, FILE *fp);
int cmp_Student(void *, void *);
void drop_Student(void *);

void *new_Student_prototype();
void drop_Student_prototype(void *);
void __attribute__((constructor)) register_Student();

#endif