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

typedef struct ast_array_t {
  ast_t *data;
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
typedef struct ast_ifstmt ast_ifstmt;
typedef struct ast_tdef ast_tdef;
typedef struct ast_cons ast_cons;
typedef struct ast_record_expr ast_record_expr;
typedef struct ast_loop ast_loop;
typedef struct ast_assign ast_assign;
typedef struct ast_while_loop ast_while_loop;
typedef struct ast_while_loop ast_while_loop;
typedef struct ast_enum_tdef ast_enum_tdef;

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
  int is_rec;
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

struct ast_ifstmt {
  ast_t expression;
  ast_t body;
  ast_t elsestmt;
};

typedef enum tdef_type_t {
  TDEF_REC,
  TDEF_PRO,
} tdef_type_t;

struct ast_tdef {
  token_t name;
  tdef_type_t t;
  ast_array_t constructors;
};

struct ast_cons {
  token_t name;
  ast_t type;
};

struct ast_record_expr {
  token_array_t names;
  ast_array_t exprs;
};

struct ast_loop {
  token_t variable;
  ast_t start;
  ast_t end;
  ast_t statement;
};

struct ast_assign {
  ast_t target;
  ast_t expr;
};

struct ast_while_loop {
  ast_t condition;
  ast_t statement;
};

struct ast_enum_tdef {
  token_t name;
  token_array_t items;
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
    ifstmt,
    tdef,
    cons,
    record_expr,
    loop,
    assign,
    while_loop,
    enum_tdef,
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
    ast_ifstmt ifstmt;
    ast_tdef tdef;
    ast_cons cons;
    ast_record_expr record_expr;
    ast_loop loop;
    ast_assign assign;
    ast_while_loop while_loop;
    ast_enum_tdef enum_tdef;
  } data;
};

ast_t new_ast(node_t node);
ast_array_t new_ast_array(void);

void push_ast_array(ast_array_t *arr, ast_t a);
void print_ast(ast_t root);
#endif // AST_H
