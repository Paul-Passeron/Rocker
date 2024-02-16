/*****************************************************
 * ROCKER AST HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef AST_H
#define AST_H

#include "token.h"


typedef struct ast_t ast_t;
typedef struct ast_op ast_op;

struct ast_op {
  ast_t left;
  ast_t right;
}


#endif  // AST_H