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

void transpile(generator_t *g, ast_t program);

#endif // GENERATOR_H
