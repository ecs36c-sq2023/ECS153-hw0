#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include "GenericTraits.h"
/// Given an array of objects, which you have no knowledge of except that they
/// implement `GenericTraits`.
void quick_sort(GenericTraits **array[], int n);

#endif