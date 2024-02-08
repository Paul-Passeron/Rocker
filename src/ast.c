#include "ast.h"
#include <stdlib.h>
#include <stdio.h>

ast_t new_ast(node_t n)
{
    ast_t ptr = malloc(sizeof(node_t));
    if (ptr == NULL)
    {
        printf("Could not allocate memory\n");
        exit(1);
    }
    *ptr = n;
    return ptr;
}

void free_ast(ast_t a)
{
    if (a == NULL)
        return;
}

ast_t new_op_ast(ast_t left, token_type_t op, ast_t right)
{
    return new_ast((node_t){
        ast_operation, {.ast_operation = {
                            .op = op,
                            .left = left,
                            .right = right,
                        }}});
}

void ast_array_push(ast_array_t *arr, ast_t a)
{
    if (arr->length >= arr->capacity)
    {
        arr->capacity *= 2;
        arr->data = realloc(arr->data, arr->capacity * sizeof(ast_t));
    }
    arr->data[arr->length++] = a;
}

void new_ast_array(ast_array_t *arr)
{
    arr->capacity = INIT_AST_ARR;
    arr->length = 0;
    arr->data = malloc(sizeof(ast_t) * arr->capacity);
}

void kill_ast_array(ast_array_t arr)
{
    // TODO
    (void)arr;
}

void print_n_tabs(int n)
{
    for (int i = 0; i < n; i++)
        printf("\t");
}

void ast_print_aux(ast_t a, int d)
{
    print_n_tabs(d);
    if (a == NULL)
        return;
    switch (a->tag)
    {
    case ast_type:
    {
        printf("Type: ");
        struct ast_type data = a->data.ast_type;
        for (int i = 0; i < data.chain.length; i++)
        {
            printf("%s", data.chain.data[i].lexeme);
            if (i != data.chain.length - 1)
                printf(" -> ");
        }
    }
    break;
    case ast_identifier:
    {
        struct ast_identifier data = a->data.ast_identifier;
        printf("Identifier: %s", data.id.lexeme);
    }
    break;
    case ast_let_binding:
    {
        struct ast_let_binding data = a->data.ast_let_binding;
        printf("Let binding:\n");
        ast_print_aux(data.type_sig, d + 1);
        print_n_tabs(d + 1);
        printf("LEFT:\n");
        ast_print_aux(data.left, d + 2);
        print_n_tabs(d + 1);
        printf("RIGHT:\n");
        ast_print_aux(data.right, d + 2);
    }
    break;
    case ast_literal:
    {
        struct ast_literal data = a->data.ast_literal;
        printf("Literal: %s", data.literal.lexeme);
    }
    break;
    case ast_operation:
    {
        struct ast_operation data = a->data.ast_operation;
        printf("Operation: %s\n", lexeme_of_type(data.op));
        print_n_tabs(d + 1);
        printf("LEFT:\n");
        ast_print_aux(data.left, d + 2);
        print_n_tabs(d + 1);
        printf("RIGHT:\n");
        ast_print_aux(data.right, d + 2);
    }
    break;
    }
    printf("\n");
}

void ast_print(ast_t a)
{
    ast_print_aux(a, 0);
}