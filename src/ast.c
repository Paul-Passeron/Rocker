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