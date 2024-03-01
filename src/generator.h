/*****************************************************
 * ROCKER GENERATOR HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include "ast.h"
#include "name_table.h"
#include <stdio.h>
typedef struct generator_t {
  FILE *f;
  name_table_t table;
} generator_t;

generator_t new_generator(char *filename);
void kill_generator(generator_t g);

name_table_t new_name_table(void);
ast_t get_ref(char *name, name_table_t table);
void new_nt_scope(name_table_t *table);
void end_nt_scope(name_table_t *table);
void push_nt(name_table_t *table, char *name, nt_kind kind, ast_t ref);
void transpile(generator_t *g, ast_t program);

#endif // GENERATOR_H
