#ifndef ROCKER_TYPEDEFS_INTERNAL
#define ROCKER_TYPEDEFS_INTERNAL

#include <aio.h>

typedef struct string {
  char *data;
  size_t length;
} string;

typedef struct __internal_dynamic_array *__internal_dynamic_array_t;

struct __internal_dynamic_array {
  void *data;
  size_t length;
  size_t capacity;
  size_t elem_size;
};

typedef char boolean;
#define true 1
#define false 0

#endif // ROCKER_TYPEDEFS_INTERNAL