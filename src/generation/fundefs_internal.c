#include "fundefs_internal.h"

#include "../../RockerAllocator/alloc.h"
#include "fundefs.h"
#include "typedefs.h"
#include <stdio.h>
#include <string.h>

__internal_dynamic_array_t __internal_make_array(size_t size) {
  __internal_dynamic_array_t ptr =
      allocate_compiler_persistent(sizeof(struct __internal_dynamic_array));
  if (size == 0) {
    printf("Could not pop elem out of dynamic array: BAD ELEMENT SIZE\n");
    return ptr;
  }
  (*ptr).capacity = __INTERNAL_DYNAMIC_ARRAY_CAP;
  (*ptr).elem_size = size;
  (*ptr).data = allocate_compiler_persistent(ptr->elem_size * ptr->capacity);
  (*ptr).length = 0;
  return ptr;
}

// We use the compiler version of thre
//  allocator as well for convenience
// but this may change btw reallocation
// does not change the scope in which
// the pointer was allocated
int __internal_push_array(__internal_dynamic_array_t arr, void *elem) {
  if (arr->data == NULL) {
    printf("Uninitialized array !\n");
    exit_rocker(1);
  }
  if (elem == NULL) {
    printf("Could not push elem to dynamic array: BAD ELEM\n");
    exit_rocker(1);
  }
  if (arr->length > arr->capacity) {
    arr->capacity *= 2;
    arr->data = reallocate_compiler_persistent(arr->data,
                                               arr->capacity * arr->elem_size);
  }
  void *dst = arr->data + arr->length * arr->elem_size;
  if (dst == NULL) {
    printf("Could not push elem to dynamic array: BAD ARRAY\n");
    exit_rocker(1);
  }
  // memccpy(dst, elem, 1, arr->elem_size);
  for (int i = 0; i < arr->elem_size; i++) {
    ((char *)dst)[i] = ((char *)elem)[i];
  }
  arr->length++;
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
  void *src = arr->data + (arr->length - 1) * arr->elem_size;
  memccpy(res, src, 1, arr->elem_size);
  arr->length--;
  return res;
}

void *__internal_get_elem(__internal_dynamic_array_t arr, size_t index) {
  if (index >= arr->length) {
    printf("Could not get elem from dynamic array: INDEX OUT OF BOUNDS\n");
    int *tmp = NULL;
    *tmp = 3;
    return NULL;
  }
  if (arr->elem_size == 0) {
    printf("Could not get elem from dynamic array: BAD ELEMENT SIZE\n");
    return NULL;
  }
  // void *res = allocate_compiler_persistent(arr->elem_size);
  void *src = arr->data + index * arr->elem_size;
  if (src == NULL)
    return NULL;
  return src;
}

void __internal_insert(__internal_dynamic_array_t arr, size_t index,
                       void *elem) {}

void __internal_set_elem(__internal_dynamic_array_t arr, size_t index,
                         void *elem) {}

size_t get_length(__internal_dynamic_array_t arr) { return arr->length; }

__internal_dynamic_array_t int_make_array(void) {
  return __internal_make_array(sizeof(int));
}

void int_push_array(__internal_dynamic_array_t arr, int elem) {
  __internal_push_array(arr, &elem);
}

int int_pop_array(__internal_dynamic_array_t arr) {
  int *res = __internal_pop_array(arr);
  return *res;
}

int int_get_elem(__internal_dynamic_array_t arr, size_t index) {
  int *res = __internal_get_elem(arr, index);
  return *res;
}

void int_set_elem(__internal_dynamic_array_t arr, size_t index, int elem) {
  __internal_set_elem(arr, index, &elem);
}

void int_insert(__internal_dynamic_array_t arr, size_t index, int elem) {
  __internal_insert(arr, index, &elem);
}

__internal_dynamic_array_t boolean_make_array(void) {
  return __internal_make_array(sizeof(boolean));
}

void boolean_push_array(__internal_dynamic_array_t arr, boolean elem) {
  __internal_push_array(arr, &elem);
}

boolean boolean_pop_array(__internal_dynamic_array_t arr) {
  boolean *res = __internal_pop_array(arr);
  return *res;
}

boolean boolean_get_elem(__internal_dynamic_array_t arr, size_t index) {
  boolean *res = __internal_get_elem(arr, index);
  return *res;
}

void boolean_set_elem(__internal_dynamic_array_t arr, size_t index,
                      boolean elem) {
  __internal_set_elem(arr, index, &elem);
}

void boolean_insert(__internal_dynamic_array_t arr, size_t index,
                    boolean elem) {
  __internal_insert(arr, index, &elem);
}

__internal_dynamic_array_t string_make_array(void) {
  return __internal_make_array(sizeof(string));
}

void string_push_array(__internal_dynamic_array_t arr, string elem) {
  __internal_push_array(arr, &elem);
}

string string_pop_array(__internal_dynamic_array_t arr) {
  string *res = __internal_pop_array(arr);
  return *res;
}

string string_get_elem(__internal_dynamic_array_t arr, size_t index) {
  string *tmp = __internal_get_elem(arr, index);
  string res = *tmp;
  return new_string(res);
}

void string_set_elem(__internal_dynamic_array_t arr, size_t index,
                     string elem) {
  __internal_set_elem(arr, index, &elem);
}

void string_insert(__internal_dynamic_array_t arr, size_t index, string elem) {
  __internal_insert(arr, index, &elem);
}

__internal_dynamic_array_t char_make_array(void) {
  return __internal_make_array(sizeof(char));
}

void char_push_array(__internal_dynamic_array_t arr, char elem) {
  __internal_push_array(arr, &elem);
}

char char_pop_array(__internal_dynamic_array_t arr) {
  char *res = __internal_pop_array(arr);
  return *res;
}

char char_get_elem(__internal_dynamic_array_t arr, size_t index) {
  char *res = __internal_get_elem(arr, index);
  return *res;
}

void char_set_elem(__internal_dynamic_array_t arr, size_t index, char elem) {
  __internal_set_elem(arr, index, &elem);
}

void char_insert(__internal_dynamic_array_t arr, size_t index, char elem) {
  __internal_insert(arr, index, &elem);
}

int global_argc;
char **global_argv;

void fill_cmd_args(int argc, char **argv) {
  global_argc = argc;
  global_argv = argv;
}

__internal_dynamic_array_t get_args(void) {
  __internal_dynamic_array_t cmd_args = string_make_array();
  for (int i = 0; i < global_argc; i++) {
    string arg = cstr_to_string(global_argv[i]);
    string_push_array(cmd_args, arg);
    // printf("Pushing arg \'");
    // print(arg);
    // printf("\'\n");
  }
  return cmd_args;
}

void init_rocker(int argc, char **argv) {
  init_compiler_stack();
  fill_cmd_args(argc, argv);
}

void end_rocker(void) {
  kill_compiler_stack();
  //
}

void exit_rocker(int status) {
  end_rocker();
  exit(status);
}