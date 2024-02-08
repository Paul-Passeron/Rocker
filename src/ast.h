/*****************************************************
 * ROCKER AST HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef AST_H
#define AST_H

#include "token.h"

typedef struct node_t node_t;
typedef node_t *ast_t;

typedef struct ast_array_t
{
    ast_t *data;
    int length;
    int capacity;
} ast_array_t;

typedef struct node_t
{
    enum
    {
        ast_type,
        ast_identifier,
        ast_let_binding,
    } tag;
    union
    {
        struct ast_type
        {
            token_array_t chain;
        } ast_type;

        struct ast_identifier
        {
            token_t id;
        } ast_identifier;

        struct ast_let_binding
        {
            ast_t left;
            ast_t right;
        } ast_let_binding;

    } data;
} node_t;

ast_t new_ast(node_t n);
void free_ast(ast_t a);

#endif // AST_H