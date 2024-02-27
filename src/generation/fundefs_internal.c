#include "fundefs_internal.h"

#include "../../RockerAllocator/alloc.h"
#include "typedefs.h"
#include <stdio.h>
#include <string.h>

__internal_dynamic_array_t __internal_make_array(size_t size) {
  __internal_dynamic_array_t arr =
      allocate_compiler_persistent(sizeof(struct __internal_dynamic_array));
  if (size == 0) {
    printf("Could not pop elem out of dynamic array: BAD ELEMENT SIZE\n");
    return arr;
  }
  arr->capacity = __INTERNAL_DYNAMIC_ARRAY_CAP;
  arr->elem_size = size;
  arr->data = allocate_compiler_persistent(arr->elem_size * arr->capacity);
  arr->length = 0;
  return arr;
}

// We use the compiler version of thre
//  allocator as well for convenience
// but this may change btw reallocation
// does not change the scope in which
// the pointer was allocated
int __internal_push_array(__internal_dynamic_array_t arr, void *elem) {
  if (elem == NULL) {
    printf("Could not push elem to dynamic array: BAD ELEM\n");
    return 1;
  }
  if (arr->length > arr->capacity) {
    arr->capacity *= 2;
    arr->data = reallocate_compiler_persistent(arr->data,
                                               arr->capacity * arr->elem_size);
  }
  void *dst = &arr->data + (arr->length++) * arr->elem_size;
  memccpy(dst, elem, 1, arr->elem_size);
  return 0;
}

void *__internal_pop_array(__internal_dynamic_array_t arr) {
  if (arr->length == 0) {
    printf("Could not pop elem out of dynamic array: EMPTY ARRAY\n");
    return NULL;
  }
  if (arr->elem_size == 0) {
    printf("Could not pop elem out of dynamic array: BAD ELEMENT SIZE\n");
    return NULL;
  }
  void *res = allocate_compiler_persistent(arr->elem_size);
  void *src = &arr->data + (arr->length - 1) * arr->elem_size;
  memccpy(res, src, 1, arr->elem_size);
  arr->length--;
  return res;
}

void *__internal_get_elem(__internal_dynamic_array_t arr, size_t index) {
  if (index >= arr->length) {
    printf("Could not get elem from dynamic array: INDEX OUT OF BOUNDS\n");
    return NULL;
  }
  if (arr->elem_size == 0) {
    printf("Could not get elem from dynamic array: BAD ELEMENT SIZE\n");
    return NULL;
  }
  void *res = allocate_compiler_persistent(arr->elem_size);
  void *src = &arr->data + index * arr->elem_size;
  memccpy(res, src, 1, arr->elem_size);
  return res;
}

void __internal_insert(__internal_dynamic_array_t arr, size_t index,
                       void *elem) {}

void __internal_set_elem(__internal_dynamic_array_t arr, size_t index,
                         void *elem) {}

size_t get_length(__internal_dynamic_array_t arr) { return arr->length; }