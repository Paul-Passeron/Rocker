/*****************************************************
 * ROCKER NAME_TABLE HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef NAME_TABLE_H
#define NAME_TABLE_H

#include "ast.h"

#define INIT_NT_CAP 1024

typedef enum nt_kind {
  NT_FUN,
  NT_VAR,
  NT_BUILTIN_TYPE,
  NT_USER_TYPE,
  // TODO: add support for type constructors
} nt_kind;

typedef struct name_table_t {
  nt_kind* kinds;
  char** names;
  int* scopes;
  ast_array_t refs;
  int scope;
  int length;
  int capacity;
} name_table_t;

ast_t get_ref(char* name, name_table_t table);
void new_nt_scope(name_table_t* table);
void end_nt_scope(name_table_t* table);
void reallocate_table(name_table_t* table);
void push_nt(name_table_t* table, char* name, nt_kind kind, ast_t ref);

#endif  // NAME_TABLE_H
