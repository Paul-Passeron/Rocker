#ifndef ROCKER_TYPEDEFS_INTERNAL
#define ROCKER_TYPEDEFS_INTERNAL

#include <aio.h>

typedef struct string {
  char* data;
  size_t length;
} string;

#endif  // ROCKER_TYPEDEFS_INTERNAL