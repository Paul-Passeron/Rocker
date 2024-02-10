/*****************************************************
 * ROCKER GENERATOR HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef GENERATOR_H
#define GENERATOR_H

#include <stdio.h>
#include "ast.h"
#include "parser.h"

typedef struct generator_t
{
    FILE *out;
    ast_array_t program;

} generator_t;

generator_t new_generator(parser_t p, char *filename);
void kill_generator(generator_t g);

#endif // GENERATOR_H