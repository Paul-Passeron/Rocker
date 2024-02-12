/*****************************************************
 * ROCKER GENERATOR HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <assert.h>
#include <stdio.h>

#include "ast.h"
#include "token.h"

#define TYPED_ARG_CAP 1024
#define CLOSURE_CAP 1024

typedef struct typed_arg {
  token_t name;
  token_array_t type;
} typed_arg;

typedef struct fun_def {
  token_t name;
  typed_arg args[TYPED_ARG_CAP];
  token_array_t return_type;
  int arity;
  char* closure_name;
} fun_def;

typedef struct closure_t {
  typed_arg elems[TYPED_ARG_CAP];
  int length;
  char* name;
} closure_t;

typedef struct closure_stack {
  closure_t data[CLOSURE_CAP];
  int length;
} closure_stack;

typedef struct doubles_table {
  char* names[1024];
  int num[1024];
  int length;
} doubles_table;

int get_num_repeat(doubles_table d, char* name);

void generate_closure_def(closure_t closure, FILE* f);
void generate_type_name(token_array_t arr, FILE* f);
void generate_function_signature(fun_def fun, FILE* f);
fun_def fundef_from_let(ast_t bind);
void generate_prolog(FILE* f);
char* name_mangle(ast_t let_binding);
#endif  // GENERATOR_H