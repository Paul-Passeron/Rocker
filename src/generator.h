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
  int allocated;
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
  ast_t reference;
} closure_t;

typedef struct closure_stack {
  closure_t data[CLOSURE_CAP];
  int length;
} closure_stack;

typedef struct doubles_table {
  char** names;
  int* num;
  int length;
} doubles_table;

typedef struct {
  closure_t* data;
  int length;
} program_closures;

void kill_global_table(void);

int get_num_repeat(doubles_table d, char* name);
void generate_closure_def(closure_t closure, FILE* f);
void generate_type_name(token_array_t arr, FILE* f);
void generate_function_signature(fun_def fun, FILE* f, char* name, char* outer);
fun_def fundef_from_let(ast_t bind);
void generate_prolog(FILE* f);
char* name_mangle(ast_t let_binding);
closure_t get_closure(ast_t let, char* outer_closure, char* inner_closure);
void print_closure(closure_t closure);
void kill_closure(closure_t closure);
program_closures get_every_closures(ast_array_t program);
void generate_closure_forward_def(closure_t closure, FILE* f);
void generate_function_ptr_type_def(closure_t closure, FILE* f);
void generate_var_def(ast_t let, FILE* f);
void generate_expression(ast_t let, FILE* f);
void generate_function_body(closure_t closure, FILE* f);
#endif  // GENERATOR_H