/*****************************************************
 * ROCKER COMPILER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef COMPILER_H
#define COMPILER_H

#include "ast.h"
// #include "generator.h"
#include "lexer.h"
#include "parser.h"
#include "token.h"

typedef struct compiler_t {
  lexer_t lexer;
  parser_t parser;
} compiler_t;

ast_array_t generate_ast_prog_file(compiler_t*, char* filename);

void kill_compiler(compiler_t c);
#endif  // COMPILER_H