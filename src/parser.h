/*****************************************************
 * ROCKER PARSER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "token.h"

typedef struct parser_t {
  token_array_t tokens;
  ast_t prog;
  int cursor;
} parser_t;

parser_t new_parser(void);
token_type_t peek_type(parser_t p);
token_t peek_token(parser_t p);
void parse_program(parser_t *p);
token_t consume_token(parser_t *p);
ast_t parse_expression(parser_t *p);
#endif // PARSER_H