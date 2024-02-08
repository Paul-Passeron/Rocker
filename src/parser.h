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

#endif // PARSER_H