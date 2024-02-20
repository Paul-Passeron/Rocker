/*****************************************************
 * ROCKER GENERATOR HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "ast.h"

#define INIT_NT_CAP 64

typedef enum nt_kind {
  NT_FUN,
  NT_VAR,
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

typedef struct generator_t {
  FILE* f;
  name_table_t table;
} generator_t;

generator_t new_generator(char* filename);
void kill_generator(generator_t g);

name_table_t new_name_table(void);
ast_t get_ref(char* name, name_table_t table);
void new_nt_scope(name_table_t* table);
void end_nt_scope(name_table_t* table);
void push_nt(name_table_t* table, char* name, nt_kind kind, ast_t ref);

void transpile(generator_t* g, ast_t program);

#endif  // GENERATOR_H