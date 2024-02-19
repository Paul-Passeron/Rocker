#include "parser.h"
#include "ast.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>

token_type_t peek_type(parser_t p) { return p.tokens.data[p.cursor].type; }

token_t peek_token(parser_t p) { return p.tokens.data[p.cursor]; }

token_t consume_token(parser_t *p) {
  if (p->cursor <= 0)
    return (token_t){0};
  return p->tokens.data[p->cursor++];
}

parser_t new_parser(void) {
  parser_t res;
  res.cursor = 0;
  res.prog = NULL;
  res.tokens = new_token_array();
  return res;
}

void expect(token_type_t a, token_type_t b) {
  if (a != b) {
    printf("Expected %s but got: %s\n", lexeme_of_type(a), lexeme_of_type(b));
  }
}

ast_t parse_expression(parser_t *p) {
  (void)p;
  return NULL;
}

void parse_program(parser_t *p) { (void)p; }

ast_t parse_tuple(parser_t *p) {
  (void)p;
  return NULL;
}

ast_t parse_ret(parser_t *p) {
  expect(peek_type(*p), TOK_RETURN);
  consume_token(p);
  ast_t expr = parse_expression(p);
  return new_ast((node_t){ret, {.ret = {expr}}});
}

ast_t parse_literal(parser_t *p) {
  return new_ast((node_t){literal, {.literal = {.lit = consume_token(p)}}});
}

ast_t parse_sub(parser_t *p) {
  token_array_t path = new_token_array();
  token_array_push(&path, consume_token(p));
  while (peek_type(*p) == TOK_SUB) {
    consume_token(p);
    token_array_push(&path, consume_token(p));
  }
  ast_t expr = NULL;
  if (peek_type(*p) == TOK_OPEN_PAREN) {
    consume_token(p);
    expr = parse_tuple(p);
    expect(peek_type(*p), TOK_CLOSE_PAREN);
  }
  return new_ast((node_t){sub, {.sub = {.expr = expr, .path = path}}});
}
