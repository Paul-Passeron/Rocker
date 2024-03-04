#ifndef ROCKER_FUNDEFS_INTERNAL
#define ROCKER_FUNDEFS_INTERNAL

#include "typedefs.h"

#define __INTERNAL_DYNAMIC_ARRAY_CAP 64

void init_rocker(int argc, char **argv);
void end_rocker(void);
void exit_rocker(int status);

__internal_dynamic_array_t __internal_make_array(size_t size);
int __internal_push_array(__internal_dynamic_array_t arr, void *elem);
void *__internal_pop_array(__internal_dynamic_array_t arr);
void __internal_insert(__internal_dynamic_array_t arr, size_t index,
                       void *elem);
void *__internal_get_elem(__internal_dynamic_array_t arr, size_t index);
void __internal_set_elem(__internal_dynamic_array_t arr, size_t index,
                         void *elem);

size_t get_length(__internal_dynamic_array_t arr);

__internal_dynamic_array_t get_args(void);
void fill_cmd_args(int argc, char **argv);

// Builtin array methods (generated)

__internal_dynamic_array_t int_make_array(void);

void int_push_array(__internal_dynamic_array_t arr, int elem);

int int_pop_array(__internal_dynamic_array_t arr);
int int_get_elem(__internal_dynamic_array_t arr, size_t index);

void int_set_elem(__internal_dynamic_array_t arr, size_t index, int elem);

void int_insert(__internal_dynamic_array_t arr, size_t index, int elem);

__internal_dynamic_array_t boolean_make_array(void);

void boolean_push_array(__internal_dynamic_array_t arr, boolean elem);

boolean boolean_pop_array(__internal_dynamic_array_t arr);

boolean boolean_get_elem(__internal_dynamic_array_t arr, size_t index);
void boolean_set_elem(__internal_dynamic_array_t arr, size_t index,
                      boolean elem);

void boolean_insert(__internal_dynamic_array_t arr, size_t index, boolean elem);

__internal_dynamic_array_t string_make_array(void);

void string_push_array(__internal_dynamic_array_t arr, string elem);

string string_pop_array(__internal_dynamic_array_t arr);

string string_get_elem(__internal_dynamic_array_t arr, size_t index);

void string_set_elem(__internal_dynamic_array_t arr, size_t index, string elem);

void string_insert(__internal_dynamic_array_t arr, size_t index, string elem);

__internal_dynamic_array_t char_make_array(void);

void char_push_array(__internal_dynamic_array_t arr, char elem);

char char_pop_array(__internal_dynamic_array_t arr);

char char_get_elem(__internal_dynamic_array_t arr, size_t index);

void char_set_elem(__internal_dynamic_array_t arr, size_t index, char elem);

void char_insert(__internal_dynamic_array_t arr, size_t index, char elem);

#endif // ROCKER_FUNDEFS_INTERNAL
