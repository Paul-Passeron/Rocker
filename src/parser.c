#include "parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"
#include "token.h"

token_type_t peek_type(parser_t p) {
  return p.tokens.data[p.cursor].type;
}

token_t peek_token(parser_t p) {
  return p.tokens.data[p.cursor];
}

token_t consume_token(parser_t* p) {
  if (p->cursor < 0)
    return (token_t){0};
  return p->tokens.data[p->cursor++];
}

parser_t new_parser(token_array_t tokens) {
  parser_t res;
  res.cursor = 0;
  res.prog = NULL;
  res.tokens = tokens;
  return res;
}

void expect(token_type_t a, token_type_t b) {
  if (a != b) {
    printf("Expected %s but got: %s\n", lexeme_of_type(b), lexeme_of_type(a));
    exit(1);
  }
}

ast_t parse_expression(parser_t* p);
ast_t parse_type(parser_t* p);
ast_t parse_fundef(parser_t* p);
ast_t parse_var_def(parser_t* p);
ast_t parse_match(parser_t* p);

ast_t parse_tuple(parser_t* p) {
  (void)p;
  assert(0 && "TODO: not implemented yet !\n");
}

ast_t parse_ret(parser_t* p) {
  expect(peek_type(*p), TOK_RETURN);
  consume_token(p);
  ast_t expr = parse_expression(p);
  expect(peek_type(*p), TOK_SEMICOL);
  consume_token(p);
  return new_ast((node_t){ret, {.ret = {expr}}});
}

ast_t parse_literal(parser_t* p) {
  return new_ast((node_t){literal, {.literal = {.lit = consume_token(p)}}});
}

ast_t parse_sub(parser_t* p) {
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

ast_t parse_statement(parser_t* p) {
  token_type_t a = peek_type(*p);
  if (a == TOK_LET) {
    parser_t p2 = *p;
    consume_token(&p2);
    consume_token(&p2);
    if (peek_type(p2) == TOK_OPEN_PAREN)  // function def
      return parse_fundef(p);
    else  // var def
    {
      ast_t vdef = parse_var_def(p);
      return vdef;
    }
  } else if (a == TOK_RETURN) {
    return parse_ret(p);
  } else if (a == TOK_MATCH)
    return parse_match(p);
  ast_t expr = parse_expression(p);
  expect(peek_type(*p), TOK_SEMICOL);
  consume_token(p);
  return expr;
}

ast_t parse_matchcase(parser_t* p) {
  ast_t expr = parse_expression(p);
  expect(peek_type(*p), TOK_SMALL_ARROW);
  ast_t stmt = parse_statement(p);
  return new_ast(
      (node_t){matchcase, {.matchcase = {.body = stmt, .expr = expr}}});
}

ast_t parse_match(parser_t* p) {
  expect(peek_type(*p), TOK_MATCH);
  consume_token(p);
  ast_t to_match = parse_expression(p);
  expect(peek_type(*p), TOK_BIG_ARROW);
  consume_token(p);
  expect(peek_type(*p), TOK_OPEN_BRACE);
  consume_token(p);
  ast_array_t cases = new_ast_array();
  while (peek_type(*p) == TOK_SMALL_ARROW) {
    consume_token(p);
    push_ast_array(&cases, parse_matchcase(p));
  }
  expect(peek_type(*p), TOK_CLOSE_BRACE);
  consume_token(p);
  return new_ast(
      (node_t){match, {.match = {.cases = cases, .expr = to_match}}});
}

ast_t parse_var_def(parser_t* p) {
  expect(peek_type(*p), TOK_LET);
  consume_token(p);
  token_t id = consume_token(p);

  expect(peek_type(*p), TOK_COLON);
  consume_token(p);

  ast_t type = parse_type(p);

  expect(peek_type(*p), TOK_BIG_ARROW);
  consume_token(p);

  ast_t expr = parse_statement(p);

  // expect(peek_type(*p), TOK_SEMICOL);
  // consume_token(p);

  return new_ast(
      (node_t){vardef, {.vardef = {.expr = expr, .name = id, .type = type}}});
}

ast_t parse_type(parser_t* p) {
  token_array_t tuple = new_token_array();
  while (peek_type(*p) == TOK_IDENTIFIER) {
    token_array_push(&tuple, consume_token(p));
    if (peek_type(*p) == TOK_STAR)
      consume_token(p);
    else
      break;
  }
  return new_ast((node_t){tupledef, {.tupledef = {.signature = tuple}}});
}
ast_t parse_compound(parser_t* p) {
  expect(peek_type(*p), TOK_OPEN_BRACE);
  consume_token(p);
  ast_array_t stmts = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_BRACE)
    push_ast_array(&stmts, parse_statement(p));
  expect(peek_type(*p), TOK_CLOSE_BRACE);
  consume_token(p);
  return new_ast((node_t){compound, {.compound = {stmts}}});
}

