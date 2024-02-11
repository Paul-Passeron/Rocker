/*****************************************************
 * ROCKER AST HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef AST_H
#define AST_H

#include "token.h"

#define INIT_AST_ARR 64

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
        ast_literal,
        ast_operation,
        ast_curry,
        ast_in,
        ast_match,
        ast_match_case,
        ast_type_def,
        ast_constructor,
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
            int is_void;
            token_t name;
            token_array_t args;
            ast_t type_sig;
            ast_t right;
        } ast_let_binding;

        struct ast_literal
        {
            token_t literal;
        } ast_literal;

        struct ast_operation
        {
            token_type_t op;
            ast_t left;
            ast_t right;
        } ast_operation;

        struct ast_curry
        {
            ast_t caller;
            ast_t arg;
        } ast_curry;
        struct ast_in
        {
            ast_t first;
            ast_t second;
        } ast_in;

        struct ast_match
        {
            ast_t to_match;
            ast_array_t cases;
        } ast_match;

        struct ast_match_case
        {
            ast_t matcher;
            ast_t expression;
        } ast_match_case;

        struct ast_type_def
        {
            int is_rec;
            token_t name;
            ast_array_t constructors;
        } ast_type_def;

        struct ast_constructor
        {
            token_t name;
            ast_t signature;
        } ast_constructor;

    } data;
} node_t;

ast_t new_ast(node_t n);
void free_ast(ast_t a);

void new_ast_array(ast_array_t *arr);
void kill_ast_array(ast_array_t arr);
void ast_array_push(ast_array_t *arr, ast_t a);

ast_t new_op_ast(ast_t left, token_type_t op, ast_t right);

void ast_print(ast_t a);

#endif // AST_H