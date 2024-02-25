/*****************************************************
 * ROCKER TYPECHECKER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef TYPECHECKER_H
#define TYPECHECKER_H

#include "ast.h"
#include "name_table.h"

typedef struct typechecker_t {
  name_table_t nt;
  ast_t current_function;
} typechecker_t;

typedef struct rocker_type_t {
  enum {
    builtin_int,
    builtin_char,
    builtin_bool,
    builtin_string,
    user_defined,
    error_type,
  } tag;
  union {
    int builtin;
    struct {
      char* name;
    } user_defined_type;
  } data;
} rocker_type_t;

int tc_program(ast_t program);

#endif  // TYPECHECKER_H