ast_t parse_fundef(parser_t* p) {
  expect(peek_type(*p), TOK_LET);
  consume_token(p);
  token_t id = consume_token(p);
  expect(peek_type(*p), TOK_OPEN_PAREN);
  consume_token(p);
  token_array_t args = new_token_array();
  ast_array_t types = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_PAREN) {
    expect(peek_type(*p), TOK_IDENTIFIER);
    token_t arg = consume_token(p);
    token_array_push(&args, arg);

    expect(peek_type(*p), TOK_COLON);
    consume_token(p);
    ast_t type = parse_type(p);
    push_ast_array(&types, type);

    if (peek_type(*p) != TOK_COMMA)
      break;
    consume_token(p);
  }

  expect(peek_type(*p), TOK_CLOSE_PAREN);
  consume_token(p);

  expect(peek_type(*p), TOK_COLON);
  consume_token(p);

  ast_t type = parse_type(p);

  expect(peek_type(*p), TOK_BIG_ARROW);
  consume_token(p);

  ast_t body = parse_compound(p);
  return new_ast((node_t){fundef,
                          {.fundef = {.args = args,
                                      .body = body,
                                      .name = id,
                                      .types = types,
                                      .ret_type = type}}});
}

int is_primary(parser_t p) {
  token_type_t t = peek_type(p);
  return t == TOK_OPEN_BRACE || t == TOK_OPEN_PAREN || t == TOK_IDENTIFIER ||
         t == TOK_STR_LIT || t == TOK_CHR_LIT || t == TOK_NUM_LIT ||
         t == TOK_WILDCARD;
}

int is_funcall(parser_t p) {
  return consume_token(&p).type == TOK_IDENTIFIER &&
         peek_type(p) == TOK_OPEN_PAREN;
}

ast_t parse_funcall(parser_t* p) {
  token_t id = consume_token(p);
  expect(peek_type(*p), TOK_OPEN_PAREN);
  consume_token(p);
  ast_array_t args = new_ast_array();
  while (peek_type(*p) != TOK_CLOSE_PAREN) {
    push_ast_array(&args, parse_expression(p));
    if (peek_type(*p) != TOK_COMMA)
      break;
    consume_token(p);
  }
  expect(peek_type(*p), TOK_CLOSE_PAREN);
  consume_token(p);
  return new_ast((node_t){funcall, {.funcall = {id, args}}});
}

ast_t parse_leaf(parser_t* p) {
  token_t t = consume_token(p);
  if (is_funcall(*p))
    return parse_funcall(p);
  if (t.type == TOK_IDENTIFIER)
    return new_ast((node_t){identifier, {.identifier = {t}}});
  else if (t.type == TOK_NUM_LIT || t.type == TOK_STR_LIT ||
           t.type == TOK_CHR_LIT || t.type == TOK_WILDCARD)
    return new_ast((node_t){literal, {.literal = {t}}});
  printf("Expected leaf\n");
  exit(1);
  return NULL;  // For TCC
}

ast_t parse_primary(parser_t* p) {
  token_type_t type = peek_type(*p);
  if (is_funcall(*p)) {
    return parse_funcall(p);
  } else if (type == TOK_STR_LIT || type == TOK_CHR_LIT ||
             type == TOK_NUM_LIT || type == TOK_WILDCARD ||
             type == TOK_IDENTIFIER) {
    return parse_leaf(p);
  } else if (type == TOK_OPEN_PAREN) {
    (void)consume_token(p);
    ast_t res = parse_expression(p);
    type = peek_type(*p);
    if (type != TOK_CLOSE_PAREN) {
      printf("%s\n", peek_token(*p).lexeme);
      printf("TODO : Better error reporting\n");
      printf("Unclosed parenthesis !\n");
      exit(1);
    }
    (void)consume_token(p);
    return res;
  } else if (type == TOK_OPEN_BRACE) {
    return parse_compound(p);
  } else {
    printf("Pb : %s\n", lexeme_of_type(type));
    printf("Could not parse as a primary !\n");
    exit(1);
  }
  return NULL;  // For TCC
}

ast_t parse_increasing_precedence(parser_t* p, ast_t left, int min_prec);

ast_t parse_expression_aux(parser_t* p, int min_precedence);

ast_t parse_expression(parser_t* p) {
  token_type_t a = peek_type(*p);
  if (a == TOK_OPEN_PAREN) {
    consume_token(p);
    ast_t res = parse_expression(p);
    expect(peek_type(*p), TOK_CLOSE_PAREN);
    consume_token(p);
    while (peek_type(*p) != TOK_CLOSE_PAREN) {  // a bit weird
      ast_t node = parse_increasing_precedence(p, res, -1);
      if (node == res)
        break;
      res = node;
    }
    consume_token(p);
    return res;
  }
  return parse_expression_aux(p, -1);  // for TCC
}

ast_t parse_expression_aux(parser_t* p, int min_precedence) {
  ast_t left = parse_primary(p);
  while (1) {
    ast_t node = parse_increasing_precedence(p, left, min_precedence);
    if (node == left)
      break;
    left = node;
  }
  return left;
}

ast_t parse_increasing_precedence(parser_t* p, ast_t left, int min_prec) {
  token_t next = peek_token(*p);
  if (!is_type_operator(next.type))
    return left;
  int next_prec = get_precedence(next.type);
  if (next_prec < min_prec)
    return left;
  (void)consume_token(p);
  ast_t right = parse_expression_aux(p, next_prec);
  return new_ast((node_t){op, {.op = {next.type, left, right}}});
}

void parse_program(parser_t* p) {
  ast_array_t prog = new_ast_array();
  while (p->cursor < p->tokens.length)
    push_ast_array(&prog, parse_statement(p));
  p->prog = new_ast((node_t){program, {.program = {prog}}});
}