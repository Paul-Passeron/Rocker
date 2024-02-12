/*****************************************************
 * ROCKER LEXER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef LEXER_H
#define LEXER_H

#include "token.h"

/*****************************************************
 * Primary Lexer structure
 * Will go through the file to create
 * the token array
 *****************************************************/

typedef struct lexer {
  char* data;
  int cursor;
  int length;
  int col;
  int line;
  char* filename;
} lexer_t;

lexer_t new_lexer(char* filename);
void kill_lexer(lexer_t l);
char lexer_peek(lexer_t l);
token_t step_lexer(lexer_t* l);
token_array_t lex_program(lexer_t* l);

#endif  // LEXER_H