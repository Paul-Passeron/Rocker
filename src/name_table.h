/*****************************************************
 * ROCKER NAME_TABLE HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef NAME_TABLE_H
#define NAME_TABLE_H

#include "ast.h"

#define INIT_NT_ARR 64

typedef struct table_elem_t
{
    char *name;
    int arity;
    ast_t type_sig;
} table_elem_t;

typedef struct name_table_t
{
    table_elem_t *data;
    int length;
    int capacity;
} name_table_t;

#endif // NAME_TABLE_H