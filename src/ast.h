/*****************************************************
 * ROCKER AST HEADER
 * MIT License
 * Copyright (c) 2024 Paul Passeron
 *****************************************************/

#ifndef AST_H
#define AST_H

#include "token.h"

typedef struct node_t node_t;
typedef node_t* ast_t;

typedef struct ast_array_t {
  ast_t* data;
  int length;
  int capacity;
} ast_array_t;

#define INIT_AST_ARR 8

typedef struct ast_op ast_op;
typedef struct ast_literal ast_literal;
typedef struct ast_identifier ast_identifier;
typedef struct ast_fundef ast_fundef;
typedef struct ast_funcall ast_funcall;
typedef struct ast_ret ast_ret;
typedef struct ast_vardef ast_vardef;
typedef struct ast_match ast_match;
typedef struct ast_matchcase ast_matchcase;
typedef struct ast_sub ast_sub;
typedef struct ast_tuple ast_tuple;
typedef struct ast_tupledef ast_tupledef;
typedef struct ast_program ast_program;
typedef struct ast_compound ast_compound;

struct ast_op {
  token_type_t op;
  ast_t left;
  ast_t right;
};

struct ast_literal {
  token_t lit;
};

struct ast_identifier {
  token_t id;
};

struct ast_fundef {
  token_t name;
  token_array_t args;
  ast_array_t types;
  ast_t body;
  ast_t ret_type;
};

struct ast_funcall {
  token_t name;
  ast_array_t args;
};

struct ast_ret {
  ast_t expr;
};

struct ast_vardef {
  token_t name;
  ast_t expr;
  ast_t type;
};

struct ast_match {
  ast_t expr;
  ast_array_t cases;
};

struct ast_matchcase {
  ast_t expr;
  ast_t body;
};

struct ast_sub {
  token_array_t path;
  ast_t expr;
};

struct ast_tuple {
  ast_array_t elems;
};

struct ast_tupledef {
  token_array_t signature;
};

struct ast_program {
  ast_array_t prog;
};

struct ast_compound {
  ast_array_t stmts;
};

struct node_t {
  enum tag {
    op,
    literal,
    identifier,
    fundef,
    funcall,
    ret,
    vardef,
    match,
    matchcase,
    sub,
    tuple,
    tupledef,
    program,
    compound,
  } tag;
  union data {
    ast_op op;
    ast_literal literal;
    ast_identifier identifier;
    ast_fundef fundef;
    ast_funcall funcall;
    ast_ret ret;
    ast_vardef vardef;
    ast_match match;
    ast_matchcase matchcase;
    ast_sub sub;
    ast_tuple tuple;
    ast_tupledef tupledef;
    ast_compound compound;
    ast_program program;
  } data;
};

ast_t new_ast(node_t node);
ast_array_t new_ast_array(void);

void push_ast_array(ast_array_t* arr, ast_t a);
void print_ast(ast_t root);
#endif  // AST_H