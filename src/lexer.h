/*****************************************************
 * ROCKER LEXER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef LEXER_H
#define LEXER_H

#include "token.h"
typedef struct lexer_t {
  int col;
  int line;
  int length;
  char* filename;
  char* data;
  int cursor;
} lexer_t;

lexer_t new_lexer(char* filename);
token_array_t lex_program(lexer_t* l);
#endif  // LEXER_H