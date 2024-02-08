/*****************************************************
 * ROCKER PARSER HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "ast.h"

typedef struct parser_t
{
    char *filename;
    token_array_t tokens;
    int cursor;
    ast_array_t prog;
} parser_t;

parser_t new_parser(token_array_t arr, char *filename);
token_t parser_peek(parser_t p);
token_t parser_consume(parser_t *p);
void parser_consume_n(parser_t *p, int n);

ast_t parse_primary(parser_t *p);
ast_t parse_expression(parser_t *p);

ast_t parse_increasing_precedence(parser_t *p, ast_t left, int min_prec);
ast_t parse_expression_aux(parser_t *p, int min_precedence);
void parse_program(parser_t *p);

#endif // PARSER_H