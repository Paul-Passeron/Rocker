#ifndef ROCKER_FUNDEFS_INTERNAL
#define ROCKER_FUNDEFS_INTERNAL

#include "typedefs.h"

#define __INTERNAL_DYNAMIC_ARRAY_CAP 2

__internal_dynamic_array_t __internal_make_array(size_t size);
int __internal_push_array(__internal_dynamic_array_t* arr, void* elem);
void* __internal_pop_array(__internal_dynamic_array_t* arr);
void __internal_insert(__internal_dynamic_array_t* arr,
                       size_t index,
                       void* elem);

#endif  // ROCKER_FUNDEFS_INTERNAL
