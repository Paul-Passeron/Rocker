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

void generate_function_sig(char *name, ast_t signature, token_array_t args);
void generate_semicolon(void);
void generate_rec_type(ast_t type_def);
void generate_pro_type(ast_t type_def);
void generate_prolog(void);
void generate_let_binding(ast_t bind);
void generate_expression(ast_t expr);
void generate_match(ast_t match_ast, ast_t type);
#endif // GENERATOR_H